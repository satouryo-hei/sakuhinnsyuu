//---------------------
//�}�E�X�̓��͏���
//---------------------
#ifndef _MOUSE_H_
#define _MOUSE_H_
#include "main.h"
#include "input.h"
#define NUM_KEY_MAX (256)//�L�[�̍ő吔

class CMouse : public CInput
{
public:
	typedef enum
	{
		MOUSE_LEFT=0,
		MOUSE_RIGHT,
		MOUSE_WHEEL,
		MOUSE_MIDDLE,
		MOUSE_MAX
	}MOUSE_TYPE;
	CMouse();
	~CMouse();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetPress(int nKey);
	bool GetTrigger(int Key);
	DIMOUSESTATE2 GetMousePos(void) {return m_aKeyState;}
private:
	DIMOUSESTATE2 m_aKeyState;//�L�[�{�[�h�̓��͏��i�v���X���j
	DIMOUSESTATE2 m_aKeyStateTrigger;

};

#endif _MOUSE_H_
