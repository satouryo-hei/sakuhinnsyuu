//=============================================================================
//
// 煙エフェクトの処理 [smoke_effect.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _SMOKE_EFFECT_H
#define _SMOKE_EFFECT_H

#include "billeffect.h"
#include "texture.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CEffect;

//*****************************************************************************
// 煙エフェクトクラス
//*****************************************************************************
class CSmoke_Effect : CBilleffect
{
public:

	CSmoke_Effect(PRIORITY nPriority = CBilleffect::PRIORITY_NOMAL);																	// コンストラクタ
	~CSmoke_Effect();																													// デストラクタ
	static CSmoke_Effect *Create(D3DXVECTOR3 pos, float rotY, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, CTexture::Tex type,	// 生成
		D3DXVECTOR3 addmove, D3DXVECTOR3 addsize, D3DXCOLOR addcol, int nRadius, int nDensity, int nLife);
	HRESULT Init(D3DXVECTOR3 pos, float rotY, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, CTexture::Tex type,					// 初期化
		D3DXVECTOR3 addmove, D3DXVECTOR3 addsize, D3DXCOLOR addcol, int nRadius, int nDensity, int nLife);
	void Uninit(void);																													// 終了
	void Update(void);																													// 更新
	void Draw(void);																													// 描画
	void SetSmoke(D3DXVECTOR3 pos, float rotY, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, CTexture::Tex type,					// 設定
		D3DXVECTOR3 addmove, D3DXVECTOR3 addsize, D3DXCOLOR addcol, int nRadius, int nDensity, int nLife);
	D3DXVECTOR3 Addmove(D3DXVECTOR3 move, D3DXVECTOR3 addmove);																			// 計算する移動量
	void SetUse(bool bUse) { m_bUse = bUse; }																							// 使っているかどうか

private:
	CEffect *m_pEffect;		//エフェクトのポインター
	D3DXVECTOR3 m_pos;		// 現在の位置
	D3DXVECTOR3 m_rot;		// 回転量
	D3DXVECTOR3 m_move;		// 移動量
	D3DXVECTOR3 m_size;		// 大きさ
	D3DXCOLOR m_col;		// 色
	int m_nLife;			// 寿命
	bool m_bUse;			// 使用しているかどうか
};

#endif