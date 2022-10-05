//=============================================================================
//
// チュートリアルの処理 [title.h]
// Author : 佐藤瞭平
// Author : 青木睦浩
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "scene.h"
//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CBg;
class CLogo;
class CNextBotton;
//*****************************************************************************
// タイトルのクラス
//*****************************************************************************
class CTutorial : public CScene
{
public:
	CTutorial(int nPriority = PRIORITY_NOMAL);										// コンストラクタ
	~CTutorial();																	// デストラクタ

																				// メンバ関数
	HRESULT Init(D3DXVECTOR3 pos);												// タイトルの初期化関数
	void Uninit(void);															// タイトルの終了関数　
	void Update(void);															// タイトルの更新関数
	void Draw(void);															// タイトルの描画関数


private:																		// 自分だけがアクセス可能		
	static CBg * m_pBg;
	static CLogo * m_pLogo;														// ロゴのポインター生成
	static CNextBotton * m_pNextBotton;											// 次のボタンのUIのポインター生成
	bool m_bFade;																// 遷移したかどうか
};

#endif