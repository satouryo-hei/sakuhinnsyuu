//=============================================================================
//
// メイン処理 [renderer.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include"renderer.h"
#include"scene.h"
#include"manager.h"
#include"ui.h"
#include"ui_manager.h"
#include"texture.h"
#include"input.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CRenderer::CRenderer()
{
	m_pD3D = NULL;
	m_pD3DDevice = NULL;
	m_pFont = NULL;
	m_pUiFont = NULL;
	m_bUIControl = false;
	m_FontCol = D3DXCOLOR(255,255,255,255);
	m_FontColType = 0;
	m_bColorTrigger = false;
	m_bUIFont = true;
}

//=============================================================================
// デストラクタ
//=============================================================================
CRenderer::~CRenderer()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CRenderer::Init(HWND hWnd, bool bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;								//プレゼンテーションパラメータ	
	D3DDISPLAYMODE d3ddm;										//ディスプレイモード

	// Direct3Dオブジェクトの作成
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}

	// 現在のディスプレイモードを取得
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));								// ワークをゼロクリア
	d3dpp.BackBufferCount = 1;										// バックバッファの数
	d3dpp.BackBufferWidth = SCREEN_WIDTH;							// ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;							// ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = d3ddm.Format;							// カラーモードの指定
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;						// 映像信号に同期してフリップする
	d3dpp.EnableAutoDepthStencil = TRUE;							// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;						// デプスバッファとして16bitを使う
	d3dpp.Windowed = bWindow;										// ウィンドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		// インターバル

	// デバイスの生成
	// ディスプレイアダプタを表すためのデバイスを作成
	// 描画と頂点処理をハードウェアで行なう
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &m_pD3DDevice)))
	{
		// 上記の設定が失敗したら
		// 描画をハードウェアで行い、頂点処理はCPUで行なう
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &m_pD3DDevice)))
		{
			// 上記の設定が失敗したら
			// 描画と頂点処理をCPUで行なう
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF, hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp, &m_pD3DDevice)))
			{
				// 生成失敗
				return E_FAIL;
			}
		}
	}

	// レンダーステートの設定
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);			// カリングを行わない
	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);					// Zバッファを使用
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);			// αブレンドを行う
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);	// αソースカラーの指定
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);// αデスティネーションカラーの指定																			

	// サンプラーステートの設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);// テクスチャアドレッシング方法(U値)を設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);// テクスチャアドレッシング方法(V値)を設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR); // テクスチャ縮小フィルタモードを設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR); // テクスチャ拡大フィルタモードを設定

	// テクスチャステージステートの設定
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	// 情報表示用フォントの生成
	D3DXCreateFont(m_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);

	// 情報表示用フォントの生成
	D3DXCreateFont(m_pD3DDevice, 20, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pUiFont);

	return S_OK;

}	// 初期化処理終了



//=============================================================================
// 終了処理
//=============================================================================
void CRenderer::Uninit(void)
{
	// UI関係用のフォントの破棄
	if (m_pUiFont != NULL)
	{
		m_pUiFont->Release();
		m_pUiFont = NULL;
	}

	// 情報表示用フォントの破棄
	if (m_pFont != NULL)
	{
		m_pFont->Release();
		m_pFont = NULL;
	}

	// デバイスの破棄
	if (m_pD3DDevice != NULL)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;
	}

	// Direct3Dオブジェクトの破棄
	if (m_pD3D != NULL)
	{
		m_pD3D->Release();
		m_pD3D = NULL;
	}
}	// 終了処理終了


//=============================================================================
// 更新処理
//=============================================================================
void CRenderer::Update(void)
{
	// 表示切り替え
	ControlFont();

	// フォントの色切り替え
	ColorFont();

	//ポリゴンの更新処理
	CScene::UpdateAll();


}	// 更新処理終了


//=============================================================================
// 描画処理
//=============================================================================
void CRenderer::Draw(void)
{
	// バックバッファ＆Ｚバッファのクリア
	m_pD3DDevice->Clear(0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// Direct3Dによる描画の開始
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		CScene *pScene = NULL;

		//ポリゴンの描画処理
		pScene->DrawAll();

		// FPS表示
		DrawFPS();

		// UI情報の表示
		DrawUiInfo();
		DrawUiControl();

		// Direct3Dによる描画の終了
		m_pD3DDevice->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);

}	// 描画処理終了


