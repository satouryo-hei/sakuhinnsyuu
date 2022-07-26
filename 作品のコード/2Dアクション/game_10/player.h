//=============================================================================
//
// プレイヤーの処理 [player.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _PLATER_H_
#define _PLATER_H_

#include"scene2D.h"

#define STATUS_TEXT "data/TEXT/Status.txt"
#define MAX_BULLET (30)
//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CBullet;
class CHoming;
class CBullet03;
//*****************************************************************************
// プレイヤークラス
//*****************************************************************************
class CPlayer : public CScene2D
{
public:																// 誰でもアクセス可能
																	//プレイヤーの状態
	typedef enum
	{
		PLAYER_NOMAL = 0,
		PLAYER_DEATH,
		PLAYER_RESTARE,
		PLAYER_MAX
	} PLAYER;

	CPlayer(int nPriority = PRIORITY_PLAYER);										// コンストラクタ
	~CPlayer();														// デストラクタ
																	// メンバ関数
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size);		// プレイヤの生成
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);				// プレイヤの初期化関数
	void Uninit(void);												// プレイヤの終了関数
	void Update(void);												// プレイヤの更新関数
	void Draw(void);												// プレイヤの描画関数
	void BlockColision(void);										// ブロックの当たり判定
	void PushColision(void);										// ブロックの当たり判定
	void MoveColision(void);										// ブロックの当たり判定
	PLAYER GetPlayerType(void) { return m_Playertype; }
	static CBullet *GetBullet(void) { return m_pBullet; }												// プレイヤの描画関数
	static int GetItem(void) { return m_nItem; }
	static void SetItem(int nItem) { m_nItem = nItem; }
	static D3DXVECTOR3 GetPos(void) { return m_pos; }
	static void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	static D3DXVECTOR2 GetSize(void) { return m_size; }
	static D3DXVECTOR3 GetPosold(void) { return m_posold; }
	static D3DXVECTOR3 GetMove(void) { return m_move; }
	static void SetMove(D3DXVECTOR3 move) { m_move = move; }
	static bool GetJump(void) { return m_bJump; }
	static void SetJump(bool bJump) { m_bJump = bJump; }
	static void SetUse(bool bUse) { m_bUse = bUse; }
	
private:															// 自分だけがアクセス可能
	void Shot(int nType, bool bMovetype);
	inline void SaveStatus(void);
	inline void LoadStatus(void);

	typedef enum
	{
		SHOTTYPE_NOMAL = 0,
		SHOTTYPE_HOMING,		
		SHOTTYPE_SHOYGUN,
		SHOTTYPE_MAX
	} SHOTTYPE;
	static D3DXVECTOR3 m_pos;												// 移動量
	static D3DXVECTOR2 m_size;
	static D3DXVECTOR3 m_posold;												// 移動量
	static D3DXVECTOR3 m_move;												// 移動量
	static float m_fGravity;												// 移動量
	static LPDIRECT3DTEXTURE9 m_pTexture;							// テクスチャへのポインタ
	int m_nCounterAnim;												// アニメーションカウンタ
	int m_nPatternAnim;												// アニメーションパターンNo
	int m_nTimer;													// 時間
	int m_nCoolTime;												// クール時間
	bool m_bBullet;													// 弾を打ったかどうか
	bool m_bDeath;													// 前回倒れたかの判定
	PLAYER m_Playertype;											// プレイヤーの状態
	static CBullet * m_pBullet;										// 弾のポインターの生成
	static CHoming * m_pHoming[MAX_BULLET];							// 拡散弾のポインターの生成
	static CBullet03 * m_pBullet03;									// ホーミング弾のポインター生成
	static int m_nItem;												// アイテムのポインター生成
	static bool m_bJump;											// ジャンプしたかどうか
	static bool m_bUse;												// 使われているかどうか
	bool m_bMovePush;												// 移動した向き
	int m_nBulletType;												// 弾の種類
};
#endif