//=============================================================================
//
// ���C������ [main.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include"manager.h"
#include"renderer.h"
#include"scene.h"
#include"scene2D.h"
#include"input.h"
#include"scene3D.h"
#include"camera.h"
#include"light.h"
#include"texture.h"
#include"effect_manager.h"

//�ÓI�����o�ϐ��錾
CRenderer *CManager::m_pRenderer = NULL;
CInputKeyboard *CManager::m_pInputKeyboard = NULL;
CScene3D*CManager::m_pScene3D = NULL;
CCamera *CManager::m_pCamera = NULL;
CLight *CManager::m_pLight[3] = {};
CTexture *CManager::m_pTexture = NULL;
CEffect_Manager*CManager::m_pEffect_Manager = NULL;

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

	// �J�����̓��I�������̊m��
	m_pCamera = new CCamera;
	if (m_pCamera != NULL)
	{	
		m_pCamera->Init();
	}

	// ���C�g�̓��I�������̊m��
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

	// �e�N�X�`���̓��I�������̊m��
	m_pTexture = new CTexture;
	if (m_pTexture != NULL)
	{
		m_pTexture->Init();
	}

	m_pScene3D = CScene3D::Creste(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(150.0f, 0.0f, 150.0f));
	m_pEffect_Manager = CEffect_Manager::Create(CEffect_Manager::EffectType_NOMAL);

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