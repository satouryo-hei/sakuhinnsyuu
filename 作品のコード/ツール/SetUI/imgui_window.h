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

	CImgui_Window();											// �R���X�g���N�^
	~CImgui_Window();										// �f�X�g���N�^
															// �����o�֐�
	HRESULT Init(HWND hWnd, bool bWindow);					// �|���S���̏������֐�
	void Uninit(void);									// �|���S���̏I���֐��@
	void Update(void);									// �|���S���̍X�V�֐�
	void Draw(void);									// �|���S���̕`��֐�
private:												// �����������A�N�Z�X�\	
};
#endif