//=============================================================================
// FPS表示
//=============================================================================
void CRenderer::DrawFPS(void)
{
	//FPSを取得
	int nCountFPS = GetFPS();

	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char str[256];
	
	wsprintf(&str[0], "FPS:%d\n", nCountFPS);
	
	// テキスト描画
	m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, m_FontCol);
}

//=============================================================================
// UIの情報表示
//=============================================================================
void CRenderer::DrawUiInfo(void)
{
	CManager *pManager = NULL;

	bool bUse = pManager->GetUi_manager()->GetUse();

	if (m_bUIFont)
	{
		if (bUse)
		{
			int nNumUI = pManager->GetUi_manager()->GetNumUI();

			D3DXVECTOR3 Pos = pManager->GetUi_manager()->GetUi(nNumUI)->GetPos();
			D3DXVECTOR2 Size = pManager->GetUi_manager()->GetUi(nNumUI)->GetSize();
			D3DXVECTOR3 Move = pManager->GetUi_manager()->GetUi(nNumUI)->GetMove();
			D3DXVECTOR3 Speed = pManager->GetUi_manager()->GetUi(nNumUI)->GetSpeed();
			bool bMove = pManager->GetUi_manager()->GetUi(nNumUI)->GetBoolMove();
			bool bSize = pManager->GetUi_manager()->GetUi(nNumUI)->GetBoolSize();
			bool bSpeed = pManager->GetUi_manager()->GetUi(nNumUI)->GetBoolSpeed();
			int nMax = pManager->GetUi_manager()->GetMax();

			int nDiff = LIMITUI - nMax;

			RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
			char str[512];

			int nNum = sprintf(&str[0], "\n位置:(X:%.1f,Y:%.1f,Z:%.1f)\n", Pos.x, Pos.y, Pos.z);
			nNum += sprintf(&str[nNum], "大きさ[幅：高さ]:(%.1f : %.1f)\n", Size.x, Size.y);
			nNum += sprintf(&str[nNum], "移動量:(X:%.1f,Y:%.1f,Z:%.1f)\n", Move.x, Move.y, Move.z);
			nNum += sprintf(&str[nNum], "移動量の加減値:(X:%.1f,Y:%.1f,Z:%.1f)\n", Speed.x, Speed.y, Speed.z);
			switch (bMove)
			{
			case false:
				nNum += sprintf(&str[nNum], "位置を変更:できない\n");
				break;
			case true:
				nNum += sprintf(&str[nNum], "位置を変更:できる\n");
				break;
			}
			switch (bSize)
			{
			case false:
				nNum += sprintf(&str[nNum], "大きさを変更:できない\n");
				break;
			case true:
				nNum += sprintf(&str[nNum], "大きさを変更:できる\n");
				break;
			}
			switch (bSpeed)
			{
			case false:
				nNum += sprintf(&str[nNum], "移動量を変更:できない\n");
				break;
			case true:
				nNum += sprintf(&str[nNum], "移動量を変更:できる\n");
				break;
			}
			nNum += sprintf(&str[nNum], "現在の個数:(%d)\n", nNumUI);
			nNum += sprintf(&str[nNum], "現在の最大個数:(%d)\n", nMax);
			nNum += sprintf(&str[nNum], "限界個数までの個数:(%d)\n", nDiff);

			int nWarning = nNum;
			if (nDiff == 0)
			{
				nWarning += sprintf(&str[nWarning], "========================================\n");
				nWarning += sprintf(&str[nWarning], "      ※※もう増やせないよ！！※※\n");
				nWarning += sprintf(&str[nWarning], "========================================\n");
			}
			else
			{
				nWarning = 0;
			}

			// テキスト描画
			m_pUiFont->DrawText(NULL, str, -1, &rect, DT_LEFT, m_FontCol);
		}
	}
}

