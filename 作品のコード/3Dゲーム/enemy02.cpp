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

//=============================================================================
// �ÓI�����o�ϐ��̐錾
//=============================================================================
CShadow* CEnemy2::m_pShadow = NULL;
CModel * CEnemy2::m_pModel[20] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEnemy2::CEnemy2(PRIORITY Priority) :CEnemy(Priority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fRadius = 10.0f;
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
	CEnemy2* pEnemy = NULL;

	// ���I�������̊m��
	pEnemy = new CEnemy2;

	// NULL�`�F�b�N
	if (pEnemy != NULL)
	{
		pEnemy->Init(pos, pFileName);
	}
	return pEnemy;
}

	//=============================================================================
	// �G�̃��[�h�֐����I�[�o�[���[�h��������������
	//=============================================================================
HRESULT CEnemy2::Init(D3DXVECTOR3 pos, const char *pFileName)
{
	// �p����̏������������Ăяo��
	CEnemy::Init(pos, pFileName);

	return S_OK;
}



//=============================================================================
// �G�̏I������
//=============================================================================
void CEnemy2::Uninit(void)
{
	// �p����̏I���������Ăяo��
	CEnemy::Uninit();
	Release();

}// �|���S���̏I�������I��


 //=============================================================================
 // �G�̍X�V����
 //=============================================================================
void CEnemy2::Update(void)
{
	////=============================================================================
	// ���@�̒e�ƓG�̓����蔻��
	//=============================================================================
	for (int nPriority = 0; nPriority < PRIORITY_MAX; nPriority++)
	{
		CScene * pScene = NULL;

		pScene = CScene::GetScene(nPriority);

		if (pScene != NULL)
		{
			if (nPriority == CScene::PRIORITY_BULLET)
			{
				CBullet *pBullet = (CBullet*)pScene;

				if (m_pos.x+10 >= pBullet->GetPos().x - pBullet->GetSize().x&&
					m_pos.x - 10 <= pBullet->GetPos().x + pBullet->GetSize().x&&
					m_pos.y+50 >= pBullet->GetPos().y - pBullet->GetSize().y&&
					m_pos.y+50 <= pBullet->GetPos().y + pBullet->GetSize().y&&
					m_pos.z -10 <= pBullet->GetPos().z
					)
				{
					pBullet->SetUse(false);
					Uninit();
					return;
				}
			}
		}
	}
		static D3DXVECTOR3 m_Playerpos = CGame::GetPlayer()->GetPos();
		// �v���C���[�ƃg���{�̎Εӂ̋����𑪂�A����i�O�������(c2�� = a2��+b2��)�j
		m_fRange = sqrtf(powf((m_Playerpos.x - m_pos.x), 2.0f) + powf((m_Playerpos.z - m_pos.z), 2.0f));

	if (m_pos.x + (m_fRadius*powf(D3DX_PI,2)) >= m_fRange&&
		m_pos.x - (m_fRadius*powf(D3DX_PI,2)) >= m_fRange&&
		m_pos.z - (m_fRadius*powf(D3DX_PI,2)) >= m_fRange&&
		m_pos.z + (m_fRadius*powf(D3DX_PI,2)) >= m_fRange
		)
	{

		if (m_fRange != NULL)
		{
			m_Move.x = (m_Playerpos.x - m_pos.x) / m_fRange * 10;
			m_Move.z = (m_Playerpos.z - m_pos.z) / m_fRange * 10;
		}
		//else
		//{
		//	m_Move.z = 1;
		//}
	}

	m_pos += m_Move;

	SetPos(m_pos);

	// �p����̍X�V�������Ăяo��
	CEnemy::Update();

}// �|���S���̍X�V�����I��



 //=============================================================================
 // �G�̕`�揈��
 //=============================================================================
void CEnemy2::Draw(void)
{
	// �p����̕`�揈�����Ăяo��
	CEnemy::Draw();

}// �|���S���̕`�揈���I��