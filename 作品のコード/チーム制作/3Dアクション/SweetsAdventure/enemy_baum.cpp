#include "main.h"
#include "enemy_baum.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "layer_structure.h"
#include "game.h"
#include "player.h"
#include "collision.h"
#include "stage.h"
#include "Enemy.h"
#include "gauge.h"
#include "fair_Effect.h"
#include "sound.h"

CEnemy_Baum::CEnemy_Baum(OBJTYPE nPriority) : CScene(nPriority)
{

}

CEnemy_Baum::~CEnemy_Baum()
{

}

CEnemy_Baum *CEnemy_Baum::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CEnemy_Baum *pEnemy_Baum = NULL;
	pEnemy_Baum = new CEnemy_Baum(OBJTYPE_ENEMY_BAUM);
	pEnemy_Baum->m_pos = pos;
	pEnemy_Baum->m_rot = rot;
	pEnemy_Baum->Init();
	return pEnemy_Baum;
}

HRESULT CEnemy_Baum::Init()
{
	m_fSoundInterval = 0.0f;
	m_fWalkSoundInterval = 0.0f;
	m_nLife = BAUM_LIFE;
	//�t�@�C���ǂݍ���
	CLayer_Structure *pLayer = NULL;
	pLayer = new CLayer_Structure;
	pLayer->SetLayer_Structure("data/TEXT/EnemyParts001.txt", &m_pModel[0]);
	if (m_pMotion == NULL)
	{
		m_pMotion = new CMotion;
		m_MotionType = 0;
		m_pMotion->MotionLoad("data/TEXT/Baumkuchen_motion.txt");

	}

	return S_OK;
}

void CEnemy_Baum::Uninit()
{
	CGauge *pGauge = CManager::GetGame()->GetGauge();
	if (pGauge != NULL)
	{
		pGauge->SetGauge(-10.0f);
	}
	for (int nCntParts = 0; nCntParts < MAX_ENEMY_BAUM_PARTS; nCntParts++)
		if (m_pModel[nCntParts] != NULL)
		{
			m_pModel[nCntParts]->Uninit();
			m_pModel[nCntParts] = NULL;
		}
	Release();

}

void CEnemy_Baum::Update()
{
	m_lastPos = m_pos;
	D3DXVECTOR3	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pos = CManager::GetGame()->GetPlayer()->GetPos();				//�ʒu
	D3DXVECTOR3 BulletVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	BulletVec = pos - m_pos;			//�G�ƒe�̃x�N�g��
	float fLength = 0.0f;
	float fLengthX = 0.0f;
	fLength = sqrtf((BulletVec.z*BulletVec.z) + (BulletVec.x*BulletVec.x));
	m_fAng = atan2(BulletVec.x, BulletVec.z);//�G�̌���
	//�G�̏o��
	if (fLength < MAX_BAUM_DRAWRADIUS)
	{
		m_bDraw = true;
	}
	else
	{
		m_bDraw = false;
	}

	//�G�̒Ǐ]
	if (fLength < MAX_COLRADIUS)
	{
		m_rot.y = m_fAng + (D3DX_PI);
		//���˂�����������߂�
		m_MoveSpeed.x = sinf(m_fAng)*MAX_BAUM_SPEED;
		m_MoveSpeed.z = cosf(m_fAng)*MAX_BAUM_SPEED;

		m_fWalkSoundInterval -= 0.1f;

		if (m_fWalkSoundInterval <= 0.0f)
		{
			CManager::GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_WALK2);
			m_fWalkSoundInterval = 2.0f;
		}

	}
	else
	{
		m_MoveSpeed.x = 0.0f;
		m_MoveSpeed.y = 0.0f;
		m_MoveSpeed.z = 0.0f;
	}
	if (fLength < MAX_TEMPTATION_RADIUS)
	{
		//�U�f�Q�[�W�𑝂₷
		CGauge *pGauge = CManager::GetGame()->GetGauge();
		pGauge->SetGauge(BAUM_ADD_SPEED);

		m_fSoundInterval -= 0.1f;

		if (m_fSoundInterval <= 0.0f)
		{
			CManager::GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_DAMAGE);

			m_fSoundInterval = 6.0f;
		}

	}
	//�ʒu�Ɉړ��ʂ𑫂�
	m_pos += m_MoveSpeed;
	//�G�̍s���p�^�[�������\��
	//if (m_bUninit == true)
	//{
	//	Uninit();
	//}
	if (m_bDraw == true)
	{
		CCollision *pCollision = new CCollision;
		//�_���[�W���󂯂��疳�G��Ԃɂ���
		if (m_bDamage == true)
		{
			if (m_bEffect == false)
			{
				m_bEffect = true;
				Cfair_Effect::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 20.0f, m_pos.x), CTexture::Effect);
			}

			//�J�E���^�[�𑝂₷
			m_nTimer++;
			//�J�E���^�[������̎��Ԃɍs������
			if (m_nTimer >= INVINCIBLE_TIME)
			{
				//�ʏ��Ԃɖ߂�
				m_bDamage = false;
				m_bEffect = false;
			}
		}

		CScene *pEnemy = CScene::GetScene(OBJTYPE_ENEMY);
		while (pEnemy!=NULL)
		{
			if (pEnemy != NULL)
			{
				pCollision->CollisionObjectEnemy((CEnemy*)pEnemy, &m_pos, &m_lastPos, 50.0f);
			}
			pEnemy = pEnemy->GetSceneNext(pEnemy);
		}

		CScene *pEnemyBaum = CScene::GetScene(OBJTYPE_ENEMY_BAUM);
		while (pEnemyBaum!=NULL)
		{
			if (pEnemyBaum != NULL&&pEnemyBaum == this)
			{
				pCollision->CollisionObjectEnemy((CEnemy_Baum*)pEnemyBaum, &m_pos, &m_lastPos, 50.0f);
			}
			pEnemyBaum = pEnemyBaum->GetSceneNext(pEnemyBaum);
		}

		CPlayer *pPlayer = CManager::GetGame()->GetPlayer();
		if (pPlayer != NULL)
		{
			pCollision->CollisionObjectPlayer(pPlayer, &m_pos, &m_lastPos, 50.0f);
		}

		//�G�̍s���p�^�[�������\��
		//if (m_bUninit == true)
		//{
		//	Uninit();
		//}
		//���[�V�����Đ�
		if (m_pMotion != NULL)
		{
			m_pMotion->PlayMotion(MAX_ENEMY_BAUM_PARTS, &m_pModel[0], m_MotionType, m_MotionLastType, m_bMotionStop, m_bAttack, m_bNeutral);
		}

		delete pCollision;

	}
}

void CEnemy_Baum::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();//�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxRotModel, mtxTransModel;//�v�Z�p�}�g���b�N�X
										  //�e�p�[�c�̃��[���h�}�g���b�N�X�̏�����gtryg
	D3DXMatrixIdentity(&m_mtxWorld);
	D3DXMatrixRotationYawPitchRoll(&mtxRotModel, m_rot.y, m_rot.x, m_rot.z);
	//�����𔽉f
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRotModel);
	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTransModel, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTransModel);

	//�e�p�[�c�̃��[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	if (m_bDraw == true)
	{
		//���f���`��
		for (int nCntParts = 0; nCntParts < MAX_ENEMY_BAUM_PARTS; nCntParts++)
		{
			m_pModel[nCntParts]->Draw();
		}

	}
}
//----------------------------------------------------------
//�̗͂̑���
//----------------------------------------------------------
void CEnemy_Baum::AddLife(int nLife)
{
	m_nLife += nLife;
}
bool  CEnemy_Baum::bColision()
{
	return 0;
}