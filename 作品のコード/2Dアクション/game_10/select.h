//=============================================================================
//
// 選択画面の処理 [select.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _SELECT_H_
#define _SELECT_H_

#include "scene.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CBg;
class CChoose_Game;

//*****************************************************************************
// 選択画面のクラス
//*****************************************************************************
class CSelect : public CScene
{
public:
	CSelect(int nPriority = PRIORITY_NOMAL);									// コンストラクタ
	~CSelect();																	// デストラクタ

																				// メンバ関数
	HRESULT Init(D3DXVECTOR3 pos);												// 選択画面の初期化関数
	void Uninit(void);															// 選択画面の終了関数　
	void Update(void);															// 選択画面の更新関数
	void Draw(void);															// 選択画面の描画関数
	static CChoose_Game * GetChoose_Game(void) { return m_pChoose_Game; }		// ゲームの選択の取得処理

private:																		// 自分だけがアクセス可能
	static CBg * m_pBg;															// 背景のポインターの生成
	static CChoose_Game * m_pChoose_Game;										// ゲームの選択のポインターの生成
};
#endif