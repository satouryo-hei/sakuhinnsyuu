//=============================================================================
//
//���C�g�̏���[light.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _LIGHT_H_//endif�ƃZ�b�g�i�K����ԏ�
#define _LIGHT_H_

#include"main.h"

//*****************************************************************************
// ���C�g�N���X
//*****************************************************************************
class CLight
{
public:													// �N�ł��A�N�Z�X�\

	CLight();											// �R���X�g���N�^
	~CLight();											// �f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 vec,D3DXCOLOR col);		// �������֐�
	void Uninit(void);									// �I���֐�
	void Update(void);									// �X�V�֐�

private:												// �����������A�N�Z�X�\
	D3DLIGHT9 m_light;									// ���C�g�̏��
	static int m_nCntLight;								// ���C�g�̐������̃J�E���g
	int m_nNumLight;									// ���C�g�̐�����
};
#endif //_LIGHT_H_//ifndef�ƃZ�b�g�i�K����ԉ�
