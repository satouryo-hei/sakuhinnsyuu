//--------------------------------------
//�}�l�[�W���[�̏���
//--------------------------------------
#include "manager.h"
#include "Renderer.h"
#include "scene.h"
#include "scene2D.h"
#include "keyboard.h"
#include "texture.h"
#include "Scene3D.h"
#include "camera.h"
#include "light.h"
#include "player.h"
#include "model_spawner.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "fade.h"
#include "XInput.h"
#include "mouse.h"
#include "sound.h"

//�ÓI�����o�ϐ��錾
CInputKeyBoard	*CManager::m_pInputKeyboard = NULL;
CRenderer		*CManager::m_pRenderer = NULL;
CTexture		*CManager::m_pTexture = NULL;
CCamera			*CManager::m_pCamera = NULL;
CLight			*CManager::m_pLight[3] = {};
CPlayer			*CManager::m_pPlayer = NULL;
CModel_Spawner	*CManager::m_pModel = NULL;
CGame			*CManager::m_pGame = NULL;
CTitle			*CManager::m_pTitle = NULL;
CResult			*CManager::m_pResult = NULL;
CFade			*CManager::m_Fade = NULL;
CXInput			*CManager::m_XInput = NULL;
CManager::MODE	 CManager::m_Mode = MODE_GAME;		// �������[�h
CMouse			*CManager::m_Mouse = NULL;
CSound			*CManager::m_pSound = NULL;

bool			CManager::m_bPause = false;
bool			CManager::m_bStop = false;
bool			CManager::m_bEnd = false;
bool			CManager::m_bClear = true;

int g_nTimer = 0;

//--------------------------------------------
//�R���X�g���N�^
//--------------------------------------------
CManager::CManager()
{
}
//--------------------------------------------
//�f�X�g���N�^
//--------------------------------------------
CManager::~CManager()
{
}
//--------------------------------------------
// ������
//--------------------------------------------
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	// �����_���[�̐���
	if (m_pRenderer == NULL)
	{
		m_pRenderer = new CRenderer;
	}

	// �e�N�X�`���̐���
	if (m_pTexture == NULL)
	{
		//�C���X�^���X����
		m_pTexture = new CTexture;
	}

	// �����_���[�̏�����
	if (m_pRenderer != NULL)
	{
		if (FAILED(m_pRenderer->Init(hInstance, hWnd, bWindow)))
		{
			return-1;
		}

		// �e�N�X�`���̓ǂݍ���
		m_pTexture->Init();
	}

	// �T�E���h�̐���
	if (m_pSound == NULL)
	{
		m_pSound = new CSound;
		m_pSound->InitSound();
	}

	//�t�F�[�h�̐���
	if (m_Fade == NULL)
	{
		m_Fade = CFade::Create(CTexture::Text, m_Mode);

		SetMode(m_Mode);

		//���[�h�̐ݒ�
	}

	// �L�[�{�[�h�̐���
	if (m_pInputKeyboard == NULL)
	{
		m_pInputKeyboard = new CInputKeyBoard;
		if (m_pInputKeyboard != NULL)
		{
			m_pInputKeyboard->Init(hInstance, hWnd);
		}
	}

	// �}�E�X�̐���
	if (m_Mouse == NULL)
	{
		m_Mouse = new CMouse;
		m_Mouse->Init(hInstance, hWnd);
	}

	//Xinput����
	if (m_XInput == NULL)
	{
		m_XInput = new CXInput;
	}

	// ���C�g�̐���
	for (int nLight = 0; nLight < 3; nLight++)
	{
		m_pLight[nLight] = new CLight;
	}
	m_pLight[0]->Init(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.22f, -0.87f, 0.44f));
	m_pLight[1]->Init(D3DXCOLOR(0.65f, 0.65f, 0.65f, 1.0f), D3DXVECTOR3(-0.18f, 0.88f, -0.44f));
	m_pLight[2]->Init(D3DXCOLOR(0.15f, 0.15f, 0.15f, 1.0f), D3DXVECTOR3(0.89f, -0.11f, 0.44f));

	// �J�����̐���
	if (m_pCamera == NULL)
	{
		m_pCamera = new CCamera;
		m_pCamera->Init();
	}

	//if (m_pPlayer == NULL)
	//{
	//	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//}
	
	return S_OK;
}
//--------------------------------------------
// �I��
//--------------------------------------------
void CManager::Uninit(void)
{
	//�L�[�{�[�h�̔j��
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}

	// ���C�g�̔j��
	for (int nLight = 0; nLight < 3; nLight++)
	{
		if (m_pLight[nLight] != NULL)
		{
			delete m_pLight[nLight];
			m_pLight[nLight] = NULL;
		}
	}

	// �}�E�X�̔j��
	if (m_Mouse != NULL)
	{
		m_Mouse->Uninit();
		delete m_Mouse;
		m_Mouse = NULL;
	}

	// �V�[���̔j��
	CScene::Delete();

	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Uniinit();
		delete m_pTexture;
		m_pTexture = NULL;
	}

	// �t�F�[�h�̔j��
	if (m_Fade != NULL)
	{
		m_Fade->Uninit();
		m_Fade = NULL;
	}

	// �����_���[�̔j��
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	// �T�E���h�̔j��
	if (m_pSound != NULL)
	{
		m_pSound->UninitSound();
		delete m_pSound;
		m_pSound = NULL;
	}
}
//--------------------------------------------
// �X�V
//--------------------------------------------
void CManager::Update(void)
{
	// �����_���[�̍X�V
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}

	//�L�[�{�[�h�̍X�V
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Update();
	}

	// �Q�[���p�b�h�̍X�V
	if (m_XInput != NULL)
	{
		m_XInput->UpdateGamepad();
	}

	// �}�E�X�̍X�V
	if (m_Mouse != NULL)
	{
		m_Mouse->Update();
	}

	// �J�����̍X�V
	m_pCamera->Update();

	// ���[�h���̍X�V
	switch (m_Mode)
	{
	case MODE_TITLE:		//�^�C�g�����
		if (m_pTitle != NULL)
		{
			m_pTitle->Update();
		}
		break;

	case MODE_GAME:			//�Q�[�����
		if (m_pGame != NULL)
		{
			m_pGame->Update();
		}
		break;

	case MODE_RESULT:		//���U���g���
		if (m_pResult != NULL)
		{
			m_pResult->Update();
		}
		break;
	}
}
//--------------------------------------------
// �`��
//--------------------------------------------
void CManager::Draw(void)
{
	// �����_���[�̕`��
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();
	}

	// �J�����̐ݒ�
	m_pCamera->SetCamera();

	// ���[�h���̕`��
	switch (m_Mode)
	{
	case MODE_TITLE:		//�^�C�g�����
		if (m_pTitle != NULL)
		{
			m_pTitle->Draw();
		}
		break;

	case MODE_GAME:			//�Q�[�����
		if (m_pGame != NULL)
		{
			m_pGame->Draw();
		}
		break;

	case MODE_RESULT:		//���U���g���
		if (m_pResult != NULL)
		{
			m_pResult->Draw();
		}
		break;
	}
}

