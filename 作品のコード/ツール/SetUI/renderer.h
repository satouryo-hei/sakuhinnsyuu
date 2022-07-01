//=============================================================================
//
// ���C������ [renderer.h]
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

	//-----------------------------------------------------------------------------
	//�F�̎��
	//-----------------------------------------------------------------------------
	typedef enum
	{
		FontCol_WHITE = 0,			// ��
		FontCol_RED,				// ��
		FontCol_GREEN,				// ��
		FontCol_BLUE,				// ��
		FontCol_YELLOW,				// ���F
		FontCol_PURPLE,				// ��
		FontCol_LIGHT_BLUE,			// ���F
		FontCol_NONE,				// �Ȃ�
		FontCol_MAX					// �ő吔
	} FontCol;

	void DrawFPS(void);													// FPS�̕`��֐�
	void DrawUiInfo(void);												// UI�̏��`��֐�
	void DrawUiControl(void);											// UI�̑�����@�`��֐�	
	void ColorFont(void);												// ������@��\�������邩�ǂ����֐�

	// �����o�ϐ�
	LPDIRECT3D9	m_pD3D;													// Direct3D�I�u�W�F�N�g
	LPDIRECT3DDEVICE9 m_pD3DDevice;										// Device�I�u�W�F�N�g(�`��ɕK�v)
	LPD3DXFONT m_pFont;													// �t�H���g�ւ̃|�C���^
	LPD3DXFONT m_pUiFont;												// �t�H���g�ւ̃|�C���^	
	bool m_bUIControl;													// ������@��\�����邩�ǂ���
	D3DXCOLOR m_FontCol;												// �t�H���g�̃J���[
	int m_FontColType;													// �t�H���g�̃J���[�̎��
	bool m_bColorTrigger;												// ���������ĕύX����邩�ǂ���

};
#endif
