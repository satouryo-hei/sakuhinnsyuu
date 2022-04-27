//--------------------------------------
//マネージャーの処理
//--------------------------------------
#include "manager.h"
#include "Renderer.h"
#include "scene.h"
#include "scene2D.h"
#include "keyboard.h"
#include "texture.h"
#include "Scene3D.h"
#include "camera.h"
#include "light.h"
#include "player.h"
#include "model_spawner.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "fade.h"
#include "XInput.h"
#include "mouse.h"
#include "sound.h"

//静的メンバ変数宣言
CInputKeyBoard	*CManager::m_pInputKeyboard = NULL;
CRenderer		*CManager::m_pRenderer = NULL;
CTexture		*CManager::m_pTexture = NULL;
CCamera			*CManager::m_pCamera = NULL;
CLight			*CManager::m_pLight[3] = {};
CPlayer			*CManager::m_pPlayer = NULL;
CModel_Spawner	*CManager::m_pModel = NULL;
CGame			*CManager::m_pGame = NULL;
CTitle			*CManager::m_pTitle = NULL;
CResult			*CManager::m_pResult = NULL;
CFade			*CManager::m_Fade = NULL;
CXInput			*CManager::m_XInput = NULL;
CManager::MODE	 CManager::m_Mode = MODE_GAME;		// 初期モード
CMouse			*CManager::m_Mouse = NULL;
CSound			*CManager::m_pSound = NULL;

bool			CManager::m_bPause = false;
bool			CManager::m_bStop = false;
bool			CManager::m_bEnd = false;
bool			CManager::m_bClear = true;

int g_nTimer = 0;

//--------------------------------------------
//コンストラクタ
//--------------------------------------------
CManager::CManager()
{
}
//--------------------------------------------
//デストラクタ
//--------------------------------------------
CManager::~CManager()
{
}
//--------------------------------------------
// 初期化
//--------------------------------------------
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	// レンダラーの生成
	if (m_pRenderer == NULL)
	{
		m_pRenderer = new CRenderer;
	}

	// テクスチャの生成
	if (m_pTexture == NULL)
	{
		//インスタンス生成
		m_pTexture = new CTexture;
	}

	// レンダラーの初期化
	if (m_pRenderer != NULL)
	{
		if (FAILED(m_pRenderer->Init(hInstance, hWnd, bWindow)))
		{
			return-1;
		}

		// テクスチャの読み込み
		m_pTexture->Init();
	}

	// サウンドの生成
	if (m_pSound == NULL)
	{
		m_pSound = new CSound;
		m_pSound->InitSound();
	}

	//フェードの生成
	if (m_Fade == NULL)
	{
		m_Fade = CFade::Create(CTexture::Text, m_Mode);

		SetMode(m_Mode);

		//モードの設定
	}

	// キーボードの生成
	if (m_pInputKeyboard == NULL)
	{
		m_pInputKeyboard = new CInputKeyBoard;
		if (m_pInputKeyboard != NULL)
		{
			m_pInputKeyboard->Init(hInstance, hWnd);
		}
	}

	// マウスの生成
	if (m_Mouse == NULL)
	{
		m_Mouse = new CMouse;
		m_Mouse->Init(hInstance, hWnd);
	}

	//Xinput生成
	if (m_XInput == NULL)
	{
		m_XInput = new CXInput;
	}

	// ライトの生成
	for (int nLight = 0; nLight < 3; nLight++)
	{
		m_pLight[nLight] = new CLight;
	}
	m_pLight[0]->Init(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.22f, -0.87f, 0.44f));
	m_pLight[1]->Init(D3DXCOLOR(0.65f, 0.65f, 0.65f, 1.0f), D3DXVECTOR3(-0.18f, 0.88f, -0.44f));
	m_pLight[2]->Init(D3DXCOLOR(0.15f, 0.15f, 0.15f, 1.0f), D3DXVECTOR3(0.89f, -0.11f, 0.44f));

	// カメラの生成
	if (m_pCamera == NULL)
	{
		m_pCamera = new CCamera;
		m_pCamera->Init();
	}

	//if (m_pPlayer == NULL)
	//{
	//	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//}
	
	return S_OK;
}
//--------------------------------------------
// 終了
//--------------------------------------------
void CManager::Uninit(void)
{
	//キーボードの破棄
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}

	// ライトの破棄
	for (int nLight = 0; nLight < 3; nLight++)
	{
		if (m_pLight[nLight] != NULL)
		{
			delete m_pLight[nLight];
			m_pLight[nLight] = NULL;
		}
	}

	// マウスの破棄
	if (m_Mouse != NULL)
	{
		m_Mouse->Uninit();
		delete m_Mouse;
		m_Mouse = NULL;
	}

	// シーンの破棄
	CScene::Delete();

	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Uniinit();
		delete m_pTexture;
		m_pTexture = NULL;
	}

	// フェードの破棄
	if (m_Fade != NULL)
	{
		m_Fade->Uninit();
		m_Fade = NULL;
	}

	// レンダラーの破棄
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	// サウンドの破棄
	if (m_pSound != NULL)
	{
		m_pSound->UninitSound();
		delete m_pSound;
		m_pSound = NULL;
	}
}
//--------------------------------------------
// 更新
//--------------------------------------------
void CManager::Update(void)
{
	// レンダラーの更新
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}

	//キーボードの更新
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Update();
	}

	// ゲームパッドの更新
	if (m_XInput != NULL)
	{
		m_XInput->UpdateGamepad();
	}

	// マウスの更新
	if (m_Mouse != NULL)
	{
		m_Mouse->Update();
	}

	// カメラの更新
	m_pCamera->Update();

	// モード毎の更新
	switch (m_Mode)
	{
	case MODE_TITLE:		//タイトル画面
		if (m_pTitle != NULL)
		{
			m_pTitle->Update();
		}
		break;

	case MODE_GAME:			//ゲーム画面
		if (m_pGame != NULL)
		{
			m_pGame->Update();
		}
		break;

	case MODE_RESULT:		//リザルト画面
		if (m_pResult != NULL)
		{
			m_pResult->Update();
		}
		break;
	}
}
//--------------------------------------------
// 描画
//--------------------------------------------
void CManager::Draw(void)
{
	// レンダラーの描画
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();
	}

	// カメラの設定
	m_pCamera->SetCamera();

	// モード毎の描画
	switch (m_Mode)
	{
	case MODE_TITLE:		//タイトル画面
		if (m_pTitle != NULL)
		{
			m_pTitle->Draw();
		}
		break;

	case MODE_GAME:			//ゲーム画面
		if (m_pGame != NULL)
		{
			m_pGame->Draw();
		}
		break;

	case MODE_RESULT:		//リザルト画面
		if (m_pResult != NULL)
		{
			m_pResult->Draw();
		}
		break;
	}
}

