//=============================================================================
//
// �ėp�^�̃��f������ [model.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include"model.h"
#include"Camera.h"
#include"input.h"
#include"manager.h"
#include"renderer.h"

//=============================================================================
// �ėp�^�̃��f���̃R���X�g���N�^
//=============================================================================
CModel::CModel()
{
	memset(&m_mtxWorld, NULL, sizeof(m_mtxWorld));//���[���h�}�g���b�N�X
	memset(&m_pTexture[0], NULL, sizeof(m_pTexture));//���[���h�}�g���b�N�X
	m_pMesh = NULL;
	m_pBuffMat = NULL;
	m_vtxMin = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
	m_vtxMax = D3DXVECTOR3(-900.0f, -900.0f, -900.0f);
	m_nNumMat = 0;
	m_Pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	m_Size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	memset(&m_Vtx, 0, sizeof(m_Vtx));
	m_pParent = NULL;
	m_bUse;
}

//=============================================================================
// �ėp�^�̃��f���̃f�X�g���N�^
//=============================================================================
CModel::~CModel()
{

}

//=============================================================================
// �ėp�^�̃��f���̐���
//=============================================================================
CModel *CModel::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *pModelFileName)
{
	// �ėp�^�̃��f���|�C���^�[����
	CModel* pModel = NULL;

	// ���I�������̊m��
	pModel = new CModel;

	// NULL�`�F�b�N
	if (pModel != NULL)
	{
		pModel->Init(pos, rot, pModelFileName);
	}
	return pModel;
}

//=============================================================================
// �ėp�^�̃��f���̏������֐�
//=============================================================================
HRESULT CModel::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *pModelFileName)
{
	m_Pos = pos;
	m_rot = rot;

	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//-------------------//
	//X�t�@�C���̓ǂݍ���//
	//-------------------//
	D3DXLoadMeshFromX(pModelFileName,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_nNumMat,
		&m_pMesh);

	D3DXMATERIAL *pMat = NULL;//�}�e���A���ւ̃|�C���^

					   //�}�e���A�����ɑ΂���|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCnt = 0; nCnt < (int)m_nNumMat; nCnt++)
	{
		if (pMat[nCnt].pTextureFilename != NULL)
		{
			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCnt].pTextureFilename,
				&m_pTexture[nCnt]);	
		}
		else
		{
			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCnt].pTextureFilename,
				nullptr);
		}
	}

	int nNumVtx;//���_��

	DWORD sizeFVF;//���_�t�H�[�}�b�g�̃T�C�Y

	BYTE *pVtxBuff;//���_�o�b�t�@�̃|�C���^

				   //���_�����擾
	nNumVtx = m_pMesh->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	//���_�o�b�t�@���A�����b�N
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCnt = 0; nCnt < nNumVtx; nCnt++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;//���_���W�̑��

		//x�̍ő�l�̔�r
		if (m_vtxMax.x <= vtx.x)
		{
			m_vtxMax.x = vtx.x;
		}
		//y�̍ő�l�̔�r
		if (m_vtxMax.y <= vtx.y)
		{
			m_vtxMax.y = vtx.y;
		}
		//z�̍ő�l�̔�r
		if (m_vtxMax.z <= vtx.z)
		{
			m_vtxMax.z = vtx.z;
		}
		//���̍ŏ��l�̔�r
		if (m_vtxMin.x >= vtx.x)
		{
			m_vtxMin.x = vtx.x;
		}
		//y�̍ŏ��l�̔�r
		if (m_vtxMin.y >= vtx.y)
		{
			m_vtxMin.y = vtx.y;
		}
		//z�̍ŏ��l�̔�r
		if (m_vtxMin.z >= vtx.z)
		{
			m_vtxMin.z = vtx.z;
		}

		m_Size.x = m_vtxMax.x - m_vtxMin.x;
		m_Size.y = m_vtxMax.y - m_vtxMin.y;
		m_Size.z = m_vtxMax.z - m_vtxMin.z;

		pVtxBuff += sizeFVF;//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
	}
	//���_�o�b�t�@���A�����b�N
	m_pMesh->UnlockVertexBuffer();

	//�����̂̏㍶��
	m_Vtx[0] = D3DXVECTOR3(
	-m_vtxMin.x,
	m_vtxMin.y, 
	m_vtxMin.z );

	//�����̂̏�E��
	m_Vtx[1] = D3DXVECTOR3(
		m_vtxMin.x,
		m_vtxMin.y,
		m_vtxMin.z);

	//�����̂̏�E�O
	m_Vtx[2] = D3DXVECTOR3(
		-m_vtxMin.x,
		m_vtxMin.y,
		-m_vtxMin.z);

	//�E�O�i��ʁj
	m_Vtx[3] = D3DXVECTOR3(
		m_vtxMin.x,
		m_vtxMin.y,
		-m_vtxMin.z);
	//�����i���ʁj
	m_Vtx[4] = D3DXVECTOR3(
		-m_vtxMin.x,
		-m_vtxMax.y,
		m_vtxMin.z);
	//�E���i���ʁj
	m_Vtx[5] = D3DXVECTOR3(
		m_vtxMin.x,
		-m_vtxMax.y,
		m_vtxMin.z);
	//���O�i���ʁj
	m_Vtx[6] = D3DXVECTOR3(
		-m_vtxMin.x,
		-m_vtxMax.y,
		-m_vtxMin.z);
	//�E�O�i���ʁj
	m_Vtx[7] = D3DXVECTOR3(
		m_vtxMin.x,
		-m_vtxMax.y,
		-m_vtxMin.z);

	return S_OK;
}

//=============================================================================
// �ėp�^�̃��f���̏I������
//=============================================================================
void CModel::Uninit(void)
{
	ReleaseModel();

	for (int nTex = 0; nTex < MAX_MODEL_TEX; nTex++)
	{
		if (m_pTexture[nTex] != NULL)
		{
			m_pTexture[nTex]->Release();
			m_pTexture[nTex] = NULL;
		}
	}
}

//=============================================================================
// �ėp�^�̃��f���̍X�V����
//=============================================================================
void CModel::Update(void)
{
}

//=============================================================================
// �ėp�^�̃��f���̕`�揈��
//=============================================================================
void CModel::Draw(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;//�}�e���A���f�[�^�̃|�C���^
	D3DXMATRIX mtxParent;						//�e�̃}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_Pos.x, m_Pos.y, m_Pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�e�p�[�c�̐e�̃}�g���b�N�X�̐ݒ�
	if (m_pParent != NULL)
	{
		mtxParent = m_pParent->GetMtx();
	}
	else
	{//�ŐV�̃}�g���b�N�X���擾
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}

	//�Z�o�����p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃��[���h�}�g���b�N�X���|�����킹��
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//�}�e���A���f�[�^�҂̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, m_pTexture[nCntMat]);

		//���f���i�p�[�c�j�̕`��
		m_pMesh->DrawSubset(nCntMat);
	}

	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);

}

//=============================================================================
// �ėp�^�̃��f���̃e�N�X�`���ȊO�̏I������
//=============================================================================
void CModel::ReleaseModel(void)
{
	//���b�V���̔j��
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}

	//�}�e���A���̔j��
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}
}