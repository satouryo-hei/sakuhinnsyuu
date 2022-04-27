//---------------------
//���͏���
//---------------------
#include "input.h"
//�}�N����`
//�O���[�o���ϐ�
LPDIRECTINPUT8 CInput::m_pInput = NULL;//DirectInput�I�u�W�F�N�g�̃|�C���^
//----------------------------------------
//�R���X�g���N�^
//----------------------------------------
CInput::CInput()
{
	m_pDevice = NULL;
}
//----------------------------------------
//�f�X�g���N�^
//----------------------------------------

CInput::~CInput()
{
}

//----------------------------------------
//����������
//----------------------------------------
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
	{
		return E_FAIL;
	}
	return S_OK;

}
//----------------------------------------
//�I������
//----------------------------------------
void CInput::Uninit(void)
{
	//���̓f�o�C�X�̊J��
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}
	//DirectInput�I�u�W�F�N�g�̊J��
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}

}

