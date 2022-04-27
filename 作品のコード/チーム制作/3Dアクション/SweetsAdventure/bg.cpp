//---------------------------------------------------
//�w�i�̏���
//---------------------------------------------------
#include"bg.h"
#include "manager.h"
#include "Renderer.h"
#include "scene2D.h"
#include "keyboard.h"



//--------------------------
//�R���X�g���N�g
//----------------------------

CBg::CBg(OBJTYPE nPriority):CScene(nPriority)
{
	m_bScroll = false;
	m_nPriority = nPriority;
}

//--------------------------
//�f�X�g���N�g
//----------------------------
CBg::~CBg()
{

}
void CBg::SetCol(D3DXCOLOR col)
{
	m_pScene2D->SetCol(col);
}
//--------------------------
//������
//----------------------------
HRESULT CBg::Init()
{
	m_pScene2D = new CScene2D(m_nPriority);

	m_pScene2D->Init(m_Type);
	m_pScene2D->SetPos(D3DXVECTOR3(0.0f,0.0f, 0.0f),
							D3DXVECTOR3(SCREEN_WIDTH,0.0f, 0.0f),
							D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f),
							D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
	m_pScene2D->SetCol(D3DXCOLOR(1.0, 1.0, 1.0, 1.0));
	return S_OK;

}

//--------------------------
//�I��
//----------------------------
void CBg::Uninit(void)
{

	m_pScene2D->Uninit();
	m_pScene2D = NULL;
	Release();
}

//--------------------------
//�X�V
//----------------------------
void CBg::Update(void)
{

	if (m_bScroll == true)
	{
		m_fSpeed -= 0.01f;

		m_pScene2D->SetTex(0.0f, m_fSpeed);

	}

}

//--------------------------
//�`��
//----------------------------
void CBg::Draw(void)
{

}

//---------------------------------------------------------------
//�C���X�^���X��������
//---------------------------------------------------------------
CBg *CBg::Create(CTexture::Type type, OBJTYPE nPriority, bool bScrol)
{
	//�C���X�^���X����
	CBg *pBg = new CBg(nPriority);
	if (pBg != NULL)
	{
		pBg->m_Type = type;
		pBg->m_bScroll = bScrol;
		pBg->Init();
	}
	return pBg;
}
