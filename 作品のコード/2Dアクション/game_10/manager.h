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
		MODE_INVALID = -1,														// 無し
		MODE_TITLE = 0,															// タイトル
		MODE_TUTORIAL,															// チュートリアル
		MODE_SELECT,															// 選択
		MODE_GAME,																// ゲーム
		MODE_RESULT,															// リザルト
		MODE_MAX																// モードの全種類
	} MODE;

	CManager();																	// コンストラクタ
	~CManager();																// デストラクタ
																				// メンバ関数
	HRESULT Init(HINSTANCE hInstance,HWND hWnd, bool bWindow);					// マネージャーの初期化関数
	void Uninit(void);															// マネージャーの終了関数　
	void Update(void);															// マネージャーの更新関数
	void Draw(void);															// マネージャーの描画関数
	static void SetMode(MODE mode);												// モードの設定処理
	static MODE GetMode(void) { return m_mode; }								// モードの取得処理
	static void ChangeMode(void);												// チェンジモードの処理
	
	static CRenderer*GetRenderer(void){ return m_pRenderer; }					// レンダラーのポインター取得処理
	static CInputKeyboard*GetInputKeyboard(void){ return m_pInputKeyboard; }	// キーボードのポインター取得処理
	static CCamera*GetCamera(void) { return m_pCamera; }						// カメラのポインター取得処理
	static CLight*GetLight(void) { return m_pLight[0]; }						// ライトのポインター取得処理
	static CTexture*GetTexture(void) { return m_pTexture; }						// テクスチャのポインター取得処理
	static CTitle*GetTitle(void) { return m_pTitle; }							// タイトルのポインター取得処理
	static CSelect*GetSelect(void) { return m_pSelect; }						// 選択のポインター取得処理	
	static CTutorial*GetTutorial(void) { return m_pTutorial; }					// チュートリアルのポインター取得処理	
	static CGame*GetGame(void) { return m_pGame; }								// ゲームのポインター取得処理
	static CResult*GetResult(void) { return m_pResult; }						// リザルトのポインター取得処理

private:																		// 自分だけがアクセス可能
	static CRenderer*m_pRenderer;												// インスタンス生成
	static CInputKeyboard*m_pInputKeyboard;										// キーボードのポインター生成
	static CCamera * m_pCamera;													// カメラのポインター生成
	static CLight * m_pLight[3];												// ライトのポインター生成
	static CTexture * m_pTexture;												// テクスチャのポインター生成
	static CTitle * m_pTitle;													// タイトルのポインター生成
	static CSelect * m_pSelect;													// 選択画面のポインター生成
	static CTutorial*m_pTutorial;												// チュートリアルのポインター生成	
	static CGame * m_pGame;														// ゲームのポインター生成
	static CResult * m_pResult;													// リザルトのポインター生成
	static MODE m_mode;															// モードのポインター生成
	static MODE m_Nextmode;														// 次のモードのポインター生成
	static CFade * m_pFade;														// フェードのポインター生成
};

#endif
