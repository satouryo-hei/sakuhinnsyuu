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
class CSound;			
class CTitle;
class CTutorial;
class CGame;
class CResult;
class CFade;
class CTexture;

//*****************************************************************************
// �}�l�[�W���[�N���X
//*****************************************************************************
class CManager
{
public:

	typedef enum
	{
		MODE_INVALID = -1,
		MODE_TITLE = 0,
		MODE_TUTORIAL,
		MODE_GAME,
		MODE_RESULT,
		MODE_MAX
	} MODE;

	CManager();																	// �R���X�g���N�^
	~CManager();																// �f�X�g���N�^
																				// �����o�֐�
	HRESULT Init(HINSTANCE hInstance,HWND hWnd, bool bWindow);					// �}�l�[�W���[�̏������֐�
	void Uninit(void);															// �}�l�[�W���[�̏I���֐��@
	void Update(void);															// �}�l�[�W���[�̍X�V�֐�
	void Draw(void);															// �}�l�[�W���[�̕`��֐�
	static CRenderer*GetRenderer(void);											// CRenderer�N���X�̃|�C���^
	static CInputKeyboard*GetInputKeyboard(void);								// �L�[�{�[�h�N���X�̃|�C���^
	static CSound*GetSound(void);												// ���N���X�̃|�C���^
	static void SetMode(MODE mode);												// ���[�h�̔z�u����
	static MODE GetMode(void) { return m_mode; }								// ���[�h�̎擾����
	static CFade* GetFade(void) { return m_pFade; };
	static CTexture* GetTexture(void) { return m_pTexture; };
	static void CManager::ChangeMode(void);

private:																		// �����������A�N�Z�X�\
	static CRenderer*m_pRenderer;												// CRenderer�̃C���X�^���X����
	static CInputKeyboard*m_pInputKeyboard;										// �L�[�{�[�h�̃C���X�^���X����
	static CSound*m_pSound;														// ���̃C���X�^���X����
	static CTitle*m_pTitle;														// �^�C�g���̃C���X�^���X����
	static CTutorial*m_pTutorial;												// �`���[�g���A���̃C���X�^���X����
	static CGame*m_pGame;														// �Q�[���̃C���X�^���X����
	static CResult*m_pResult;													// ���U���g�̃C���X�^���X����
	static MODE m_mode;															// ���[�h�̃C���X�^���X����
	static CFade * m_pFade;
	static CTexture * m_pTexture;
	static MODE m_Nextmode;
};
#endif
