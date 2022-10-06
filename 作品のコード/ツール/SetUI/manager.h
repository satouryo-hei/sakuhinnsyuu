//=============================================================================
//
// �}�l�[�W���[���� [manager.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include"main.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CRenderer;		
class CInputKeyboard;	
class CUi;
class CUI_Manager;
class CTexture;
class CImgui_Window;

//*****************************************************************************
// �}�l�[�W���[�N���X
//*****************************************************************************
class CManager
{
public:
	CManager();																	// �R���X�g���N�^
	~CManager();																// �f�X�g���N�^
																				// �����o�֐�
	HRESULT Init(HINSTANCE hInstance,HWND hWnd, bool bWindow);					// �}�l�[�W���[�̏������֐�
	void Uninit(void);															// �}�l�[�W���[�̏I���֐��@
	void Update(void);															// �}�l�[�W���[�̍X�V�֐�
	void Draw(void);															// �}�l�[�W���[�̕`��֐�
	static CRenderer*GetRenderer(void) { return m_pRenderer; }					// CRenderer�N���X�̃|�C���^
	static CInputKeyboard*GetInputKeyboard(void) { return m_InputKeyboard; }	// �L�[�{�[�h�N���X�̃|�C���^
	static CUI_Manager*GetUi_manager(void) { return m_pUi_manager;}				// UI�N���X�̊Ǘ��^�̃|�C���^
	static CTexture *GetTexture(void) { return m_pTexture; }					// �e�N�X�`���N���X�̃|�C���^
	static CImgui_Window* GetImguiWindow(void) { return m_pImguiWindow; }		// Imgui_Window�N���X�̃|�C���^

private:																		// �����������A�N�Z�X�\
																				// �����o�ϐ�
	static CRenderer*m_pRenderer;												// CRenderer�̃C���X�^���X����
	static CInputKeyboard*m_InputKeyboard;										// �L�[�{�[�h�̃C���X�^���X����
	static CUI_Manager*m_pUi_manager;											// UI�N���X�̃C���X�^���X����
	static CTexture * m_pTexture;												// �e�N�X�`���N���X�̃C���X�^���X����
	static CImgui_Window* m_pImguiWindow;										// Imgui_Window�N���X�̃|�C���^
};
#endif
