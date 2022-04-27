//=============================================================================
//
// エフェクトの処理 [effect.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _EXPLOSION_EFFECT_H
#define _EXPLOSION_EFFECT_H

#include "billeffect.h"
#include "texture.h"

#define RANDCOLOR (rand()%255+50)
#define MAX_LIFE (10)
#define MIN_LIFE (5)
#define SET_COL (1.0f,0.0f,0.0f,1.0f)
#define Set_COL_R (1.0)
#define Set_COL_G (0.6)
#define Set_COL_B (0.3)
#define Set_COL_A (1.0)

class CEffect;

class CExplosion_Effect : CBilleffect
{
public:

	CExplosion_Effect(CScene::OBJTYPE nPriority = CBilleffect::OBJTYPE_EFFECT);
	~CExplosion_Effect();
	static CExplosion_Effect *Create(D3DXVECTOR3 pos, int nMaxLife, int nMinLife, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, CTexture::Type type, int nDensity, D3DXVECTOR3 addmove);
	HRESULT Init(D3DXVECTOR3 pos, int nMaxLife, int nMinLife, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, CTexture::Type type, int nDensity, D3DXVECTOR3 addmove);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetExplosion(D3DXVECTOR3 pos, int nMaxLife, int nMinLife, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, int nDensity, D3DXVECTOR3 addmove);
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
	int m_nDensity;
	int nNum;
};

#endif
