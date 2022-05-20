//=============================================================================
//
// �J�������� [camera.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _CAMERA_H_//endif�ƃZ�b�g�i�K����ԏ�
#define _CAMERA_H_

#include"main.h"

//*****************************************************************************
// �J�����N���X
//*****************************************************************************
class CCamera
{
public:													// �N�ł��A�N�Z�X�\
	CCamera();											// �R���X�g���N�^
	~CCamera();											// �f�X�g���N�^

	HRESULT Init(void);									// �������֐�
	void Uninit(void);									// �I���֐�
	void Update(void);									// �X�V�֐�
	void SetCamera(void);								// �J�����̐ݒ�֐�
	D3DXVECTOR3 GetPosV(void) { return m_posV; }		// ���݂̎��_�̎擾
	D3DXVECTOR3 GetPosR(void) { return m_posR; }		// ���݂̒����_�̎擾
	D3DXVECTOR3 GetRot(void) { return m_rot; }			// �����_�܂ł̋����̎擾

private:												// �����������A�N�Z�X�\
	D3DXMATRIX m_mtxProjection;							//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView;								//�r���[�}�g���b�N�X
	D3DVIEWPORT9 m_viewport;							//�r���[�{�[�g
	D3DXVECTOR3 m_posV;									//���݂̎��_
	D3DXVECTOR3 m_posVDest;								//�ړI�̎��_
	D3DXVECTOR3	m_posR;									//���݂̒����_
	D3DXVECTOR3 m_posRDest;								//�ړI�̒����_
	D3DXVECTOR3 m_vecU;									//������̃x�N�g��
	D3DXVECTOR3 m_rot;									//�J�����̌���
	float m_Range;										//�����_�܂ł̋���
};
#endif //_LIGHT_H_//ifndef�ƃZ�b�g�i�K����ԉ