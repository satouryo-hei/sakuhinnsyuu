//-----------------------------------------------------------------------------
//�Q�[���p�b�h����̏���
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include<Windows.h>
#include "XInput.h"
#include "Player.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CXInput::CXInput()
{
	ZeroMemory(&m_GamePad.m_state, sizeof(XINPUT_STATE));
	ZeroMemory(&m_GamePad.m_stateLast, sizeof(XINPUT_STATE));

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CXInput::~CXInput()
{

}
//-----------------------------------------------------------------------------
//�X�V����
//-----------------------------------------------------------------------------
void CXInput::UpdateGamepad(void)
{
	XINPUT_STATE state;

	DWORD dwResult = XInputGetState(0, &state);

	m_GamePad.m_stateLast = m_GamePad.m_state;
	m_GamePad.m_state = state;

	//���̓f�o�C�X����f�[�^���擾

	//-----------------------------------------------------------------------------
	//�Q�[���p�b�h�̑��� (�J�����ړ�)
	//-----------------------------------------------------------------------------

	//if (m_GamePad.m_state.Gamepad.sThumbRX >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) //�E
	//{
	//	pcamera->rot.y += 0.03f;
	//	pcamera->posR.x = pcamera->posV.x + sinf(pcamera->rot.y) * 1000;
	//	pcamera->posR.z = pcamera->posV.z + cosf(pcamera->rot.y) * 1000;
	//}

	//if (m_GamePad.m_state.Gamepad.sThumbRX <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) //��
	//{
	//	pcamera->rot.y -= 0.03f;
	//	pcamera->posR.x = pcamera->posV.x + sinf(pcamera->rot.y) * 1000;
	//	pcamera->posR.z = pcamera->posV.z + cosf(pcamera->rot.y) * 1000;
	//}

	//if (m_GamePad.m_state.Gamepad.sThumbRY >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) //��
	//{
	//	pcamera->posV.y = pcamera->posV.y - sinf(0.75)*KAMERA;
	//}

	//if (m_GamePad.m_state.Gamepad.sThumbRY <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) //��
	//{
	//	pcamera->posV.y = pcamera->posV.y + sinf(0.75)*KAMERA;
	//}

}
bool CXInput::GetButtonTrigger(int nButton)
{
	return (m_GamePad.m_stateLast.Gamepad.wButtons & nButton)==false&& (m_GamePad.m_state.Gamepad.wButtons & nButton) ? true : false;
}
bool CXInput::GetGamepadPress(int nButton)
{
	return (m_GamePad.m_state.Gamepad.wButtons & nButton);

}

CXInput::GAMEPAD *CXInput::GetGamePad(void)
{
	return &m_GamePad;
}