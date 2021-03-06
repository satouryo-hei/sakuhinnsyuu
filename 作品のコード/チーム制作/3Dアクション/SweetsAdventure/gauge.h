#ifndef _GAUGE_H_
#define _GAUGE_H_
#include "scene.h"
#include "Scene2D.h"
#include "texture.h"



class CGauge : public CScene2D
{
public:
	CGauge(OBJTYPE nPriority = OBJTYPE_POLYGON);
	~CGauge();
	static CGauge*Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static void SetGauge(float Set);//ゲージの増減

private:
	D3DXVECTOR3 m_pos;//位置
	static D3DXVECTOR3 m_Scale;//ゲージの大きさ
	float m_fScaleSpeed;//ゲージを増やしていく
	bool				m_bNextMode;//二重押し防止変数
	bool				m_bOneTimeOnlyPlay;

};

#endif // !_TIME_H_*/#pragma once
