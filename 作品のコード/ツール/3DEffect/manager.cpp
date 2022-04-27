//=============================================================================
//
// メイン処理 [main.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include"manager.h"
#include"renderer.h"
#include"scene.h"
#include"scene2D.h"
#include"input.h"
#include"scene3D.h"
#include"camera.h"
#include"light.h"
#include"texture.h"
#include"effect_manager.h"

//静的メンバ変数宣言
CRenderer *CManager::m_pRenderer = NULL;
CInputKeyboard *CManager::m_pInputKeyboard = NULL;
CScene3D*CManager::m_pScene3D = NULL;
CCamera *CManager::m_pCamera = NULL;
CLight *CManager::m_pLight[3] = {};
CTexture *CManager::m_pTexture = NULL;
CEffect_Manager*CManager::m_pEffect_Manager = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CManager::CManager()
{

}

//=============================================================================
//　デストラクタ
//=============================================================================
CManager::~CManager()
{
}


//=============================================================================
// 初期化処理
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

	// カメラの動的メモリの確保
	m_pCamera = new CCamera;
	if (m_pCamera != NULL)
	{	
		m_pCamera->Init();
	}

	// ライトの動的メモリの確保
	for (int nLight = 0; nLight < 3; nLight++)
	{
		// ライトの動的メモリの確保	
		m_pLight[nLight] = new CLight;
	}

	if (m_pLight[0] != NULL)
	{
		m_pLight[0]->Init(D3DXVECTOR3(0.22f, -0.87f, 0.44f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	if (m_pLight[1] != NULL)
	{
		m_pLight[1]->Init(D3DXVECTOR3(-0.18f, 0.88f, -0.44f), D3DXCOLOR(0.65f, 0.65f, 0.65f, 1.0f));
	}
	if (m_pLight[2] != NULL)
	{
		m_pLight[2]->Init(D3DXVECTOR3(0.89f, -0.11f, 0.44f), D3DXCOLOR(0.15f, 0.15f, 0.15f, 1.0f));
	}

	// テクスチャの動的メモリの確保
	m_pTexture = new CTexture;
	if (m_pTexture != NULL)
	{
		m_pTexture->Init();
	}

	m_pScene3D = CScene3D::Creste(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(150.0f, 0.0f, 150.0f));
	m_pEffect_Manager = CEffect_Manager::Create(CEffect_Manager::EffectType_NOMAL);

	return S_OK;
}


//=============================================================================
// 終了処理
//=============================================================================
void CManager::Uninit(void)
{
	CScene::ReleaseAll();

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

	if (m_pTexture != NULL)
	{
		// 終了処理
		m_pTexture->Uninit();

		// 動的メモリの確保したものを解放
		delete m_pTexture;
		m_pTexture = NULL;
	}
}


//=============================================================================
// 更新処理
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

	m_pCamera->Update();
}


//=============================================================================
// 描画処理
//=============================================================================
void CManager::Draw(void)
{
	m_pCamera->SetCamera();

	if (m_pRenderer != NULL)
	{
		// 描画処理
		m_pRenderer->Draw();
	}
}