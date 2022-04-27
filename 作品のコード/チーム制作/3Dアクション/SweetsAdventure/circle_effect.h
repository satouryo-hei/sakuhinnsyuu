//=============================================================================
//
// エフェクトの処理 [effect.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _CIRCLE_EFFECT_H
#define _CIRCLE_EFFECT_H

#include "billeffect.h"
#include "texture.h"

class CEffect;

class CCircle_Effect : CBilleffect
{
public:

	CCircle_Effect(CScene::OBJTYPE nPriority = CBilleffect::OBJTYPE_EFFECT);
	~CCircle_Effect();
	static CCircle_Effect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, CTexture::Type type, D3DXVECTOR3 addmove, int nDensity, int nRadius, int nLife);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, CTexture::Type type, D3DXVECTOR3 addmove, int nDensity, int nRadius,int nLife);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetCircle(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR3 addmove, int nDensity, int nRadius, int nLife);
	D3DXVECTOR3 Addmove(D3DXVECTOR3 move, D3DXVECTOR3 addmove);

	void SetUse(bool bUse) { m_bUse = bUse; }

private:
	CEffect *m_pEffect;		//エフェクトのポインター
	D3DXVECTOR3 m_pos;		// 現在の位置
	D3DXVECTOR3 m_rot;		// 回転量
	D3DXVECTOR3 m_move;		// 移動量
	D3DXVECTOR3 m_size;		// 大きさ
	D3DXCOLOR m_col;		// 色
	int m_nLife;			// 寿命
	bool m_bUse;			// 使用しているかどうか
	float m_fRoll;
};

#endif