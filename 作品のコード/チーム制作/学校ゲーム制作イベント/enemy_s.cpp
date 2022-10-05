//=============================================================================
//
// エネミーSの処理 [enemy_s.cpp]
// Author : 青木睦浩
//
//=============================================================================
#include"enemy_s.h"
#include"bullet.h"
#include"game.h"
#include "rupture.h"
#include "score.h"
//=============================================================================
// エネミーSのコンストラクタ
//=============================================================================
CEnemyS::CEnemyS() : CEnemy(TYPE_S)
{
	// 任意の値でクリア
	m_nLife = 0;
	m_nSpeed = 0;
}

//=============================================================================
// エネミーSのデストラクタ
//=============================================================================
CEnemyS::~CEnemyS()
{
}

//CEnemyS * CEnemyS::Create()
//{
//	/*CEnemyS *pEnemy;
//
//	pEnemy = new CEnemyS;
//
//	pEnemy->Init(D3DXVECTOR3(100.0f, 100.0f, 0.0f), D3DXVECTOR2(20.0f, 20.0f));
//
//	return pEnemy;*/
//}

//=============================================================================
// エネミーSの初期化処理
//=============================================================================
HRESULT CEnemyS::Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	srand(time(NULL));
	int nSpawn = (int)(rand() % 10 + 1);

	switch (nSpawn)
	{
	case 1:
		CEnemy::Init(D3DXVECTOR3(-80.0f, 100, 0.0f), D3DXVECTOR2(25.0f, 25.0f));
		m_nSpeed = 1;
		break;

	case 2:
		CEnemy::Init(D3DXVECTOR3(-80.0f, 200, 0.0f), D3DXVECTOR2(25.0f, 25.0f));
		m_nSpeed = 1;
		break;

	case 3:
		CEnemy::Init(D3DXVECTOR3(-80.0f, 300, 0.0f), D3DXVECTOR2(25.0f, 25.0f));
		m_nSpeed = 1;
		break;

	case 4:
		CEnemy::Init(D3DXVECTOR3(-80.0f, 400, 0.0f), D3DXVECTOR2(25.0f, 25.0f));
		m_nSpeed = 1;
		break;

	case 5:
		CEnemy::Init(D3DXVECTOR3(-80.0f, 500, 0.0f), D3DXVECTOR2(25.0f, 25.0f));
		m_nSpeed = 1;
		break;

	case 6:
		CEnemy::Init(D3DXVECTOR3(1360.0f, 100, 0.0f), D3DXVECTOR2(25.0f, 25.0f));
		m_nSpeed = -1;
		break;

	case 7:
		CEnemy::Init(D3DXVECTOR3(1360.0f, 200, 0.0f), D3DXVECTOR2(25.0f, 25.0f));
		m_nSpeed = -1;
		break;

	case 8:
		CEnemy::Init(D3DXVECTOR3(1360.0f, 300, 0.0f), D3DXVECTOR2(25.0f, 25.0f));
		m_nSpeed = -1;
		break;

	case 9:
		CEnemy::Init(D3DXVECTOR3(1360.0f, 400, 0.0f), D3DXVECTOR2(25.0f, 25.0f));
		m_nSpeed = -1;
		break;

	case 10:
		CEnemy::Init(D3DXVECTOR3(1360.0f, 500, 0.0f), D3DXVECTOR2(25.0f, 25.0f));
		m_nSpeed = -1;
		break;

	default:
		break;
	}

	// 初期化
	m_nLife = 0;

	return S_OK;
}

//=============================================================================
// エネミーSの終了処理
//=============================================================================
void CEnemyS::Uninit(void)
{
	CEnemy::Uninit();
}

//=============================================================================
// エネミーSの更新処理
//=============================================================================
void CEnemyS::Update(void)
{
	m_pos.x += m_nSpeed;

	if (BulletCollision() == true)
	{
		CRupture::Create(m_pos, D3DXVECTOR2(10.0f, 10.0f), CRupture::RUPTURE_TYPE_FOURTH);
	}

	CEnemy::Update();
}

//=============================================================================
// エネミーSの描画処理
//=============================================================================
void CEnemyS::Draw(void)
{
	CEnemy::Draw();
}

//=============================================================================
// 敵とブロックの当たり判定処理
//=============================================================================
bool CEnemyS::BulletCollision()
{
	int nNum = 0;
	CScene * pScene = CScene::GetScene(CScene::PRIORITY_BULLET);
	CScore *pScore = CGame::GetScore();
	while (pScene != NULL)
	{
		// 取得したオブジェクトを普通のブロックに代入
		CBullet *pBullet = (CBullet*)pScene;

		D3DXVECTOR3 Bulletpos = pBullet->GetPosition();
		D3DXVECTOR2 Bulletsize = pBullet->GetSize();

		if (m_pos.x - m_size.x <= Bulletpos.x + Bulletsize.x &&				//ブロックの右端
			m_pos.x + m_size.x >= Bulletpos.x - Bulletsize.x &&				//ブロックの左端
			m_pos.y - m_size.y <= Bulletpos.y + Bulletsize.y &&				//ブロックの下部
			m_pos.y + m_size.y >= Bulletpos.y - Bulletsize.y)					//ブロックの上部
		{

			pBullet->SetUse(true);
			pScore->AddScore(100);
			Uninit();
			return true;
		}

		// ブロックオブジェクトの次のオブジェクトを取得
		CScene * pSceneNext = CScene::GetNext(pScene);
		pScene = pSceneNext;
	}
	return false;
}