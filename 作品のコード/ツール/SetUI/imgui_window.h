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

	CImgui_Window();											// コンストラクタ
	~CImgui_Window();										// デストラクタ
															// メンバ関数
	HRESULT Init(HWND hWnd, bool bWindow);					// ポリゴンの初期化関数
	void Uninit(void);									// ポリゴンの終了関数　
	void Update(void);									// ポリゴンの更新関数
	void Draw(void);									// ポリゴンの描画関数
private:												// 自分だけがアクセス可能
	static bool m_bUseWindow;							// 使用しているかどうか
};
#endif