//=============================================================================
//
// ゲームの選択処理 [choose_game.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _CHOOSE_GAME_H_
#define _CHOOSE_GAME_H_

#include"scene.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CPolygon;
class CEffect;

//*****************************************************************************
// ゲームの選択クラス
//*****************************************************************************
class CChoose_Game : public CScene
{
public:																// 誰でもアクセス可能
	// ゲームの選択種類
	typedef enum 
	{
		CHOOSE_NEWGAME = 0,
		CHOOSE_CONTINUE,
		CHOOSE_TUTORIAL,
		CHOOSE_RESULT,
		CHOOSE_MAX
	} CHOOSE;

	CChoose_Game(PRIORITY Priority = PRIORITY_UI);				// コンストラクタ
	~CChoose_Game();												// デストラクタ
	// メンバ関数
	static CChoose_Game *Create(D3DXVECTOR3 pos);					// ゲームの選択の生成
	HRESULT Init(D3DXVECTOR3 pos);									// ゲームの選択の初期化関数
	void Uninit(void);												// ゲームの選択の終了関数
	void Update(void);												// ゲームの選択の更新関数
	void Draw(void);												// ゲームの選択の描画関数
	static bool GetNewGame(void) { return m_bNewGame; }				// 新しく始めるかを取得
	void Resetcol(void);												// 色をリセット

private:															// 自分だけがアクセス可能
	inline void LodeChooseUI(void);									// UIの読み込み処理
	static const char * m_pChooseUiFile;							// 選択画面のUIファイル名
	static CPolygon * m_pPolygon[CHOOSE_MAX];						// ポリゴンの配列ポインターを生成
	static CEffect * m_pEffect;							// エフェクトの配列ポインターを生成
	static bool m_bNewGame;											// 新しく始めるかどうか
	const float m_fInterval;										// ポリゴンの間隔
	const D3DXCOLOR ResetCol;										// 初期値の色
	D3DXVECTOR3 m_LodePos[CHOOSE_MAX];								// uiの位置の読み込み
	D3DXVECTOR2 m_LodeSize[CHOOSE_MAX];								// uiの大きさの読み込み
	D3DXVECTOR2 m_Size;												// 大きさ
	int m_nLodeUI;													// uiの数の読み込み
	int m_nSituation;												// ゲームの選択状態遷移
	bool m_bFade;													// フェードさせたかどうか
	bool m_bEffectUse;												// エフェクトをしようしたかどうか

};
#endif