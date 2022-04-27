//=============================================================================
//
// エフェクトの処理 [effect.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _SMOKE_EFFECT_H
#define _SMOKE_EFFECT_H

#include "billeffect.h"
#include "texture.h"
#define MAX_SMOKE_NUMALL (1)
#define MAX_SMOKE_CNT (8)//煙のカウンター
#define MAX_SMOKE_SIZE (10)//煙の大きさ
#define MAX_SMOKE_MOVE_X (0.5)//煙の移動量
#define MAX_SMOKE_MOVE_Y (0.5)//煙の移動量
#define MAX_SMOKE_MOVE_Z (0.5)//煙の移動量

#define CIRCLE_HALF (float((rand() % 314) / 100.0f)/2 - float((rand() % 314) / 100.0f))/2 //円の半分のマクロ

class CEffect;

class CSmoke_Effect : CBilleffect
{
public:

	CSmoke_Effect(CScene::OBJTYPE nPriority = CBilleffect::OBJTYPE_EFFECT);
	~CSmoke_Effect();
	static CSmoke_Effect *Create(D3DXVECTOR3 pos, float rotY, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, CTexture::Type type, D3DXVECTOR3 addmove, int nDensity, int nRadius, int nLife);
	HRESULT Init(D3DXVECTOR3 pos, float rotY, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, CTexture::Type type, D3DXVECTOR3 addmove, int nDensity, int nRadius, int nLife);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetSmoke(D3DXVECTOR3 pos, float rotY, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR3 addmove, int nDensity, int nRadius, int nLife);
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
	int m_nTimer;			//カウンター
	bool m_bUse;			// 使用しているかどうか
	float m_fRoll;
};

#endif