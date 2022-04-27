//=============================================================================
//
// 着地エフェクトの処理 [landing_effect.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _LANDING_EFFECT_H_//endifとセット（必ず一番上
#define _LANDING_EFFECT_H_

#include"billeffect.h"
#include "texture.h"

//*****************************************************************************
// 着地エフェクトクラス
//*****************************************************************************
class CLanding_Effect : public CBilleffect
{
public:

	CLanding_Effect(PRIORITY nPriority = CBilleffect::PRIORITY_NOMAL);															// コンストラクタ
	~CLanding_Effect();																											// デストラクタ
																																//プロトタイプ宣言
	static CLanding_Effect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, CTexture::Tex type,		// 生成
		D3DXVECTOR3 addmove, D3DXVECTOR3 addsize, D3DXCOLOR addcol, int nRadius, int nDensity, int nLife);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, CTexture::Tex type,						// 初期化
		D3DXVECTOR3 addmove, D3DXVECTOR3 addsize, D3DXCOLOR addcol, int nRadius, int nDensity, int nLife);						
	void Uninit(void);																											// 終了
	void Update(void);																											// 更新
	void Draw(void);																											// 描画
	void SetLanding(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, CTexture::Tex type,						// 設定
		D3DXVECTOR3 addmove, D3DXVECTOR3 addsize, D3DXCOLOR addcol, int nRadius, int nDensity, int nLife);						
	D3DXVECTOR3 Addmove(D3DXVECTOR3 move, D3DXVECTOR3 addmove);																	// 計算する移動量

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