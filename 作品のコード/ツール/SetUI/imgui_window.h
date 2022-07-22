//=============================================================================
//
// IMGUIのウィンドウ設定の処理 [imgui_window.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _IMGUI_WINDOW_H_
#define _IMGUI_WINDOW_H_
#include"main.h"

//*****************************************************************************
// IMGUIのウィンドウクラス
//*****************************************************************************
class CImgui_Window
{
public:

	CImgui_Window();									// IMGUIのウィンドウのコンストラクタ
	~CImgui_Window();									// IMGUIのウィンドウのデストラクタ
	// メンバ関数
	HRESULT Init(HWND hWnd, bool bWindow);				// IMGUIのウィンドウの初期化関数
	void Uninit(void);									// IMGUIのウィンドウの終了関数　
	void Update(void);									// IMGUIのウィンドウの更新関数
	void Draw(void);									// IMGUIのウィンドウの描画関数
};
#endif