//=============================================================================
//
// ���f���N���X [model.cpp]
// Author : ���}���@�V��
//
//=============================================================================
//=============================================================================
//�w�b�_�t�@�C���̃C���N���[�h
//=============================================================================
#include "model.h"
#include"renderer.h"
//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CModel::CModel()
{
	// �����o�ϐ��̃N���A
	memset(m_pTexture, NULL, sizeof(m_pTexture));	// �e�N�X�`���̃|�C���^
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ����
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �傫��
	m_vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �e���_�̍ŏ��l
	m_vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �e���_�̍ő�l
	m_pMesh = NULL;									// ���b�V���i���_���j�ւ̃|�C���^
	m_pBuffMat = NULL;								// �}�e���A���i�ގ����j�ւ̃|�C���^
	m_pParent = NULL;								// �e���f���ւ̃|�C���^
	m_nNumMat = 0;									// �}�e���A����
	m_nIdxParent = 0;								// �e���f���̃C���f�b�N�X
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CModel::~CModel()
{
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CModel::Init(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(m_pModelFileName, D3DXMESH_SYSTEMMEM,
		pDevice, NULL, &m_pBuffMat, NULL, &m_nNumMat, &m_pMesh);

	// �}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATERIAL	*pMat;
	int nCntTex = 0;

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &m_pTexture[nCntTex]);
			nCntTex++;
		}
	}

	// ���_���̎擾
	int nNumVtx;		// ���_��
	DWORD sizeFVF;		// ���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^

	// ���_�����擾
	nNumVtx = m_pMesh->GetNumVertices();

	// ���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	// ���_�o�b�t�@�����b�N
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{	
		// ���_���W�̑��
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		// �S�Ă̒��_���r���čő�l�ƍŏ��l�𔲂��o��
		// �ő�l
		if (vtx.x >= m_vtxMax.x)
		{
			m_vtxMax.x = vtx.x;
		}
		if (vtx.y >= m_vtxMax.y)
		{
			m_vtxMax.y = vtx.y;
		}
		if (vtx.z >= m_vtxMax.z)
		{
			m_vtxMax.z = vtx.z;
		}
		// �ŏ��l
		if (vtx.x <= m_vtxMin.x)
		{
			m_vtxMin.x = vtx.x;
		}
		if (vtx.y <= m_vtxMin.y)
		{
			m_vtxMin.y = vtx.y;
		}
		if (vtx.z <= m_vtxMin.z)
		{
			m_vtxMin.z = vtx.z;
		}
		// �ő�l�ƍŏ��l���������l�����f���̑傫��
		m_size.x = m_vtxMax.x - m_vtxMin.x;
		m_size.y = m_vtxMax.y - m_vtxMin.y;
		m_size.z = m_vtxMax.z - m_vtxMin.z;

		// ���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
		pVtxBuff += sizeFVF;
	}

	// ���_�o�b�t�@���A�����b�N
	m_pMesh->UnlockVertexBuffer();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CModel::Uninit(void)
{
	// ���b�V���̔j��
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}
	// �}�e���A���̔j��
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}
	// �e�N�X�`���̔j��
	for (int nCntTex = 0; nCntTex < MODEL_TEX; nCntTex++)
	{
		if (m_pTexture[nCntTex] != NULL)
		{
			m_pTexture[nCntTex]->Release();
			m_pTexture[nCntTex] = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CModel::Update(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void CModel::Draw(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX	mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9		matDef;		// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL		*pMat;		// �}�e���A���f�[�^�ւ̃|�C���^
	int					nCntTex = 0;// �e�N�X�`�����J�E���g

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// �e�p�[�c�̐e�̃}�g���b�N�X�̐ݒ�
	D3DXMATRIX	mtxParent;

	if (m_pParent != NULL)
	{	// �e�̃}�g���b�N�X���擾
		mtxParent = m_pParent->GetMtxWorld();
	}
	else
	{	// ��ԍŏ��̃}�g���b�N�X(��{�ɂȂ�}�g���b�N�X)���|�����킹��
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}

	// �Z�o�����e�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���|�����킹��
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	// �e�p�[�c�̃��[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// �}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		if (pMat->pTextureFilename)
		{	// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, m_pTexture[nCntTex]);
			nCntTex++;
		}
		else
		{	// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, NULL);
		}
		// ���f���i�p�[�c�j�̕`��	
		m_pMesh->DrawSubset(nCntMat);
	}
	// �ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}
//=============================================================================
// ��������
//=============================================================================
CModel *CModel::Create(const char *pModelFileName)
{
	CModel *pModel = nullptr;
	if (pModel == nullptr)
	{
		pModel = new CModel;

		if (pModel != nullptr)
		{
			pModel->SetModelFile(pModelFileName);	// �t�@�C���̃p�X�ݒ�
			pModel->Init();		// ����������
		}
	}
	return pModel;
}
