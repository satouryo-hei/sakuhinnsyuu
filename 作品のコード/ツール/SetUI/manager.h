//=============================================================================
//
// マネージャー処理 [manager.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include"main.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CRenderer;		
class CInputKeyboard;	
class CUi;
class CUI_Manager;
class CTexture;
class CImgui_Window;

//*****************************************************************************
// マネージャークラス
//*****************************************************************************
class CManager
{
public:
	CManager();																	// コンストラクタ
	~CManager();																// デストラクタ
																				// メンバ関数
	HRESULT Init(HINSTANCE hInstance,HWND hWnd, bool bWindow);					// マネージャーの初期化関数
	void Uninit(void);															// マネージャーの終了関数　
	void Update(void);															// マネージャーの更新関数
	void Draw(void);															// マネージャーの描画関数
	static CRenderer*GetRenderer(void) { return m_pRenderer; }					// CRendererクラスのポインタ
	static CInputKeyboard*GetInputKeyboard(void) { return m_InputKeyboard; }	// キーボードクラスのポインタ
	static CUI_Manager*GetUi_manager(void) { return m_pUi_manager;}				// UIクラスの管理型のポインタ
	static CTexture *GetTexture(void) { return m_pTexture; }					// テクスチャクラスのポインタ
	static CImgui_Window* GetImguiWindow(void) { return m_pImguiWindow; }		// Imgui_Windowクラスのポインタ

private:																		// 自分だけがアクセス可能
																				// メンバ変数
	static CRenderer*m_pRenderer;												// CRendererのインスタンス生成
	static CInputKeyboard*m_InputKeyboard;										// キーボードのインスタンス生成
	static CUI_Manager*m_pUi_manager;											// UIクラスのインスタンス生成
	static CTexture * m_pTexture;												// テクスチャクラスのインスタンス生成
	static CImgui_Window* m_pImguiWindow;										// Imgui_Windowクラスのポインタ
};
#endif
