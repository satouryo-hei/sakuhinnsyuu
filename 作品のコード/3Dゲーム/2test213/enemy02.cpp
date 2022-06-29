//=============================================================================
//
// �G�̏��� [player2.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include"enemy02.h"
#include"renderer.h"
#include"manager.h"
#include"input.h"
#include"model.h"
#include"shadow.h"
#include"title.h"
#include"bullet.h"
#include"game.h"
#include"player.h"
#include"score.h"
#include"choose_game.h"
#include"tutorial.h"
#include"explosion.h"

//=============================================================================
// �ÓI�����o�ϐ��̐錾
//=============================================================================
CShadow* CEnemy2::m_pShadow = NULL;
CModel * CEnemy2::m_pModel[20] = {};
bool CEnemy2::m_bUse = true;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEnemy2::CEnemy2(PRIORITY Priority) :CEnemy(PRIORITY_ENEMY)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fRadius = 10.0f;
	m_fFlame = 5.0f;
	m_nNumKey = 0;	
}


//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEnemy2::~CEnemy2()
{

}

//=============================================================================
// �G�̐�������
//=============================================================================
CEnemy2 *CEnemy2::Create(D3DXVECTOR3 pos, const char *pFileName)
{
	// �G�̃|�C���^�[����
	CEnemy2* pEnemy2 = NULL;

	// ���I�������̊m��
	pEnemy2 = new CEnemy2;

	// NULL�`�F�b�N
	if (pEnemy2 != NULL)
	{
		// �����������̌Ăяo��
		pEnemy2->Init(pos, pFileName);		
	}
	return pEnemy2;
}

	//=============================================================================
	// �G�̃��[�h�֐����I�[�o�[���[�h��������������
	//=============================================================================
HRESULT CEnemy2::Init(D3DXVECTOR3 pos, const char *pFileName)
{
	// �G�̏������������Ăяo��
	CEnemy::Init(pos, pFileName);
	// �e�̐��������́@
	m_pShadow = CShadow::Create(D3DXVECTOR3(0,0,0), D3DXVECTOR3(20,0,20),D3DXVECTOR3(0,0,0));

	return S_OK;
}



//=============================================================================
// �G�̏I������
//=============================================================================
void CEnemy2::Uninit(void)
{
	// �g���Ȃ�����
	m_bUse = false;

	// NULL�`�F�b�N
	if (m_pShadow != NULL)
	{// �e�̏I���������Ăяo��
		m_pShadow->Uninit();
		m_pShadow = NULL;
	}

	// �G�̏I���������Ăяo��
	CEnemy::Uninit();

	// �������
	Release();

}// �G�̏I�������I��


 //=============================================================================
 // �G�̍X�V����
 //=============================================================================
