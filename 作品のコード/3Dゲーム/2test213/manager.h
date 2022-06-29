//=============================================================================
//
// 管理処理 [manager.h]
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
class CCamera;
class CLight;
class CTexture;
class CTitle;
class CTutorial;
class CSelect;
class CGame;
class CResult;
class CFade;
//*****************************************************************************
// マネージャークラス
//*****************************************************************************
class CManager
{
public:
	// モードの種類
	typedef enum
	{
		MODE_INVALID = -1,
		MODE_TITLE = 0,
		MODE_SELECT,
		MODE_TUTORIAL,
		MODE_GAME,
		MODE_RESULT,
		MODE_MAX
	} MODE;

	CManager();																	// コンストラクタ
	~CManager();																// デストラクタ
																				// メンバ関数
	HRESULT Init(HINSTANCE hInstance,HWND hWnd, bool bWindow);					// 初期化関数
	void Uninit(void);															// 終了関数　
	void Update(void);															// 更新関数
	void Draw(void);															// 描画関数
	static void SetMode(MODE mode);												// モード設定関数
	static MODE GetMode(void) { return m_mode; }								// モードの取得関数
	static void ChangeMode(void);
	
	static CRenderer*GetRenderer(void){ return m_pRenderer; }					// レンダラーの取得
	static CInputKeyboard*GetInputKeyboard(void){ return m_pInputKeyboard; }	// キーボードの取得
	static CCamera*GetCamera(void) { return m_pCamera; }						// カメラの取得
	static CLight*GetLight(void) { return m_pLight[0]; }						// ライトの取得
	static CTexture*GetTexture(void) { return m_pTexture; }						// テクスチャの取得
	static CTitle*GetTitle(void) { return m_pTitle; }							// タイトルの取得
	static CTutorial*GetTutorial(void) { return m_pTutorial; }					// チュートリアルの取得
	static CSelect*GetSelect(void) { return m_pSelect; }						// 選択の取得
	static CGame*GetGame(void) { return m_pGame; }								// ゲームの取得
	static CResult*GetResult(void) { return m_pResult; }						// リザルトの取得
	
private:																		// 自分だけがアクセス可能
	static CRenderer*m_pRenderer;												// レンダラーのポインターを生成
	static CInputKeyboard*m_pInputKeyboard;										// キーボードのポインターを生成
	static CCamera * m_pCamera;													// カメラのポインターを生成
	static CLight * m_pLight[3];												// ライトのポインターを生成
	static CTexture * m_pTexture;												// テクスチャのポインターを生成
	static CTitle * m_pTitle;													// タイトルのポインターを生成
	static CTutorial * m_pTutorial;												// チュートリアルのポインターを生成
	static CSelect * m_pSelect;													// チュートリアルの取得
	static CGame * m_pGame;														// ゲームのポインターを生成
	static CResult * m_pResult;													// リザルトポインターを生成
	static MODE m_mode;															// モードのインスタンス生成
	static MODE m_Nextmode;														// 次のモードのインスタンス生成
	static CFade * m_pFade;														// フェードのポインターを生成
};
#endif
