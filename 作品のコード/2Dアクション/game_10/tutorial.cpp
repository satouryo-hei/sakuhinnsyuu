//=============================================================================
//
// �Q�[���̏��� [game.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include "tutorial.h"
#include"input.h"
#include"manager.h"
#include"result.h"
#include"fade.h"
#include"timer.h"
#include"player.h"
#include"item.h"
#include"block.h"
#include"bg.h"
#include"meshfield.h"
#include"meshsky.h"
#include"wall.h"
#include"stage_tutorial.h"
#include"enemy02.h"
#include"noneblock.h"
#include"pushblock.h"
#include"moveblock.h"
#include"goal.h"
#include"score.h"

//=============================================================================
// �ÓI�����o�֐��̐錾
//=============================================================================
CPlayer* CTutorial::m_pPlayer = NULL;
CItem* CTutorial::m_pAttack_up = NULL;
CMeshSky		* CTutorial::m_pMeshSky = NULL;
CStage_Tutorial* CTutorial::m_pStage = NULL;
CEnemy02* CTutorial::m_pEnemy = NULL;

//=============================================================================
// �Q�[���̃R���X�g���N�^
//=============================================================================
CTutorial::CTutorial(int nPriority) : CScene(PRIORITY_NOMAL)
{
	m_bUse = false;
	m_bFade = false;
}

//=============================================================================
// �Q�[���̃f�X�g���N�^
//=============================================================================
CTutorial::~CTutorial()
{

}

//=============================================================================
// �Q�[���̏���������
//=============================================================================
HRESULT CTutorial::Init(D3DXVECTOR3 pos)
{	
	// ���Ԃ̐���
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(1200.0f, 200.0f, 0.0f), D3DXVECTOR3(10, 10, 0), D3DXVECTOR2(20, 30));
	// ���Ԃ̐���
	m_pAttack_up = CItem::Create(D3DXVECTOR3(1020.0f, 150.0f, 0.0f), D3DXVECTOR2(50, 50));

	m_pStage = CStage_Tutorial::Create(D3DXVECTOR3(0.0f, 0.0f, 0));
	m_pEnemy = CEnemy02::Create(D3DXVECTOR3(100.0f, 100.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 0.0f), D3DXVECTOR2(30, 30));

	// ���b�V���X�J�C(��)�̐���
	m_pMeshSky = CMeshSky::Create(D3DXVECTOR3(0.0f, 100.0f, 100.0f), D3DXVECTOR3(1000.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 32, 8);
		
	return S_OK;
}

//=============================================================================
// �Q�[���̏I������
//=============================================================================
void CTutorial::Uninit(void)
{
	CScene::Release();
}

//=============================================================================
// �Q�[���̍X�V����
//=============================================================================
void CTutorial::Update(void)
{
#ifdef _DEBUG	
	CInputKeyboard *pInputKeyboard = NULL;
	pInputKeyboard = CManager::GetInputKeyboard();

	//�C�ӂŉ����ꂽ���ǂ���
	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true && !m_bFade)//ENTER��������
	{
		CFade::SetFade(CManager::MODE_RESULT);
		m_bFade = true;
	}
#endif // _DEBUG
}

//=============================================================================
// �Q�[���̕`�揈��
//=============================================================================
void CTutorial::Draw(void)
{

}