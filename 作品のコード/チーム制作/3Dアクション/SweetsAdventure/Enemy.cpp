#include "main.h"
#include "Enemy.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "layer_structure.h"
#include "game.h"
#include "player.h"
#include "collision.h"
#include "stage.h"
#include "gauge.h"
#include "fair_Effect.h"
#include "sound.h"

CEnemy::CEnemy(OBJTYPE nPriority) : CScene(nPriority)
{

}

CEnemy::~CEnemy()
{

}

CEnemy *CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CEnemy *pPlayer = NULL;
	pPlayer = new CEnemy;
	pPlayer->m_pos = pos;
	pPlayer->m_rot = rot;
	pPlayer->Init();
	return pPlayer;
}

HRESULT CEnemy::Init()
{
	m_fWalkSoundInterval = 0.0f;
	m_fSoundInterval = 0.0f;
	m_nLife = ENEMY_LIFE;
	m_bDamage = false;
	//�t�@�C���ǂݍ���
	CLayer_Structure *pLayer = NULL;
	pLayer = new CLayer_Structure;
	pLayer->SetLayer_Structure("data/TEXT/EnemyParts000.txt", &m_pModel[0]);
	if (m_pMotion == NULL)
	{
		m_pMotion = new CMotion;
		m_MotionType = 0;
		m_pMotion->MotionLoad("data/TEXT/cookie_motion.txt");

	}


	return S_OK;
}

void CEnemy::Uninit()
{
	CGauge *pGauge = CManager::GetGame()->GetGauge();
	
	// �Q�[�W���炷
	if (pGauge != NULL)
	{
		pGauge->SetGauge(-10.0f);
	}

	// ���f���j��
	for (int nCntParts = 0; nCntParts < MAX_ENEMY_PARTS; nCntParts++)
	{
		if (m_pModel[nCntParts] != NULL)
		{
			m_pModel[nCntParts]->Uninit();
			m_pModel[nCntParts] = NULL;
		}
	}

	Release();
}

void CEnemy::Update()
{

	m_lastPos = m_pos;
	D3DXVECTOR3	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pos = CManager::GetGame()->GetPlayer()->GetPos();				//�ʒu
	D3DXVECTOR3 BulletVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	BulletVec = pos - m_pos;			//�G�ƒe�̃x�N�g��
	float fLength = 0.0f;
	float fLengthX = 0.0f;
	fLength = sqrtf((BulletVec.z*BulletVec.z)+ (BulletVec.x*BulletVec.x));
	m_fAng = atan2(BulletVec.x, BulletVec.z);//�G�̌���
	//�G�̏o��
	if (fLength < MAX_DRAWRADIUS)
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
		m_rot.y = m_fAng+ (D3DX_PI);
		//���˂�����������߂�
		m_MoveSpeed.x = sinf(m_fAng)*MAX_SPEED;
		m_MoveSpeed.z = cosf(m_fAng)*MAX_SPEED;
		m_MotionType = MOVE;

		m_fWalkSoundInterval -= 0.1f;

		if (m_fWalkSoundInterval <= 0.0f)
		{
			CManager::GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_WALK2);
			m_fWalkSoundInterval = 2.0f;
		}
	}
	//�͈͊O�̎�
	else
	{
		m_MotionType = NEUTRAL;
		m_MoveSpeed.x = 0.0f;
		m_MoveSpeed.y = 0.0f;
		m_MoveSpeed.z = 0.0f;
	}
	//�G�̗U�f
	if (fLength < MAX_TEMPTATION_RADIUS)
	{
		CGauge *pGauge = CManager::GetGame()->GetGauge();

		//�U�f�Q�[�W�𑝂₷
		pGauge->SetGauge(ENEMY_ADD_SPEED);

		m_fSoundInterval -= 0.1f;

		if (m_fSoundInterval <= 0.0f)
		{
			CManager::GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_DAMAGE);

			m_fSoundInterval = 6.0f;
		}
	}

	m_pos += m_MoveSpeed;

	//�G�̍s���p�^�[�������\��
	//if (m_bUninit == true)
	//{
	//	Uninit();
	//}
	if (m_bDraw == true)
	{
		CCollision *pCollision = new CCollision;

		CScene *pEnemy = CScene::GetScene(OBJTYPE_ENEMY);

		//�_���[�W���󂯂��疳�G��Ԃɂ���
		if (m_bDamage == true)
		{
			if (m_bEffect == false)
			{
				m_bEffect = true;
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

		while (pEnemy!=NULL)
		{
			if (pEnemy != NULL && pEnemy == this)
			{
				pCollision->CollisionObjectEnemy((CEnemy*)pEnemy, &m_pos, &m_lastPos, 50.0f);
			}
			pEnemy = pEnemy->GetSceneNext(pEnemy);
		}

		CScene *pEnemyBaum = CScene::GetScene(OBJTYPE_ENEMY_BAUM);
		while (pEnemyBaum!=NULL)
		{
			if (pEnemyBaum != NULL)
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
		//���[�V�����Đ�
		if (m_pMotion != NULL)
		{
			m_pMotion->PlayMotion(MAX_ENEMY_PARTS, &m_pModel[0], m_MotionType, m_MotionLastType, m_bMotionStop, m_bAttack, m_bNeutral);
		}
		delete pCollision;
	}
}

void CEnemy::Draw()
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
		for (int nCntParts = 0; nCntParts < MAX_ENEMY_PARTS; nCntParts++)
		{
			m_pModel[nCntParts]->Draw();
		}

	}
}
//----------------------------------------------------------
//�̗͂̑���
//----------------------------------------------------------
void CEnemy::AddLife(int nLife)
{
	m_nLife += nLife;
}

bool  CEnemy::bColision()
{
	return 0;
}