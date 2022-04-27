//=============================================================================
//
// �^�C�g�����S�̏��� [bg.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include"title_logo.h"
#include"renderer.h"
#include"manager.h"
#include"scene2D.h"

// �ÓI�����o�ϐ��̐錾
LPDIRECT3DTEXTURE9 CTitle_Logo::m_pTexture = NULL;

//=============================================================================
// �^�C�g�����S�̃R���X�g���N�^
//=============================================================================
CTitle_Logo::CTitle_Logo(int nPriority) : CScene(nPriority)
{
	m_apScene2D = NULL;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// �^�C�g�����S�̃f�X�g���N�^
//=============================================================================
CTitle_Logo::~CTitle_Logo()
{

}

//=============================================================================
// �^�C�g�����S�̐�������
//=============================================================================																				
CTitle_Logo *CTitle_Logo::Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	CTitle_Logo* pTitle_Logo;

	pTitle_Logo = new CTitle_Logo(PRIORITY_BG);

	if (pTitle_Logo != NULL)
	{
		pTitle_Logo->Init(pos, Size);
	}
	return pTitle_Logo;
}

//=============================================================================
// �e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CTitle_Logo::Load(void)
{
	CManager *pManager = NULL;

	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/title002.png",
		&m_pTexture);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���̔j��
//=============================================================================
void CTitle_Logo::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

}

//=============================================================================
// �^�C�g�����S�̏���������
//=============================================================================
HRESULT CTitle_Logo::Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	m_apScene2D = new CScene2D(PRIORITY_BG);

	if (m_apScene2D != NULL)
	{
		m_apScene2D->Init(pos, Size);
		m_apScene2D->BindTextuer(m_pTexture);
	}

	m_pos = pos;
	m_Size = Size;
	return S_OK;
}

//=============================================================================
// �^�C�g�����S�̏I������
//=============================================================================
void CTitle_Logo::Uninit(void)
{
	//for (int nCntLogo = 0; nCntLogo < 1; nCntLogo++)
	//{
		if (m_apScene2D != NULL)
		{
			m_apScene2D->Uninit();
			m_apScene2D = NULL;
		}
	//}
	Relese();
}

//=============================================================================
// �^�C�g�����S�̍X�V����
//=============================================================================
void CTitle_Logo::Update(void)
{
	if (m_pos.y < 320)
	{
		m_pos.y++;
		m_apScene2D->SetPosition(m_pos);
	}
	m_apScene2D->Update();
}

//=============================================================================
// �^�C�g�����S�̕`�揈��
//=============================================================================
void CTitle_Logo::Draw(void)
{
}