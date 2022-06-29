//=============================================================================
//
// メイン処理 [main.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include "main.h"
#include"manager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CLASS_NAME		"AppClass"			// ウインドウのクラス名
#define WINDOW_NAME		"ポリゴンの描画"	// ウインドウのキャプション名

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//*****************************************************************************
// グローバル変数:
//*****************************************************************************
int						g_nCountFPS;			// FPSカウンタ
//=============================================================================
// メイン関数
//=============================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),				//WNDCLASSENのメモリサイズの指示
		CS_CLASSDC,						//表示するウィンドウのスタイルを設定
		WndProc,						//ウィンドウプロシージャのアドレス(関数名)を指定
		0,								//ふつう使わんから0を指定
		0,								//ふつう使わんから0を指定
		hInstance,						//Windowsの引数のインスタンスハンドルを指定
		NULL,							//タスクバーに使うアイコンを指定
		LoadCursor(NULL, IDC_ARROW),	//使うマウスカーソルを指定
		(HBRUSH)(COLOR_WINDOW + 1),		//ウィンドウのクライアント領域の背景色を指定
		NULL,							//Windowにつけるメニューを設定
		CLASS_NAME,						//ウィンドウクラスの名前
		NULL							//ファイルアイコンに使うアイコンを設定
	};

	//変数宣言
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	HWND hWnd;		//ウィンドウハンドル
	MSG msg;		//メッセージを格納する変数
	DWORD dwCurrentTime;
	DWORD dwFrameCount;
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;

	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	// 指定したクライアント領域を確保するために必要なウィンドウ座標を計算
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	// ウィンドウの作成（作ったウィンドウをウィンドウハンドルに納めて管理する）
	hWnd = CreateWindow(CLASS_NAME,					//拡張ウィンドウスタイル
		WINDOW_NAME,				//ウィンドウクラスの名前
		WS_OVERLAPPEDWINDOW,		//ウィンドウの名前
		CW_USEDEFAULT,				//ウィンドウスタイル
		CW_USEDEFAULT,				//ウィンドウの左上のＸ座標
		(rect.right - rect.left),	//ウィンドウの左上のＹ座標
		(rect.bottom - rect.top),	//ウィンドウの幅
		NULL,						//ウィンドウの高さ
		NULL,						//親ウィンドウのハンドル
		hInstance,					//メニューウィンドウまたは子ウィンドウ
		NULL);						//インすタンスハンドル
									//ウィンドウ作成データ
									//動的メモリの確保
	CManager *pManager = NULL;

	pManager = new CManager;

	// 初期化処理
	if (FAILED(pManager->Init(hInstance,hWnd, true)))
	{
		return -1;
	}

	// 分解能を設定
	timeBeginPeriod(1);

	// フレームカウント初期化
	dwCurrentTime =
		dwFrameCount = 0;
	dwExecLastTime =
		dwFPSLastTime = timeGetTime();

	// ウインドウの表示
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{// PostQuitMessage()が呼ばれたらループ終了
				break;
			}
			else
			{
				// メッセージの翻訳とディスパッチ
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();	// 現在の時間を取得
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{// 0.5秒ごとに実行
#ifdef _DEBUG
			 // FPSを算出
				g_nCountFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);
#endif
				dwFPSLastTime = dwCurrentTime;	// 現在の時間を保存
				dwFrameCount = 0;
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{// 1/60秒経過
				dwExecLastTime = dwCurrentTime;	// 現在の時間を保存

				// 更新処理
				if (pManager != NULL)
				{
					pManager->Update();
				}

				if (pManager != NULL)
				{
					// 描画処理
					pManager->Draw();
				}
				dwFrameCount++;
			}
		}
	}

	if (pManager != NULL)
	{
		// 終了処理
		pManager->Uninit();
		//動的メモリの確保したものを解放
		delete pManager;
		pManager = NULL;
	}

	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// 分解能を戻す
	timeEndPeriod(1);

	return (int)msg.wParam;
}

//=============================================================================
// ウインドウプロシージャ
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:				// [ESC]キーが押された
			DestroyWindow(hWnd);	// ウィンドウを破棄するよう指示する
			break;
		}
		break;

	default:
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//=============================================================================
// FPS表示
//=============================================================================
int GetFPS(void)
{
	return g_nCountFPS;
}