void CEnemy2::Update(void)
{
	D3DXVECTOR3 size = CEnemy::GetSize();

	CPlayer * pPlayer = NULL;
	int nAttack = 0;
	CScore * pScore = NULL;

	// �Q�[�����������ǂ���
	if (CChoose_Game::GetGame())
	{
		// �v���C���[���Q�[������擾
		pPlayer = CGame::GetPlayer();

		// �v���C���[�̍U���͂��擾
		nAttack = pPlayer->GetAttack();

		// �Q�[�����猻�݂̃X�R�A�󋵂��擾
		pScore = CGame::GetScore();
	}
	else 	// �Q�[�������ĂȂ��Ƃ�
	{// �v���C���[��ʂŐ�������̂̓`���[�g���A�������Ȃ̂�
		// �`���[�g���A���ł̃v���C���[���擾
		pPlayer = CTutorial::GetPlayer();

		// �v���C���[�̍U���͂��擾
		nAttack = pPlayer->GetAttack();
	}

	//=============================================================================
	// ���@�̒e�ƓG�̓����蔻��
	//=============================================================================
	for (int nPriority = 0; nPriority < PRIORITY_MAX; nPriority++)
	{
		// �I�u�W�F�N�g�̃|�C���^�[����
		CScene * pScene = NULL;

		// ���݂̃I�u�W�F�N�g�̎擾
		pScene = CScene::GetScene(nPriority);

		// NULL�`�F�b�N
		if (pScene != NULL)
		{
			// ���݂̃I�u�W�F�N�g���e�������ꍇ
			if (nPriority == CScene::PRIORITY_BULLET)
			{				
				// ���݂̃I�u�W�F�N�g�̎�ނ�e�̃|�C���^�[�����������̂ɒe�̃|�C���^�[�ŃL���X�g���đ��
				CBullet *pBullet = (CBullet*)pScene;

				if (m_pos.x/* + (size.x / 2)*/ + 10 >= pBullet->GetPos().x - pBullet->GetSize().x&&
					m_pos.x/* - (size.x / 2)*/ - 10 <= pBullet->GetPos().x + pBullet->GetSize().x&&
					m_pos.y/* + (size.y / 2)*/ + 50 >= pBullet->GetPos().y - pBullet->GetSize().y&&
					m_pos.y/* + (size.y / 2)*/ + 50 <= pBullet->GetPos().y + pBullet->GetSize().y&&
					m_pos.z/* - (size.z / 2)*/ - 10 <= pBullet->GetPos().z
					)
				{
					// �e���g��Ȃ�����
					pBullet->SetUse(false);

					// �Q�[�����������ǂ������擾
					if (CChoose_Game::GetGame())
					{// ���Ă����
						// �X�R�A�����Z����
						pScore->AddScore(100);
						// �v���C���[�̍U���͂����Z������
						pPlayer->SetAttack(nAttack + 10);

						CExplosion::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 50, m_pos.z), D3DXVECTOR2(50,50));
					}
					// �I�������̌Ăяo��
					Uninit();
					return;
				}
			}
		}
	}
	
	// �v���C���[�̌��݂̈ʒu���擾
	D3DXVECTOR3 Playerpos = pPlayer->GetPos();

	// �v���C���[�ƓG�̎Εӂ̋����𑪂�A����i�O�������(c2�� = a2��+b2��)�j
	m_fRange = sqrtf(powf((Playerpos.x - m_pos.x), 2.0f) + powf((Playerpos.z - m_pos.z), 2.0f));

	// ���݂̈ʒu+�~�̖ʐς��v���C���[�ƓG�̎Εӂ̋������~�̖ʐψȏ�(�E�̏ꍇ)or�ȉ��i���̏ꍇ�j�ɓ����Ă�����
	if (m_pos.x + (m_fRadius*powf(D3DX_PI, 2)) >= m_fRange &&
		m_pos.x - (m_fRadius*powf(D3DX_PI, 2)) <= m_fRange &&
		m_pos.z + (m_fRadius*powf(D3DX_PI, 2)) >= m_fRange &&
		m_pos.z - (m_fRadius*powf(D3DX_PI, 2)) <= m_fRange)
	{
		// �v���C���[�ƓG�̎Εӂ̋����������Ă��邩�̊m�F
		if (m_fRange != NULL)
		{// �����Ă�����
			// �ړ��� = ((�v���C���[�̌��݂̈ʒu - �G�̌��݂̈ʒu)/�Ε�)/�t���[����
			m_Move.x = ((Playerpos.x - m_pos.x) / m_fRange) / m_fFlame;
			m_Move.z = ((Playerpos.z - m_pos.z) / m_fRange) / m_fFlame;
		}
	}
	// �͈͊O�̏ꍇ
	else
	{
		m_Move.x = 0;
		m_Move.z = 0;
	}

	// ���݂̈ʒu�Ɉړ��ʂ����Z������
	m_pos += m_Move;

	// ���݂̈ʒu�̍X�V
	SetPos(m_pos);

	// �e�̌��݂̈ʒu���X�V
	m_pShadow->SetPosition(m_pos);

	// �p�����̍X�V�������Ăяo��
	CEnemy::Update();


}// �|���S���̍X�V�����I��



 //=============================================================================
 // �G�̕`�揈��
 //=============================================================================
void CEnemy2::Draw(void)
{
	// �p�����̕`�揈�����Ăяo��
	CEnemy::Draw();

}// �G�̕`�揈���I��