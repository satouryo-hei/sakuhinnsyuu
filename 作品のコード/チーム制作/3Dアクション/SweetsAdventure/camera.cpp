//----------------------------------
//�|���S���̏���
//-----------------------------------
#include "camera.h"
#include "input.h"
#include "Renderer.h"
#include "manager.h"
#include "keyboard.h"
#include "player.h"
#include "mouse.h"
#include "XInput.h"
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCamera::CCamera()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCamera::~CCamera()
{

}
//=============================================================================
// �|���S���̏���������
//=============================================================================
HRESULT CCamera::Init(void)
{
	m_fLong = 300.0f;
	m_posV = D3DXVECTOR3(0.0f, 200.0f, - m_fLong);
	m_posR = D3DXVECTOR3(0.0f, 40.0f,0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	return S_OK;
}

//=============================================================================
// �|���S���̏I������
//=============================================================================
void CCamera::Uninit(void)
{
}

//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CCamera::Update(void)
{
	CMouse *pMouse = CManager::GetMouse();
	CXInput *pGamePad = CManager::GetXInput();

	CInputKeyBoard *pKey = CManager::GetInputKeyboard();
	//	//�����_�̉�]
	//if (pKey->GetPress(DIK_E) == true)
	//{
	//	m_rot.y += 0.01f;
	//	if (m_rot.y > D3DX_PI)
	//	{
	//		m_rot.y -= D3DX_PI;
	//	}

	//	m_posR.x = m_posV.x + sinf(m_rot.y)* m_fLong;
	//	m_posR.z = m_posV.z + cosf(m_rot.y)* m_fLong;
	//}
	//if (pKey->GetPress(DIK_Q) == true)
	//{
	//	m_rot.y += -0.01f;
	//	if (m_rot.y < -D3DX_PI)
	//	{
	//		m_rot.y = D3DX_PI;
	//	}

	//	m_posR.x = m_posV.x + sinf(m_rot.y)* m_fLong;
	//	m_posR.z = m_posV.z + cosf(m_rot.y)* m_fLong;
	//}
	//if (pKey->GetPress(DIK_R) == true)
	//{

	//	m_posR.y += 2.0f;

	//}
	//if (pKey->GetPress(DIK_F) == true)
	//{
	//	m_posR.y += -2.0f;
	//}

	//���_�̉�]
	if (pGamePad->GetGamePad()->m_state.Gamepad.sThumbRX >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
	{
		m_rot.y += 0.04f;
		if (m_rot.y > D3DX_PI)
		{
			m_rot.y = -D3DX_PI;
		}
		m_posV.x = m_posR.x - sinf(m_rot.y)* m_fLong;
		m_posV.z = m_posR.z - cosf(m_rot.y)* m_fLong;
	}
	
	if (pGamePad->GetGamePad()->m_state.Gamepad.sThumbRX <= -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
	{
		m_rot.y += -0.04f;
		if (m_rot.y < -D3DX_PI)
		{
			m_rot.y = D3DX_PI;
		}


		m_posV.x = m_posR.x - sinf(m_rot.y)* m_fLong;
		m_posV.z = m_posR.z - cosf(m_rot.y)* m_fLong;
	}
	if (pGamePad->GetGamePad()->m_state.Gamepad.sThumbRY >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
	{
		m_posV.y += -3.0f;

	}
	if (pGamePad->GetGamePad()->m_state.Gamepad.sThumbRY <= -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
	{
		m_posV.y += 3.0f;

	}
	//���N���b�N
	if (pMouse->GetTrigger(CMouse::MOUSE_LEFT) == true)
	{
		//�N���b�N�����ʒu�̃}�E�X���W���擾
		GetCursorPos(&m_Cursol);

	}
	if (pMouse->GetPress(CMouse::MOUSE_LEFT) == true)
	{

		SetCursorPos(m_Cursol.x, m_Cursol.y);

		m_rot.y += pMouse->GetMousePos().lX*0.01f;
		if (m_rot.y > D3DX_PI)
		{
			m_rot.y = -D3DX_PI;
		}
		m_posV.y += pMouse->GetMousePos().lY*-0.1f;
		m_posV.x = m_posR.x - sinf(m_rot.y)* m_fLong;
		m_posV.z = m_posR.z - cosf(m_rot.y)* m_fLong;
	}
	if (pMouse->GetTrigger(CMouse::MOUSE_RIGHT) == true)
	{
		//�N���b�N�����ʒu�̃}�E�X���W���擾
		GetCursorPos(&m_Cursol);

	}

	else if (pMouse->GetPress(CMouse::MOUSE_RIGHT) == true)
	{

		SetCursorPos(m_Cursol.x, m_Cursol.y);

		m_rot.y += pMouse->GetMousePos().lX*0.001f;
		if (m_rot.y > D3DX_PI)
		{
			m_rot.y = -D3DX_PI;
		}
		m_posR.y += pMouse->GetMousePos().lY*-0.1f;
		m_posR.x = m_posV.x + sinf(m_rot.y)* m_fLong;
		m_posR.z = m_posV.z + cosf(m_rot.y)* m_fLong;
	}
	if (pMouse->GetTrigger(CMouse::MOUSE_WHEEL) == true)
	{
		//�N���b�N�����ʒu�̃}�E�X���W���擾
		GetCursorPos(&m_Cursol);
	}
	else if (pMouse->GetPress(CMouse::MOUSE_WHEEL) == true)
	{
		SetCursorPos(m_Cursol.x, m_Cursol.y);
		m_rot.x += pMouse->GetMousePos().lX*0.1f;

		m_posR.y += pMouse->GetMousePos().lY*-0.1f;
		m_posV.y += pMouse->GetMousePos().lY*-0.1f;
		m_posR.x += cosf(m_rot.y)*(m_fLong*pMouse->GetMousePos().lX*0.001f);
		m_posR.z -= sinf(m_rot.y)*(m_fLong*pMouse->GetMousePos().lX*0.001f);
		m_posV.x += cosf(m_rot.y)*(m_fLong*pMouse->GetMousePos().lX*0.001f);
		m_posV.z -= sinf(m_rot.y)*(m_fLong*pMouse->GetMousePos().lX*0.001f);

	}

	////�ߊ��
	//if (pKey->GetPress(DIK_O) == true)
	//{
	//	m_fLong += 2.0f;
	//	m_posV.x = m_posR.x - sinf(m_rot.y)* m_fLong;
	//	m_posV.z = m_posR.z - cosf(m_rot.y)* m_fLong;
	//	if (m_fLong < 0.0f)
	//	{
	//		m_fLong = m_fLong;
	//	}

	//}
	////�����
	//if (pKey->GetPress(DIK_L) == true)
	//{
	//	m_fLong += -2.0f;
	//	m_posV.x = m_posR.x - sinf(m_rot.y)* m_fLong;
	//	m_posV.z = m_posR.z - cosf(m_rot.y)* m_fLong;
	//	if (m_fLong < 4.0f)
	//	{
	//		m_fLong = 4.0f;
	//	}


	//}

}

//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CCamera::Draw(void)
{

}
//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CCamera::SetPlayerCamera(CPlayer *pPlayer)
{
	m_posR = D3DXVECTOR3(pPlayer->GetPos().x, m_posR.y, pPlayer->GetPos().z);
	m_posV.x = pPlayer->GetPos().x- sinf(m_rot.y)*m_fLong;
	m_posV.z = pPlayer->GetPos().z - cosf(m_rot.y)*m_fLong;

}
//�ݒ�
void CCamera::SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�̃|�C���^
	pDevice = CManager::GetRenderer()->GetDevice();

	//�r���[�|�[�g�̐ݒ�
	//pDevice->SetViewport(&m_viewport);
	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);
	//�v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(70.0f),//�J�����̉�p
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,//��ʔ䗦!!!�r���[�|�[�g���g���Ƃ��r���[�|�[�g�̕��������g��
		10.0f,//��O�̕`�搧��
		10000.0f);//���̕`�搧��
				  //�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);
	//�r���[�}�g���b�N�X���쐬
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU);
	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}
