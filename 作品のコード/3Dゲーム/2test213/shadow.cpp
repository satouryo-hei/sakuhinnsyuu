//=============================================================================
//
// �e�̏��� [shadow.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include"shadow.h"
#include"renderer.h"
#include"manager.h"
#include"texture.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CShadow::CShadow(PRIORITY Priority) : CScene3D(PRIORITY_SECOND)
{
	m_pVtxBuff = NULL;
	m_mtxWorld;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bUse = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CShadow::~CShadow()
{

}

//=============================================================================
// �e�̐�������
//=============================================================================
CShadow *CShadow::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 Rot)
{
	// �e�̃|�C���^�[����
	CShadow* pShadow = NULL;

	// ���I�������̊m��
	pShadow = new CShadow;

	// NULL�`�F�b�N
	if (pShadow != NULL)
	{
		// ����������
		pShadow->Init(pos, size);

		// ������ݒ�
		pShadow->m_rot = Rot;

		// �e�N�X�`���̐ݒ�
		pShadow->BindTextuer(4);
	}

	return pShadow;
}

//=============================================================================
// �e�̏���������
//=============================================================================
HRESULT CShadow::Init(D3DXVECTOR3 pos, D3DXVECTOR3 Size)
{
	// �e�̈ʒu�Ƒ傫���̐ݒ菈�����Ăяo��
	SetShodow(pos, Size);

	// �p�����̏������������Ăяo��
	CScene3D::Init(pos, Size, m_rot);

	return S_OK;
}	// �|���S���̏����������I��



//=============================================================================
// �e�̏I������
//=============================================================================
void CShadow::Uninit(void)
{
	// �p�����̏I���������Ăяo��
	CScene3D::Uninit();

	// �������
	Release();

}// �|���S���̏I�������I��


 //=============================================================================
 // �e�̍X�V����
 //=============================================================================
void CShadow::Update(void)
{

}// �|���S���̍X�V�����I��


 //=============================================================================
 // �e�̕`�揈��
 //=============================================================================
void CShadow::Draw(void)
{
	//�f�o�C�X���擾����
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;//�v�Z�p�̃}�g���b�N�X

								//���Z�����̐ݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// �p�����̕`�揈�����Ăяo��
	CScene3D::Draw();

	//�ʏ�̍����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}	// �|���S���̕`�揈���I��

//=============================================================================
// �e�̈ʒu�Ƒ傫���̐ݒ菈��
//=============================================================================
void CShadow::SetShodow(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	m_pos = pos;
	m_size = size;
}