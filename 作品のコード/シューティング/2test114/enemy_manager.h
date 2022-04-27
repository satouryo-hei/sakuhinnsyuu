//=============================================================================
//
// 敵の処理 [enemy_manager.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _ENEMY_MANAGER_H_
#define _ENEMY_MANAGER_H_

/*
ランキング実装するならカウントupにしてる時間ースコアでランキングを計算する

順位はバブルソートなどで探して順位付けをするか
上から探していって同じスコアじゃなかったら順位付けをするみたいな処理
別のファイルで順位付けをしてそれを読み込むのもあり
*/

#include"main.h"
//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CEnemy;
class CEnemy_Doragonfly;
class CTimer;
//*****************************************************************************
// 敵マネージャークラス（敵管理クラス
//*****************************************************************************
class CEnemy_manager
{
public:																				// 誰でもアクセス可能
																					//カットインの状態
	typedef enum
	{
		ENEMY_NONE = 0,																//設置型の敵(蜘蛛)
		ENEMY_DORAGONFLY,															//敵(トンボ)
		ENEMY_MAX
	} ENEMY;

	CEnemy_manager();																// コンストラクタ
	~CEnemy_manager();																	// デストラクタ

	// メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);				// 敵の初期化関数
	void Uninit(void);																// 敵の終了関数
	void Update(void);																// 敵の更新関数
	void Draw(void);																// 敵の描画関数

private:																			// 自分だけがアクセス可能
	CEnemy*m_pEnemy;
	CEnemy_Doragonfly*m_pEmemy_Doragonfly;
	static int m_nNowTimer;
	char m_Name[256];
	char m_Data[256];
	int m_GetTime[128];
	int m_GetEnemyType;
	int m_nCntTime;
	int m_nCoolTime;
};

#endif