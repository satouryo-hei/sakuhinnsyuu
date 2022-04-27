//----------------------------------
//�|���S���̏���
//----------------------------------
#ifndef _LIGHT_H
#define _LIGHT_H
#include "main.h"
#include "scene.h"
#include "texture.h"
//------------------------------------------------------------------------------
//�N���X�̒�`
//------------------------------------------------------------------------------
class CLight
{
public:
	CLight();
	~CLight();
	HRESULT Init(D3DXCOLOR Diffuse, D3DXVECTOR3 vecDir);
private:
	D3DLIGHT9 m_light;//���C�g�̏��
	static int m_nCntLight;//�������̃J�E���g
	int m_nId;//������
};


#endif // !_LIGHT_H
#pragma once
