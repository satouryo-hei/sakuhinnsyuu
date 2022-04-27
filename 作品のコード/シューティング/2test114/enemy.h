//=============================================================================
//
// 敵の処理 [enemy.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include"scene2D.h"

//*****************************************************************************
// 敵のクラス
//*****************************************************************************
class CEnemy : public CScene2D
{
public:																				// 誰でもアクセス可能
	CEnemy(int nPriority = PRIORITY_PLAYER);										// コンストラクタ
	virtual ~CEnemy();																		// デストラクタ
																					// メンバ関数
	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size);		// プレイヤの生成
	static HRESULT Load(void);														// テクスチャの読み込む
	static void Unload(void);														// テクスチャの破棄
	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size);				// 敵の初期化関数
	virtual void Uninit(void);																// 敵の終了関数
	void Update(void);																// 敵の更新関数
	virtual void Draw(void);																// 敵の描画関数

private:																			// 自分だけがアクセス可能				
	static LPDIRECT3DTEXTURE9 m_pTexture;											// テクスチャへのポインタ
	D3DXVECTOR3 m_Move;																// 敵の移動量
	D3DXVECTOR2 m_Size;
};
#endif