//=============================================================================
// 操作方法表示
//=============================================================================
void CRenderer::DrawUiControl(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char str[1024];

	int nNum = sprintf(&str[0], "UIの操作方法を表示するorしない[1]\n");	

	if (m_bUIControl)
	{
		nNum += sprintf(&str[nNum], "==========================================UIの操作方法============================================\n");
		nNum += sprintf(&str[nNum], "位置の移動([W][A][S][D])\n");
		nNum += sprintf(&str[nNum], "大きさの変更([Q][E][Z][C])\n");
		nNum += sprintf(&str[nNum], "移動量の変更(Xを大きく[F] Xを小さく[H] Yを大きく[T] Yを小さく[G])\n");
		nNum += sprintf(&str[nNum], "移動量の加減値を変更(Xの加減値を0.1に[R] Xの加減値を1.0に[Y] Yの加減値を0.1に[V] Yの加減値を1.0に[N])\n");
		nNum += sprintf(&str[nNum], "位置を変更できるようにするかしないか:[0]\n");
		nNum += sprintf(&str[nNum], "大きさを変更できるようにするかしないか:[9]\n");
		nNum += sprintf(&str[nNum], "移動量を変更できるようにするかしないか:[8]\n");
		nNum += sprintf(&str[nNum], "アニメーションのUIにするかしないか:[7]\n");
		nNum += sprintf(&str[nNum], "最大数の増減(増やす:[←] 減らす:[→])\n");
		nNum += sprintf(&str[nNum], "位置と大きさの初期化:[SPACE]\n");
		nNum += sprintf(&str[nNum], "移動量の初期化:[X]\n");
		nNum += sprintf(&str[nNum], "UIを配置:[ENTER]\n");
		nNum += sprintf(&str[nNum], "UI配置の書き出し:[F9]\n");
		nNum += sprintf(&str[nNum], "UI配置の読み込み:[F8]\n");
		nNum += sprintf(&str[nNum], "現在操作中のUiを読み込んだ位置と大きさで配置:[F7]\n");
		nNum += sprintf(&str[nNum], "すべてのUiを読み込んだ位置と大きさで配置:[F6]\n");
	}
	nNum += sprintf(&str[nNum], "========================================\n");
	nNum += sprintf(&str[nNum], "UIの書き込みファイル:%s\n", SETUITEXT);
	nNum += sprintf(&str[nNum], "========================================\n");
	nNum += sprintf(&str[nNum], "フォントの色の変更:[U][J]\n");

	// テキスト描画
	m_pUiFont->DrawText(NULL, str, -1, &rect, DT_RIGHT, m_FontCol);
}

//=============================================================================
// 操作方法表示の設定
//=============================================================================
void CRenderer::ControlFont(void)
{
	// 1を押したら
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_1) == true)
	{
		switch (m_bUIControl)
		{
		case true:
			m_bUIControl = false;
			break;
		case false:
			m_bUIControl = true;
			break;
		}
	}
	// 2を押したら
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_2) == true)
	{
		switch (m_bUIFont)
		{
		case true:
			m_bUIFont = false;
			break;
		case false:
			m_bUIFont = true;
			break;
		}
	}
}

//=============================================================================
// フォントの色の切り替え処理
//=============================================================================
void CRenderer::ColorFont(void)
{
	//-----------------------------------------------------------------------------
	// 色の変更
	//-----------------------------------------------------------------------------
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_U) == true)
	{
		m_FontColType++;
		if (m_FontColType > FontCol_NONE)
		{
			m_FontColType = FontCol_WHITE;
		}
	}
	else if (CManager::GetInputKeyboard()->GetTrigger(DIK_J) == true)
	{
		m_FontColType--;
		if (m_FontColType < FontCol_WHITE)
		{
			m_FontColType = FontCol_NONE;
		}
	}

	//-----------------------------------------------------------------------------
	// 色の切り替え
	//-----------------------------------------------------------------------------
	switch (m_FontColType)
	{
	case FontCol_WHITE:
		m_FontCol = D3DXCOLOR(255, 255, 255, 255);
		break;
	case FontCol_RED:
		m_FontCol = D3DXCOLOR(255, 0, 0, 255);
		break;

	case FontCol_GREEN:
		m_FontCol = D3DXCOLOR(0, 255, 0, 255);
		break;

	case FontCol_BLUE:
		m_FontCol = D3DXCOLOR(0, 0, 255, 255);
		break;

	case FontCol_YELLOW:
		m_FontCol = D3DXCOLOR(255, 255, 0, 255);
		break;

	case FontCol_PURPLE:
		m_FontCol = D3DXCOLOR(255, 0, 255, 255);
		break;

	case FontCol_LIGHT_BLUE:
		m_FontCol = D3DXCOLOR(0, 255, 255, 255);
		break;
		
	case FontCol_BLACK:
		m_FontCol = D3DXCOLOR(0, 0, 0, 255);
		break;

	case FontCol_NONE:
		m_FontCol = D3DXCOLOR(0, 0, 0, 0);
		break;

	default:
		break;
	}
}