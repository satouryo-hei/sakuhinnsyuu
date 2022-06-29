//=============================================================================
//
// タイトルの処理 [title.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include "tutorial.h"
#include "scene2D.h"
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"bg.h"
#include"fade.h"
#include"scene3D.h"
#include"model.h"
#include"model_single.h"
#include"player.h"
#include"meshfield.h"
#include"meshsky.h"
#include"shadow.h"
#include"billboard.h"
#include"wall_manager.h"
#include"wall.h"
#include"timer.h"
#include"item.h"
#include"enemy.h"
#include"enemy02.h"
#include"score.h"
#include"status_ui.h"
#include"goal.h"
#include"bom.h"

//=============================================================================
// 静的メンバ変数の宣言
//=============================================================================
CBg* CTutorial::m_pBg = NULL;
CScene3D		* CTutorial::m_pScene3D = NULL;
CModel			* CTutorial::m_pModel = NULL;
CModel_Single	* CTutorial::m_pModel_Single = NULL;
CPlayer			* CTutorial::m_pPlayer = NULL;
CMeshField		* CTutorial::m_pMeshField = NULL;
CMeshSky		* CTutorial::m_pMeshSky = NULL;
CShadow			* CTutorial::m_pShadow = NULL;
CBillboard		* CTutorial::m_pBillboard = NULL;
CWall_Manager	* CTutorial::m_pWall_Manager = NULL;
CWall			* CTutorial::m_pWall = NULL;
CTimer			* CTutorial::m_pTimer = NULL;
CItem			* CTutorial::m_pItem[3] = {};
CEnemy			* CTutorial::m_pEnemy = NULL;
CEnemy2			* CTutorial::m_pEnemy2 = NULL;
CScore			* CTutorial::m_pScore = NULL;
CStatus_UI		* CTutorial::m_pStatus_UI = NULL;
CGoal			* CTutorial::m_pGoal = NULL;
CBom			* CTutorial::m_pBom = NULL;


const char* CTutorial::m_pModelAttack = "data/MODEL/ITEM/AttackUp.x";
const char* CTutorial::m_pModelData = "data/MODEL/PLAYER/Eye.x";
const char* CTutorial::m_pModelGoal = "data/MODEL/goal.x";

//=============================================================================
// チュートリアルのコンストラクタ
//=============================================================================
CTutorial::CTutorial(int nPriority) : CScene(PRIORITY_NOMAL)
{
	m_bFade = true;
}

//=============================================================================
// チュートリアルのデストラクタ
//=============================================================================
CTutorial::~CTutorial()
{

}

//=============================================================================
// チュートリアルの初期化処理
//=============================================================================
HRESULT CTutorial::Init(D3DXVECTOR3 pos)
{
	//m_pBg = CBg::Create(pos, D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), 2);
	// 1つのモデルを生成
	m_pModel_Single = CModel_Single::Create(D3DXVECTOR3(10.0f, 0.0f, 50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_pModelData);
	// 3Dのプレイヤーを生成
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(50.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	// メッシュフィールド(地上)の生成
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(100.0f, 0.0f, 100.0f));
	// メッシュスカイ(空)の生成
	m_pMeshSky = CMeshSky::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1000.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 32, 8);
	// 四角形設定の壁を生成
	m_pWall_Manager = CWall_Manager::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(100.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f));
	// アイテムの生成
	m_pItem[0] = CItem::Create(D3DXVECTOR3(-30.0f, 0.0f, 40.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_pModelAttack);
	// アイテムの生成
	m_pItem[1] = CItem::Create(D3DXVECTOR3(30.0f, 0.0f, 40.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_pModelAttack);
	// アイテムの生成
	m_pItem[2] = CItem::Create(D3DXVECTOR3(-30.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_pModelAttack);
	// 敵の生成
	m_pEnemy2 = CEnemy2::Create(D3DXVECTOR3(-60.0f, 0.0f, 0.0f), PLAYER_TEXT);
	// ステータスUIの生成
	m_pStatus_UI = CStatus_UI::Create(D3DXVECTOR3(160.0f, 100.0f, 0.0f), D3DXVECTOR2(20.0f, 30.0f));
	// ゴールの生成
	m_pGoal = CGoal::Create(D3DXVECTOR3(0.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_pModelGoal);

	return S_OK;
}

//=============================================================================
// チュートリアルの終了処理
//=============================================================================
void CTutorial::Uninit(void)
{
	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		if (m_pItem[nCnt] != NULL)
		{
			if (m_pItem[nCnt]->GetUse())
			{
				m_pItem[nCnt]->Uninit();
				m_pItem[nCnt] = NULL;
			}
		}
	}

	if (m_pMeshField != NULL)
	{
		m_pMeshField->Uninit();
		m_pMeshField = NULL;
	}

	if (m_pPlayer != NULL)
	{
		m_pPlayer->Uninit();
		m_pPlayer = NULL;
	}

	if (m_pEnemy2 != NULL)
	{
		if (m_pEnemy2->GetUse())
		{
			m_pEnemy2->Uninit();
			m_pEnemy2 = NULL;
		}
	}

	if (m_pModel_Single != NULL)
	{
		m_pModel_Single->Uninit();
		m_pModel_Single = NULL;
	}

	if (m_pWall_Manager != NULL)
	{
		m_pWall_Manager->Uninit();
		m_pWall_Manager = NULL;
	}

	if (m_pMeshSky != NULL)
	{
		m_pMeshSky->Uninit();
		m_pMeshSky = NULL;
	}

	CScene::Release();
}

//=============================================================================
// チュートリアルの更新処理
//=============================================================================
void CTutorial::Update(void)
{
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN) == true && m_bFade)
	{
		CFade::SetFade(CManager::MODE_SELECT);
		m_bFade = false;
	}
}

//=============================================================================
// チュートリアルの描画処理
//=============================================================================
void CTutorial::Draw(void)
{

}