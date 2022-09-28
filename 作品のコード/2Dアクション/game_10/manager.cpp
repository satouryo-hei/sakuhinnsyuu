//=============================================================================
//
// �Ǘ����� [maneger.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include"manager.h"
#include"renderer.h"
#include"scene.h"
#include"input.h"
#include"texture.h"
#include"title.h"
#include"result.h"
#include"game.h"
#include"fade.h"
#include"camera.h"
#include"light.h"
#include"select.h"
#include"tutorial.h"

//=============================================================================
// �ÓI�����o�֐��̐錾
//=============================================================================
CRenderer *CManager::m_pRenderer = NULL;
CInputKeyboard *CManager::m_pInputKeyboard = NULL;
CCamera *CManager::m_pCamera = NULL;
CLight *CManager::m_pLight[3] = {};
CTexture *CManager::m_pTexture = NULL;
CManager::MODE CManager::m_mode = MODE_TITLE;
CTitle*CManager::m_pTitle = NULL;
CSelect*CManager::m_pSelect = NULL;
CTutorial*CManager::m_pTutorial = NULL;
CGame*CManager::m_pGame = NULL;
CResult*CManager::m_pResult = NULL;
CManager::MODE CManager::m_Nextmode = MODE_INVALID;
CFade * CManager::m_pFade = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CManager::CManager()
{
}

//=============================================================================
//�@�f�X�g���N�^
//=============================================================================
CManager::~CManager()
{
}


//=============================================================================
// ����������
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance,HWND hWnd, bool bWindow)
{	
	// Renderer�̓��I�������̊m��
	m_pRenderer = new CRenderer;
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Init(hWnd, bWindow);
	}


	// �L�[�{�[�h�̓��I�������̊m��
	m_pInputKeyboard = new CInputKeyboard;
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Init(hInstance, hWnd);
	}

	// �e�N�X�`���̓��I�������̊m��
	m_pTexture = new CTexture;
	if (m_pTexture != NULL)
	{
		m_pTexture->Init();
	}

	// �J�����̓��I�������̊m��
	m_pCamera = new CCamera;
	if (m_pCamera != NULL)
	{
		m_pCamera->Init();
	}

	for (int nLight = 0; nLight < 3; nLight++)
	{
		// ���C�g�̓��I�������̊m��	
		m_pLight[nLight] = new CLight;
	}

	if (m_pLight[0] != NULL)
	{
		m_pLight[0]->Init(D3DXVECTOR3(0.22f, -0.87f, 0.44f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	if (m_pLight[1] != NULL)
	{
		m_pLight[1]->Init(D3DXVECTOR3(-0.18f, 0.88f, -0.44f), D3DXCOLOR(0.65f, 0.65f, 0.65f, 1.0f));
	}
	if (m_pLight[2] != NULL)
	{
		m_pLight[2]->Init(D3DXVECTOR3(0.89f, -0.11f, 0.44f), D3DXCOLOR(0.15f, 0.15f, 0.15f, 1.0f));
	}

	//SetMode(m_mode);

	m_pFade = CFade::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), 
		D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), CManager::MODE_TITLE);
	return S_OK;
}


//=============================================================================
// �I������
//=============================================================================
void CManager::Uninit(void)
{
	CScene::ReleaseAll();

	if (m_pInputKeyboard != NULL)
	{
		// �I������
		m_pInputKeyboard->Uninit();

		// ���I�������̊m�ۂ������̂����
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}
	
	if (m_pRenderer != NULL)
	{
		// �I������
		m_pRenderer->Uninit();

		// ���I�������̊m�ۂ������̂����
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	if (m_pTexture != NULL)
	{
		// �I������
		m_pTexture->Uninit();

		// ���I�������̊m�ۂ������̂����
		delete m_pTexture;
		m_pTexture = NULL;
	}
}


//=============================================================================
// �X�V����
//=============================================================================
void CManager::Update(void)
{
	// �X�V����
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Update();
	}
	// �X�V����
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}

	m_pCamera->Update();
}


//=============================================================================
// �`�揈��
//=============================================================================
void CManager::Draw(void)
{
	m_pCamera->SetCamera();

	if (m_pRenderer != NULL)
	{
		// �`�揈��
		m_pRenderer->Draw();
	}
}

//=============================================================================
// ���[�h�̐ݒ菈��
//=============================================================================
void CManager::SetMode(MODE mode)
{
	m_Nextmode = mode;
}

//=============================================================================
// ���[�h�̐؂�ւ�����
//=============================================================================
void CManager::ChangeMode(void)
{
	if (m_Nextmode == MODE_INVALID)
	{
		return;
	}

	switch (m_mode)
	{
	case MODE_TITLE:
		if (m_pTitle != NULL)
		{
			m_pTitle->Uninit();
			m_pTitle = NULL;
		}
		break;

	case MODE_SELECT:
		if (m_pSelect != NULL)
		{
			m_pSelect->Uninit();
			m_pSelect = NULL;
		}
		break;

	case MODE_TUTORIAL:
		if (m_pTutorial != NULL)
		{
			m_pTutorial->Uninit();
			m_pTutorial = NULL;
		}
		break;

	case MODE_GAME:
		if (m_pGame != NULL)
		{
			m_pGame->Uninit();
			m_pGame = NULL;
		}
		break;

	case MODE_RESULT:
		if (m_pResult != NULL)
		{
			m_pResult->Uninit();
			m_pResult = NULL;
		}
		break;

	default:
		break;
	}

	CScene::ReleaseAll();

	switch (m_Nextmode)
	{
	case MODE_TITLE:
		m_pTitle = new CTitle;
		if (m_pTitle != NULL)
		{
			m_pTitle->Init(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
		}
		break;

	case MODE_SELECT:
		m_pSelect = new CSelect;
		if (m_pSelect != NULL)
		{
			m_pSelect->Init(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
		}
		break;

	case MODE_TUTORIAL:
		m_pTutorial = new CTutorial;
		if (m_pTutorial != NULL)
		{
			m_pTutorial->Init(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
		}
		break;

	case MODE_GAME:
		m_pGame = new CGame;
		if (m_pGame != NULL)
		{
			m_pGame->Init(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
		}
		break;

	case MODE_RESULT:
		m_pResult = new CResult;
		if (m_pResult != NULL)
		{
			m_pResult->Init(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
		}
		break;

	default:
		break;
	}
	m_mode = m_Nextmode;
	m_Nextmode = MODE_INVALID;
}