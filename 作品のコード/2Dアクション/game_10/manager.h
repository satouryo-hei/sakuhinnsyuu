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
		MODE_INVALID = -1,														// ����
		MODE_TITLE = 0,															// �^�C�g��
		MODE_TUTORIAL,															// �`���[�g���A��
		MODE_SELECT,															// �I��
		MODE_GAME,																// �Q�[��
		MODE_RESULT,															// ���U���g
		MODE_MAX																// ���[�h�̑S���
	} MODE;

	CManager();																	// �R���X�g���N�^
	~CManager();																// �f�X�g���N�^
																				// �����o�֐�
	HRESULT Init(HINSTANCE hInstance,HWND hWnd, bool bWindow);					// �}�l�[�W���[�̏������֐�
	void Uninit(void);															// �}�l�[�W���[�̏I���֐��@
	void Update(void);															// �}�l�[�W���[�̍X�V�֐�
	void Draw(void);															// �}�l�[�W���[�̕`��֐�
	static void SetMode(MODE mode);												// ���[�h�̐ݒ菈��
	static MODE GetMode(void) { return m_mode; }								// ���[�h�̎擾����
	static void ChangeMode(void);												// �`�F���W���[�h�̏���
	
	static CRenderer*GetRenderer(void){ return m_pRenderer; }					// �����_���[�̃|�C���^�[�擾����
	static CInputKeyboard*GetInputKeyboard(void){ return m_pInputKeyboard; }	// �L�[�{�[�h�̃|�C���^�[�擾����
	static CCamera*GetCamera(void) { return m_pCamera; }						// �J�����̃|�C���^�[�擾����
	static CLight*GetLight(void) { return m_pLight[0]; }						// ���C�g�̃|�C���^�[�擾����
	static CTexture*GetTexture(void) { return m_pTexture; }						// �e�N�X�`���̃|�C���^�[�擾����
	static CTitle*GetTitle(void) { return m_pTitle; }							// �^�C�g���̃|�C���^�[�擾����
	static CSelect*GetSelect(void) { return m_pSelect; }						// �I���̃|�C���^�[�擾����	
	static CTutorial*GetTutorial(void) { return m_pTutorial; }					// �`���[�g���A���̃|�C���^�[�擾����	
	static CGame*GetGame(void) { return m_pGame; }								// �Q�[���̃|�C���^�[�擾����
	static CResult*GetResult(void) { return m_pResult; }						// ���U���g�̃|�C���^�[�擾����

private:																		// �����������A�N�Z�X�\
	static CRenderer*m_pRenderer;												// �C���X�^���X����
	static CInputKeyboard*m_pInputKeyboard;										// �L�[�{�[�h�̃|�C���^�[����
	static CCamera * m_pCamera;													// �J�����̃|�C���^�[����
	static CLight * m_pLight[3];												// ���C�g�̃|�C���^�[����
	static CTexture * m_pTexture;												// �e�N�X�`���̃|�C���^�[����
	static CTitle * m_pTitle;													// �^�C�g���̃|�C���^�[����
	static CSelect * m_pSelect;													// �I����ʂ̃|�C���^�[����
	static CTutorial*m_pTutorial;												// �`���[�g���A���̃|�C���^�[����	
	static CGame * m_pGame;														// �Q�[���̃|�C���^�[����
	static CResult * m_pResult;													// ���U���g�̃|�C���^�[����
	static MODE m_mode;															// ���[�h�̃|�C���^�[����
	static MODE m_Nextmode;														// ���̃��[�h�̃|�C���^�[����
	static CFade * m_pFade;														// �t�F�[�h�̃|�C���^�[����
};

#endif
