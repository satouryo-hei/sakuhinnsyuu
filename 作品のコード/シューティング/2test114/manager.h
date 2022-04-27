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
class CSound;			
class CTitle;
class CTutorial;
class CGame;
class CResult;
class CFade;
class CTexture;

//*****************************************************************************
// マネージャークラス
//*****************************************************************************
class CManager
{
public:

	typedef enum
	{
		MODE_INVALID = -1,
		MODE_TITLE = 0,
		MODE_TUTORIAL,
		MODE_GAME,
		MODE_RESULT,
		MODE_MAX
	} MODE;

	CManager();																	// コンストラクタ
	~CManager();																// デストラクタ
																				// メンバ関数
	HRESULT Init(HINSTANCE hInstance,HWND hWnd, bool bWindow);					// マネージャーの初期化関数
	void Uninit(void);															// マネージャーの終了関数　
	void Update(void);															// マネージャーの更新関数
	void Draw(void);															// マネージャーの描画関数
	static CRenderer*GetRenderer(void);											// CRendererクラスのポインタ
	static CInputKeyboard*GetInputKeyboard(void);								// キーボードクラスのポインタ
	static CSound*GetSound(void);												// 音クラスのポインタ
	static void SetMode(MODE mode);												// モードの配置処理
	static MODE GetMode(void) { return m_mode; }								// モードの取得処理
	static CFade* GetFade(void) { return m_pFade; };
	static CTexture* GetTexture(void) { return m_pTexture; };
	static void CManager::ChangeMode(void);

private:																		// 自分だけがアクセス可能
	static CRenderer*m_pRenderer;												// CRendererのインスタンス生成
	static CInputKeyboard*m_pInputKeyboard;										// キーボードのインスタンス生成
	static CSound*m_pSound;														// 音のインスタンス生成
	static CTitle*m_pTitle;														// タイトルのインスタンス生成
	static CTutorial*m_pTutorial;												// チュートリアルのインスタンス生成
	static CGame*m_pGame;														// ゲームのインスタンス生成
	static CResult*m_pResult;													// リザルトのインスタンス生成
	static MODE m_mode;															// モードのインスタンス生成
	static CFade * m_pFade;
	static CTexture * m_pTexture;
	static MODE m_Nextmode;
};
#endif
