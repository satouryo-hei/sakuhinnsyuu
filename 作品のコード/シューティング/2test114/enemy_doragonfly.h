//=============================================================================
//
// 敵の処理 [enemy_doragonfly.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _ENEMY_DORAGONFLY_H_
#define _ENEMY_DORAGONFLY_H_

#include"enemy.h"

//*****************************************************************************
// 敵のクラス
//*****************************************************************************
class CEnemy_Doragonfly : public CEnemy
{
public:																						// 誰でもアクセス可能
	CEnemy_Doragonfly(int nPriority = PRIORITY_PLAYER);										// コンストラクタ
	~CEnemy_Doragonfly();																	// デストラクタ
																							// メンバ関数
	static CEnemy_Doragonfly *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size);	// プレイヤの生成
	static HRESULT Load(void);																// テクスチャの読み込む
	static void Unload(void);																// テクスチャの破棄
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size);						// 敵の初期化関数
	void Uninit(void);																		// 敵の終了関数
	void Update(void);																		// 敵の更新関数
	void Draw(void);																		// 敵の描画関数
	void SetAnimesion(int nPatternAnim, float fSizeAnimU, float fSizeMinV, float fSizeMaxV);// 敵のアニメーション設定関数

private:																					// 自分だけがアクセス可能				
	static LPDIRECT3DTEXTURE9 m_pTexture;													// テクスチャへのポインタ
	D3DXVECTOR3 m_pos;																		// トンボの現在の位置
	D3DXVECTOR3 m_Move;																		// 敵の移動量
	D3DXVECTOR2 m_Size;																		// 敵の大きさ
	D3DXVECTOR3 m_Playerpos;																// プレイヤーの現在
	float m_fRange;																			// 敵とプレイヤーの距離
	bool m_bUse;																			// 敵が画面内にいるかどうか
	int m_nCounterAnim;																		// アニメーションカウンタ
	int m_nPatternAnim;																		// アニメーションパターンNo
	float m_fSizeAnimU;																		// アニメーションテクスチャの横サイズ
	float m_fSizeMinV;																		// アニメーションの縦の最小サイズ
	float m_fSizeMaxV;																		// アニメーションの縦の最大サイズ
	bool m_bAimPlayer;																		// 敵がプレイヤーをねらっているかどうか
};																							
#endif