//=============================================================================
//
// ゲームの処理 [game.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "scene.h"
//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CBg;
class CTimer;
class CPlayer;
class CItem;
class CMeshField;
class CMeshSky;
class CWall;
class CStage_Top;
class CEnemy02;
class CGoal;
class CScore;
class CKeyui;

//*****************************************************************************
// ゲームのクラス
//*****************************************************************************
class CGame : public CScene
{
public:
	CGame(int nPriority = PRIORITY_NOMAL);																	// コンストラクタ
	~CGame();																	// デストラクタ

																				// メンバ関数
	HRESULT Init(D3DXVECTOR3 pos);												// ゲームの初期化関数
	void Uninit(void);															// ゲームの終了関数　
	void Update(void);															// ゲームの更新関数
	void Draw(void);															// ゲームの描画関数

	static CBg*GetBg(void) { return m_pBg; }									// 背景の取得処理
	static CTimer*GetTimer(void) { return m_pTimer; }							// タイマーの取得処理
	static CPlayer * GetPlayer(void) { return m_pPlayer; }
	static CMeshField*GetMeshField(void) { return m_pMeshField; }				// メッシュフィールドのポインターを取得
	static CMeshSky*GetMeshSky(void) { return m_pMeshSky; }						// 空のポインターを取得
	static CEnemy02*GetEnemy(void) { return m_pEnemy; }						// 空のポインターを取得
	static CScore*GetScore(void) { return m_pScore; }						// 空のポインターを取得


private:																		// 自分だけがアクセス可能		
	static CBg *m_pBg;															// 背景のポインター
	static CTimer* m_pTimer;													// タイマーのポインター
	static CPlayer* m_pPlayer;													// プレイヤーのポインター
	static CItem* m_pItem;											// 攻撃力アップのポインター
	static CMeshField * m_pMeshField;											// メッシュフィールドのポインター
	static CMeshSky * m_pMeshSky;												// 空のポインター
	static CWall * m_pWall;											// 壁のポインター
	static CStage_Top * m_pStage;											// ステージのポインター
	static CEnemy02* m_pEnemy;													// 敵のポインター
	static CGoal * m_pGoal;														// ゴールのポインター
	static CScore * m_pScore;														// ゴールのポインター	
	static CKeyui* m_pKeyui;														// ゴールのポインター	
	static bool m_bRanking;														// ランキングをさせるかどうか
	bool m_bUse;																// 使っているかどうか
	bool m_bFade;																// 遷移したかどうか
};
#endif