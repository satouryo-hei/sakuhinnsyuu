//=============================================================================
//
// マネージャー処理 [manager.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"sound.h"
#include"title.h"
#include"tutorial.h"
#include"game.h"
#include"result.h"
#include"fade.h"
#include"title_logo.h"
#include"texture.h"

//=============================================================================
// 静的メンバ変数の宣言
//=============================================================================
CRenderer *CManager::m_pRenderer = NULL;
CInputKeyboard *CManager::m_pInputKeyboard = NULL;
CSound *CManager::m_pSound = NULL;
CTitle*CManager::m_pTitle = NULL;
CTutorial*CManager::m_pTutorial = NULL;
CGame*CManager::m_pGame = NULL;
CResult*CManager::m_pResult = NULL;
CManager::MODE CManager::m_mode = CManager::MODE_TITLE;
CFade * CManager::m_pFade = NULL;
CTexture * CManager::m_pTexture = NULL;
CManager::MODE CManager::m_Nextmode = CManager::MODE_INVALID;

//=============================================================================
// マネージャーのコンストラクタ
//=============================================================================
CManager::CManager()
{
}

//=============================================================================
// マネージャーのデストラクタ
//=============================================================================
CManager::~CManager()
{
}


//=============================================================================
// マネージャーの初期化処理
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance,HWND hWnd, bool bWindow)
{
	// Rendererの動的メモリの確保
	m_pRenderer = new CRenderer;
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Init(hWnd, bWindow);
	}

	// キーボードの動的メモリの確保
	m_pInputKeyboard = new CInputKeyboard;
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Init(hInstance, hWnd);
	}

	// 音の動的メモリの確保
	m_pSound = new CSound;
	if (m_pSound != NULL)
	{
		m_pSound->Init(hWnd);
	}

	m_pTexture = new CTexture;
	if (m_pTexture != NULL)
	{
		m_pTexture->Init();
	}

	//SetMode(m_mode);
	
	m_pFade = CFade::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), CManager::MODE_TITLE);

	CTitle::Load();

	CTutorial::Load();

	CResult::Load();

	return S_OK;
}


//=============================================================================
// マネージャーの終了処理
//=============================================================================
void CManager::Uninit(void)
{
	CScene::ReleseAll();

	CTitle::Unload();

	CTutorial::Unload();

	CResult::Unload();

	if (m_pTexture != NULL)
	{
		// 終了処理
		m_pTexture->Uninit();

		// 動的メモリの確保したものを解放
		delete m_pTexture;
		m_pTexture = NULL;
	}

	if (m_pSound != NULL)
	{
		// 終了処理
		m_pSound->Uninit();

		// 動的メモリの確保したものを解放
		delete m_pSound;
		m_pSound = NULL;
	}

	if (m_pInputKeyboard != NULL)
	{
		// 終了処理
		m_pInputKeyboard->Uninit();

		// 動的メモリの確保したものを解放
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}

	if (m_pRenderer != NULL)
	{
		// 終了処理
		m_pRenderer->Uninit();

		// 動的メモリの確保したものを解放
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
}


//=============================================================================
// マネージャーの更新処理
//=============================================================================
void CManager::Update(void)
{
	// 更新処理
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Update();
	}

	// 更新処理
	if (m_pRenderer != NULL)
	{	
		m_pRenderer->Update();
	}
}


//=============================================================================
// マネージャーの描画処理
//=============================================================================
void CManager::Draw(void)
{
	if (m_pRenderer != NULL)
	{
		// 描画処理
		m_pRenderer->Draw();
	}
}

//取得処理関係
#if 1 //取得処理関係
//=============================================================================
// CRendererの取得処理
//=============================================================================
CRenderer* CManager::GetRenderer(void)
{
	return m_pRenderer;
}

//=============================================================================
// キーボードの取得処理
//=============================================================================
CInputKeyboard* CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}

//=============================================================================
// 音の取得処理
//=============================================================================
CSound *CManager::GetSound(void)
{
	return m_pSound;
}

#endif

//=============================================================================
// モードの設定処理
//=============================================================================
void CManager::SetMode(MODE mode)
{
	m_Nextmode = mode;
}

//=============================================================================
// モードの切り替え処理
//=============================================================================
void CManager::ChangeMode(void)
{
	if (m_Nextmode == MODE_INVALID)
	{
		return;
	}

	switch (m_mode)
	{
	case MODE_TITLE:
		if (m_pTitle != NULL)
		{
			m_pTitle->Uninit();
			m_pTitle = NULL;
		}
		break;

	case MODE_TUTORIAL:
		if (m_pTutorial != NULL)
		{
			m_pTutorial->Uninit();
			m_pTutorial = NULL;
		}
		break;

	case MODE_GAME:
		if (m_pGame != NULL)
		{
			m_pGame->Uninit();
			m_pGame = NULL;
		}
		break;

	case MODE_RESULT:
		if (m_pResult != NULL)
		{
			m_pResult->Uninit();
			m_pResult = NULL;
		}
		break;

	default:
		break;
	}

	CScene::ReleseAll();

	switch (m_Nextmode)
	{
	case MODE_TITLE:
		m_pTitle = new CTitle;
		if (m_pTitle != NULL)
		{
			m_pTitle->Init(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT));
		}
		break;

	case MODE_TUTORIAL:
		m_pTutorial = new CTutorial;
		if (m_pTutorial != NULL)
		{
			m_pTutorial->Init(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR2(SCREEN_WIDTH / 1.5f, SCREEN_HEIGHT / 1.5f));
		}
		break;

	case MODE_GAME:
		m_pGame = new CGame;
		if (m_pGame != NULL)
		{
			m_pGame->Init(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR2(0, 0));
		}
		break;

	case MODE_RESULT:
		m_pResult = new CResult;
		if (m_pResult != NULL)
		{
			m_pResult->Init(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT));
		}
		break;

	default:
		break;
	}
	m_mode = m_Nextmode;
	m_Nextmode = MODE_INVALID;
}