//=============================================================================
//
// プレイヤーの処理 [player.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _PLATER_H_
#define _PLATER_H_

#include"scene2D.h"

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
	static HRESULT Load(void);										// テクスチャの読み込む
	static void Unload(void);										// テクスチャの破棄
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size);				// プレイヤの初期化関数
	void Uninit(void);												// プレイヤの終了関数
	void Update(void);												// プレイヤの更新関数
	void Draw(void);												// プレイヤの描画関数
	PLAYER GetPlayerType(void) { return m_Playertype; }

private:															// 自分だけがアクセス可能
	D3DXVECTOR3 m_move;												// 移動量
	const float m_fSpeedMax;										// すばやさの最大値																	
	static LPDIRECT3DTEXTURE9 m_pTexture;							// テクスチャへのポインタ
	int m_nCounterAnim;												// アニメーションカウンタ
	int m_nPatternAnim;												// アニメーションパターンNo
	int m_nTimer;													// 弾を飛ばす時間
	bool m_bDeath;													// 前回倒れたかの判定
	PLAYER m_Playertype;											// プレイヤーの状態
};
#endif
