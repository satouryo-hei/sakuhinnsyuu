#include "main.h"
#include "manager.h"
#include "scene.h"
#include "renderer.h"
#include "texture.h"	
#include "Scene3D.h"
#include "meshsphere.h"

CMeshSphere::CMeshSphere(OBJTYPE nPriority) :CScene(nPriority)
{
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_pIdxBuff = NULL;
	m_nMax_Vtx_X = 0;
	m_nMax_Vtx_Y = 0;
	m_nVtx_Num_Max = 0;
	m_nIdx_Num_Max = 0;
	m_nPoly_Num_Max = 0;
	m_fHalfWidth = 0.0f;
	m_fHalfDepth = 0.0f;
	m_bCulling = false;
}

CMeshSphere::~CMeshSphere()
{

}

//------------------------------------------------------------------------------------------------
//�C���X�^���X��������(�ʒu�A�傫���A�p�x�AX���̃u���b�N���AZ���̃u���b�N���A�\��e�N�X�`���̎��)
//-------------------------------------------------------------------------------------------------
CMeshSphere *CMeshSphere::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNum_X, int nNum_Z,float fRadius, float fNor, CTexture::Type Tex)
{
	//�C���X�^���X����

	CMeshSphere *pField = new CMeshSphere(OBJTYPE_FIELD);

	pField->m_pos = pos;
	pField->m_fNor = fNor;
	float radion = D3DXToRadian(rot.y);
	pField->m_rot.y = radion;
	pField->m_fHalfWidth = pField->m_size.x / 2.0f;
	pField->m_fHalfDepth = pField->m_size.z / 2.0f;
	pField->m_nMax_Vtx_X = (float)nNum_X;
	pField->m_nMax_Vtx_Y = (float)nNum_Z;
	pField->m_pTexture = CManager::GetTexture()->GetTexture(Tex);
	pField->m_radius = fRadius;
	if (pField != NULL)
	{
		pField->Init();
		//���b�V���̐ݒ�
		pField->SetMesh(pos, D3DXCOLOR(1.0, 1.0, 1.0, 1.0), fRadius, 0.0f);

	}

	return pField;
}
void CMeshSphere::SetMesh(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius, float tex_rotX)
{
	m_nVtx_Num_Max = (m_nMax_Vtx_X + 1)*(m_nMax_Vtx_Y + 1);
	m_nIdx_Num_Max = (m_nMax_Vtx_X + 1)*(m_nMax_Vtx_Y + 1) + (m_nMax_Vtx_Y - 1)*(m_nMax_Vtx_X + 3);
	m_nPoly_Num_Max = 2 * m_nMax_Vtx_X * m_nMax_Vtx_Y + (m_nMax_Vtx_Y * 4) - 4;

	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();//�f�o�C�X�̃|�C���^
																	 //�e�N�X�`���摜�̐ݒ�

																	 //�p�x����~�����ɕϊ�����
																	 //���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nVtx_Num_Max,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);
	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD)* m_nIdx_Num_Max,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	//���_�o�b�t�@�̐���
	//-----------------------------
	//���_���
	//-----------------------------
	VERTEX_3D *pVtx;		//���_���ւ̃|�C���^

							//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	int nVtxNum = 0;
	float f2pi = D3DX_PI * 2;
	for (int nCntY = 0; nCntY < m_nMax_Vtx_Y + 1; nCntY++)
	{
		for (int nCntX = 0; nCntX < m_nMax_Vtx_X + 1; nCntX++, nVtxNum++)
		{
			pVtx[nVtxNum].pos = D3DXVECTOR3(
				cosf(((D3DX_PI * 2) / m_nMax_Vtx_X)*nCntX)*(sinf((f2pi / m_nMax_Vtx_X*nCntY) + (D3DX_PI / 2))*fRadius) + pos.x,
				sinf(((D3DX_PI * 2) / m_nMax_Vtx_X)*nCntY)*m_radius + pos.y,
				sinf(((D3DX_PI * 2) / m_nMax_Vtx_X)*nCntX)*(sinf((f2pi / m_nMax_Vtx_X*nCntY) + (D3DX_PI / 2))*fRadius) + pos.z
			);

			pVtx[nVtxNum].nor = D3DXVECTOR3(0.0f, m_fNor, 0.0f);
			pVtx[nVtxNum].col = col;
			pVtx[nVtxNum].tex = D3DXVECTOR2((6.0f / m_nMax_Vtx_X)*nCntX + tex_rotX, (4.0f / m_nMax_Vtx_Y)*nCntY);

		}
	}
	nVtxNum = 0;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
	//----------------------------
	//�C���f�b�N�X���
	//----------------------------
	WORD *pIdx;			//�C���f�b�N�X���ւ̃|�C���^

						//�C���f�b�N�X�o�b�t�@�����b�N���A�ԍ��f�[�^�ւ̃|�C���^���擾
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);
	//�p���ȊO�̒��_
	for (int nCntY = 0; nCntY < m_nMax_Vtx_Y; nCntY++)
	{
		for (int nCntX = 0; nCntX < m_nMax_Vtx_X + 1; nCntX++)
		{
			pIdx[(nCntX * 2) + 0 + ((m_nMax_Vtx_X + 2) * 2) * nCntY] = ((m_nMax_Vtx_X + 1) + nCntX) + ((m_nMax_Vtx_X + 1) * nCntY);
			pIdx[(nCntX * 2) + 1 + ((m_nMax_Vtx_X + 2) * 2) * nCntY] = (0 + nCntX) + ((m_nMax_Vtx_X + 1) * nCntY);
		}
	}
	//�p���̒��_
	for (int nCntY = 0; nCntY < m_nMax_Vtx_Y - 1; nCntY++)
	{
		pIdx[(((m_nMax_Vtx_X + 1) * 2 + 0) * (nCntY + 1)) + (2 * nCntY)] = m_nMax_Vtx_X + ((m_nMax_Vtx_X + 1) * nCntY);
		pIdx[(((m_nMax_Vtx_X + 1) * 2 + 1) * (nCntY + 1)) + (1 * nCntY)] = (m_nMax_Vtx_X * 2 + 2) + ((m_nMax_Vtx_X + 1) * nCntY);
	}
	//�C���f�b�N�X�o�b�t�@���A�����b�N����
	m_pIdxBuff->Unlock();

}


HRESULT CMeshSphere::Init(void)
{
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CMeshSphere::Uninit(void)
{

	//���_�o�b�t�@�̔j��
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
// �X�V����
//=============================================================================
void CMeshSphere::Update(void)
{

}
//=======================================================================
//�`�揈��
//=======================================================================
void CMeshSphere::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();//�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�}�g���b�N�X

								//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	////�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���Ńo�X�̂Ł[�����Ƃ�[�ނɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);

	pDevice->SetFVF(FVF_VERTEX_3D);//���_�t�H�[�}�b�g�̐ݒ�

	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,					//�v���~�e�B�u�̎��
		0,									//�C���f�b�N�X�o�b�t�@�̊J�n�n�_����ŏ��̃C���f�b�N�X�܂ł̃I�t�Z�b�g
		0,	//�`��Ŏg�p�����ŏ��̒��_�ԍ�
		(m_nMax_Vtx_X + 1)*(m_nMax_Vtx_Y + 1),		//���_�̐�
		0,	//�C���f�b�N�X�z��̓ǂݎ����J�n����ʒu
		m_nPoly_Num_Max);	//�O�p�`�|���S���̐�

}

