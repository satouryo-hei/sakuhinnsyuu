//=============================================================================
//
// ���͂̏��� [input.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include "input.h"

//=============================================================================
// �ÓI�����o�֐��̐錾
//=============================================================================
LPDIRECTINPUT8 CInput::m_pInput = NULL;

//=============================================================================
// ���̓N���X�̃R���X�g���N�^
//=============================================================================
CInput::CInput()
{
	m_pDevice = NULL; //���̓f�o�C�X(�L�[�{�[�h)�ւ̃|�C���^�̏�����
}

//=============================================================================
// ���̓N���X�̃f�X�g���N�^
//=============================================================================
CInput::~CInput()
{
}

//=============================================================================
// ���̓N���X�̏���������
//=============================================================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT hr = S_FALSE;

	//Ditrect Input�I�u�W�F�N�g�̃|�C���^��NULL��������
	if (m_pInput == NULL)
	{
		// ���̓f�o�C�X����͂��ꂽ�����f����
		hr = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL);
	}
	return hr;	
}

//=============================================================================
// ���̓N���X�̏I������
//=============================================================================
void CInput::Uninit(void)
{
	// ���̓f�o�C�X(�L�[�{�[�h�̊J��)
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();

		m_pDevice->Release();

		m_pDevice = NULL;
	}

	// DirectInput�I�u�W�F�N�g�̊J��
	if (m_pInput != NULL)
	{	
		m_pInput->Release();
		
		m_pInput = NULL;
	}
}

//=============================================================================
// �L�[�{�[�h���̓N���X�̃R���X�g���N�^
//=============================================================================
CInputKeyboard::CInputKeyboard()
{
	memset(&m_aKeyState[0], 0, sizeof(m_aKeyState));					//0�N���A
	memset(&m_aKeyStateTrigger[0], 0, sizeof(m_aKeyStateTrigger));		//0�N���A
	memset(&m_aKeyStateRelease[0], 0, sizeof(m_aKeyStateRelease));		//0�N���A
}

//=============================================================================
// �L�[�{�[�h���̓N���X�̃f�X�g���N�^
//=============================================================================
CInputKeyboard::~CInputKeyboard()
{
}

//=============================================================================
// �L�[�{�[�h���̓N���X�̏���������
//=============================================================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	//���K�f�o�C�X�̐���
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


//=============================================================================
// �L�[�{�[�h���̓N���X�̏I������
//=============================================================================
void CInputKeyboard::Uninit(void)
{
	// ���̓N���X�̏I�������̌Ăяo��
	CInput::Uninit();
}


//=============================================================================
// �L�[�{�[�h���̓N���X�̍X�V����
//=============================================================================
void CInputKeyboard::Update(void)
{
	// �L�[�{�[�h�̓��͏��
	BYTE aKeyState[NUM_KEY_MAX];

	// �J�E���g�p�̕ϐ�
	int nCntKey;

	// ���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			/*
			AND(1&1=1����ȊO��0)
			XOR(�L�����b�g(^)1^1�܂���0^0�Ȃ�0,
			1^0�܂���0^1�Ȃ�1)
			�g���K�[���(0��1)= (�v���X���(0��1)^���͏��(0��1))&���͏��(0��1)
			*/
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];

			/*
			AND(1&1=1����ȊO��0)
			XOR(�L�����b�g(^)1^1�܂���0^0�Ȃ�0,
			1^0�܂���0^1�Ȃ�1)
			�����[�X���(0��1)= (�v���X���(0��1)^���͏��(0��1))&�v���X���(0��1)
			*/
			m_aKeyStateRelease[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & m_aKeyState[nCntKey];

			m_aKeyState[nCntKey] = aKeyState[nCntKey];// �L�[�{�[�h�̓��͏��ۑ�
		}
	}
	else
	{
		m_pDevice->Acquire();// �L�[�{�[�h�ւ̃A�N�Z�X�����l��
	}
}


//=============================================================================
// �L�[�{�[�h�̓��͏��(�v���X���)���擾
//=============================================================================
bool CInputKeyboard::GetPress(int nKey)
{
	/* 
	m_aKeyState[nKey] &(AND(1&1=1����ȊO��0)) 128(0b1000 0000)
	a?b:c a���^�Ȃ�b, a���U�Ȃ�c���Ԃ����
	(...)?true:false�͐^(1)�Ȃ�true, �U(0)�Ȃ�false*/
	return(m_aKeyState[nKey] & 0x80) ? true : false;
}


//=============================================================================
// �L�[�{�[�h�̓��͏��(�g���K�[���)���擾
//=============================================================================
bool CInputKeyboard::GetTrigger(int nKey)
{
	/* m_aKeyStateTrigger[nKey] &(AND(1&1=1����ȊO��0)) 128(0b1000 0000)
	a?b:c a���^�Ȃ�b, a���U�Ȃ�c���Ԃ����
	(...)?true:false�͐^(1)�Ȃ�true, �U(0)�Ȃ�false*/
	return(m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}


//=============================================================================
// �L�[�{�[�h�̓��͏��(�����[�X���)���擾
//=============================================================================
bool CInputKeyboard::GetRelease(int nKey)
{
	/* m_aKeyStateRelease[nKey] &(AND(1&1=1����ȊO��0)) 128(0b1000 0000)
	a?b:c a���^�Ȃ�b, a���U�Ȃ�c���Ԃ����
	(...)?true:false�͐^(1)�Ȃ�true, �U(0)�Ȃ�false*/
	return(m_aKeyStateRelease[nKey] & 0x80) ? true : false;
}