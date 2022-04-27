//---------------------
//�L�[�{�[�h�̓��͏���
//---------------------
#include"mouse.h"

//----------------------------------------
//�R���X�g���N�^
//----------------------------------------

CMouse::CMouse()
{

}
//----------------------------------------
//�f�X�g���N�^
//----------------------------------------

CMouse::~CMouse()
{

}

//----------------------------------------
//����������
//----------------------------------------
HRESULT CMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);
	if (FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIMouse2)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	m_pDevice->Acquire();

	return S_OK;

}
//----------------------------------------
//�I������
//----------------------------------------
void CMouse::Uninit(void)
{
	CInput::Uninit();
}
//----------------------------------------
//�X�V����
//----------------------------------------
void CMouse::Update(void)
{
	DIMOUSESTATE2 aKeyState;
	int nCntKey;

	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState)))
	{
		for (nCntKey = 0; nCntKey < MOUSE_MAX;
			nCntKey++)
		{
			m_aKeyStateTrigger.rgbButtons[nCntKey] = (m_aKeyState.rgbButtons[nCntKey] ^ aKeyState.rgbButtons[nCntKey])&aKeyState.rgbButtons[nCntKey];

			m_aKeyState = aKeyState;//�L�[�{�[�h�̓��͏��̕ۑ�
		}
	}

	else
	{
		m_pDevice->Acquire();
	}
}
//----------------------------------------
//�L�[�{�[�h�̓��͏����擾
//----------------------------------------
bool CMouse::GetPress(int nKey)
{
	//ShowCursor(TRUE);

	return(m_aKeyState.rgbButtons[nKey] & 0x80) ? true : false;
}
bool CMouse::GetTrigger(int nKey)
{
	return (m_aKeyStateTrigger.rgbButtons[nKey] & 0x80) ? true : false;
}