//-----------------------------------------------------------------------------
//ゲームパッド操作の処理
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include<Windows.h>
#include "XInput.h"
#include "Player.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CXInput::CXInput()
{
	ZeroMemory(&m_GamePad.m_state, sizeof(XINPUT_STATE));
	ZeroMemory(&m_GamePad.m_stateLast, sizeof(XINPUT_STATE));

}

//=============================================================================
// デストラクタ
//=============================================================================
CXInput::~CXInput()
{

}
//-----------------------------------------------------------------------------
//更新処理
//-----------------------------------------------------------------------------
void CXInput::UpdateGamepad(void)
{
	XINPUT_STATE state;

	DWORD dwResult = XInputGetState(0, &state);

	m_GamePad.m_stateLast = m_GamePad.m_state;
	m_GamePad.m_state = state;

	//入力デバイスからデータを取得

	//-----------------------------------------------------------------------------
	//ゲームパッドの操作 (カメラ移動)
	//-----------------------------------------------------------------------------

	//if (m_GamePad.m_state.Gamepad.sThumbRX >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) //右
	//{
	//	pcamera->rot.y += 0.03f;
	//	pcamera->posR.x = pcamera->posV.x + sinf(pcamera->rot.y) * 1000;
	//	pcamera->posR.z = pcamera->posV.z + cosf(pcamera->rot.y) * 1000;
	//}

	//if (m_GamePad.m_state.Gamepad.sThumbRX <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) //左
	//{
	//	pcamera->rot.y -= 0.03f;
	//	pcamera->posR.x = pcamera->posV.x + sinf(pcamera->rot.y) * 1000;
	//	pcamera->posR.z = pcamera->posV.z + cosf(pcamera->rot.y) * 1000;
	//}

	//if (m_GamePad.m_state.Gamepad.sThumbRY >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) //上
	//{
	//	pcamera->posV.y = pcamera->posV.y - sinf(0.75)*KAMERA;
	//}

	//if (m_GamePad.m_state.Gamepad.sThumbRY <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) //下
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