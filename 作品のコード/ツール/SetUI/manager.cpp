//=============================================================================
//
// マネージャー処理 [manager.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include"manager.h"
#include"renderer.h"
#include"scene.h"
#include"scene2D.h"
#include"input.h"
#include"ui.h"
#include"ui_manager.h"
#include"texture.h"
#include"imgui_window.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
CRenderer *CManager::m_pRenderer = NULL;
CInputKeyboard *CManager::m_InputKeyboard = NULL;
CUI_Manager *CManager::m_pUi_manager = NULL;
CTexture *CManager::m_pTexture = NULL;
CImgui_Window* CManager::m_pImguiWindow = NULL;

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
	// NULLチェック
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Init(hWnd, bWindow);
	}

	// キーボードの動的メモリの確保
	m_InputKeyboard = new CInputKeyboard;
	// NULLチェック
	if (m_InputKeyboard != NULL)
	{
		m_InputKeyboard->Init(hInstance, hWnd);
	}

	// IMGUIのウィンドウの動的メモリの確保
	m_pImguiWindow = new CImgui_Window;
	// NULLチェック
	if (m_pImguiWindow != NULL)
	{
		m_pImguiWindow->Init(hWnd, bWindow);
	}

	// 画像の動的メモリの確保
	m_pTexture = new CTexture;
	// NULLチェック
	if (m_pTexture != NULL)
	{
		m_pTexture->Init();
	}

	m_pUi_manager = CUI_Manager::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f), D3DXVECTOR3(100.0f, 50.0f, 0.0f));
	return S_OK;
}


//=============================================================================
// マネージャーの終了処理
//=============================================================================
void CManager::Uninit(void)
{
	// すべてのオブジェクトの開放処理
	CScene::ReleaseAll();

	// NULLチェック
	if (m_InputKeyboard != NULL)
	{
		// 終了処理
		m_InputKeyboard->Uninit();

		// 動的メモリの確保したものを解放
		delete m_InputKeyboard;
		m_InputKeyboard = NULL;
	}

	// NULLチェック
	if (m_pImguiWindow != NULL)
	{//ImgUI終了処理
		m_pImguiWindow->Uninit();

		// 動的メモリの確保したものを解放
		delete m_pImguiWindow;
		m_pImguiWindow = NULL;
	}


	// NULLチェック
	if (m_pTexture != NULL)
	{
		// 終了処理
		m_pTexture->Uninit();

		// 動的メモリの確保したものを解放
		delete m_pTexture;
		m_pTexture = NULL;
	}

	// NULLチェック
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
	// NULLチェック
	if (m_pImguiWindow != NULL)
	{
		// IMGUIのウィンドウの更新処理
		m_pImguiWindow->Update();
	}

	// NULLチェック
	if (m_InputKeyboard != NULL)
	{
		// キーボードの更新処理
		m_InputKeyboard->Update();
	}

	// NULLチェック
	if (m_pRenderer != NULL)
	{	
		// 更新処理
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