//=============================================================================
//
// 爆発のエフェクトの処理 [Explosion_effect.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _EXPLOSION_EFFECT_H
#define _EXPLOSION_EFFECT_H

#include "billeffect.h"
#include "texture.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CEffect;

//*****************************************************************************
// 爆発のエフェクトクラス
//*****************************************************************************
class CExplosion_Effect : CBilleffect
{
public:

	CExplosion_Effect(PRIORITY nPriority = CBilleffect::PRIORITY_NOMAL);														// コンストラクタ
	~CExplosion_Effect();																										// デストラクタ
	static CExplosion_Effect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, CTexture::Tex type,	// 生成
		D3DXVECTOR3 addsize, D3DXVECTOR3 addmove, D3DXCOLOR addcol, int nDensity, int nLife);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, CTexture::Tex type,						// 初期化
		D3DXVECTOR3 addsize, D3DXVECTOR3 addmove, D3DXCOLOR addcol, int nDensity, int nLife);
	void Uninit(void);																											// 終了
	void Update(void);																											// 更新
	void Draw(void);																											// 描画
	void SetExplosion(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, CTexture::Tex type,					// 設定
		D3DXVECTOR3 addsize, D3DXVECTOR3 addmove, D3DXCOLOR addcol, int nDensity, int nLife);
	D3DXVECTOR3 Addmove(D3DXVECTOR3 move, D3DXVECTOR3 addmove);																	// 計算する移動量
	D3DXCOLOR Addcol(D3DXCOLOR col, D3DXCOLOR addcol);																			// 計算する色
	void SetUse(bool bUse) { m_bUse = bUse; }																					// 使っているかどうか

private:
	CEffect *m_pEffect;		//エフェクトのポインター
	D3DXVECTOR3 m_pos;		// 現在の位置
	D3DXVECTOR3 m_rot;		// 回転量
	D3DXVECTOR3 m_move;		// 移動量
	D3DXVECTOR3 m_addmove;		// 移動量
	D3DXVECTOR3 m_size;		// 大きさ
	D3DXCOLOR m_col;		// 色
	D3DXCOLOR m_addcol;		// 移動量
	int m_nLife;			// 寿命
	bool m_bUse;			// 使用しているかどうか
};

#endif
