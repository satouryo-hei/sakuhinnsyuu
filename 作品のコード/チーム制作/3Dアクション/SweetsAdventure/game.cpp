//--------------------------------------
//ゲーム画面の処理
//--------------------------------------
#include "game.h"
#include "bg.h"
#include "texture.h"
#include "manager.h"
#include "keyboard.h"
#include "player.h"
#include "fade.h"
#include "Scene3D.h"
#include "time.h"
#include "model_spawner.h"
#include "collision.h"
#include "score.h"
#include "goal.h"
#include "field.h"
#include "meshsphere.h"
#include "effect_sphere.h"
#include "stage.h"
#include "Enemy.h"
#include "gauge.h"
#include "Polygon.h"
#include "pause.h"
#include "XInput.h"
CBg		*CGame::m_pBg = NULL;
CPlayer	*CGame::m_Player = NULL;
CTime   *CGame::m_pTime = NULL;
CModel_Spawner *CGame::m_pModel = NULL;
CScore	*CGame::m_pScore = NULL;
CGoal   *CGame::m_pGoal = NULL;
CField	*CGame::m_pField = NULL;
CField	*CGame::m_pSea = NULL;
CPolygon *CGame::m_Polygon = NULL;
CPolygon *CGame::m_Cursol = NULL;
CMeshSphere *CGame::m_pMeshSphere = NULL;
CEffectSphere *CGame::m_pEffectSphere = NULL;
CStage	*CGame::m_pStage = NULL;
CEnemy  *CGame::m_pEnemy = NULL;
CGauge	*CGame::m_pGauge = NULL;
static float s_texrotx = 0.0f;
static float s_texseax = 0.0f;
static int s_nTime = 0;
static bool s_bTime = false;
//--------------------------------------------
//コンストラクタ
//--------------------------------------------
CGame::CGame()
{
	m_Player = NULL;
	m_pFlore = NULL;
	m_pBg = NULL;
	m_pTime = NULL;
	m_pModel = NULL;
	m_pScore = NULL;
	m_pGoal = NULL;
	m_pField = NULL;
	m_pMeshSphere = NULL;
	m_pEffectSphere = NULL;
	m_pEnemy = NULL;
	m_pSea = NULL;
}
//--------------------------------------------
//デストラクタ
//--------------------------------------------
CGame::~CGame()
{
}
//--------------------------------------------
//初期化
//--------------------------------------------
HRESULT CGame::Init(void)
{
	//プレイヤーの生成
	if (m_Player == NULL)
	{
		m_Player = CPlayer::Create();
	}
	if (m_pField == NULL)
	{
		m_pField = CField::Create(D3DXVECTOR3(0.0f, -200.0f, -0.0f), D3DXVECTOR3(500.0f, 0.0f, 500.0f), D3DXVECTOR3(0.0f, 0.0f, -0.0f)
			, 50, 50, CTexture::SEA000);
		m_pField->SetCol(0.8);
	}
	if (m_pSea == NULL)
	{
		m_pSea = CField::Create(D3DXVECTOR3(0.0f, -200.0f, -0.0f), D3DXVECTOR3(600.0f, 0.0f, 600.0f), D3DXVECTOR3(0.0f, 0.0f, -0.0f)
			, 50, 50, CTexture::SEA001);
		m_pSea->SetCol(0.4);

	}
	//空の生成
	if (m_pMeshSphere == NULL)
	{
		m_pMeshSphere = CMeshSphere::Create(D3DXVECTOR3(0.0f, -1000.0f, 0.0f),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			8, 4, 8000.0f, 1.0f, CTexture::SKY);
	}
	CPolygon::Create(D3DXVECTOR3(250.0f, 60.0f, 0.0f), D3DXVECTOR3(200.0f, 30.0f, 0.0f), CTexture::Gage001);

	if (m_pGauge == NULL)
	{
		m_pGauge = CGauge::Create(D3DXVECTOR3(50.0f, 60.0f, 0.0f), D3DXVECTOR3(0.0f, 25.0f, 0.0f));

	}
	CPolygon::Create(D3DXVECTOR3(60.0f, 60.0f, 0.0f), D3DXVECTOR3(40.0f, 40.0f, 0.0f), CTexture::Gage003);
	//武器の選択表示
	CPolygon::Create(D3DXVECTOR3(900.0f, 65.0f, 0.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f), CTexture::HAMMERTEX);
	CPolygon::Create(D3DXVECTOR3(1200.0f, 65.0f, 0.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f), CTexture::NAIHUTEX);
	CPolygon::Create(D3DXVECTOR3(900.0f, 65.0f, 0.0f), D3DXVECTOR3(60.5f, 60.5f, 0.0f), CTexture::FREAM);
	CPolygon::Create(D3DXVECTOR3(1200.0f, 65.0f, 0.0f), D3DXVECTOR3(60.5f, 60.5f, 0.0f), CTexture::FREAM);
	CPolygon::Create(D3DXVECTOR3(1000.0f, 65.0f, 0.0f), D3DXVECTOR3(40.5f, 25.0f, 0.0f), CTexture::LB);
	CPolygon::Create(D3DXVECTOR3(1100.0f, 65.0f, 0.0f), D3DXVECTOR3(40.5f, 25.0f, 0.0f), CTexture::RB);

	m_Cursol= CPolygon::Create(D3DXVECTOR3(1200.0f, 65.0f, 0.0f), D3DXVECTOR3(60.5f, 60.5f, 0.0f), CTexture::WEAPONSELECT);


	if (m_pStage == NULL)
	{
		m_pStage = new CStage;
		m_pStage->Init();
		m_pStage->StageSet("data/TEXT/stage001.txt");
	}
	if (m_pGoal == NULL)
	{
		m_pGoal= CGoal::Create(D3DXVECTOR3(70.0f, 50.0f, 3800.0f), D3DXVECTOR3(5.0f, 7.5f, 0.0f), CTexture::GOAL);
	}
	m_fAlpha = 1.0f;
	m_bNextMode = false;
	m_nTimer = 0;
	return S_OK;
}
//--------------------------------------------
//終了
//--------------------------------------------
void CGame::Uninit(void)
{
	if (m_Player != NULL)
	{
		m_Player->Uninit();
		m_Player = NULL;
	}
	if (m_pModel != NULL)
	{
		m_pModel->Uninit();
		delete m_pModel;
		m_pModel = NULL;
	}
	if (m_pTime != NULL)
	{
		m_pTime->Uninit();
		delete m_pTime;
		m_pTime = NULL;
	}
	if (m_pScore != NULL)
	{
		m_pScore->Uninit();
		delete m_pScore;
		m_pScore = NULL;
	}
	if (m_pStage != NULL)
	{
		m_pStage->Uninit();
		delete m_pStage;
		m_pStage = NULL;
	}
	if (m_pMeshSphere != NULL)
	{
		m_pMeshSphere->Uninit();
		delete m_pMeshSphere;
		m_pMeshSphere = NULL;
	}
	if (m_pGauge != NULL)
	{
		m_pGauge->Uninit();
		m_pGauge = NULL;
	}
	if (m_Cursol != NULL)
	{
		m_Cursol->Uninit();
		m_Cursol = NULL;
	}
	m_pGoal = NULL;

}
//--------------------------------------------
//更新
//--------------------------------------------
void CGame::Update(void)
{
	CXInput *pGamePad = CManager::GetXInput();

	s_texrotx += 0.0001f;
	s_texseax += 0.0002f;
	if (s_texrotx >= 1.0f)
	{
		s_texrotx = 0.0f;
	}
	if (s_texseax >= 1.0f)
	{
		s_texseax = 0.0f;
	}
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN) == true && m_bNextMode==false)
	{
		//Resultへ行く
		CFade::SetFade(CManager::MODE_RESULT);
		////二回以上通らないようにする
		m_bNextMode = true;
	}
	if (m_pField != NULL)
	{
		m_pField->SetMoveTex(s_texrotx, s_texrotx);
	}
	if (m_pMeshSphere != NULL)
	{
		m_pMeshSphere->SetMesh(D3DXVECTOR3(0.0f, -1000.0f, 0.0f),
			D3DXCOLOR(1.0, 1.0, 1.0, 1.0),
			8000.0f,
			s_texrotx);
	}
	if (m_pSea != NULL)
	{
		m_pSea->SetMoveTex(s_texseax, s_texseax);

	}
	if (m_pStage != NULL)
	{
		m_pStage->Update();
	}
	if (m_Cursol != NULL)
	{
		switch (m_Player->GetWeaponType())
		{
		case CPlayer::TYPE_SWORD:
			m_Cursol->SetPos(D3DXVECTOR3(1200.0f, 65.0f, 0.0f));
			break;
		case CPlayer::TYPE_HAMMER:
			m_Cursol->SetPos(D3DXVECTOR3(900.0f, 65.0f, 0.0f));
			break;
		}
	}


}
//--------------------------------------------
//描画
//--------------------------------------------
void CGame::Draw(void)
{
}

