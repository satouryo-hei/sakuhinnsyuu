//=============================================================================
//
// メイン処理 [main.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#define DIRECTINPUT_VERSION (0x0800)	//ビルド時警告対処理用マクロ
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include<WinSock2.h>
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "d3dx9.h"
#include<stdio.h>
#include<stdlib.h>
#include "dinput.h"						//入力処理に必要
#include "xaudio2.h"
#include<time.h>
//#include<thread>

//*****************************************************************************
// ライブラリファイルのリンク
//*****************************************************************************
#pragma comment(lib,"d3d9.lib")			//描画に必要
#pragma comment(lib,"d3dx9.lib")		//[d3d9.lib]の拡張ライブラリ
#pragma comment(lib,"dxguid.lib")		//DirectXコンポーネント使用に必要
#pragma comment(lib,"dinput8.lib")		//入力処理に必要
#pragma comment(lib,"winmm.lib")		
#pragma comment(lib,"ws2_32.lib")
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SCREEN_WIDTH (1280)				//ウィンドウの幅  
#define SCREEN_HEIGHT (720)				//ウィンドウの高さ
#define ID_TIMER		(121)			//タイマーのID
#define TIMER_INTERVAL	(1000/60)		//タイマーの発生間隔(ミリ秒) (1000000/60)(マイクロ秒)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
int GetFPS(void);						// FPS表示処理

//加算処理
template<class T, class P> T add(T data0, P data1)
{
	T answer;
	answer = data0 + data1;
	return answer;
}

//入れ替え処理
template<class T> void swap(T &data0, T &data1)
{
	T dataWk;
	dataWk = data0;
	data0 = data1;
	data1 = dataWk;
}
#endif