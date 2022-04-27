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
	 �ʒu�̐ݒ�,
	 �ړ���,
	 �T�C�Y,
	 �F�ݒ�
	 �������Ȃ�X�s�[�h
	 Texture
	*/
	static CEffect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 m_move, D3DXVECTOR3 size, D3DXCOLOR col, float ScaleSpeed,CTexture::Type type = CTexture::TIME);
	
private:
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_size;
	D3DXCOLOR m_col;//�F
	float m_fScaleSpeed;//�T�C�Y������������ϐ�
	int m_gravity;//�d��
	int m_nLife;//����
	float m_fRand;
};


#endif // !_EFFECT_H_

