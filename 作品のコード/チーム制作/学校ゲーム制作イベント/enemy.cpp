//=============================================================================
//
// エネミーの処理 [enemy.cpp]
// Author : 青木睦浩
//
//=============================================================================

#include "enemy.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "game.h"
#include "fade.h"
#include "enemy_s.h"
#include "enemy_m.h"
#include "enemy_l.h"
#include"bullet.h"

//=============================================================================
// 静的メンバ関数の宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CEnemy::m_pTexture = NULL;
int CEnemy::m_nItem = 0;
bool CEnemy::m_bUse = true;
int CEnemy::m_EnemyAll = 0;
CEnemy * CEnemy::m_pEnemy[100] = {};

//=============================================================================
// エネミーのコンストラクタ
//=============================================================================
CEnemy::CEnemy(int nPriority) : CScene2D(PRIORITY_ENEMY), m_fSizeU(0.25f)
{
	// 変数をクリア
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR2(0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nTimer = 0;
	m_nCoolTime = 50;
	m_bDeath = false;
	m_bBullet = false;
	m_bMovePush = true;
	m_nBulletType = 0;
	m_fSizeMaxV = 0.5f;
	m_fSizeMinV = 0.0f;
	m_EnemyAll++;
}


//=============================================================================
// エネミーのデストラクタ
//=============================================================================
CEnemy::~CEnemy()
{

}

//=============================================================================
// エネミーの生成処理
//=============================================================================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size, TYPE type)
{
	static int nCnt = m_EnemyAll;
	switch (type)
	{
	case TYPE_S:
		m_pEnemy[nCnt] = new CEnemyS;
		break;

		case TYPE_M:
		m_pEnemy[nCnt] = new CEnemyM;
		break;

		case TYPE_L:
		m_pEnemy[nCnt] = new CEnemyL;
		break;

	default:
		break;
	}
	// メモリを確保
	//pEnemy = new CEnemy;

	if (m_pEnemy[nCnt] != NULL)
	{
		// それぞれの処理へ
		m_pEnemy[nCnt]->Init(pos, Size);
		m_pEnemy[nCnt]->m_move = move;
		
		switch (type)
		{
		case TYPE_S:
			m_pEnemy[nCnt]->Bindtexture(7);
			break;

		case TYPE_M:
			m_pEnemy[nCnt]->Bindtexture(8);
			break;

		case TYPE_L:
			m_pEnemy[nCnt]->Bindtexture(9);
			break;

		default:
			break;
		}

		m_pEnemy[nCnt]->m_Type = type;
	}

	// ポインタを戻り値へ返す
	return m_pEnemy[nCnt];
}

//=============================================================================
// エネミーの初期化処理
//=============================================================================
HRESULT CEnemy::Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	CScene2D::Init(pos, Size);
	int m_Life = 2;
	float m_fSpeed = 0;
	m_posold = pos;
	m_pos = pos;
	m_size = Size;
	m_bUse = true;

	return S_OK;
}

//=============================================================================
// エネミーの終了処理
//=============================================================================
void CEnemy::Uninit(void)
{
	//CScene2D::Uninit();
	Release();
}


 //=============================================================================
 // エネミーの更新処理
 //=============================================================================
void CEnemy::Update(void)
{	
	/*if (m_Type == TYPE_S)
	{
		m_pos.x += 1.0f;
	}

	else if (m_Type == TYPE_M)
	{
		m_pos.x += 2.0f;
	}*/
	//BulletCollision();
	CScene2D::Update();
	SetPosition(m_pos);
	SetSize(m_size);
}

 //=============================================================================
 // エネミーの描画処理
 //=============================================================================
void CEnemy::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// 敵とブロックの当たり判定処理
//=============================================================================
void CEnemy::BulletCollision()
{
	int nCnt = 0;
	CEnemy * pEnemy = NULL;
	switch (m_Type)
	{
	case TYPE_S:
		pEnemy = new CEnemyS;
		break;

	case TYPE_M:
		pEnemy = new CEnemyM;
		break;

	case TYPE_L:
		pEnemy = new CEnemyL;
		break;

	default:
		break;
	}
	CScene * pScene = CScene::GetScene(CScene::PRIORITY_BULLET);

	while (pScene != NULL)
	{
		// 取得したオブジェクトを普通のブロックに代入
		CBullet *pBullet = (CBullet*)pScene;

		D3DXVECTOR3 Bulletpos = pBullet->GetPosition();
		D3DXVECTOR2 Bulletsize = pBullet->GetSize();

		if (m_pEnemy[nCnt]->m_pos.x - m_pEnemy[nCnt]->m_size.x <= Bulletpos.x + Bulletsize.x &&				//ブロックの右端
			m_pEnemy[nCnt]->m_pos.x + m_pEnemy[nCnt]->m_size.x >= Bulletpos.x - Bulletsize.x &&				//ブロックの左端
			m_pEnemy[nCnt]->m_pos.y - m_pEnemy[nCnt]->m_size.y <= Bulletpos.y + Bulletsize.y &&				//ブロックの下部
			m_pEnemy[nCnt]->m_pos.y + m_pEnemy[nCnt]->m_size.y >= Bulletpos.y - Bulletsize.y)					//ブロックの上部
		{
			pBullet->SetUse(true);
			
		}
		// ブロックオブジェクトの次のオブジェクトを取得
		CScene * pSceneNext = CScene::GetNext(pScene);
		pScene = pSceneNext;
	}
}