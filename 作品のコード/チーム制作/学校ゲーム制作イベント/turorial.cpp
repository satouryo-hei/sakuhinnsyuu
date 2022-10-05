//=============================================================================
//
// �`���[�g���A���̏��� [title.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include "turorial.h"
#include "scene2D.h"
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"bg.h"
#include"fade.h"
#include"game.h"
#include"logo.h"
#include"nextbutton.h"

//=============================================================================
// �ÓI�����o�ϐ��̐錾
//=============================================================================
CBg* CTutorial::m_pBg = NULL;
CLogo* CTutorial::m_pLogo = NULL;
CNextBotton* CTutorial::m_pNextBotton = NULL;

//=============================================================================
// �^�C�g���̃R���X�g���N�^
//=============================================================================
CTutorial::CTutorial(int nPriority) : CScene(PRIORITY_NOMAL)
{
	m_bFade = false;
}

//=============================================================================
// �^�C�g���̃f�X�g���N�^
//=============================================================================
CTutorial::~CTutorial()
{

}

//=============================================================================
// �^�C�g���̏���������
//=============================================================================
HRESULT CTutorial::Init(D3DXVECTOR3 pos)
{
	m_pBg = CBg::Create(pos, D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 18);

	/*m_pLogo = CLogo::Create(pos, D3DXVECTOR2(100, 600));
	m_pNextBotton = CNextBotton::Create(pos, D3DXVECTOR2(500, 500));*/
	return S_OK;
}

//=============================================================================
// �^�C�g���̏I������
//=============================================================================
void CTutorial::Uninit(void)
{
	CScene::Release();

	if (m_pBg != NULL)
	{
		m_pBg->Uninit();
		m_pBg = NULL;
	}
}

//=============================================================================
// �^�C�g���̍X�V����
//=============================================================================
void CTutorial::Update(void)
{
	CInputKeyboard *pInputKeyboard = NULL;
	pInputKeyboard = CManager::GetInputKeyboard();


	//�C�ӂŉ����ꂽ���ǂ���
	if (pInputKeyboard->GetTrigger(DIK_SPACE) && !m_bFade)//ENTER��������
	{
		CFade::SetFade(CManager::MODE_GAME);
		m_bFade = true;
	}
}

//=============================================================================
// �^�C�g���̕`�揈��
//=============================================================================
void CTutorial::Draw(void)
{

}