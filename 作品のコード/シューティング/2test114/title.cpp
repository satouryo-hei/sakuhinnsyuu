//=============================================================================
//
// �^�C�g���̏��� [title.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include "title.h"
#include "scene2D.h"
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"fade.h"
#include"title_logo.h"
#include"sound.h"
#include"press_next.h"

// �ÓI�����o�ϐ��̐錾
LPDIRECT3DTEXTURE9 CTitle::m_pTexture = NULL;
CTitle_Logo* CTitle::m_pTitle_Logo = NULL;
CPress_Next * CTitle::m_Press_Next = NULL;
//=============================================================================
// �^�C�g���̃R���X�g���N�^
//=============================================================================
CTitle::CTitle(int nPriority)
{
	m_apScene2D = NULL;
	m_bNextMode = false; 
}

//=============================================================================
// �^�C�g���̃f�X�g���N�^
//=============================================================================
CTitle::~CTitle()
{

}

//=============================================================================
// �e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CTitle::Load(void)
{
	CManager *pManager = NULL;

	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/woods002.jpg",
		&m_pTexture);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���̔j��
//=============================================================================
void CTitle::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// �^�C�g���̏���������
//=============================================================================
HRESULT CTitle::Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	m_apScene2D = new CScene2D(PRIORITY_BG);

	if (m_apScene2D != NULL)
	{
		m_apScene2D->Init(pos, Size);
		m_apScene2D->BindTextuer(m_pTexture);
	}

	// �e�N�X�`���̓ǂݍ���
	CTitle_Logo::Load();
	CPress_Next::Load();

	// �^�C�g�����S�̐���
	m_pTitle_Logo = CTitle_Logo::Create(D3DXVECTOR3(640.0f, 100.0f, 0.0f), D3DXVECTOR2(640.0f, 320.0f));

	// ENTER���������玟�ɂ̐���
	m_Press_Next = CPress_Next::Create(D3DXVECTOR3(640.0f, 740.0f, 0.0f), D3DXVECTOR3(0.0f,5.0f, 0.0f), D3DXVECTOR2(300.0f, 100.0f), 540.0f);

	CManager *pManager = NULL;
	pManager->GetSound()->Play(CSound::SOUND_LABEL_SUMMER_FOG);

	return S_OK;
}

//=============================================================================
// �^�C�g���̏I������
//=============================================================================
void CTitle::Uninit(void)
{
	// �e�N�X�`���̔j��
	CTitle_Logo::Unload();
	CPress_Next::Unload();

	// �V�[���̔j��
	CScene::Relese();
}

//=============================================================================
// �^�C�g���̍X�V����
//=============================================================================
void CTitle::Update(void)
{
	CInputKeyboard *pInputKeyboard = NULL;
	pInputKeyboard = CManager::GetInputKeyboard();


	//�C�ӂŉ����ꂽ���ǂ���
	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true && !m_bNextMode)//ENTER��������
	{
		// �`���[�g���A���ɑJ��
		CFade::SetFade(CManager::MODE_TUTORIAL);
		m_bNextMode = true;
	}
}

//=============================================================================
// �^�C�g���̕`�揈��
//=============================================================================
void CTitle::Draw(void)
{

}