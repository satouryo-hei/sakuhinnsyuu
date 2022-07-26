//=============================================================================
//
// ���Ԃ̏��� [score.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include "attack_up.h"
#include"player.h"

//=============================================================================
// ���Ԃ̃R���X�g���N�^
//=============================================================================
CAttack_up::CAttack_up(int nPriority) : CScene2D(PRIORITY_ITEM)
{


}

//=============================================================================
// ���Ԃ̃f�X�g���N�^
//=============================================================================
CAttack_up::~CAttack_up()
{

}

//=============================================================================
// ���Ԃ̐�������
//=============================================================================
CAttack_up *CAttack_up::Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	CAttack_up *pAttack_up = NULL;
	pAttack_up = new CAttack_up;

	if (pAttack_up != NULL)
	{
		pAttack_up->Init(pos, Size);
		pAttack_up->Bindtexture(0);
	}
	return pAttack_up;
}

//=============================================================================
// ���Ԃ̏���������
//=============================================================================
HRESULT CAttack_up::Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	m_pos = pos;
	m_size = Size;
	CScene2D::Init(pos,Size);
	return S_OK;
}

//=============================================================================
// ���Ԃ̏I������
//=============================================================================
void CAttack_up::Uninit(void)
{
	Release();
}

//=============================================================================
// ���Ԃ̍X�V����
//=============================================================================
void CAttack_up::Update(void)
{
	int nAttack = CPlayer::GetItem();

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
					CPlayer::SetItem(nAttack + 3);
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
void CAttack_up::Draw(void)
{
	CScene2D::Draw();
}