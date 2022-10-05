//=============================================================================
//
// ゲームの処理 [game.h]
// Author : 佐藤瞭平
// Author : 青木睦浩
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "scene.h"
//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CBg;
class CPlayer;
class CEnemy;
class CScore;
class CTimer;
class CBulletui;

//*****************************************************************************
// ゲームのクラス
//*****************************************************************************
class CGame : public CScene
{
public:
	CGame(int nPriority = PRIORITY_NOMAL);										// コンストラクタ
	~CGame();																	// デストラクタ

																				// メンバ関数
	HRESULT Init(D3DXVECTOR3 pos);												// ゲームの初期化関数
	void Uninit(void);															// ゲームの終了関数　
	void Update(void);															// ゲームの更新関数
	void Draw(void);															// ゲームの描画関数
	static CBg*GetBg(void) { return m_pBg; }									// 背景の取得処理
	static CEnemy*GetEnemy(int nNum) { return m_pEnemy[nNum]; }									// 背景の取得処理
	static CScore*GetScore(void) { return m_pScore; }

private:																		// 自分だけがアクセス可能		
	static CBg *m_pBg;															// 背景のポインター
	static CPlayer * m_pPlayer;													// プレイヤーのポインター
	static CEnemy *m_pEnemy[10];													// エネミーのポインター
	static CScore * m_pScore;													// 点数のポインター	
	static CTimer* m_pTimer;													// タイマーのポインター
	static CBulletui* m_pBulletui;													// タイマーのポインター
	bool m_bFade;																// 遷移したかどうか
	int m_nSpawn;
};
#endif
