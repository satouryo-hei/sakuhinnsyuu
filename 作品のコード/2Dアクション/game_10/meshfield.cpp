//=============================================================================
//
// ���b�V���t�B�[���h�̏��� [meshfield.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include"meshfield.h"
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"scene3D.h"
#include"texture.h"

//=============================================================================
// �ÓI�����o�ϐ��̐錾
//=============================================================================
LPDIRECT3DTEXTURE9 CMeshField::m_pTexTure = NULL;

//=============================================================================
// ���b�V���t�B�[���h�̃R���X�g���N�^
//=============================================================================
CMeshField::CMeshField(PRIORITY Priority) : CScene(Priority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot =	D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
//�@���b�V���t�B�[���h�̃f�X�g���N�^
//=============================================================================
CMeshField::~CMeshField()
{

}


//=============================================================================
// ���b�V���t�B�[���h�̐�������
//=============================================================================
CMeshField *CMeshField::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// ���b�V���t�B�[���h�̃|�C���^�[����
	CMeshField* pMeshField = NULL;

	// ���I�������̊m��
	pMeshField = new CMeshField;

	// NULL�`�F�b�N
	if (pMeshField != NULL)
	{
		// �����������̌Ăяo��
		pMeshField->Init(pos, size);
	}
	return pMeshField;
}

//=============================================================================
// ���b�V���t�B�[���h�̃f�t�H���g����������
//=============================================================================
HRESULT CMeshField::Init(D3DXVECTOR3 pos)
{
	m_pos = pos;
	return S_OK;
}
//=============================================================================
// ���b�V���t�B�[���h�̏���������
//=============================================================================								
HRESULT CMeshField::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = NULL;

	//�f�o�C�X�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();

	//���_�������(X,Y,Z)
	m_Size = size;

	Init(pos);

	BindTextuer(0);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 9,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_3D*pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void **)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(- m_Size.x, + m_Size.y, + m_Size.z);
	pVtx[1].pos = D3DXVECTOR3(0.0f, + m_Size.y,+ m_Size.z);
	pVtx[2].pos = D3DXVECTOR3(+ m_Size.x, + m_Size.y, + m_Size.z);
							  
	pVtx[3].pos = D3DXVECTOR3( - m_Size.x, + m_Size.y, 0.0f);
	pVtx[4].pos = D3DXVECTOR3(0.0f,  + m_Size.y, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(+ m_Size.x, + m_Size.y, 0.0f);
							  
	pVtx[6].pos = D3DXVECTOR3( - m_Size.x, + m_Size.y, - m_Size.z);
	pVtx[7].pos = D3DXVECTOR3(0.0f,  + m_Size.y, - m_Size.z);
	pVtx[8].pos = D3DXVECTOR3( + m_Size.x, + m_Size.y, - m_Size.z);

	//�@���x�N�g��
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[4].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[5].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[6].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[7].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[8].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[8].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(2.0f, 0.0f);
	pVtx[3].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[4].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[5].tex = D3DXVECTOR2(2.0f, 1.0f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 2.0f);
	pVtx[7].tex = D3DXVECTOR2(1.0f, 2.0f);
	pVtx[8].tex = D3DXVECTOR2(2.0f, 2.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * 14,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	WORD*pIdx; //�C���f�b�N�X���ւ̃|�C���^

			   //�C���f�b�N�X�o�b�t�@�����b�N���ԍ��f�[�^�ւ̃|�C���^���擾
	m_pIdxBuff->Lock(0, 0, (void **)&pIdx, 0);

	//�ԍ��f�[�^�̐ݒ�
	pIdx[0] = 3;
	pIdx[1] = 0;
	pIdx[2] = 4;
	pIdx[3] = 1;
	pIdx[4] = 5;
	pIdx[5] = 2;
	pIdx[6] = 2;
	pIdx[7] = 6;
	pIdx[8] = 6;
	pIdx[9] = 3;
	pIdx[10] = 7;
	pIdx[11] = 4;
	pIdx[12] = 8;
	pIdx[13] = 5;

	//�C���f�b�N�X�o�b�t�@���A�����b�N����
	m_pIdxBuff->Unlock();

	return S_OK;

}

//=============================================================================
// ���b�V���t�B�[���h�̏I������
//=============================================================================
void CMeshField::Uninit(void)
{
	//�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̔j��
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}

	Release();
}

//=============================================================================
// ���b�V���t�B�[���h�̍X�V����
//=============================================================================
void CMeshField::Update(void)
{
}

//=============================================================================
// ���b�V���t�B�[���h�̕`�揈��
//=============================================================================								
void CMeshField::Draw(void)
{	
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = NULL;

	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�̃}�g���b�N�X

	//CManager*pManager = NULL;

	//�f�o�C�X���擾����
	pDevice = CManager::GetRenderer()->GetDevice();

						  //���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);

	pDevice->SetFVF(FVF_VERTEX_3D);//���_�t�H�[�}�b�g�̐ݒ�

								   //�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexTure);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 14);

	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 9, 0, 14);
}


//((x+1)*(z+1))*1,
//�C���f�b�N�X�������߂����
//(�S�Ă̒��_��)+(���Ԃ蒸�_��)
//((x+1)*(z+1))+((x+3)*(z-1))

//=============================================================================
// ���b�V���t�B�[���h�̃e�N�X�`���̐ݒ�
//=============================================================================
void CMeshField::BindTextuer(int nTextuer)
{
	m_pTexTure = CManager::GetTexture()->GetTex(nTextuer);
}