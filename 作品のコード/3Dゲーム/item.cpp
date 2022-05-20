//=============================================================================
//
// �A�C�e������ [model_single.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include"item.h"
#include"manager.h"
#include"renderer.h"
#include"model.h"
#include"player.h"

//=============================================================================
// �A�C�e���̃R���X�g���N�^
//=============================================================================
CItem::CItem(PRIORITY Priprity) :CModel_Single(Priprity)
{
	memset(&m_mtxWorld, NULL, sizeof(m_mtxWorld));
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// �A�C�e���̃f�X�g���N�^
//=============================================================================
CItem::~CItem()
{

}

//=============================================================================
// �A�C�e���̐�������
//=============================================================================
CItem *CItem::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char*Filedata)
{
	// �A�C�e���̃|�C���^�[����
	CItem * pItem = NULL;

	// ���I�������̊m��
	pItem = new CItem;

	//NULL�`�F�b�N
	if (pItem != NULL)
	{
		pItem->Init(pos, rot, Filedata);
	}

	return pItem;
}

//=============================================================================
// �A�C�e���̏���������
//=============================================================================
HRESULT CItem::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char*Filedata)
{
	// �p����̏������������Ăяo��
	CModel_Single::Init(pos, rot, Filedata);
	m_pos = pos;
	m_rot = rot;
	SetPos(m_pos);
	SetRot(m_rot);
	return S_OK;
}

//=============================================================================
// �A�C�e���̏I������
//=============================================================================
void CItem::Uninit(void)
{
	// �p����̏I���������Ăяo��
	CModel_Single::Uninit();
	Release();
}

//=============================================================================
// �A�C�e���̍X�V����
//=============================================================================
void CItem::Update(void)
{
	m_rot.y += 0.05f;
	if (m_rot.y >= D3DX_PI)
	{
		m_rot.y = -D3DX_PI;
	}
	else if(m_rot.y <= -D3DX_PI)
	{		
		m_rot.y = D3DX_PI;
	}
	SetRot(m_rot);

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
				int nAttack = pPlayer->GetAttack();

				if (m_pos.x+10 >= pPlayer->GetPos().x &&
					m_pos.x - 10 <= pPlayer->GetPos().x &&
					m_pos.y >= pPlayer->GetPos().y &&
					m_pos.y <= pPlayer->GetPos().y &&
					m_pos.z >= pPlayer->GetPos().z
					)
				{
					pPlayer->SetAttack(nAttack+10);
					Uninit();
					return;
				}
			}
		}
	}
	// �p����̍X�V�������Ăяo��
	CModel_Single::Update();
}

//=============================================================================
// �A�C�e���̕`�揈��
//=============================================================================
void CItem::Draw(void)
{
	// �p����̕`�揈�����Ăяo��
	CModel_Single::Draw();
}