//-----------------------------------------------------------------------------
// Renderer�擾����
//-----------------------------------------------------------------------------
CRenderer *CManager::GetRenderer(void)
{
	return m_pRenderer;
}

//-----------------------------------------------------------------------------
// �L�[�{�[�h�̃C���X�^���X�擾����
//-----------------------------------------------------------------------------
CInputKeyBoard *CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}

//-----------------------------------------------------------------------------
// �e�N�X�`���̃C���X�^���X�擾����
//-----------------------------------------------------------------------------
CTexture *CManager::GetTexture(void)
{
	return m_pTexture;
}

//-----------------------------------------------------------------------------
// ���[�h�̏���
//-----------------------------------------------------------------------------
CManager::MODE CManager::GetMode(void)
{
	return m_Mode;
}

//-----------------------------------------------------------------------------
// ���[�h�̏���
//-----------------------------------------------------------------------------
void CManager::SetMode(MODE mode)
{
	m_bEnd = false;

	switch (m_Mode)
	{
	case MODE_TITLE:		//�^�C�g�����
		if (m_pTitle != NULL)
		{
			m_pSound->StopSound(m_pSound->SOUND_LABEL_BGM_TITLE);
			m_pTitle->Uninit();
			delete m_pTitle;
			m_pTitle = NULL;
		}
		break;

	case MODE_GAME:			//�Q�[�����
		if (m_pGame != NULL)
		{
			m_pSound->StopSound(m_pSound->SOUND_LABEL_BGM_GAME);
			m_pGame->Uninit();
			delete m_pGame;
			m_pGame = NULL;
		}
		break;

	case MODE_RESULT:		//���U���g���
		if (m_pResult != NULL)
		{
			m_pSound->StopSound(m_pSound->SOUND_LABEL_BGM_RESULT);
			m_pResult->Uninit();
			delete m_pResult;
			m_pResult = NULL;
		}
		break;
	}

	//���ݑI�����Ă��郂�[�h�̍폜+���̃��[�h�Ő��������I�u�W�F�N�g�̍폜
	CScene::Delete();

	//���Ɉڍs���郂�[�h�̐���
	switch (mode)
	{
	case MODE_TITLE:		//�^�C�g�����
		if (m_pTitle == NULL)
		{
			m_bClear = false;
			m_pTitle = new CTitle;
			m_pTitle->Init();
			m_pSound->PlaySoundA(m_pSound->SOUND_LABEL_BGM_TITLE);	// �^�C�g���T�E���h
		}
		break;
	case MODE_GAME:			//�Q�[�����
		if (m_pGame == NULL)
		{
			m_pGame = new CGame;
			m_pGame->Init();
			m_pSound->PlaySoundA(m_pSound->SOUND_LABEL_BGM_GAME);	// �^�C�g���T�E���h
		}
		break;
	case MODE_RESULT:		//���U���g���
		if (m_pResult == NULL)
		{
			m_pResult = new CResult;
			m_pResult->Init();
			m_pSound->PlaySoundA(m_pSound->SOUND_LABEL_BGM_RESULT);	// ���U���g�T�E���h
		}
		break;
	}
	//���̃��[�h�����݂̃��[�h�ɏ㏑��
	m_Mode = mode;
}