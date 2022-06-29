//=============================================================================
//
// �����̏��� [number.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include "number.h"
#include"manager.h"
#include"renderer.h"
#include"scene2D.h"
#include"texture.h"

//=============================================================================
// �ÓI�����o�ϐ��̐錾
//=============================================================================
LPDIRECT3DTEXTURE9 CNumber::m_pTexture = NULL;

//=============================================================================
// �����̃R���X�g���N�^
//=============================================================================
CNumber::CNumber()
{
	m_pVtxBuff = NULL;
}

//=============================================================================
// �����̃f�X�g���N�^
//=============================================================================
CNumber::~CNumber()
{

}

//=============================================================================
// �����̐�������
//=============================================================================
CNumber *CNumber::Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size, int nNum)
{
	// �����̃|�C���^�[����
	CNumber *pNumber = NULL;

	// ���I�������̊m��
	pNumber = new CNumber;

	// NULL�`�F�b�N
	if (pNumber != NULL)
	{
		// �����̏������������Ăяo��
		pNumber->Init(pos, Size);
		// �����̃e�N�X�`���̐ݒ菈�����Ăяo��
		pNumber->BindTextuer(nNum);
	}
	return pNumber;
}

//=============================================================================
// �e�N�X�`���̐ݒ�
//=============================================================================
void CNumber::BindTextuer(int nTextuer)
{
	m_pTexture = CManager::GetTexture()->GetTex(nTextuer);
}

//=============================================================================
// �����̏���������
//=============================================================================
HRESULT CNumber::Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = NULL;

	//�f�o�C�X�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void **)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(pos.x - Size.x, pos.y - Size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + Size.x, pos.y - Size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - Size.x, pos.y + Size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + Size.x, pos.y + Size.y, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

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
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// �����̏I������
//=============================================================================
void CNumber::Uninit(void)
{
	////�e�N�X�`���̔j��
	//if (m_pTexture != NULL)
	//{
	//	m_pTexture->Release();
	//	m_pTexture = NULL;
	//}

	//�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//=============================================================================
// �����̍X�V����
//=============================================================================
void CNumber::Update(void)
{

}


//=============================================================================
// �����̕`�揈��
//=============================================================================
void CNumber::Draw(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = NULL;

	// �f�o�C�X�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0, 2);
}

//=============================================================================
// �����̔z�u����
//=============================================================================
void CNumber::SetNumber(int nNumber)
{
	// �e�N�X�`����U���W�̐ݒ�ϐ�
	static const float fTexU = 0.1f;

	//���_���ւ̃|�C���^
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void **)&pVtx, 0);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(fTexU*nNumber, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(fTexU*nNumber + fTexU, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(fTexU*nNumber, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(fTexU*nNumber + fTexU, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �����̐F�̐ݒ菈��
//=============================================================================
void CNumber::SetColor(D3DXCOLOR col)
{
	//���_���ւ̃|�C���^
	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void **)&pVtx, 0);

	//���_�J���[
	pVtx[0].col = D3DXCOLOR(col);
	pVtx[1].col = D3DXCOLOR(col);
	pVtx[2].col = D3DXCOLOR(col);
	pVtx[3].col = D3DXCOLOR(col);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}