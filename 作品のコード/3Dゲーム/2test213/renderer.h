//=============================================================================
//
// ���`���ĕ`�揈�� [renderer.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include"main.h"

//*****************************************************************************
// ���C�������̃N���X
//*****************************************************************************
class CRenderer
{
public:																	// �N�ł��A�N�Z�X�\
	CRenderer();														// �R���X�g���N�^
	~CRenderer();														// �f�X�g���N�^
																		// �����o�֐�
	HRESULT Init(HWND hWnd, bool bWindow);								// �������֐�
	void Uninit(void);													// �I���֐�
	void Update(void);													// �X�V�֐�
	void Draw(void);													// �`��֐�
	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }			// �f�o�C�X�̎擾�֐�
private:																// �����������A�N�Z�X�\
	void DrawFPS(void);													// FPS�̕`��֐�

	LPDIRECT3D9	m_pD3D;													// Direct3D�I�u�W�F�N�g
	LPDIRECT3DDEVICE9 m_pD3DDevice;										// Device�I�u�W�F�N�g(�`��ɕK�v)
	LPD3DXFONT m_pFont;													// �t�H���g�̃|�C���^�[����
};
#endif