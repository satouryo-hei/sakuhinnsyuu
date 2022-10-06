//=============================================================================
//
// ���͏��� [input.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _INPUT_H_//endif�ƃZ�b�g�i�K����ԏ�

#define _INPUT_H_

#include "main.h"
#include<XInput.h>

//�}�N����`
#define D3DX_PI    ((FLOAT)  3.141592654f) //�΂̂���
#define NUM_KEY_MAX (256)//�L�[�̍ő吔

//=============================================================================
// ���̓N���X
//=============================================================================
class CInput
{
public:														// �N�ł��A�N�Z�X�\
	CInput();												// �R���X�g���N�^
	virtual ~CInput();										// �f�X�g���N�^
															// �����o�֐�
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// ���͂̏������֐�
	virtual void Uninit(void);								// ���͂̏I���֐��@
	virtual void Update(void) = 0;							// ���͂̍X�V�֐�
															
protected:													
	// �����o�ϐ�
	LPDIRECTINPUTDEVICE8 m_pDevice;							//���̓f�o�C�X(�L�[�{�[�h)�ւ̃|�C���^
	static LPDIRECTINPUT8 m_pInput;							//Ditrect Input�I�u�W�F�N�g�̃|�C���^

};

//=============================================================================
// �L�[�{�[�h�̃N���X
//=============================================================================
class CInputKeyboard : public CInput
{
public:				
	CInputKeyboard();									// �R���X�g���N�^
	~CInputKeyboard();									// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);		// �L�[�{�[�h�̏������֐�
	void Uninit(void);									// �L�[�{�[�h�̏I���֐��@
	void Update(void);									// �L�[�{�[�h�̍X�V�֐�
	bool GetPress(int nKey);							// �L�[�{�[�h�������������֐�
	bool GetTrigger(int nKey);							// �L�[�{�[�h��1��̂݉������֐�
	bool GetRelease(int nKey);							// �L�[�{�[�h�𗣂����Ƃ��֐�

private:
	BYTE m_aKeyState[NUM_KEY_MAX];						//�L�[�{�[�h�̓��͏��(�v���X���)
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];				//�L�[�{�[�h�̓��͏��(�g���K���)
	BYTE m_aKeyStateRelease[NUM_KEY_MAX];				//�L�[�{�[�h�̓��͏��(�����[�X���)
};

#endif// _INPUT_H_//ifndef�ƃZ�b�g�i�K����ԉ�
