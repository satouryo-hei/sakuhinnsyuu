//=============================================================================
//
// 弾の処理 [bullet.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "billboard.h"

//*****************************************************************************
// 弾クラス
//*****************************************************************************
class CBullet : public CBillboard
{
public:
	CBullet(PRIORITY nPriority = PRIORITY_BULLET);					// コンストラクタ
	~CBullet();														// デストラクタ
	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size,int nLife);		// ポリゴンの生成	
	
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 size);			// 弾の初期化関数
	void Uninit();												// 弾の終了関数
	void Update();												// 弾の更新関数
	void Draw();												// 弾の描画関数
	D3DXVECTOR3 GetMove() { return m_move; }
	void SetMove(D3DXVECTOR3 move) { m_move = move; }
	void SetUse(bool buse) { m_bUse = buse; }
	
private:
	LPDIRECT3DTEXTURE9	m_pTexture = NULL;					// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;				// 頂点バッファへのポインタ
	D3DXMATRIX m_mtxWorld;									// ワールドマトリックス	
	D3DXVECTOR3 m_pos;										// 位置
	D3DXVECTOR2 m_size;										// 大きさ
	D3DXVECTOR3 m_move;										// 移動量
	D3DXCOLOR m_col;										// 色
	int m_nLife;											// 弾の体力
	bool m_bUse;											// 弾が使われてるかどうか

};
#endif // !_BILLBOARD_H_