//=============================================================================
//
// ���U���g�̏��� [result.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include "result.h"
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"bg.h"
#include"fade.h"
#include"ranking.h"

//=============================================================================
// �ÓI�����o�ϐ��̐錾
//=============================================================================
LPDIRECT3DTEXTURE9 CResult::m_pTexture = NULL;
CBg* CResult::m_pBg = NULL;
CRanking* CResult::m_pRanking = NULL;

//=============================================================================
// ���U���g�̃R���X�g���N�^
//=============================================================================
CResult::CResult(int nPriority) : CScene(PRIORITY_NOMAL)
{
	m_bFade = true;
}

//=============================================================================
// ���U���g�̃f�X�g���N�^
//=============================================================================
CResult::~CResult()
{

}
//=============================================================================
// ���U���g�̏���������
//=============================================================================
HRESULT CResult::Init(D3DXVECTOR3 pos)
{
	m_pBg = CBg::Create(pos, D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), 3);
	m_pRanking = CRanking::Create(pos, D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT));
	return S_OK;
}

//=============================================================================
// ���U���g�̏I������
//=============================================================================
void CResult::Uninit(void)
{
	//if (m_pBg != NULL)
	//{
	//	m_pBg->Uninit();
	//	m_pBg = NULL;
	//}

	CScene::Release();
}

//=============================================================================
// ���U���g�̍X�V����
//=============================================================================
void CResult::Update(void)
{
	CInputKeyboard *pInputKeyboard = NULL;
	pInputKeyboard = CManager::GetInputKeyboard();

	//�C�ӂŉ����ꂽ���ǂ���
	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true && m_bFade)//ENTER��������
	{
		//CManager::SetMode(CManager::MODE_TITLE);
		CFade::SetFade(CManager::MODE_TITLE);
		m_bFade = false;
	}
}

//=============================================================================
// ���U���g�̕`�揈��
//=============================================================================
void CResult::Draw(void)
{

}