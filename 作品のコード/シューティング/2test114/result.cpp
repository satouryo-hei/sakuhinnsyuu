//=============================================================================
//
// ���U���g�̏��� [result.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include "result.h"
#include "scene2D.h"
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"fade.h"
#include"ranking.h"
#include"number.h"
#include"sound.h"

//=============================================================================
// �ÓI�����o�ϐ��̐錾
//=============================================================================
LPDIRECT3DTEXTURE9 CResult::m_pTexture = NULL;

//=============================================================================
// ���U���g�̃R���X�g���N�^
//=============================================================================
CResult::CResult(int nPriority)
{
	m_apScene2D = NULL;
	m_bNextMode = false;
}

//=============================================================================
// ���U���g�̃f�X�g���N�^
//=============================================================================
CResult::~CResult()
{

}

//=============================================================================
// �e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CResult::Load(void)
{
	CManager *pManager = NULL;

	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/result000.jpg",
		&m_pTexture);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���̔j��
//=============================================================================
void CResult::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// ���U���g�̏���������
//=============================================================================
HRESULT CResult::Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	m_apScene2D = new CScene2D;

	if (m_apScene2D != NULL)
	{
		m_apScene2D->Init(pos, Size);
		m_apScene2D->BindTextuer(m_pTexture);
	}

	CManager *pManager = NULL;
	pManager->GetSound()->Play(CSound::SOUND_LABEL_BGM00);

	CNumber::Load();

	CRanking::Create(D3DXVECTOR3(440.0f, 100.0f, 0.0f), D3DXVECTOR2(25.0f, 25.0f));
	return S_OK;
}

//=============================================================================
// ���U���g�̏I������
//=============================================================================
void CResult::Uninit(void)
{
	CScene::Relese();
}

//=============================================================================
// ���U���g�̍X�V����
//=============================================================================
void CResult::Update(void)
{
	CInputKeyboard *pInputKeyboard = NULL;
	pInputKeyboard = CManager::GetInputKeyboard();

	//�C�ӂŉ����ꂽ���ǂ���
	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true && !m_bNextMode)//ENTER��������
	{
		CManager *pManager = NULL;
		pManager->GetSound()->Stop(CSound::SOUND_LABEL_BGM00);
		CFade::SetFade(CManager::MODE_TITLE);
		m_bNextMode = true;
	}
}

//=============================================================================
// ���U���g�̕`�揈��
//=============================================================================
void CResult::Draw(void)
{

}