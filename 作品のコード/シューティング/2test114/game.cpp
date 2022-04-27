//=============================================================================
//
// �Q�[���̏��� [game.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include "game.h"
#include"input.h"
#include "bg.h"
#include"player.h"
#include"manager.h"
#include"enemy.h"
#include"score.h"
#include"life.h"
#include"bullet.h"
#include"effect.h"
#include"number.h"
#include"explosion.h"
#include"polygon.h"
#include"fade.h"
#include "timer.h"
#include"cutin.h"
#include"enemy_doragonfly.h"
#include"enemy_manager.h"
#include"sound.h"
#include"ranking.h"
#include"ui.h"

// �ÓI�����o�ϐ��̐錾
CBg *CGame::m_pBg = NULL;
CPlayer *CGame::m_pPlayer = NULL;
CEnemy *CGame::m_pEnemy = NULL;
CScore *CGame::m_pScore = NULL;
CLife*CGame::m_pLife = NULL;
CTimer*CGame::m_pTimer = NULL;
CEnemy_Doragonfly*CGame::m_pEmemy_Doragonfly = NULL;
CUi*CGame::m_pUi = NULL;
bool CGame::m_bRanking = false;
//=============================================================================
// �Q�[���̃R���X�g���N�^
//=============================================================================
CGame::CGame()
{
	m_pEmemy_Manager = NULL;
	m_bNextMode = false;
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
HRESULT CGame::Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	CPlayer::Load();
	CBullet::Load();
	CExplosion::Load();
	CBg::Load();
	CEnemy::Load();
	CEnemy_Doragonfly::Load();
	CNumber::Load();
	CEffect::Load();
	CPolygon::Load();

	m_pEmemy_Manager = new CEnemy_manager;

	if (m_pEmemy_Manager != NULL)
	{
		m_pEmemy_Manager->Init(pos, Size);
	}

	// �w�i�̐���
	m_pBg = CBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT));

	// ���Ԃ̐���
	m_pTimer = CTimer::Create(D3DXVECTOR3(420.0f, 50.0f, 0.0f), D3DXVECTOR2(20.0f, 30.0f));

	// �X�R�A�̐���
	m_pScore = CScore::Create(D3DXVECTOR3(920.0f, 50.0f, 0.0f), D3DXVECTOR2(20.0f, 30.0f));

	// �̗͂̐���
	m_pLife = CLife::Create(D3DXVECTOR3(150.0f, 50.0f, 0.0f), D3DXVECTOR2(20.0f, 30.0f));

	m_pUi = CUi::Create(D3DXVECTOR3(50.0f, 50.0f, 0.0f), D3DXVECTOR2(20.0f, 30.0f));

	// 2D�̃v���C���[����
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(440.0f, 320.0f, 0.0f), D3DXVECTOR3(2.5f, 2.5f, 0.0f), D3DXVECTOR2(50.0f, 50.0f));

	// 2D�̓G����/*�ݒu�^((move.x = 1.8) =bg[0]�Ɠ�������)*/
	//m_pEnemy = CEnemy::Create(D3DXVECTOR3(1100.0f, 200.0f, 0.0f), D3DXVECTOR3(1.8f, 0.0f, 0.0f), D3DXVECTOR2(75.0f, 75.0f));

	// 2D�̓G����
	//m_pEmemy_Doragonfly = CEnemy_Doragonfly::Create(D3DXVECTOR3(-100.0f, 500.0f, 0.0f), D3DXVECTOR3(1.8f, 0.0f, 0.0f), D3DXVECTOR2(75.0f, 75.0f));

	CManager *pManager = NULL;
	pManager->GetSound()->Play(CSound::SOUND_LABEL_SUMMER_EXPEDITION);

	return S_OK;
}

//=============================================================================
// �Q�[���̏I������
//=============================================================================
void CGame::Uninit(void)
{
	CScene::Relese();

	// �e�N�X�`���̔j��	
	CNumber::Unload();

	// �e�N�X�`���̔j��	
	CEffect::Unload();

	// �e�N�X�`���̔j��	
	CPolygon::Unload();

	// �e�N�X�`���̔j��
	CPlayer::Unload();

	CEnemy_Doragonfly::Unload();

	// �e�N�X�`���̔j��	
	CEnemy::Unload();

	// �e�N�X�`���̔j��		
	CBullet::Unload();

	// �e�N�X�`���̔j��		
	CExplosion::Unload();

	// �e�N�X�`���̔j��		
	CBg::Unload();

}

//=============================================================================
// �Q�[���̍X�V����
//=============================================================================
void CGame::Update(void)
{
	m_pEmemy_Manager->Update();

	CInputKeyboard *pInputKeyboard = NULL;
	pInputKeyboard = CManager::GetInputKeyboard();

	//�C�ӂŉ����ꂽ���ǂ���
	if (pInputKeyboard->GetTrigger(DIK_END) == true && !m_bNextMode)//ENTER��������
	{	
		CManager *pManager = NULL;
		pManager->GetSound()->Stop(CSound::SOUND_LABEL_SUMMER_EXPEDITION);

		CFade::SetFade(CManager::MODE_RESULT);

		m_bNextMode = true;
	}

	//�C�ӂŉ����ꂽ���ǂ���
	if (pInputKeyboard->GetTrigger(DIK_G) == true)//ENTER��������
	{
		//CCutin::SetCutin(CManager::MODE_GAME);
	}
}

//=============================================================================
// �Q�[���̕`�揈��
//=============================================================================
void CGame::Draw(void)
{

}