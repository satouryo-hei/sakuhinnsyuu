//=============================================================================
//
// �Q�[���̏��� [game.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include "game.h"
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
#include"stage_top.h"
#include"enemy02.h"
#include"noneblock.h"
#include"pushblock.h"
#include"moveblock.h"
#include"goal.h"
#include"score.h"
#include"keyui.h"

//=============================================================================
// �ÓI�����o�֐��̐錾
//=============================================================================
CBg* CGame::m_pBg = NULL;
CTimer* CGame::m_pTimer = NULL;
CPlayer* CGame::m_pPlayer = NULL;
CItem* CGame::m_pItem = NULL;
CMeshField		* CGame::m_pMeshField = NULL;
CMeshSky		* CGame::m_pMeshSky = NULL;
CWall* CGame::m_pWall = NULL;
CStage_Top* CGame::m_pStage = NULL;
CEnemy02* CGame::m_pEnemy = NULL;
CGoal * CGame::m_pGoal = NULL;
CScore * CGame::m_pScore = NULL;
CKeyui * CGame::m_pKeyui = NULL;

//=============================================================================
// �Q�[���̃R���X�g���N�^
//=============================================================================
CGame::CGame(int nPriority) : CScene(PRIORITY_NOMAL)
{
	m_bUse = false;
	m_bFade = false;
}

//=============================================================================
// �Q�[���̃f�X�g���N�^
//=============================================================================
CGame::~CGame()
{

}

//=============================================================================
// �Q�[���̏���������
//=============================================================================
HRESULT CGame::Init(D3DXVECTOR3 pos)
{	
	// ���Ԃ̐���
	m_pTimer = CTimer::Create(D3DXVECTOR3(420.0f, 50.0f, 0.0f), D3DXVECTOR2(20.0f, 30.0f));	
	// ���Ԃ̐���
	m_pItem = CItem::Create(D3DXVECTOR3(1020.0f, 150.0f, 0.0f), D3DXVECTOR2(50, 50));	
	m_pKeyui = CKeyui::Create(D3DXVECTOR3(120.0f, 50.0f, 0.0f), D3DXVECTOR2(50, 50));

	m_pStage = CStage_Top::Create(D3DXVECTOR3(0.0f, 0.0f, 0));
	m_pEnemy = CEnemy02::Create(D3DXVECTOR3(1000.0f, 500.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 0.0f), D3DXVECTOR2(30,30));

	// ���b�V���t�B�[���h(�n��)�̐���
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(0.0f, 0.0f, 200.0f), D3DXVECTOR3(300.0f, 0.0f, 200.0f));

	// ���b�V���X�J�C(��)�̐���
	m_pMeshSky = CMeshSky::Create(D3DXVECTOR3(0.0f, 100.0f, 100.0f), D3DXVECTOR3(1000.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 32, 8);	

	m_pScore = CScore::Create(D3DXVECTOR3(950.0f, 50.0f, 0.0f), D3DXVECTOR2(20, 30));
	return S_OK;
}

//=============================================================================
// �Q�[���̏I������
//=============================================================================
void CGame::Uninit(void)
{
	if (m_pTimer != NULL)
	{
		m_pTimer->Uninit();
		delete m_pTimer;
		m_pTimer = NULL;
	}
	//if (m_pPlayer != NULL)
	//{
	//	m_pPlayer->Uninit();
	//	delete m_pPlayer;
	//	m_pPlayer = NULL;
	//}

	//if (m_pItem != NULL)
	//{
	//	m_pItem->Uninit();
	//	delete m_pItem;
	//	m_pItem = NULL;
	//}
	CScene::Release();
}

//=============================================================================
// �Q�[���̍X�V����
//=============================================================================
void CGame::Update(void)
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
void CGame::Draw(void)
{

}