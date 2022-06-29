//=============================================================================
//
// �r���{�[�h���� [billboard.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include "billboard.h"
#include "input.h"
#include "renderer.h"
#include "manager.h"
#include"scene3D.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBillboard::CBillboard(PRIORITY nPriority) :CScene(nPriority)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBillboard::~CBillboard()
{

}
//=============================================================================
//�@�r���{�[�h�̃e�N�X�`���̐ݒ�
//=============================================================================
void CBillboard::BindTextuer(int type)
{
	m_pTexture = CManager::GetTexture()->GetTex(type);
}
//=============================================================================
//�@�r���{�[�h�̐���
//=============================================================================
CBillboard *CBillboard::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	// �r���{�[�h�̃|�C���^�[����
	CBillboard* pBillboard = NULL;

	// ���I�������̊m��
	pBillboard = new CBillboard;

	// NULL�`�F�b�N
	if (pBillboard != NULL)
	{
		// �r���{�[�h�̏����������̌Ăяo��
		pBillboard->Init(pos, size);
		pBillboard->BindTextuer(0);
	}
	return pBillboard;
}

//=============================================================================
// �r���{�[�h�̃f�t�H���g����������
//=============================================================================
HRESULT CBillboard::Init(D3DXVECTOR3 pos)
{
	m_pos = pos;
	return S_OK;
}

//=============================================================================
// �r���{�[�h�̏���������
//=============================================================================
HRESULT CBillboard::Init(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	// �r���{�[�h�̃f�t�H���g�����������̌Ăяo��
	Init(pos);
	m_size = size;

	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();//�f�o�C�X�̃|�C���^

	 // ���_����ݒ�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;
	
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(- m_size.x, + m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+ m_size.x, + m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(- m_size.x, - m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+ m_size.x, - m_size.y, 0.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0, 0.0);
	pVtx[1].tex = D3DXVECTOR2(1.0, 0.0);
	pVtx[2].tex = D3DXVECTOR2(0.0, 1.0);
	pVtx[3].tex = D3DXVECTOR2(1.0, 1.0);

	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// �r���{�[�h�̏I������
//=============================================================================
void CBillboard::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	////���_�o�b�t�@�̔j��
	//if (m_pTexture != NULL)
	//{
	//	m_pTexture->Release();
	//	m_pTexture = NULL;
	//}

	// �������
	Release();
}

//=============================================================================
// �r���{�[�h�̍X�V����
//=============================================================================
void CBillboard::Update(void)
{
}

//=============================================================================
// �r���{�[�h�̕`�揈��
//=============================================================================
void CBillboard::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();//�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxRot,mtxTrans;//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView;									// �r���[�}�g���b�N�X

								//���C�g����
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�A���t�@�e�X�g�֌W
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//Z�e�X�g�֌W
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�r���[�}�g���b�N�X�̎擾
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
	D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxView); //�t�s������߂�

	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);		// m_mtxWorld = m_mtxWorld * mtxTrans �s����|�����킹��
	
	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
	pDevice->SetFVF(FVF_VERTEX_3D);//���_�t�H�[�}�b�g�̐ݒ�

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);

	////Z�e�X�g�֌W
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//�A���t�@�e�X�g�֌W
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);

	//���C�g�����Ƃɖ߂�
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}

//=============================================================================
// �r���{�[�h�̈ʒu�ݒ菈��
//=============================================================================
void  CBillboard::SetPosSize(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	m_pos = pos;

	VERTEX_3D *pVtx = NULL;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(- size.x, + size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+ size.x, + size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(- size.x, - size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+ size.x, - size.y, 0.0f);

	m_pVtxBuff->Unlock();
}

//=============================================================================
// �r���{�[�h�́i1.0f�ő�j�F�̐ݒ菈��
//=============================================================================
void CBillboard::SetColor(D3DXCOLOR col)
{
	VERTEX_3D *pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
	pVtx[1].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
	pVtx[2].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
	pVtx[3].col = D3DXCOLOR(col.r, col.g, col.b, col.a);

	m_pVtxBuff->Unlock();

}

//=============================================================================
// �r���{�[�h�́i255�ő�j�F�̐ݒ菈��
//=============================================================================
void CBillboard::SetColor(int nRad, int nGreen, int nBlue, int nAlpha)
{
	VERTEX_3D *pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].col = D3DCOLOR_RGBA(nRad, nGreen, nBlue, nAlpha);
	pVtx[1].col = D3DCOLOR_RGBA(nRad, nGreen, nBlue, nAlpha);
	pVtx[2].col = D3DCOLOR_RGBA(nRad, nGreen, nBlue, nAlpha);
	pVtx[3].col = D3DCOLOR_RGBA(nRad, nGreen, nBlue, nAlpha);

	m_pVtxBuff->Unlock();

}

//=============================================================================
// �A�j���[�V�����̃e�N�X�`���z�u����
//=============================================================================
void CBillboard::SetTexAnime(int nPatternAnim, float fSizeAnimU, float fSizeMinV, float fSizeMaxV)
{
	//���_���ւ̃|�C���^
	VERTEX_3D*pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void **)&pVtx, 0);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(nPatternAnim*fSizeAnimU, fSizeMinV);
	pVtx[1].tex = D3DXVECTOR2(nPatternAnim*fSizeAnimU + fSizeAnimU, fSizeMinV);
	pVtx[2].tex = D3DXVECTOR2(nPatternAnim*fSizeAnimU, fSizeMaxV);
	pVtx[3].tex = D3DXVECTOR2(nPatternAnim*fSizeAnimU + fSizeAnimU, fSizeMaxV);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}