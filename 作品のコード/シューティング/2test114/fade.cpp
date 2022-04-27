//=============================================================================
//
// フェードの処理 [fade.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include"fade.h"
#include"renderer.h"

// 静的メンバ変数の宣言
LPDIRECT3DTEXTURE9 CFade::m_pTexture = NULL;
CFade::FADE CFade::m_Fade = CFade::FADE_NONE;
D3DXCOLOR CFade::m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
CManager::MODE CFade::m_ModeNext = CManager::MODE_TITLE;


//=============================================================================
// フェードのコンストラクタ
//=============================================================================
CFade::CFade(int nPriority) : CScene2D(nPriority)
{
}

//=============================================================================
// フェードのデストラクタ
//=============================================================================
CFade::~CFade()
{

}

//=============================================================================
// フェードの生成処理
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
// フェードの読み込み
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
// フェードの破棄
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
// フェードの初期化処理
//=============================================================================
HRESULT CFade::Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	m_Fade = FADE_IN;
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

	CScene2D::Init(pos, Size);
	return S_OK;
}


//=============================================================================
// フェードの終了処理
//=============================================================================
void CFade::Uninit(void)
{
	CScene2D::Uninit();
}


//=============================================================================
// フェードの更新処理
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

				//モードの設定処理
				CManager::SetMode(m_ModeNext);
			}
		}
		CScene2D::SetColor(m_col);
	}
	//CScene2D::Update();
}

//=============================================================================
// フェードの描画処理
//=============================================================================
void CFade::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// フェードの配置処理
//=============================================================================
void CFade::SetFade(CManager::MODE modeNext)
{
	m_Fade = FADE_OUT;

	m_ModeNext = modeNext;

	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}