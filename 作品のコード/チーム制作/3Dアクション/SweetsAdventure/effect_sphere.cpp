#include "main.h"
#include "manager.h"
#include "scene.h"
#include "renderer.h"
#include "texture.h"	
#include "Scene3D.h"
#include "effect_sphere.h"

CEffectSphere::CEffectSphere(OBJTYPE nPriority) :CScene3D(nPriority)
{
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_pIdxBuffWall = NULL;
	m_nMax_Vtx_X = 0;
	m_nMax_Vtx_Y = 0;
	m_nVtx_Num_Max = 0;
	m_nIdx_Num_Max = 0;
	m_nPoly_Num_Max = 0;
	m_fHalfWidth = 0.0f;
	m_fHalfDepth = 0.0f;
	m_bUninit = false;
}

CEffectSphere::~CEffectSphere()
{

}

//------------------------------------------------------------------------------------------------
//�C���X�^���X��������(�ʒu�A�傫���A�p�x�AX���̃u���b�N���AZ���̃u���b�N���A�\��e�N�X�`���̎��)
//-------------------------------------------------------------------------------------------------
CEffectSphere *CEffectSphere::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNum_X, int nNum_Z, float fRadius, float fNor, CTexture::Type Tex)
{
	//�C���X�^���X����
	CEffectSphere *pEffectSphere = new CEffectSphere();

	pEffectSphere->m_pos = pos;
	pEffectSphere->m_fNor = fNor;
	float radion = D3DXToRadian(rot.y);
	pEffectSphere->m_rot = D3DXVECTOR3(rot.x, radion,rot.z) ;
	pEffectSphere->m_fHalfWidth = pEffectSphere->m_size.x / 2.0f;
	pEffectSphere->m_fHalfDepth = pEffectSphere->m_size.z / 2.0f;
	pEffectSphere->m_nMax_Vtx_X = (float)nNum_X;
	pEffectSphere->m_nMax_Vtx_Y = (float)nNum_Z;
	pEffectSphere->m_pTexture = CManager::GetTexture()->GetTexture(Tex);
	pEffectSphere->m_radius = fRadius;
	if (pEffectSphere != NULL)
	{
		pEffectSphere->Init();
		//���b�V���̐ݒ�
		pEffectSphere->SetMesh(pos, D3DXCOLOR(1.0,1.0,1.0,1.0), fRadius, 0.0f);
	}

	return pEffectSphere;
}

void CEffectSphere::SetMesh(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius, float tex_rotX)
{
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
				cosf(((D3DX_PI * 2) / m_nMax_Vtx_X)*nCntX)*(sinf((f2pi / m_nMax_Vtx_X*nCntY) + (D3DX_PI/2))*fRadius)+ pos.x,
				sinf(((D3DX_PI * 2) / m_nMax_Vtx_X)*nCntY)*m_radius + pos.y,
				sinf(((D3DX_PI * 2) / m_nMax_Vtx_X)*nCntX)*(sinf((f2pi / m_nMax_Vtx_X*nCntY) + (D3DX_PI/2 ))*fRadius)+ pos.z
			);

			pVtx[nVtxNum].nor = D3DXVECTOR3(0.0f, m_fNor, 0.0f);
			pVtx[nVtxNum].col = col;
			pVtx[nVtxNum].tex = D3DXVECTOR2((4.0f / m_nMax_Vtx_X)*nCntX + tex_rotX, (1.0f / m_nMax_Vtx_Y)*nCntY);

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
	m_pIdxBuffWall->Lock(0, 0, (void**)&pIdx, 0);
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
	m_pIdxBuffWall->Unlock();

}
HRESULT CEffectSphere::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();//�f�o�C�X�̃|�C���^

	m_nVtx_Num_Max = (m_nMax_Vtx_X + 1)*(m_nMax_Vtx_Y + 1);
	m_nIdx_Num_Max = (m_nMax_Vtx_X + 1)*(m_nMax_Vtx_Y + 1) + (m_nMax_Vtx_Y - 1)*(m_nMax_Vtx_X + 3);
	m_nPoly_Num_Max = 2 * m_nMax_Vtx_X * m_nMax_Vtx_Y + (m_nMax_Vtx_Y * 4) - 4;
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
		&m_pIdxBuffWall,
		NULL);


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CEffectSphere::Uninit(void)
{

	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̔j��
	if (m_pIdxBuffWall != NULL)
	{
		m_pIdxBuffWall->Release();
		m_pIdxBuffWall = NULL;
	}

	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CEffectSphere::Update(void)
{
	//if (m_col.a <= 0.0f)
	//{
	//	m_bUninit = true;
	//}
	if (m_bUninit == true)
	{
		Uninit();
	}
}
//=======================================================================
//�`�揈��
//=======================================================================
void CEffectSphere::Draw()
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
	pDevice->SetIndices(m_pIdxBuffWall);

	pDevice->SetFVF(FVF_VERTEX_3D);//���_�t�H�[�}�b�g�̐ݒ�

	pDevice->SetTexture(0, m_pTexture);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);//�J�����O������
														  //�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,					//�v���~�e�B�u�̎��
		0,									//�C���f�b�N�X�o�b�t�@�̊J�n�n�_����ŏ��̃C���f�b�N�X�܂ł̃I�t�Z�b�g
		m_nVtx_Num_Max,	//�`��Ŏg�p�����ŏ��̒��_�ԍ�
		(m_nMax_Vtx_X + 1)*(m_nMax_Vtx_Y + 1),		//���_�̐�
		0,	//�C���f�b�N�X�z��̓ǂݎ����J�n����ʒu
		m_nPoly_Num_Max);	//�O�p�`�|���S���̐�
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);//�J�����O������

}

