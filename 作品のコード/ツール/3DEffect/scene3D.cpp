//=============================================================================
//
// �|���S���̏��� [scene3D.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include"scene3D.h"
#include"renderer.h"
#include"manager.h"


//=============================================================================
// �|���S���̃R���X�g���N�^
//=============================================================================
CScene3D::CScene3D(PRIORITY Priority) : CScene(Priority)
{
	m_pTexTure = NULL;
	m_pVlxBuff = NULL;
	m_pIdxBuff = NULL;
	memset(&m_mtxWorld, NULL, sizeof(m_mtxWorld));
	m_pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
	m_Size = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
}


//=============================================================================
//�@�|���S���̃f�X�g���N�^
//=============================================================================
CScene3D::~CScene3D()
{

}

//=============================================================================
// �e�N�X�`���̏���������
//=============================================================================
void CScene3D::BindTextuer(CTexture::Tex type)
{
	m_pTexTure = CManager::GetTexture()->GetTex(type);
}

//=============================================================================
// �|���S���̏���������
//=============================================================================
CScene3D *CScene3D::Creste(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene3D* pScene3D;

	pScene3D = new CScene3D;

	if (pScene3D != NULL)
	{
		pScene3D->Init(pos, size);
	}
	return pScene3D;
}


//=============================================================================
// �|���S���̏���������
//=============================================================================
HRESULT CScene3D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 Size)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = NULL;

	CManager*pManager = NULL;

	//�f�o�C�X�̎擾
	pDevice = pManager->GetRenderer()->GetDevice();

	m_pos = pos;
	m_Size = Size;

	BindTextuer(CTexture::Tex_Fild);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVlxBuff,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_3D*pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVlxBuff->Lock(0, 0, (void **)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_Size.x, m_pos.y + m_Size.y, m_pos.z + m_Size.z);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_Size.x, m_pos.y + m_Size.y, m_pos.z + m_Size.z);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_Size.x, m_pos.y + m_Size.y, m_pos.z - m_Size.z);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_Size.x, m_pos.y + m_Size.y, m_pos.z - m_Size.z);

	//�@���x�N�g��
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVlxBuff->Unlock();
/*
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
*/
	return S_OK;
}	// �|���S���̏����������I��



	//=============================================================================
	// �|���S���̏I������
	//=============================================================================
void CScene3D::Uninit(void)
{
	//�o�b�t�@�̔j��
	if (m_pVlxBuff != NULL)
	{
		m_pVlxBuff->Release();
		m_pVlxBuff = NULL;
	}
	//�I�u�W�F�N�g�̔j��
	Release();

}// �|���S���̏I�������I��


 //=============================================================================
 // �|���S���̍X�V����
 //=============================================================================
void CScene3D::Update(void)
{

}// �|���S���̍X�V�����I��


 //=============================================================================
 // �|���S���̕`�揈��
 //=============================================================================
void CScene3D::Draw(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = NULL;

	CManager*pManager = NULL;

	//�f�o�C�X���擾����
	pDevice = pManager->GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�̃}�g���b�N�X

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
	pDevice->SetStreamSource(0, m_pVlxBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	//pDevice->SetTexture(0, m_pTexTure[m_Typ]);
	pDevice->SetTexture(0, m_pTexTure);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0, 2);
}	// �|���S���̕`�揈���I��