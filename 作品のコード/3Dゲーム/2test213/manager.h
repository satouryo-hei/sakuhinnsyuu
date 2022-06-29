//=============================================================================
//
// �Ǘ����� [manager.h]
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
class CCamera;
class CLight;
class CTexture;
class CTitle;
class CTutorial;
class CSelect;
class CGame;
class CResult;
class CFade;
//*****************************************************************************
// �}�l�[�W���[�N���X
//*****************************************************************************
class CManager
{
public:
	// ���[�h�̎��
	typedef enum
	{
		MODE_INVALID = -1,
		MODE_TITLE = 0,
		MODE_SELECT,
		MODE_TUTORIAL,
		MODE_GAME,
		MODE_RESULT,
		MODE_MAX
	} MODE;

	CManager();																	// �R���X�g���N�^
	~CManager();																// �f�X�g���N�^
																				// �����o�֐�
	HRESULT Init(HINSTANCE hInstance,HWND hWnd, bool bWindow);					// �������֐�
	void Uninit(void);															// �I���֐��@
	void Update(void);															// �X�V�֐�
	void Draw(void);															// �`��֐�
	static void SetMode(MODE mode);												// ���[�h�ݒ�֐�
	static MODE GetMode(void) { return m_mode; }								// ���[�h�̎擾�֐�
	static void ChangeMode(void);
	
	static CRenderer*GetRenderer(void){ return m_pRenderer; }					// �����_���[�̎擾
	static CInputKeyboard*GetInputKeyboard(void){ return m_pInputKeyboard; }	// �L�[�{�[�h�̎擾
	static CCamera*GetCamera(void) { return m_pCamera; }						// �J�����̎擾
	static CLight*GetLight(void) { return m_pLight[0]; }						// ���C�g�̎擾
	static CTexture*GetTexture(void) { return m_pTexture; }						// �e�N�X�`���̎擾
	static CTitle*GetTitle(void) { return m_pTitle; }							// �^�C�g���̎擾
	static CTutorial*GetTutorial(void) { return m_pTutorial; }					// �`���[�g���A���̎擾
	static CSelect*GetSelect(void) { return m_pSelect; }						// �I���̎擾
	static CGame*GetGame(void) { return m_pGame; }								// �Q�[���̎擾
	static CResult*GetResult(void) { return m_pResult; }						// ���U���g�̎擾
	
private:																		// �����������A�N�Z�X�\
	static CRenderer*m_pRenderer;												// �����_���[�̃|�C���^�[�𐶐�
	static CInputKeyboard*m_pInputKeyboard;										// �L�[�{�[�h�̃|�C���^�[�𐶐�
	static CCamera * m_pCamera;													// �J�����̃|�C���^�[�𐶐�
	static CLight * m_pLight[3];												// ���C�g�̃|�C���^�[�𐶐�
	static CTexture * m_pTexture;												// �e�N�X�`���̃|�C���^�[�𐶐�
	static CTitle * m_pTitle;													// �^�C�g���̃|�C���^�[�𐶐�
	static CTutorial * m_pTutorial;												// �`���[�g���A���̃|�C���^�[�𐶐�
	static CSelect * m_pSelect;													// �`���[�g���A���̎擾
	static CGame * m_pGame;														// �Q�[���̃|�C���^�[�𐶐�
	static CResult * m_pResult;													// ���U���g�|�C���^�[�𐶐�
	static MODE m_mode;															// ���[�h�̃C���X�^���X����
	static MODE m_Nextmode;														// ���̃��[�h�̃C���X�^���X����
	static CFade * m_pFade;														// �t�F�[�h�̃|�C���^�[�𐶐�
};
#endif
