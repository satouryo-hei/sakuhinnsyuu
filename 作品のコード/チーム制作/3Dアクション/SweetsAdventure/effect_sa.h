//=============================================================================
//
// エフェクトの処理 [effect.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _EFFECT_SA_H_//endifとセット（必ず一番上
#define _EFFECT_SA_H_

#include"billeffect.h"
#include "texture.h"

// マクロ定義
#define CIRCLE (float(rand() % 360) / 100.0f - float(rand() % 360) / 100.0f) //円のマクロ
#define POSRAND (rand() % 10 + 10)

class CEffect_sa : public CBilleffect
{
public:

	CEffect_sa(OBJTYPE OBJTYPE_EFFECT);
	~CEffect_sa();

	//プロトタイプ宣言
	static CEffect_sa *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, CTexture::Type type, int nLife);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, CTexture::Type type, int nLife);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	D3DXVECTOR3 m_pos;						// 現在の位置
	D3DXVECTOR3 m_rot;						// 回転量
	D3DXVECTOR3 m_move;						// 移動量
	D3DXVECTOR3 m_size;						// 大きさ
	D3DXCOLOR m_col;						// 色
	int m_nLife;							// 寿命
	bool m_bUse;							// 使用しているかどうか

};
#endif // !_EFFECT_H_
