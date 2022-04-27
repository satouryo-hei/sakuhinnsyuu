//=============================================================================
//
// �t�F�[�h�̏��� [fade.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include"fade.h"
#include"renderer.h"

// �ÓI�����o�ϐ��̐錾
LPDIRECT3DTEXTURE9 CFade::m_pTexture = NULL;
CFade::FADE CFade::m_Fade = CFade::FADE_NONE;
D3DXCOLOR CFade::m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
CManager::MODE CFade::m_ModeNext = CManager::MODE_TITLE;


//=============================================================================
// �t�F�[�h�̃R���X�g���N�^
//=============================================================================
CFade::CFade(int nPriority) : CScene2D(nPriority)
{
}

//=============================================================================
// �t�F�[�h�̃f�X�g���N�^
//=============================================================================
CFade::~CFade()
{

}

//=============================================================================
// �t�F�[�h�̐�������
//=============================================================================
CFade *CFade::Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size, CManager::MODE mode)
{
	CFade* pFade;

	pFade = new CFade;

	if (pFade != NULL)
	{
		pFade->Init(pos, Size);
		pFade->SetFade(mode);
	}
	return pFade;

}

//=============================================================================
// �t�F�[�h�̓ǂݍ���
//=============================================================================
HRESULT CFade::Load(void)
{
	CManager *pManager = NULL;

	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/effect000.jpg",
		&m_pTexture);
	return S_OK;
}

//=============================================================================
// �t�F�[�h�̔j��
//=============================================================================
void CFade::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// �t�F�[�h�̏���������
//=============================================================================
HRESULT CFade::Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	m_Fade = FADE_IN;
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

	CScene2D::Init(pos, Size);
	return S_OK;
}


//=============================================================================
// �t�F�[�h�̏I������
//=============================================================================
void CFade::Uninit(void)
{
	CScene2D::Uninit();
}


//=============================================================================
// �t�F�[�h�̍X�V����
//=============================================================================
void CFade::Update(void)
{
	if (m_Fade != FADE_NONE)
	{
		if (m_Fade == FADE_IN)
		{
			m_col.a -= 0.03f;

			if (m_col.a <= 0.00f)
			{
				m_col.a = 0.00f;

				m_Fade = FADE_NONE;
			}
		}
		else if (m_Fade == FADE_OUT)
		{
			m_col.a += 0.05f;

			if (m_col.a >= 1.00f)
			{
				m_col.a = 1.00f;

				m_Fade = FADE_IN;

				//���[�h�̐ݒ菈��
				CManager::SetMode(m_ModeNext);
			}
		}
		CScene2D::SetColor(m_col);
	}
	//CScene2D::Update();
}

//=============================================================================
// �t�F�[�h�̕`�揈��
//=============================================================================
void CFade::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// �t�F�[�h�̔z�u����
//=============================================================================
void CFade::SetFade(CManager::MODE modeNext)
{
	m_Fade = FADE_OUT;

	m_ModeNext = modeNext;

	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}