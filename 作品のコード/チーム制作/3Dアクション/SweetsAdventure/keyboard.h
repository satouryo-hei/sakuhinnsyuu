//---------------------
//�L�[�{�[�h�̓��͏���
//---------------------
#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_
#include "main.h"
#include "input.h"
#define NUM_KEY_MAX (256)//�L�[�̍ő吔

class CInputKeyBoard : public CInput
{
public:
	CInputKeyBoard();
	~CInputKeyBoard();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetPress(int nKey);
	bool GetTrigger(int Key);

private:
	BYTE m_aKeyState[NUM_KEY_MAX];//�L�[�{�[�h�̓��͏��i�v���X���j
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];

};

#endif _KEYBOARD_H_