//-----------------------------------------------------------------------------
// Renderer取得処理
//-----------------------------------------------------------------------------
CRenderer *CManager::GetRenderer(void)
{
	return m_pRenderer;
}

//-----------------------------------------------------------------------------
// キーボードのインスタンス取得処理
//-----------------------------------------------------------------------------
CInputKeyBoard *CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}

//-----------------------------------------------------------------------------
// テクスチャのインスタンス取得処理
//-----------------------------------------------------------------------------
CTexture *CManager::GetTexture(void)
{
	return m_pTexture;
}

//-----------------------------------------------------------------------------
// モードの処理
//-----------------------------------------------------------------------------
CManager::MODE CManager::GetMode(void)
{
	return m_Mode;
}

//-----------------------------------------------------------------------------
// モードの処理
//-----------------------------------------------------------------------------
void CManager::SetMode(MODE mode)
{
	m_bEnd = false;

	switch (m_Mode)
	{
	case MODE_TITLE:		//タイトル画面
		if (m_pTitle != NULL)
		{
			m_pSound->StopSound(m_pSound->SOUND_LABEL_BGM_TITLE);
			m_pTitle->Uninit();
			delete m_pTitle;
			m_pTitle = NULL;
		}
		break;

	case MODE_GAME:			//ゲーム画面
		if (m_pGame != NULL)
		{
			m_pSound->StopSound(m_pSound->SOUND_LABEL_BGM_GAME);
			m_pGame->Uninit();
			delete m_pGame;
			m_pGame = NULL;
		}
		break;

	case MODE_RESULT:		//リザルト画面
		if (m_pResult != NULL)
		{
			m_pSound->StopSound(m_pSound->SOUND_LABEL_BGM_RESULT);
			m_pResult->Uninit();
			delete m_pResult;
			m_pResult = NULL;
		}
		break;
	}

	//現在選択しているモードの削除+そのモードで生成したオブジェクトの削除
	CScene::Delete();

	//次に移行するモードの生成
	switch (mode)
	{
	case MODE_TITLE:		//タイトル画面
		if (m_pTitle == NULL)
		{
			m_bClear = false;
			m_pTitle = new CTitle;
			m_pTitle->Init();
			m_pSound->PlaySoundA(m_pSound->SOUND_LABEL_BGM_TITLE);	// タイトルサウンド
		}
		break;
	case MODE_GAME:			//ゲーム画面
		if (m_pGame == NULL)
		{
			m_pGame = new CGame;
			m_pGame->Init();
			m_pSound->PlaySoundA(m_pSound->SOUND_LABEL_BGM_GAME);	// タイトルサウンド
		}
		break;
	case MODE_RESULT:		//リザルト画面
		if (m_pResult == NULL)
		{
			m_pResult = new CResult;
			m_pResult->Init();
			m_pSound->PlaySoundA(m_pSound->SOUND_LABEL_BGM_RESULT);	// リザルトサウンド
		}
		break;
	}
	//次のモードを現在のモードに上書き
	m_Mode = mode;
}