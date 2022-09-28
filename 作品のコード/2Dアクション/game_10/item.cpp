//=============================================================================
//
// ���Ԃ̏��� [score.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include "item.h"
#include"player.h"

//=============================================================================
// ���Ԃ̃R���X�g���N�^
//=============================================================================
CItem::CItem(int nPriority) : CScene2D(PRIORITY_ITEM)
{


}

//=============================================================================
// ���Ԃ̃f�X�g���N�^
//=============================================================================
CItem::~CItem()
{

}

//=============================================================================
// ���Ԃ̐�������
//=============================================================================
CItem *CItem::Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	CItem *pAttack_up = NULL;
	pAttack_up = new CItem;

	if (pAttack_up != NULL)
	{
		pAttack_up->Init(pos, Size);
		pAttack_up->Bindtexture(17);
	}
	return pAttack_up;
}

//=============================================================================
// ���Ԃ̏���������
//=============================================================================
HRESULT CItem::Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	m_pos = pos;
	m_size = Size;
	CScene2D::Init(pos,Size);
	return S_OK;
}

//=============================================================================
// ���Ԃ̏I������
//=============================================================================
void CItem::Uninit(void)
{
	Release();
}

//=============================================================================
// ���Ԃ̍X�V����
//=============================================================================
void CItem::Update(void)
{
	int nItem = CPlayer::GetItem();

	//=============================================================================
	// ���@�̒e�ƓG�̓����蔻��
	//=============================================================================
	for (int nPriority = 0; nPriority < PRIORITY_MAX; nPriority++)
	{
		CScene * pScene = NULL;

		pScene = CScene::GetScene(nPriority);

		if (pScene != NULL)
		{
			if (nPriority == CScene::PRIORITY_PLAYER)
			{
				CPlayer *pPlayer = (CPlayer*)pScene;

				if (m_pos.x + (m_size.x / 2) >= pPlayer->GetPos().x - pPlayer->GetSize().x &&
					m_pos.x - (m_size.x / 2) <= pPlayer->GetPos().x + pPlayer->GetSize().x &&
					m_pos.y + (m_size.y / 2) >= pPlayer->GetPos().y - pPlayer->GetSize().y &&
					m_pos.y - (m_size.y / 2) <= pPlayer->GetPos().y + pPlayer->GetSize().y)
				{
					Uninit();
					CPlayer::SetItem(nItem+1);
					return;
				}
			}
		}
	}

	CScene2D::Update();
}

//=============================================================================
// ���Ԃ̕`�揈��
//=============================================================================
void CItem::Draw(void)
{
	CScene2D::Draw();
}