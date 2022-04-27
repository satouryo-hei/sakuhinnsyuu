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

	static void SetGauge(float Set);//�Q�[�W�̑���

private:
	D3DXVECTOR3 m_pos;//�ʒu
	static D3DXVECTOR3 m_Scale;//�Q�[�W�̑傫��
	float m_fScaleSpeed;//�Q�[�W�𑝂₵�Ă���
	bool				m_bNextMode;//��d�����h�~�ϐ�
	bool				m_bOneTimeOnlyPlay;

};

#endif // !_TIME_H_*/#pragma once
