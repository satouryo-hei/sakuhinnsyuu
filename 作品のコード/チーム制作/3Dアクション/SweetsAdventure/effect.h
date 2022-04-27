#ifndef _EFFECT_H_
#define _EFFECT_H_
#include "billboard.h"
#include "texture.h"

class CEffect : public CBillboard
{
public:
	CEffect(OBJTYPE OBJTYPE_EFFECT);
	~CEffect();
	HRESULT Init(CTexture::Type type);
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	/*
	 位置の設定,
	 移動量,
	 サイズ,
	 色設定
	 小さくなるスピード
	 Texture
	*/
	static CEffect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 m_move, D3DXVECTOR3 size, D3DXCOLOR col, float ScaleSpeed,CTexture::Type type = CTexture::TIME);
	
private:
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_size;
	D3DXCOLOR m_col;//色
	float m_fScaleSpeed;//サイズを小さくする変数
	int m_gravity;//重力
	int m_nLife;//寿命
	float m_fRand;
};


#endif // !_EFFECT_H_

