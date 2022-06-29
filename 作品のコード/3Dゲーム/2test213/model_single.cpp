//=============================================================================
//
// �P�̂̃��f������ [model_single.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include"model_single.h"
#include"manager.h"
#include"renderer.h"
#include"model.h"
#include"player.h"

//=============================================================================
// �P�̂̃��f���̃R���X�g���N�^
//=============================================================================
CModel_Single::CModel_Single(PRIORITY Priprity) :CScene(Priprity)
{
	m_pModel = NULL;
	memset(&m_mtxWorld, NULL, sizeof(m_mtxWorld));
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// �P�̂̃��f���̃f�X�g���N�^
//=============================================================================
CModel_Single::~CModel_Single()
{

}

//=============================================================================
// �P�̂̃��f���̐�������
//=============================================================================
CModel_Single *CModel_Single::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char*pFiledata)
{
	// �P�̂̃��f���̃|�C���^�[����
	CModel_Single * pSingle = NULL;

	// ���I�������̊m��
	pSingle = new CModel_Single;

	// NULL�`�F�b�N
	if (pSingle != NULL)
	{
		// �����������̌Ăяo��
		pSingle->Init(pos, rot, pFiledata);
	}
	return pSingle;
}

//=============================================================================
// �P�̂̃��f���̃f�t�H���g����������
//=============================================================================
HRESULT CModel_Single::Init(D3DXVECTOR3 pos)
{
	m_Pos = pos;
	return S_OK;
}

//=============================================================================
// �P�̂̃��f���̏���������
//=============================================================================
HRESULT CModel_Single::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot , const char * pFiledata)
{	
	// m_pModel��NULL��������
	if (m_pModel == NULL)
	{
		//�@���f���V���O���̐����ݒ�
		m_pModel = CModel::Create(pos, rot, pFiledata);

		// �e�̃��f���̐ݒ�
		m_pModel->SetParent(NULL);
	}

	Init(pos);
	m_rot = rot;
	return S_OK;
}

//=============================================================================
// �P�̂̃��f���̏I������
//=============================================================================
void CModel_Single::Uninit(void)
{
	// NULL�`�F�b�N
	if (m_pModel != NULL)
	{
		// �I�������̌Ăяo��
		m_pModel->Uninit();		
		m_pModel = NULL;
	}

	// �P�̂̃��f���̉������
	ReleaseSingle();
}

//=============================================================================
// �P�̂̃��f���̍X�V����
//=============================================================================
void CModel_Single::Update(void)
{
	////=============================================================================
	//// ���@�̒e�ƓG�̓����蔻��
	////=============================================================================
	//for (int nPriority = 0; nPriority < PRIORITY_MAX; nPriority++)
	//{
	//	CScene * pScene = NULL;

	//	pScene = CScene::GetScene(nPriority);

	//	if (pScene != NULL)
	//	{
	//		if (nPriority == CScene::PRIORITY_PLAYER)
	//		{
	//			CPlayer *pPlayer = (CPlayer*)pScene;

	//			D3DXVECTOR3 Playerpos = pPlayer->GetPos();
	//			D3DXVECTOR3 PlayerposOld = pPlayer->GetPosOld();
	//			D3DXVECTOR3 PlayerSize = pPlayer->GetPosOld();


	//			if (Playerpos.x / 2.0f > m_Pos.x / 2.0f &&
	//				Playerpos.x / 2.0f < m_Pos.x / 2.0f &&
	//				Playerpos.z / 2.0f > m_Pos.z / 2.0f &&
	//				Playerpos.z / 2.0f < m_Pos.z / 2.0f &&
	//				Playerpos.y <= m_Pos.y &&
	//				PlayerposOld.y >= m_Pos.y)
	//			{
	//				Playerpos.y = m_Pos.y;
	//				//�ʒu��ݒ�
	//				pPlayer->SetPos(Playerpos);
	//			}
	//		}
	//	}
	//}
}

//=============================================================================
// �P�̂̃��f���̕`�揈��
//=============================================================================
void CModel_Single::Draw(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_Pos.x, m_Pos.y, m_Pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// NULL�`�F�b�N
	if (m_pModel != NULL)
	{
		m_pModel->Draw();
	}
}

//=============================================================================
// �P�̂̃��f���̉������
//=============================================================================
void CModel_Single::ReleaseSingle(void)
{
	if (m_pModel != NULL)
	{
		// �P�̂̃��f���̃e�N�X�`���ȊO�̉������
		m_pModel->ReleaseModel();
		m_pModel = NULL;
	}

	// �������
	Release();
}

//=============================================================================
// �P�̂̃��f���̌����̐ݒ�
//=============================================================================
void CModel_Single::SetRot(D3DXVECTOR3 rot)
{
	// NULL�`�F�b�N
	if (m_pModel != NULL)
	{
		m_pModel->SetRot(rot);
	}
}

//=============================================================================
// �P�̂̃��f���̈ʒu�̐ݒ�
//=============================================================================
void CModel_Single::SetPos(D3DXVECTOR3 pos)
{
	// NULL�`�F�b�N
	if (m_pModel != NULL)
	{
		m_pModel->SetPos(pos);
	}
}