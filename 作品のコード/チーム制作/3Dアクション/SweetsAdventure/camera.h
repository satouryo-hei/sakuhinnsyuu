//----------------------------------
//�|���S���̏���
//----------------------------------
#ifndef _CAMERA_H
#define _CAMERA_H
#include "main.h"
#include "scene.h"
#include "texture.h"
class CPlayer;
//------------------------------------------------------------------------------
//�N���X�̒�`
//------------------------------------------------------------------------------
class CCamera
{
public:
	CCamera();
	~CCamera();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetCamera(void);
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	void SetPlayerCamera(CPlayer *pPlayer);
private:
	D3DXVECTOR3 m_posV;//���݂̎��_
	D3DXVECTOR3 m_posR;//���݂̒����_
	D3DXVECTOR3 m_vecU;//������x�N�g��
	D3DXVECTOR3 m_rot;//�J�����̌���
	float m_fLong;//����
	D3DXMATRIX m_mtxProjection;//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView;//�r���[�}�g���b�N�X
	POINT m_Cursol;

};


#endif // !_CAMERA_H
#pragma once
