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
// 前方宣言
//*****************************************************************************
class CBullet;
//*****************************************************************************
// プレイヤークラス
//*****************************************************************************
class CPlayer : public CScene2D
{
public:																				// 誰でもアクセス可能
	CPlayer(int nPriority = PRIORITY_PLAYER);										// コンストラクタ
	~CPlayer();																		// デストラクタ
																					// メンバ関数
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size);	// プレイヤの生成
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);								// プレイヤの初期化関数
	void Uninit(void);																// プレイヤの終了関数
	void Update(void);																// プレイヤの更新関数
	void Draw(void);																// プレイヤの描画関数
	static D3DXVECTOR3 GetPos(void) { return m_pos; }								// 現在の位置の取得処理
	static void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }							// 現在の位置の設定処理
	static D3DXVECTOR2 GetSize(void) { return m_size; }								// 大きさの取得処理
	static D3DXVECTOR3 GetPosold(void) { return m_posold; }							// 前回の位置の取得処理
	static void SetUse(bool bUse) { m_bUse = bUse; }								// 弾のポインターの取得処理
	
private:																			// 自分だけがアクセス可能		
	static D3DXVECTOR3 m_pos;														// 現在の位置
	static D3DXVECTOR2 m_size;														// 大きさ
	static D3DXVECTOR3 m_posold;													// 前回の位置
	static D3DXVECTOR3 m_move;														// 移動量	
	static LPDIRECT3DTEXTURE9 m_pTexture;											// テクスチャへのポインタ
	int m_nTimer;																	// 時間
	int m_nCoolTime;																// クール時間
	bool m_bBullet;																	// 弾を打ったかどうか			
	static bool m_bUse;																// 使われているかどうか	
	static CBullet * m_pBullet;														// 弾のポインターの生成
};
#endif