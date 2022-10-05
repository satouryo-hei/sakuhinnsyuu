//=============================================================================
//
// ゲームの処理 [game.cpp]
// Author : 佐藤瞭平
// Author : 青木睦浩
//
//=============================================================================
#include "game.h"
#include"input.h"
#include"manager.h"
#include"result.h"
#include"fade.h"
#include"bg.h"
#include"player.h"
#include"enemy.h"
#include"timer.h"
#include"score.h"

//=============================================================================
// 静的メンバ関数の宣言
//=============================================================================
CBg* CGame::m_pBg = NULL;
CPlayer* CGame::m_pPlayer = NULL;
CEnemy* CGame::m_pEnemy[10] = {};
CScore* CGame::m_pScore = NULL;
CTimer* CGame::m_pTimer = NULL;

//=============================================================================
// ゲームのコンストラクタ
//=============================================================================
CGame::CGame(int nPriority) : CScene(PRIORITY_NOMAL)
{	
	m_bFade = false;
	m_nSpawn = 0;
}

//=============================================================================
// ゲームのデストラクタ
//=============================================================================
CGame::~CGame()
{

}

//=============================================================================
// ゲームの初期化処理
//=============================================================================
HRESULT CGame::Init(D3DXVECTOR3 pos)
{	
	m_pBg = CBg::Create(pos, D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 17);
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT-20,0), D3DXVECTOR2(40,60));

	m_pScore = CScore::Create(D3DXVECTOR3(950.0f, 50.0f, 0.0f), D3DXVECTOR2(20, 30));
	// 時間の生成
	m_pTimer = CTimer::Create(D3DXVECTOR3(560.0f, 50.0f, 0.0f), D3DXVECTOR2(20.0f, 30.0f));
	return S_OK;
}

//=============================================================================
// ゲームの終了処理
//=============================================================================
void CGame::Uninit(void)
{
	CScene::Release();
}

//=============================================================================
// ゲームの更新処理
//=============================================================================
void CGame::Update(void)
{
#ifdef _DEBUG	
	CInputKeyboard *pInputKeyboard = NULL;
	pInputKeyboard = CManager::GetInputKeyboard();

	//任意で押されたかどうか
	if (pInputKeyboard->GetTrigger(DIK_RETURN)&& !m_bFade)//ENTERを押した
	{
		CFade::SetFade(CManager::MODE_RESULT);
		m_bFade = true;
	}
#endif // _DEBUG

	m_nSpawn++;

	if (m_nSpawn >= 100)
	{
		srand(time(NULL));
		int nEnemySpawn = (int)(rand() % 3 + 1);

		switch (nEnemySpawn)
		{
		case 1:
			m_pEnemy[0] = CEnemy::Create(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR2(0, 0), CEnemy::TYPE_S);
			m_nSpawn = 0;
			break;

		case 2:
			m_pEnemy[1] = CEnemy::Create(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR2(0, 0), CEnemy::TYPE_M);
			m_nSpawn = 0;
			break;

		case 3:
			m_pEnemy[2] = CEnemy::Create(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR2(0, 0), CEnemy::TYPE_L);
			m_nSpawn = 0;
			break;

		default:
			break;
		}
	}
}

//=============================================================================
// ゲームの描画処理
//=============================================================================
void CGame::Draw(void)
{

}