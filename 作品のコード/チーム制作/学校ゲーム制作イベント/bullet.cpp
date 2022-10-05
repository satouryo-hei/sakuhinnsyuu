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

//=============================================================================
// �e�̃R���X�g���N�^
//=============================================================================
CBullet::CBullet(int nPriority) : CScene2D(PRIORITY_BULLET), m_AddSize(D3DXVECTOR2(1.0f, 1.0f)), m_AddColor(D3DXCOLOR(0, 0, 0, 20))
{
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Size = D3DXVECTOR2(0.0f, 0.0f);	
	m_bEffect = true;		
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
CBullet *CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size, bool bEffect)
{
	CBullet* pBullet = NULL;

	pBullet = new CBullet;

	if (pBullet != NULL)
	{
		pBullet->Init(pos, Size);
		pBullet->m_Move = move;		
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
	m_Pos = pos;
	m_Size = Size;	

	return S_OK;
}	// �|���S���̏����������I��



//=============================================================================
// �e�̏I������
//=============================================================================
void CBullet::Uninit(void)
{
	// �������
	Release();

}// �|���S���̏I�������I��


//=============================================================================
// �e�̍X�V����
//=============================================================================
void CBullet::Update(void)
{
	m_PosOld = m_Pos;
	
	if (m_bEffect)
	{
		CEffect::Create(m_Pos, m_Size, m_AddSize, m_AddColor,0);
	}

	m_Pos += m_Move;

	SetPosition(m_Pos);	

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
	//	m_bAlive = true;
	//}
	//else if (m_Pos.y <= (m_Size.y / 2))
	//{
	//	m_bAlive = true;
	//}


//	EnemyColision();

	if (m_bUse)
	{
		Uninit();
		return;
	}
	CScene2D::Update();

}// �|���S���̍X�V�����I��



//=============================================================================
// �e�̕`�揈��
//=============================================================================
void CBullet::Draw(void)
{
	CScene2D::Draw();

}	// �|���S���̕`�揈���I��

//	//=============================================================================
//	// �u���b�N�ƒe�̓����蔻��
//	//=============================================================================
//void CBullet::EnemyColision()
//{
//	CScene * pScene = CScene::GetScene(CScene::PRIORITY_ENEMY);
//
//	while (pScene != NULL)
//	{
//		CEnemy02 *pBlock = (CEnemy02*)pScene;
//
//		if (m_Pos.x + m_Size.x >= pBlock->GetPosition().x - pBlock->GetSize().x &&
//			m_Pos.x - m_Size.x <= pBlock->GetPosition().x + pBlock->GetSize().x &&
//			m_Pos.y + m_Size.y >= pBlock->GetPosition().y - pBlock->GetSize().y &&
//			m_Pos.y - m_Size.y <= pBlock->GetPosition().y + pBlock->GetSize().y)
//		{			
//			m_bUse = true;					
//		}
//		// �u���b�N�I�u�W�F�N�g�̎��̃I�u�W�F�N�g���擾
//		CScene * pSceneNext = CScene::GetNext(pScene);
//		pScene = pSceneNext;
//	}
//}
