//=============================================================================
//
// �`���[�g���A���̏��� [tutorial.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include "tutorial.h"
#include "scene2D.h"
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"fade.h"
#include"sound.h"
#include"press_next.h"

// �ÓI�����o�ϐ��̐錾
LPDIRECT3DTEXTURE9 CTutorial::m_pTexture = NULL;
CPress_Next * CTutorial::m_Press_Next = NULL;

//=============================================================================
// �`���[�g���A���̃R���X�g���N�^
//=============================================================================
CTutorial::CTutorial(int nPriority)
{
	m_apScene2D = NULL;
	m_bNextMode = false;
}

//=============================================================================
// �`���[�g���A���̃f�X�g���N�^
//=============================================================================
CTutorial::~CTutorial()
{

}

//=============================================================================
// �e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CTutorial::Load(void)
{
	CManager *pManager = NULL;

	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/tyutorial001.png",
		&m_pTexture);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���̔j��
//=============================================================================
void CTutorial::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// �`���[�g���A���̏���������
//=============================================================================
HRESULT CTutorial::Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	m_apScene2D = new CScene2D(PRIORITY_BG);

	if (m_apScene2D != NULL)
	{
		m_apScene2D->Init(pos, Size);
		m_apScene2D->BindTextuer(m_pTexture);
	}

	CPress_Next::Load();
	
	m_Press_Next = CPress_Next::Create(D3DXVECTOR3(1100.0f, 700.0f, 0.0f), D3DXVECTOR3(0.0f, 0.1f, 0.0f), D3DXVECTOR2(200.0f, 50.0f),1100.0f);

	return S_OK;
}

//=============================================================================
// �`���[�g���A���̏I������
//=============================================================================
void CTutorial::Uninit(void)
{
	CScene::Relese();
}

//=============================================================================
// �`���[�g���A���̍X�V����
//=============================================================================
void CTutorial::Update(void)
{
	CInputKeyboard *pInputKeyboard = NULL;
	pInputKeyboard = CManager::GetInputKeyboard();

	//�C�ӂŉ����ꂽ���ǂ���
	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true && !m_bNextMode)//ENTER��������
	{
		CManager *pManager = NULL;
		pManager->GetSound()->Stop(CSound::SOUND_LABEL_SUMMER_FOG);
		CFade::SetFade(CManager::MODE_GAME);

		m_bNextMode = true;
	}
}

//=============================================================================
// �`���[�g���A���̕`�揈��
//=============================================================================
void CTutorial::Draw(void)
{

}