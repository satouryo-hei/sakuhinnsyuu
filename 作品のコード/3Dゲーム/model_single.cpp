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
	if (m_pModel != NULL)
	{
		m_pModel->ReleaseModel();
		m_pModel = NULL;
	}

	Release();
}

//=============================================================================
// �P�̂̃��f���̍X�V����
//=============================================================================
void CModel_Single::Update(void)
{

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

	if (m_pModel != NULL)
	{
		m_pModel->Draw();
	}
}

//=============================================================================
// �P�̂̃��f���̌����̐ݒ�
//=============================================================================
void CModel_Single::SetRot(D3DXVECTOR3 rot)
{
	if (m_pModel != NULL)
	{
		m_pModel->SetRot(rot);
	}
}

//=============================================================================
// �P�̂̃��f���̌����̐ݒ�
//=============================================================================
void CModel_Single::SetPos(D3DXVECTOR3 pos)
{
	if (m_pModel != NULL)
	{
		m_pModel->SetPos(pos);
	}
}