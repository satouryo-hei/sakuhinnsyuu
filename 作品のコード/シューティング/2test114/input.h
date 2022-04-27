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
public:
	CInput();
	virtual ~CInput();
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void) = 0;

protected:
	LPDIRECTINPUTDEVICE8 m_pDevice; //���̓f�o�C�X(�L�[�{�[�h)�ւ̃|�C���^
	static LPDIRECTINPUT8 m_pInput; //Ditrect Input�I�u�W�F�N�g�̃|�C���^

};

//=============================================================================
// �L�[�{�[�h�̃N���X
//=============================================================================
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();
	~CInputKeyboard();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetPress(int nKey);
	bool GetTrigger(int nKey);
	bool GetRelease(int nKey);

private:
	BYTE m_aKeyState[NUM_KEY_MAX];			//�L�[�{�[�h�̓��͏��(�v���X���)
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];	//�L�[�{�[�h�̓��͏��(�g���K���)
	BYTE m_aKeyStateRelease[NUM_KEY_MAX];	//�L�[�{�[�h�̓��͏��(�����[�X���)
};

#endif// _INPUT_H_//ifndef�ƃZ�b�g�i�K����ԉ�
