//=============================================================================
//
// IMGUI�̃E�B���h�E�ݒ�̏��� [imgui_window.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _IMGUI_WINDOW_H_
#define _IMGUI_WINDOW_H_
#include"main.h"

//*****************************************************************************
// IMGUI�̃E�B���h�E�N���X
//*****************************************************************************
class CImgui_Window
{
public:

	CImgui_Window();									// IMGUI�̃E�B���h�E�̃R���X�g���N�^
	~CImgui_Window();									// IMGUI�̃E�B���h�E�̃f�X�g���N�^
	// �����o�֐�
	HRESULT Init(HWND hWnd, bool bWindow);				// IMGUI�̃E�B���h�E�̏������֐�
	void Uninit(void);									// IMGUI�̃E�B���h�E�̏I���֐��@
	void Update(void);									// IMGUI�̃E�B���h�E�̍X�V�֐�
	void Draw(void);									// IMGUI�̃E�B���h�E�̕`��֐�
};
#endif