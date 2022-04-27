////----------------------------------
////�|���S���̏���
////�쐬�ҁ@�ъC�l
////-----------------------------------
//#include "stage_total_model.h"
//#include "input.h"
//#include "Renderer.h"
//#include "manager.h"
//
////=============================================================================
//// �R���X�g���N�^
////=============================================================================
//CStage_Total_Model::CStage_Total_Model()
//{
//	m_pMesh = NULL;					//���b�V���i���_���j�ւ̃|�C���^
//	memset(m_vtx, NULL, sizeof(m_vtx));
//	m_nNumVtx = 0;						//���_�̐�
//	m_vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//	m_vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//���f���̍ŏ��l�A�ő�l
//	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//���f���̈ʒu�i�I�t�Z�b�g�j
//	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//����
//	m_bDraw = false;
//}
//
////=============================================================================
//// �f�X�g���N�^
////=============================================================================
//CStage_Total_Model::~CStage_Total_Model()
//{
//}
////=============================================================================
//// �|���S���̏���������
////=============================================================================
//void CStage_Total_Model::LoadX(const char *sModelFailName)
//{
//	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();//�f�o�C�X�̃|�C���^
//
//																	 //X�t�@�C���̓ǂݍ���
//	D3DXLoadMeshFromX(m_sFailName,
//		D3DXMESH_SYSTEMMEM,
//		pDevice,
//		NULL,
//		&m_pBuffMat,
//		NULL,
//		&m_nNumMat,
//		&m_pMesh);
//
//	//�}�e���A�����ɑ΂���|�C���^���擾
//	m_pMat = (D3DXMATERIAL *)m_pBuffMat->GetBufferPointer();
//	//�}�e���A������ۑ�
//	m_pSaveMat = m_pMat;
//	for (int nCnt = 0; nCnt < (int)m_nNumMat; nCnt++)
//	{
//		if (m_pMat[nCnt].pTextureFilename != NULL)
//		{
//			//�e�N�X�`���̓ǂݍ���
//			D3DXCreateTextureFromFile
//			(pDevice,
//				m_pMat[nCnt].pTextureFilename,
//				&m_pTexture[nCnt]);
//		}
//	}
//	//���_�����擾
//	m_nNumVtx = m_pMesh->GetNumVertices();
//	//���_�t�H�[�}�b�g�̃T�C�Y���擾
//	m_sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());
//	//���_�o�b�t�@���A�����b�N
//	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&m_pVtxBuff);
//	//���f���̑傫���𑪂�
//	for (int nCnt = 0; nCnt < m_nNumVtx; nCnt++)
//	{
//		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)m_pVtxBuff;//���_���W�̑��
//													//x�̍ő�l�̔�r
//		if (m_vtxMax.x >= vtx.x)
//		{
//			m_vtxMax.x = vtx.x;
//		}
//		//���̍ŏ��l�̔�r
//		else if (m_vtxMin.x <= vtx.x)
//		{
//			m_vtxMin.x = vtx.x;
//		}
//		//y�̍ő�l�̔�r
//		if (m_vtxMax.y >= vtx.y)
//		{
//			m_vtxMax.y = vtx.y;
//		}
//		//y�̍ŏ��l�̔�r
//		else if (m_vtxMin.y <= vtx.y)
//		{
//			m_vtxMin.y = vtx.y;
//		}
//		//z�̍ő�l�̔�r
//		if (m_vtxMax.z >= vtx.z)
//		{
//			m_vtxMax.z = vtx.z;
//		}
//		//z�̍ŏ��l�̔�r
//		else if (m_vtxMin.z <= vtx.z)
//		{
//			m_vtxMin.z = vtx.z;
//		}
//		m_pVtxBuff += m_sizeFVF;//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
//	}
//	//���_�o�b�t�@���A�����b�N
//	m_pMesh->UnlockVertexBuffer();
//	//8�̒��_���̕ۑ�
//	//�����i��ʁj
//	m_vtx[0].vtx = D3DXVECTOR3(
//		-m_vtxMin.x,
//		m_vtxMin.y,
//		m_vtxMin.z);
//	//�E���i��ʁj
//	m_vtx[1].vtx = D3DXVECTOR3(
//		m_vtxMin.x,
//		m_vtxMin.y,
//		m_vtxMin.z);
//	//���O�i��ʁj
//	m_vtx[2].vtx = D3DXVECTOR3(
//		-m_vtxMin.x,
//		m_vtxMin.y,
//		-m_vtxMin.z);
//	//�E�O�i��ʁj
//	m_vtx[3].vtx = D3DXVECTOR3(
//		m_vtxMin.x,
//		m_vtxMin.y,
//		-m_vtxMin.z);
//	//�����i���ʁj
//	m_vtx[4].vtx = D3DXVECTOR3(
//		-m_vtxMin.x,
//		-m_vtxMax.y,
//		m_vtxMin.z);
//	//�E���i���ʁj
//	m_vtx[5].vtx = D3DXVECTOR3(
//		m_vtxMin.x,
//		-m_vtxMax.y,
//		m_vtxMin.z);
//	//���O�i���ʁj
//	m_vtx[6].vtx = D3DXVECTOR3(
//		-m_vtxMin.x,
//		-m_vtxMax.y,
//		-m_vtxMin.z);
//	//�E�O�i���ʁj
//	m_vtx[7].vtx = D3DXVECTOR3(
//		m_vtxMin.x,
//		-m_vtxMax.y,
//		-m_vtxMin.z);
//
//}
//
////=============================================================================
//// �|���S���̏���������
////=============================================================================
//void CStage_Total_Model::Init(void)
//{
//	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();//�f�o�C�X�̃|�C���^
//
//																	 //X�t�@�C���̓ǂݍ���
//	D3DXLoadMeshFromX(m_sFailName,
//		D3DXMESH_SYSTEMMEM,
//		pDevice,
//		NULL,
//		&m_pBuffMat,
//		NULL,
//		&m_nNumMat,
//		&m_pMesh);
//
//	//�}�e���A�����ɑ΂���|�C���^���擾
//	m_pMat = (D3DXMATERIAL *)m_pBuffMat->GetBufferPointer();
//	//�}�e���A������ۑ�
//	m_pSaveMat = m_pMat;
//	for (int nCnt = 0; nCnt < (int)m_nNumMat; nCnt++)
//	{
//		if (m_pMat[nCnt].pTextureFilename != NULL)
//		{
//			//�e�N�X�`���̓ǂݍ���
//			D3DXCreateTextureFromFile
//			(pDevice,
//				m_pMat[nCnt].pTextureFilename,
//				&m_pTexture[nCnt]);
//		}
//	}
//	//���_�����擾
//	m_nNumVtx = m_pMesh->GetNumVertices();
//	//���_�t�H�[�}�b�g�̃T�C�Y���擾
//	m_sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());
//	//���_�o�b�t�@���A�����b�N
//	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&m_pVtxBuff);
//	//���f���̑傫���𑪂�
//	for (int nCnt = 0; nCnt < m_nNumVtx; nCnt++)
//	{
//		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)m_pVtxBuff;//���_���W�̑��
//													//x�̍ő�l�̔�r
//		if (m_vtxMax.x >= vtx.x)
//		{
//			m_vtxMax.x = vtx.x;
//		}
//		//���̍ŏ��l�̔�r
//		else if (m_vtxMin.x <= vtx.x)
//		{
//			m_vtxMin.x = vtx.x;
//		}
//		//y�̍ő�l�̔�r
//		if (m_vtxMax.y >= vtx.y)
//		{
//			m_vtxMax.y = vtx.y;
//		}
//		//y�̍ŏ��l�̔�r
//		else if (m_vtxMin.y <= vtx.y)
//		{
//			m_vtxMin.y = vtx.y;
//		}
//		//z�̍ő�l�̔�r
//		if (m_vtxMax.z >= vtx.z)
//		{
//			m_vtxMax.z = vtx.z;
//		}
//		//z�̍ŏ��l�̔�r
//		else if (m_vtxMin.z <= vtx.z)
//		{
//			m_vtxMin.z = vtx.z;
//		}
//		m_pVtxBuff += m_sizeFVF;//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
//	}
//	//���_�o�b�t�@���A�����b�N
//	m_pMesh->UnlockVertexBuffer();
//	//8�̒��_���̕ۑ�
//	//�����i��ʁj
//	m_vtx[0].vtx = D3DXVECTOR3(
//		-m_vtxMin.x,
//		m_vtxMin.y,
//		m_vtxMin.z);
//	//�E���i��ʁj
//	m_vtx[1].vtx = D3DXVECTOR3(
//		m_vtxMin.x,
//		m_vtxMin.y,
//		m_vtxMin.z);
//	//���O�i��ʁj
//	m_vtx[2].vtx = D3DXVECTOR3(
//		-m_vtxMin.x,
//		m_vtxMin.y,
//		-m_vtxMin.z);
//	//�E�O�i��ʁj
//	m_vtx[3].vtx = D3DXVECTOR3(
//		m_vtxMin.x,
//		m_vtxMin.y,
//		-m_vtxMin.z);
//	//�����i���ʁj
//	m_vtx[4].vtx = D3DXVECTOR3(
//		-m_vtxMin.x,
//		-m_vtxMax.y,
//		m_vtxMin.z);
//	//�E���i���ʁj
//	m_vtx[5].vtx = D3DXVECTOR3(
//		m_vtxMin.x,
//		-m_vtxMax.y,
//		m_vtxMin.z);
//	//���O�i���ʁj
//	m_vtx[6].vtx = D3DXVECTOR3(
//		-m_vtxMin.x,
//		-m_vtxMax.y,
//		-m_vtxMin.z);
//	//�E�O�i���ʁj
//	m_vtx[7].vtx = D3DXVECTOR3(
//		m_vtxMin.x,
//		-m_vtxMax.y,
//		-m_vtxMin.z);
//
//
//}
//
////=============================================================================
//// �|���S���̏I������
////=============================================================================
//void CStage_Total_Model::Uninit(void)
//{
//	//���b�V���̔j��
//	if (m_pMesh != NULL)
//	{
//		m_pMesh->Release();
//		m_pMesh = NULL;
//	}
//	//�}�e���A���̔j��
//	if (m_pBuffMat != NULL)
//	{
//		m_pBuffMat->Release();
//		m_pBuffMat = NULL;
//	}
//
//	for (int nTex = 0; nTex < MAX_STAGE_TOTAL_MODEL_TEX; nTex++)
//	{
//		if (m_pTexture[nTex] != NULL)
//		{
//			m_pTexture[nTex]->Release();
//			m_pTexture[nTex] = NULL;
//		}
//	}
//}
//
////=============================================================================
//// �|���S���̍X�V����
////=============================================================================
//void CStage_Total_Model::Update(void)
//{
//
//}
//
////=============================================================================
//// �|���S���̕`�揈��
////=============================================================================
//void CStage_Total_Model::Draw(void)
//{
//	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();//�f�o�C�X�̃|�C���^
//
//																	 //���݂̃}�e���A�����擾
//	D3DXMATRIX mtxRotModel, mtxTransModel, mtxScale;//�v�Z�p�}�g���b�N�X
//	D3DXMATRIX mtxParent;//�e�̃}�g���b�N�X
//	D3DMATERIAL9 Matdef;
//	//�e�p�[�c�̃��[���h�}�g���b�N�X�̏�����
//	D3DXMatrixIdentity(&m_mtxWorld);
//	//�T�C�Y�ύX
//	D3DXMatrixScaling(&mtxScale, m_scale.x, m_scale.y, m_scale.z);
//	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);
//
//	D3DXMatrixRotationYawPitchRoll(&mtxRotModel, m_rot.y, m_rot.x, m_rot.z);
//	////�����𔽉f
//	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRotModel);
//	//�ʒu�𔽉f
//	D3DXMatrixTranslation(&mtxTransModel, m_pos.x, m_pos.y, m_pos.z);
//	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTransModel);
//	pDevice->GetMaterial(&Matdef);
//
//	//�����p�[�c�̐e�̃}�g���b�N�X��ݒ�
//	if (m_pParent != NULL)
//	{
//		mtxParent = m_pParent->GetMatrix();
//	}
//	else
//	{
//		//�ŐV�̃}�g���b�N�X���擾
//		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
//	}
//
//	//�Z�o�����e�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���|�����킹��
//	D3DXMatrixMultiply(&m_mtxWorld,
//		&m_mtxWorld,
//		&mtxParent);
//	//�e�p�[�c�̃��[���h�}�g���b�N�X�̐ݒ�
//	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
//
//	if (m_bDraw == false)
//	{
//		//�}�e���A���f�[�^�҂̃|�C���^���擾
//		m_pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();
//
//		for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
//		{
//			//�}�e���A���̐ݒ�
//			pDevice->SetMaterial(&m_pMat[nCntMat].MatD3D);
//			//�e�N�X�`���̐ݒ�
//			pDevice->SetTexture(0, m_pTexture[nCntMat]);
//			//���f���i�p�[�c�j�̕`��
//			m_pMesh->DrawSubset(nCntMat);
//		}
//		//�ۑ����Ă����}�e���A����߂�
//		pDevice->SetMaterial(&Matdef);
//
//	}
//
//}
////=============================================================================
//// �|���S���̕`�揈��
////=============================================================================
//void CStage_Total_Model::SetDiffuse(float DiffuseA)
//{
//	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();//�f�o�C�X�̃|�C���^
//																	 //�}�e���A���f�[�^�҂̃|�C���^���擾
//	m_pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();
//
//	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
//	{
//		m_pMat[nCntMat].MatD3D.Diffuse.a = DiffuseA;
//		//�}�e���A���̐ݒ�
//		pDevice->SetMaterial(&m_pMat[nCntMat].MatD3D);
//	}
//
//}
////---------------------------------------------------------------
////�C���X�^���X��������
////---------------------------------------------------------------
//CStage_Total_Model *CStage_Total_Model::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *sModelFailName, D3DXVECTOR3 scale)
//{
//	//�C���X�^���X����
//	CStage_Total_Model *pModel = new CStage_Total_Model;
//	if (pModel != NULL)
//	{
//		strcpy(pModel->m_sFailName, sModelFailName);
//		pModel->Init();
//	}
//	pModel->m_pos = pos;
//	pModel->m_rot = rot;
//	pModel->m_scale = scale;
//	return pModel;
//}
