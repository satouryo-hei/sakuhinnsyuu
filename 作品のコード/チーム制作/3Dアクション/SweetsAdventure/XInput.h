//���͏���
//---------------------
#ifndef _XInput_H_
#define _XInput_H_
#include "main.h"
#include<XInput.h>

//-----------------------------------------------------------------------------
//�}�N����`
//-----------------------------------------------------------------------------
#define KAMERA (10.0f) 
#define BUTTON_MAX (32)
#define XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE  7849
#define XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE 8689
#define MAX_GAMECONTROLLER (1)						//�Q�[���p�b�h�̍ő吔
//-----------------------------------------------------------------------------
//�N���X��`
//-----------------------------------------------------------------------------
class CXInput
{
public:
	typedef struct
	{
		DWORD m_wButtons[BUTTON_MAX];//�{�^���̓��͏��i�v���X���j
		XINPUT_STATE m_state;
		XINPUT_STATE m_stateLast;
	} GAMEPAD;
	CXInput();
	~CXInput();
	void UpdateGamepad(void);
	bool GetGamepadPress(int nButton);
	bool GetButtonTrigger(int nButton);
	GAMEPAD *GetGamePad(void);
	GAMEPAD	m_GamePad;
private:
	XINPUT_STATE m_laststate;

};
#endif _XInput_H_
																																					