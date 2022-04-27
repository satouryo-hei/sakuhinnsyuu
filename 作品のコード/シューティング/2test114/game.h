//=============================================================================
//
// ゲームの処理 [game.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "scene.h"
//=============================================================================
// 前方宣言
//=============================================================================
class CBg;
class CPlayer;
class CEnemy;
class CScore;
class CLife;
class CTimer;
class CEnemy_Doragonfly;
class CEnemy_manager;
class CRanking;
class CUi;

//*****************************************************************************
// ゲームのクラス
//*****************************************************************************
class CGame : public CScene
{
public:
	CGame();																	// コンストラクタ
	~CGame();																	// デストラクタ

																				// メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);							// タイトルの初期化関数
	void Uninit(void);															// タイトルの終了関数　
	void Update(void);															// タイトルの更新関数
	void Draw(void);															// タイトルの描画関数

	static CBg*GetBg(void) { return m_pBg; }									// 背景の取得処理
	static CPlayer*GetPlayer(void) { return m_pPlayer; }						// プレイヤーの取得処理
	static CEnemy*GetEnemy(void) { return m_pEnemy; }							// 敵の取得処理
	static CScore*GetScore(void) { return m_pScore; }							// スコアの取得処理
	static CLife*GetLife(void) { return m_pLife; }								// 体力の取得処理
	static CTimer*GetTimer(void) { return m_pTimer; }
	static CEnemy_Doragonfly*GetEnemy_Doragonfly(void) { return m_pEmemy_Doragonfly; }
	static CUi*GetUI(void) { return m_pUi; }
	CEnemy_manager*GetEnemy_Manager(void) { return m_pEmemy_Manager; }
	static bool GetRanking(void) { return m_bRanking; }


private:																		// 自分だけがアクセス可能
	static CBg *m_pBg;															// 背景のポインター
	static CPlayer *m_pPlayer;													// プレイヤーのポインター
	static CEnemy*m_pEnemy;														// 敵のポインター
	static CScore*m_pScore;														// スコアのポインター
	static CLife*m_pLife;														// 体力のポインター
	static CTimer*m_pTimer;
	static CEnemy_Doragonfly*m_pEmemy_Doragonfly;
	static CUi * m_pUi;
	CEnemy_manager*m_pEmemy_Manager;
	static bool m_bRanking;
	bool m_bNextMode;
};
#endif