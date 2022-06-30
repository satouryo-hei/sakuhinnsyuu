//=============================================================================
//
// �}�l�[�W���[���� [manager.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include"manager.h"
#include"renderer.h"
#include"scene.h"
#include"scene2D.h"
#include"input.h"
#include"ui.h"
#include"ui_manager.h"
#include"texture.h"
#include"imgui_window.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
CRenderer *CManager::m_pRenderer = NULL;
CInputKeyboard *CManager::m_InputKeyboard = NULL;
CUI_Manager *CManager::m_pUi_manager = NULL;
CTexture *CManager::m_pTexture = NULL;
CImgui_Window* CManager::m_pImguiWindow = NULL;

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
	// NULL�`�F�b�N
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Init(hWnd, bWindow);
	}

	// �L�[�{�[�h�̓��I�������̊m��
	m_InputKeyboard = new CInputKeyboard;
	// NULL�`�F�b�N
	if (m_InputKeyboard != NULL)
	{
		m_InputKeyboard->Init(hInstance, hWnd);
	}

	// IMGUI�̃E�B���h�E�̓��I�������̊m��
	m_pImguiWindow = new CImgui_Window;
	// NULL�`�F�b�N
	if (m_pImguiWindow != NULL)
	{
		m_pImguiWindow->Init(hWnd, bWindow);
	}

	// �摜�̓��I�������̊m��
	m_pTexture = new CTexture;
	// NULL�`�F�b�N
	if (m_pTexture != NULL)
	{
		m_pTexture->Init();
	}

	m_pUi_manager = CUI_Manager::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f), D3DXVECTOR3(100.0f, 50.0f, 0.0f));
	return S_OK;
}


//=============================================================================
// �}�l�[�W���[�̏I������
//=============================================================================
void CManager::Uninit(void)
{
	// ���ׂẴI�u�W�F�N�g�̊J������
	CScene::ReleaseAll();

	// NULL�`�F�b�N
	if (m_InputKeyboard != NULL)
	{
		// �I������
		m_InputKeyboard->Uninit();

		// ���I�������̊m�ۂ������̂����
		delete m_InputKeyboard;
		m_InputKeyboard = NULL;
	}

	// NULL�`�F�b�N
	if (m_pImguiWindow != NULL)
	{//ImgUI�I������
		m_pImguiWindow->Uninit();

		// ���I�������̊m�ۂ������̂����
		delete m_pImguiWindow;
		m_pImguiWindow = NULL;
	}


	// NULL�`�F�b�N
	if (m_pTexture != NULL)
	{
		// �I������
		m_pTexture->Uninit();

		// ���I�������̊m�ۂ������̂����
		delete m_pTexture;
		m_pTexture = NULL;
	}

	// NULL�`�F�b�N
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
	// NULL�`�F�b�N
	if (m_pImguiWindow != NULL)
	{
		// IMGUI�̃E�B���h�E�̍X�V����
		m_pImguiWindow->Update();
	}

	// NULL�`�F�b�N
	if (m_InputKeyboard != NULL)
	{
		// �L�[�{�[�h�̍X�V����
		m_InputKeyboard->Update();
	}

	// NULL�`�F�b�N
	if (m_pRenderer != NULL)
	{	
		// �X�V����
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