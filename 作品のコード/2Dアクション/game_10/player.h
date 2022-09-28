//=============================================================================
//
// プレイヤーの処理 [player.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _PLATER_H_
#define _PLATER_H_

#include"scene2D.h"

#define ITEM_TEXT "data/TEXT/Item.txt"
#define MAX_BULLET (30)
//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CBullet;
class CHoming;
class CShotgun;
//*****************************************************************************
// プレイヤークラス
//*****************************************************************************
class CPlayer : public CScene2D
{
public:																				// 誰でもアクセス可能
	//プレイヤーの状態
	typedef enum
	{
		PLAYER_NOMAL = 0,															// 普通の状態
		PLAYER_DEATH,																// やられた状態
		PLAYER_RESTARE,																// 再スタート状態
		PLAYER_MAX																	// 状態の最大数
	} PLAYER;

	CPlayer(int nPriority = PRIORITY_PLAYER);										// コンストラクタ
	~CPlayer();																		// デストラクタ
																					// メンバ関数
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size);	// プレイヤの生成
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);								// プレイヤの初期化関数
	void Uninit(void);																// プレイヤの終了関数
	void Update(void);																// プレイヤの更新関数
	void Draw(void);																// プレイヤの描画関数
	void BlockColision(void);														// ブロックの当たり判定
	void PushColision(void);														// 押すブロックの当たり判定
	void MoveColision(void);														// 移動ブロックの当たり判定
	PLAYER GetPlayerType(void) { return m_Playertype; }								// プレイヤーの状態遷移
	static CBullet *GetBullet(void) { return m_pBullet; }							// 弾のポインターの取得処理
	static int GetItem(void) { return m_nItem; }									// アイテムのポインターの取得処理
	static void SetItem(int nItem) { m_nItem = nItem; }								// アイテムのポインターの設定処理
	static D3DXVECTOR3 GetPos(void) { return m_pos; }								// 現在の位置の取得処理
	static void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }							// 現在の位置の設定処理
	static D3DXVECTOR2 GetSize(void) { return m_size; }								// 大きさの取得処理
	static D3DXVECTOR3 GetPosold(void) { return m_posold; }							// 前回の位置の取得処理
	static D3DXVECTOR3 GetMove(void) { return m_move; }								// 移動量の取得処理
	static void SetMove(D3DXVECTOR3 move) { m_move = move; }						// 移動量の設定処理
	static bool GetJump(void) { return m_bJump; }									// ジャンプしたかどうかの取得処理
	static void SetJump(bool bJump) { m_bJump = bJump; }							// ジャンプしたかどうかの設定処理
	static void SetUse(bool bUse) { m_bUse = bUse; }								// 弾のポインターの取得処理
	
private:																			// 自分だけがアクセス可能
	void Shot(int nType, bool bMovetype);											// 弾の種類の関数
	void EnemyColision(void);														// 敵との当たり判定
	inline void SaveItem(void);													// ステータスの書き込み処理
	inline void LoadItem(void);													// ステータスの読み込み処理
	void SetAnimesion(int nPattern, float fSizeU, float fSizeMinV, float fSizeMaxV);// アニメーション処理関数

	// 弾の種類
	typedef enum
	{
		SHOTTYPE_NOMAL = 0,															// 普通の弾
		SHOTTYPE_HOMING,															// ホーミング弾
		SHOTTYPE_SHOTGUN,															// 散弾
		SHOTTYPE_MAX																// 全ての弾の種類
	} SHOTTYPE;
	static D3DXVECTOR3 m_pos;														// 現在の位置
	static D3DXVECTOR2 m_size;														// 大きさ
	static D3DXVECTOR3 m_posold;													// 前回の位置
	static D3DXVECTOR3 m_move;														// 移動量
	float m_fQuickening;															// 加速量
	static float m_fGravity;														// 重力
	static LPDIRECT3DTEXTURE9 m_pTexture;											// テクスチャへのポインタ
	int m_nCounterAnim;																// アニメーションカウンタ
	int m_nPatternAnim;																// アニメーションパターンNo
	const float m_fSizeU;
	float m_fSizeMinV;
	float m_fSizeMaxV;
	int m_nTimer;																	// 時間
	int m_nCoolTime;																// クール時間
	bool m_bBullet;																	// 弾を打ったかどうか
	bool m_bDeath;																	// 前回倒れたかの判定
	PLAYER m_Playertype;															// プレイヤーの状態
	static CBullet * m_pBullet;														// 弾のポインターの生成
	static CHoming * m_pHoming[MAX_BULLET];											// ホーミング弾のポインターの生成
	static CShotgun * m_pShotgun;													// 散弾のポインター生成
	static int m_nItem;																// アイテムのポインター生成
	static bool m_bJump;															// ジャンプしたかどうか
	static bool m_bUse;																// 使われているかどうか
	bool m_bMovePush;																// 移動した向き
	int m_nBulletType;																// 弾の種類
	int m_nAttack;
};
#endif