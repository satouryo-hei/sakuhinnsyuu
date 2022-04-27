//=============================================================================
//
// エフェクトの処理 [effect.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _FAIR_EFFECT_H
#define _FAIR_EFFECT_H

#include "billeffect.h"
#include "texture.h"

#define RANGE (float(rand() % 100) / 100.0f - float(rand() % 100) / 100.0f) //円のマクロ

class CEffect;

class Cfair_Effect : CBilleffect
{
public:

	Cfair_Effect(CScene::OBJTYPE nPriority = CBilleffect::OBJTYPE_EFFECT);
	~Cfair_Effect();
	static Cfair_Effect *Create(D3DXVECTOR3 pos, CTexture::Type type);
	HRESULT Init(D3DXVECTOR3 pos, CTexture::Type type);
	void Uninit(void);
	void Update(void);
	void Draw(void);

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

