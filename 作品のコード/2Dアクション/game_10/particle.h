//=============================================================================
//
// パーティクルの処理 [effect.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _PARTICLE_H_//endifとセット（必ず一番上
#define _PARTICLE_H_

#include"billeffect.h"
#include "texture.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CIRCLE_HALF (float((rand() % 314) / 100.0f)/2 - float((rand() % 314) / 100.0f))/2 //円の半分のマクロ
#define CIRCLE (float(rand() % 314) / 100.0f - float(rand() % 314) / 100.0f) //円のマクロ

//*****************************************************************************
// パーティクルのエフェクトクラス
//*****************************************************************************
class CParticle : public CBilleffect
{
public:

	CParticle(PRIORITY nPriority = PRIORITY_NOMAL);
	~CParticle();

	//プロトタイプ宣言
	static CParticle *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, int type,
		D3DXVECTOR3 addmove,D3DXVECTOR3 addsize, D3DXCOLOR addcol, int nLife);							// 生成処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, int type,
		D3DXVECTOR3 addmove,D3DXVECTOR3 addsize,D3DXCOLOR addcol, int nLife);							// 初期化処理
	void Uninit(void);																					// 終了処理
	void Update(void);																					// 更新処理
	void Draw(void);																					// 描画処理

private:
	D3DXVECTOR3 m_pos;						// 現在の位置
	D3DXVECTOR3 m_rot;						// 回転量
	D3DXVECTOR3 m_move;						// 移動量
	D3DXVECTOR3 m_Addmove;					// 移動量の減算値
	D3DXVECTOR3 m_size;						// 大きさ
	D3DXVECTOR3 m_AddSize;					// 大きさの減算値
	D3DXCOLOR m_col;						// 色
	D3DXCOLOR m_addcol;						// 色の減算値
	int m_nLife;							// 寿命
	bool m_bUse;							// 使用しているかどうか

};
#endif // !_EFFECT_H_
