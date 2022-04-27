//=============================================================================
//
// �}�l�[�W���[���� [manager.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"sound.h"
#include"title.h"
#include"tutorial.h"
#include"game.h"
#include"result.h"
#include"fade.h"
#include"title_logo.h"
#include"texture.h"

//=============================================================================
// �ÓI�����o�ϐ��̐錾
//=============================================================================
CRenderer *CManager::m_pRenderer = NULL;
CInputKeyboard *CManager::m_pInputKeyboard = NULL;
CSound *CManager::m_pSound = NULL;
CTitle*CManager::m_pTitle = NULL;
CTutorial*CManager::m_pTutorial = NULL;
CGame*CManager::m_pGame = NULL;
CResult*CManager::m_pResult = NULL;
CManager::MODE CManager::m_mode = CManager::MODE_TITLE;
CFade * CManager::m_pFade = NULL;
CTexture * CManager::m_pTexture = NULL;
CManager::MODE CManager::m_Nextmode = CManager::MODE_INVALID;

//=============================================================================
// �}�l�[�W���[�̃R���X�g���N�^
//=============================================================================
CManager::CManager()
{
}

//=============================================================================
// �}�l�[�W���[�̃f�X�g���N�^
//=============================================================================
CManager::~CManager()
{
}


//=============================================================================
// �}�l�[�W���[�̏���������
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

	// ���̓��I�������̊m��
	m_pSound = new CSound;
	if (m_pSound != NULL)
	{
		m_pSound->Init(hWnd);
	}

	m_pTexture = new CTexture;
	if (m_pTexture != NULL)
	{
		m_pTexture->Init();
	}

	//SetMode(m_mode);
	
	m_pFade = CFade::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), CManager::MODE_TITLE);

	CTitle::Load();

	CTutorial::Load();

	CResult::Load();

	return S_OK;
}


//=============================================================================
// �}�l�[�W���[�̏I������
//=============================================================================
void CManager::Uninit(void)
{
	CScene::ReleseAll();

	CTitle::Unload();

	CTutorial::Unload();

	CResult::Unload();

	if (m_pTexture != NULL)
	{
		// �I������
		m_pTexture->Uninit();

		// ���I�������̊m�ۂ������̂����
		delete m_pTexture;
		m_pTexture = NULL;
	}

	if (m_pSound != NULL)
	{
		// �I������
		m_pSound->Uninit();

		// ���I�������̊m�ۂ������̂����
		delete m_pSound;
		m_pSound = NULL;
	}

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
}


//=============================================================================
// �}�l�[�W���[�̍X�V����
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
}


//=============================================================================
// �}�l�[�W���[�̕`�揈��
//=============================================================================
void CManager::Draw(void)
{
	if (m_pRenderer != NULL)
	{
		// �`�揈��
		m_pRenderer->Draw();
	}
}

//�擾�����֌W
#if 1 //�擾�����֌W
//=============================================================================
// CRenderer�̎擾����
//=============================================================================
CRenderer* CManager::GetRenderer(void)
{
	return m_pRenderer;
}

//=============================================================================
// �L�[�{�[�h�̎擾����
//=============================================================================
CInputKeyboard* CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}

//=============================================================================
// ���̎擾����
//=============================================================================
CSound *CManager::GetSound(void)
{
	return m_pSound;
}

#endif

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

	CScene::ReleseAll();

	switch (m_Nextmode)
	{
	case MODE_TITLE:
		m_pTitle = new CTitle;
		if (m_pTitle != NULL)
		{
			m_pTitle->Init(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT));
		}
		break;

	case MODE_TUTORIAL:
		m_pTutorial = new CTutorial;
		if (m_pTutorial != NULL)
		{
			m_pTutorial->Init(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR2(SCREEN_WIDTH / 1.5f, SCREEN_HEIGHT / 1.5f));
		}
		break;

	case MODE_GAME:
		m_pGame = new CGame;
		if (m_pGame != NULL)
		{
			m_pGame->Init(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR2(0, 0));
		}
		break;

	case MODE_RESULT:
		m_pResult = new CResult;
		if (m_pResult != NULL)
		{
			m_pResult->Init(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT));
		}
		break;

	default:
		break;
	}
	m_mode = m_Nextmode;
	m_Nextmode = MODE_INVALID;
}