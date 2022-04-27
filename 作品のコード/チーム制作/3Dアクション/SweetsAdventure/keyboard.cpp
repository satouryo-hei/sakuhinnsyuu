//---------------------
//�L�[�{�[�h�̓��͏���
//---------------------
#include"keyboard.h"

//----------------------------------------
//�R���X�g���N�^
//----------------------------------------

CInputKeyBoard::CInputKeyBoard()
{

}
//----------------------------------------
//�f�X�g���N�^
//----------------------------------------

CInputKeyBoard::~CInputKeyBoard()
{

}

//----------------------------------------
//����������
//----------------------------------------
HRESULT CInputKeyBoard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
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
void CInputKeyBoard::Uninit(void)
{
	CInput::Uninit();
}
//----------------------------------------
//�X�V����
//----------------------------------------
void CInputKeyBoard::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];
	int nCntKey;

	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX;
			nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey])&aKeyState[nCntKey];

			m_aKeyState[nCntKey] = aKeyState[nCntKey];//�L�[�{�[�h�̓��͏��̕ۑ�
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
bool CInputKeyBoard::GetPress(int nKey)
{
	return(m_aKeyState[nKey] & 0x80) ? true : false;

}
bool CInputKeyBoard::GetTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}