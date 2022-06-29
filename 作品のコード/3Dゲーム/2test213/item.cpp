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
	m_bUse = true;
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
		// �A�C�e���̏����������̌Ăяo��
		pItem->Init(pos, rot, Filedata);
	}

	return pItem;
}

//=============================================================================
// �A�C�e���̏���������
//=============================================================================
HRESULT CItem::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char*Filedata)
{
	// �p�����̏������������Ăяo��
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
	// �p�����̏I���������Ăяo��
	CModel_Single::ReleaseSingle();

	// �������
	Release();
}

//=============================================================================
// �A�C�e���̍X�V����
//=============================================================================
void CItem::Update(void)
{
	// Y�����Ԃ��h���ĉ�
	m_rot.y += 0.05f;

	// ���݂̌������΂����傫�������ꍇ
	if (m_rot.y >= D3DX_PI)
	{
		// ���݂̌�����-�΂������č���Ԃ�ۑ����ăΈȏ�ɂ��Ȃ��悤�ɂ���
		m_rot.y = -D3DX_PI;
	}
	// ���݂̌�����-�΂����傫�������ꍇ
	else if(m_rot.y <= -D3DX_PI)
	{	
		// ���݂̌����Ƀ΂������č���Ԃ�ۑ�����-�Έȏ�ɂ��Ȃ��悤�ɂ���
		m_rot.y = D3DX_PI;
	}
	// ���݂̌����̍X�V
	SetRot(m_rot);

	//=============================================================================
	// ���@�̒e�ƓG�̓����蔻��
	//=============================================================================
	for (int nPriority = 0; nPriority < PRIORITY_MAX; nPriority++)
	{
		// �I�u�W�F�N�g�̃|�C���^�[����
		CScene * pScene = NULL;

		// �I�u�W�F�N�g�̎擾����
		pScene = CScene::GetScene(nPriority);

		// NULL�`�F�b�N
		if (pScene != NULL)
		{
			// �I�u�W�F�N�g�̎�ނ��v���C���[��������
			if (nPriority == CScene::PRIORITY_PLAYER)
			{
				// ���݂̃I�u�W�F�N�g�̎�ނ�G�̃|�C���^�[�����������̂ɓG�̃|�C���^�[�ŃL���X�g���đ��
				CPlayer *pPlayer = (CPlayer*)pScene;

				// �v���C���[�������Ă���A�C�e�������擾
				int nItem = pPlayer->GetItem();

				// ���݂̈ʒu���v���C���[�̌��݂̈ʒu���傫��or������������
				if (m_pos.x >= pPlayer->GetPos().x &&
					m_pos.x <= pPlayer->GetPos().x &&
					m_pos.y >= pPlayer->GetPos().y &&
					m_pos.y <= pPlayer->GetPos().y &&
					m_pos.z >= pPlayer->GetPos().z)
				{				
					// �g���Ȃ�����
					m_bUse = false;
					// �I�������̌Ăяo��
					Uninit();
					// �v���C���[�������Ă���A�C�e���������Z
					pPlayer->SetItem(nItem + 1);
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