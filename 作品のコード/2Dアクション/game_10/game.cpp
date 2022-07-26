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
#include"attack_up.h"
#include"block.h"
#include"bg.h"
#include"meshfield.h"
#include"meshsky.h"
#include"wall.h"
#include"stage.h"
#include"enemy02.h"
#include"noneblock.h"
#include"pushblock.h"
#include"moveblock.h"
#include"goal.h"

//=============================================================================
// �ÓI�����o�֐��̐錾
//=============================================================================
CBg* CGame::m_pBg = NULL;
CTimer* CGame::m_pTimer = NULL;
CPlayer* CGame::m_pPlayer = NULL;
CAttack_up* CGame::m_pAttack_up = NULL;
CMeshField		* CGame::m_pMeshField = NULL;
CMeshSky		* CGame::m_pMeshSky = NULL;
CWall* CGame::m_pWall = NULL;
CStage_Tutorial* CGame::m_pStage = NULL;
CEnemy02* CGame::m_pEnemy = NULL;
CGoal * CGame::m_pGoal = NULL;

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
	//m_pBg = CBg::Create(pos, D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), 0);
	// ���Ԃ̐���
	m_pTimer = CTimer::Create(D3DXVECTOR3(420.0f, 50.0f, 0.0f), D3DXVECTOR2(20.0f, 30.0f));
	// ���Ԃ̐���
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(1200.0f, 200.0f, 0.0f), D3DXVECTOR3(10,10,0), D3DXVECTOR2(20,20));
	// ���Ԃ̐���
	m_pAttack_up = CAttack_up::Create(D3DXVECTOR3(1020.0f, 150.0f, 0.0f), D3DXVECTOR2(50, 50));

	m_pGoal = CGoal::Create(D3DXVECTOR3(1020.0f,630.0f, 0.0f), D3DXVECTOR2(50.0f, 50.0f));

	m_pStage = CStage_Tutorial::Create(D3DXVECTOR3(0.0f, 0.0f, 0));
	m_pEnemy = CEnemy02::Create(D3DXVECTOR3(100.0f, 100.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 0.0f), D3DXVECTOR2(30,30));

	// ���b�V���t�B�[���h(�n��)�̐���
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(0.0f, 0.0f, 200.0f), D3DXVECTOR3(300.0f, 0.0f, 200.0f));


	// ���b�V���X�J�C(��)�̐���
	m_pMeshSky = CMeshSky::Create(D3DXVECTOR3(0.0f, 100.0f, 100.0f), D3DXVECTOR3(1000.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 32, 8);
	//m_pWall = CWall::Create(D3DXVECTOR3(0.0f, 0.0f, 300.0f), D3DXVECTOR3(280.0f, 1000.0f, 0.0f), D3DXVECTOR3(0.0f, 0, 0.0f));
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

	//if (m_pAttack_up != NULL)
	//{
	//	m_pAttack_up->Uninit();
	//	delete m_pAttack_up;
	//	m_pAttack_up = NULL;
	//}
	CScene::Release();
}

//=============================================================================
// �Q�[���̍X�V����
//=============================================================================
void CGame::Update(void)
{
	CInputKeyboard *pInputKeyboard = NULL;
	pInputKeyboard = CManager::GetInputKeyboard();

	//�C�ӂŉ����ꂽ���ǂ���
	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true && !m_bFade)//ENTER��������
	{
		CFade::SetFade(CManager::MODE_RESULT);
		m_bFade = true;
	}
}

//=============================================================================
// �Q�[���̕`�揈��
//=============================================================================
void CGame::Draw(void)
{

}