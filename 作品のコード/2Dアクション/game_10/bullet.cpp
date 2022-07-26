//=============================================================================
//
// �e�̏��� [bullet.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include"bullet.h"
#include"renderer.h"
#include"manager.h"
#include"input.h"
#include"player.h"
#include"effect.h"
#include"noneblock.h"
#include"explosion.h"

/*��肽������*/
/*�e�̉�]�@������̂��H
�`���[�W�V���b�g
�`���[�W�V���b�g�Œe�̊g��*/

////=============================================================================
//// �ÓI�����o�֐��̐錾
////=============================================================================
//bool CBullet::m_bUse = false;

//=============================================================================
// �e�̃R���X�g���N�^
//=============================================================================
CBullet::CBullet(int nPriority) : CScene2D(PRIORITY_BULLET)
{
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Size = D3DXVECTOR2(0.0f, 0.0f);
	m_nLife = 0;
	m_bEffect = true;
	//m_bUse = false;
}


//=============================================================================
// �e�̃f�X�g���N�^
//=============================================================================
CBullet::~CBullet()
{

}


//=============================================================================
// �e�̐�������
//=============================================================================
CBullet *CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size, int nLife, bool bEffect)
{
	CBullet* pBullet = NULL;

	pBullet = new CBullet;

	if (pBullet != NULL)
	{
		pBullet->Init(pos, Size);
		pBullet->m_Move = move;
		pBullet->m_nLife = nLife;
		pBullet->m_bEffect = bEffect;
		pBullet->Bindtexture(6);
		pBullet->m_bUse = false;
	}

	return pBullet;
}

//=============================================================================
// �e�̏���������
//=============================================================================
HRESULT CBullet::Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	CScene2D::Init(pos, Size);
	
	int nItem = CPlayer::GetItem();
	m_nLife += nItem;
	m_Pos = pos;
	m_Size = Size;	

	return S_OK;
}	// �|���S���̏����������I��



//=============================================================================
// �e�̏I������
//=============================================================================
void CBullet::Uninit(void)
{
	//CScene2D::Uninit();

	Release();

}// �|���S���̏I�������I��


//=============================================================================
// �e�̍X�V����
//=============================================================================
void CBullet::Update(void)
{
	if (m_bUse)
	{
		Uninit();
		return;
	}

	m_PosOld = m_Pos;
	
	if (m_bEffect)
	{
		CEffect::Create(m_Pos, m_Size, D3DXVECTOR2(1.0f, 1.0f), D3DXCOLOR(0, 0, 0, 20));
	}

	m_Pos += m_Move;

	SetPosition(m_Pos);

	m_nLife -= 5;
	if (m_nLife < 0)
	{
		m_nLife = 0;
		m_bUse = true;
	}

	// ��ʊO����
	if (m_Pos.x >= SCREEN_WIDTH - (m_Size.x / 2))
	{
		m_bUse = true;
	}
	else if (m_Pos.x <= (m_Size.x / 2))
	{
		m_bUse = true;
	}
	//if (m_Pos.y >= SCREEN_HEIGHT - (m_Size.y / 2))
	//{
	//	m_bUse = true;
	//}
	//else if (m_Pos.y <= (m_Size.y / 2))
	//{
	//	m_bUse = true;
	//}

	////=============================================================================
	//// ���@�̒e�ƓG�̓����蔻��
	////=============================================================================
	//for (int nPriority = 0; nPriority < PRIORITY_MAX; nPriority++)
	//{
	//	CScene * pScene = NULL;

	//	pScene = CScene::GetScene(nPriority);

	//	if (pScene != NULL)
	//	{
	//		CScene::OBJTYPE objType;
	//		objType = pScene->GetOnjType();

	//		if (objType == CScene::OBJTYPE_ENEMY &&m_ObjType == CScene::OBJTYPE_PLAYERBULLET)
	//		{
	//			CEnemy *pEnemy = (CEnemy*)pScene;

	//			if (pos.x + (m_Size.x / 2) >= pEnemy->GetPosition().x - pEnemy->GetSize().x &&
	//				pos.x - (m_Size.x / 2) <= pEnemy->GetPosition().x + pEnemy->GetSize().x &&
	//				pos.y + (m_Size.y / 2) >= pEnemy->GetPosition().y - pEnemy->GetSize().y &&
	//				pos.y - (m_Size.y / 2) <= pEnemy->GetPosition().y + pEnemy->GetSize().y)
	//			{
	//				//�����̐���
	//				CExplosion::Create(pos, D3DXVECTOR2(100.0f, 100.0f));
	//				pScore->AddScore(100);
	//				Uninit();
	//				pEnemy->Uninit();
	//				return;
	//			}
	//		}
	//	}
	//}
	//BlockColision();

	CScene2D::Update();

}// �|���S���̍X�V�����I��



//=============================================================================
// �e�̕`�揈��
//=============================================================================
void CBullet::Draw(void)
{
	CScene2D::Draw();

}	// �|���S���̕`�揈���I��

	//=============================================================================
	// �u���b�N�ƒe�̓����蔻��
	//=============================================================================
void CBullet::BlockColision()
{
	CScene * pScene = CScene::GetScene(CScene::PRIORITY_BLOCK);

	if(pScene != NULL)
	{
		CNoneBlock *pBlock = (CNoneBlock*)pScene;

		if (m_Pos.x >= pBlock->GetPosition().x - pBlock->GetSize().x &&
			m_Pos.x <= pBlock->GetPosition().x + pBlock->GetSize().x &&
			m_Pos.y >= pBlock->GetPosition().y - pBlock->GetSize().y &&
			m_Pos.y <= pBlock->GetPosition().y + pBlock->GetSize().y)
		{
			if (pBlock->GetPosition().y - pBlock->GetSize().y >= m_PosOld.y + m_Size.y)						//�u���b�N�̏㕔
			{
				m_bUse = true;
			}			
		}
	}
}
