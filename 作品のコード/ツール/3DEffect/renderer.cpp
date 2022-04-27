//=============================================================================
//
// メイン処理 [renderer.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include"renderer.h"
#include"scene.h"
#include"manager.h"
#include"camera.h"
#include"effect_manager.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CRenderer::CRenderer()
{
	m_pD3D = NULL;
	m_pD3DDevice = NULL;
	m_pFont = NULL;
	m_pEffectInfoFont = NULL;
	m_nNumFont = 0;
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

	// デバッグ情報表示用フォントの生成
	D3DXCreateFont(m_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);

	// エフェクトの情報表示用フォントの生成
	D3DXCreateFont(m_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pEffectInfoFont);
	return S_OK;

}	// 初期化処理終了



	//=============================================================================
	// 終了処理
	//=============================================================================
void CRenderer::Uninit(void)
{

	// デバッグ情報表示用フォントの破棄
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
	CScene *pScene = NULL;

	//ポリゴンの更新処理
	pScene->UpdateAll();

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

		// エフェクトの情報表示
		Effectinfo();
		
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
	CManager *pManager = NULL;
	//FPSを取得
	int nCountFPS = GetFPS();

	D3DXVECTOR3 PosV = pManager->GetCamera()->GetPosV();
	D3DXVECTOR3 PosR= pManager->GetCamera()->GetPosR();
	D3DXVECTOR3 rot = pManager->GetCamera()->GetRot();


	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char str[256];

	int nNum = wsprintf(&str[0], "FPS:%d\n", nCountFPS);
	nNum += sprintf(&str[nNum], "カメラの視点:%.1f,%.1f,%.1f\n", PosV.x, PosV.y, PosV.z);
	nNum += sprintf(&str[nNum], "カメラの注視点:%.1f,%.1f,%.1f\n", PosR.x, PosR.y, PosR.z);
	nNum += sprintf(&str[nNum], "カメラの回転量:%.2f,%.2f,%.2f\n", rot.x, rot.y, rot.z);

	m_nNumFont = nNum;

	// テキスト描画
	m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

}

//=============================================================================
// エフェクトの情報表示処理
//=============================================================================
void CRenderer::Effectinfo(void)
{

	CManager *pManager = NULL;

	D3DXVECTOR3 pos = pManager->GetEffectManager()->GetPos();
	D3DXVECTOR3 move = pManager->GetEffectManager()->GetMove();
	D3DXVECTOR3 addmove = pManager->GetEffectManager()->GetAddMove();
	D3DXVECTOR3 Size = pManager->GetEffectManager()->GetSize();
	D3DXVECTOR3 AddSize = pManager->GetEffectManager()->GetAddSize();
	D3DXCOLOR col = pManager->GetEffectManager()->GetCol();
	D3DXCOLOR AddCol = pManager->GetEffectManager()->GetAddCol();
	int nLife = pManager->GetEffectManager()->GetLife();			
	int nDensity = pManager->GetEffectManager()->GetDensity();
	int nRadius = pManager->GetEffectManager()->GetRadius();
	int nType = pManager->GetEffectManager()->GetEffectType();
	int nColor = pManager->GetEffectManager()->GetColorType();
	int nVerType = pManager->GetEffectManager()->GetVectorType();

	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char str[1024];

	int nNum = 0;
	nNum += sprintf(&str[nNum], "現在の位置の値[X,Y,Z]:%.2f,%.2f,%.2f\n", pos.x, pos.y, pos.z);
	nNum += sprintf(&str[nNum], "移動量の値[X,Y,Z]:%.2f,%.2f,%.2f\n", move.x, move.y, move.z);
	nNum += sprintf(&str[nNum], "移動量の減算値[X,Y,Z]:%.2f,%.2f,%.2f\n", addmove.x, addmove.y, addmove.z);
	nNum += sprintf(&str[nNum], "大きさの値[X,Y,Z]:%.2f,%.2f,%.2f\n", Size.x, Size.y, Size.z);
	nNum += sprintf(&str[nNum], "大きさの減算値[X,Y,Z]:%.2f,%.2f,%.2f\n", AddSize.x, AddSize.y, AddSize.z);
	nNum += sprintf(&str[nNum], "色の値[R,G,B,A]:%.2f,%.2f,%.2f,%.2f\n", col.r, col.g, col.b, col.a);
	nNum += sprintf(&str[nNum], "色の減算値[R,G,B,A]:%.2f,%.2f,%.2f,%.2f\n", AddCol.r, AddCol.g, AddCol.b, AddCol.a);
	nNum += sprintf(&str[nNum], "寿命:%d\n", nLife);
	nNum += sprintf(&str[nNum], "密度:%d\n", nDensity);

	switch (nType)
	{
	case CEffect_Manager::EffectType_STRAIGHT:
		nNum += sprintf(&str[nNum], "エフェクトの種類:ストレート\n");
		break;
	case CEffect_Manager::EffectType_CIRCLE:
		nNum += sprintf(&str[nNum], "半径:%d\n", nRadius);
		nNum += sprintf(&str[nNum], "エフェクトの種類:円形\n");
		break;
	case CEffect_Manager::EffectType_EXPLOSIN:
		nNum += sprintf(&str[nNum], "エフェクトの種類:爆発\n");
		break;
	case CEffect_Manager::EffectType_DOME:
		nNum += sprintf(&str[nNum], "半径:%d\n", nRadius);
		nNum += sprintf(&str[nNum], "エフェクトの種類:ドーム型\n");
		break;
	case CEffect_Manager::EffectType_WATER_CREST:
		nNum += sprintf(&str[nNum], "半径:%d\n", nRadius);
		nNum += sprintf(&str[nNum], "エフェクトの種類:波紋\n");
		break;
	case CEffect_Manager::EffectType_SMOKE:
		nNum += sprintf(&str[nNum], "半径:%d\n", nRadius);
		nNum += sprintf(&str[nNum], "エフェクトの種類:煙\n");
		break;
	case CEffect_Manager::EffectType_LANDING:
		nNum += sprintf(&str[nNum], "半径:%d\n", nRadius);
		nNum += sprintf(&str[nNum], "エフェクトの種類:着地\n");
		break;
	default:
		nNum += sprintf(&str[nNum], "エフェクトの種類:なし\n");
		break;
	}

	switch (nColor)
	{
	case CEffect_Manager::ColorType_RED:
		nNum += sprintf(&str[nNum], "色:赤\n");
		break;
	case CEffect_Manager::ColorType_GREEN:
		nNum += sprintf(&str[nNum], "色:緑\n");
		break;
	case CEffect_Manager::ColorType_BLUE:
		nNum += sprintf(&str[nNum], "色:青\n");
		break;
	case CEffect_Manager::ColorType_ARUFA:
		nNum += sprintf(&str[nNum], "色:透明度\n");
		break;	
	default:	
		break;
	}

	switch (nVerType)
	{
	case CEffect_Manager::Vector_X:
		nNum += sprintf(&str[nNum], "今のベクトル:X\n");
		break;
	case CEffect_Manager::Vector_Y:
		nNum += sprintf(&str[nNum], "今のベクトル:Y\n");
		break;
	case CEffect_Manager::Vector_Z:
		nNum += sprintf(&str[nNum], "今のベクトル:Z\n");
		break;
	default:
		break;
	}

	// テキスト描画
	m_pEffectInfoFont->DrawText(NULL, str, -1, &rect, DT_RIGHT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}