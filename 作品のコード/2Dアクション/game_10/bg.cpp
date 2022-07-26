//=============================================================================
//
// �w�i�̏��� [bg.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include"bg.h"
#include"renderer.h"
#include"manager.h"
#include"scene2D.h"

//=============================================================================
// �w�i�̃R���X�g���N�^
//=============================================================================
CBg::CBg(int nPriority) : CScene(PRIORITY_NOMAL)
{
	m_apScene2D = NULL;
}

//=============================================================================
// �w�i�̃f�X�g���N�^
//=============================================================================
CBg::~CBg()
{

}

//=============================================================================
// �w�i�̐�������
//=============================================================================																				
CBg *CBg::Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size,int nTex)
{
	CBg* pBg;

	pBg = new CBg(PRIORITY_NOMAL);

	if (pBg != NULL)
	{
		pBg->Init(pos, Size, nTex);
	}
	return pBg;
}

HRESULT CBg::Init(D3DXVECTOR3 pos)
{
	return S_OK;
}

//=============================================================================
// �w�i�̏���������
//=============================================================================
HRESULT CBg::Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size,int nTex)
{
	Init(pos);

	// 2D�I�u�W�F�N�g�̐���
	m_apScene2D = CScene2D::Create(pos, Size, nTex);

	return S_OK;
}

//=============================================================================
// �w�i�̏I������
//=============================================================================
void CBg::Uninit(void)
{
	if (m_apScene2D != NULL)
	{
		m_apScene2D->Uninit();
		m_apScene2D = NULL;
	}

}

//=============================================================================
// �w�i�̍X�V����
//=============================================================================
void CBg::Update(void)
{

}

//=============================================================================
// �w�i�̕`�揈��
//=============================================================================
void CBg::Draw(void)
{

}
