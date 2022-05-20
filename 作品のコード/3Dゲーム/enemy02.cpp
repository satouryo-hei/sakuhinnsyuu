//=============================================================================
//
// 敵の処理 [player2.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include"enemy02.h"
#include"renderer.h"
#include"manager.h"
#include"input.h"
#include"model.h"
#include"shadow.h"
#include"title.h"
#include"bullet.h"
#include"game.h"
#include"player.h"

//=============================================================================
// 静的メンバ変数の宣言
//=============================================================================
CShadow* CEnemy2::m_pShadow = NULL;
CModel * CEnemy2::m_pModel[20] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CEnemy2::CEnemy2(PRIORITY Priority) :CEnemy(Priority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fRadius = 10.0f;
	m_nNumKey = 0;
}


//=============================================================================
// デストラクタ
//=============================================================================
CEnemy2::~CEnemy2()
{

}

//=============================================================================
// 敵の生成処理
//=============================================================================
CEnemy2 *CEnemy2::Create(D3DXVECTOR3 pos, const char *pFileName)
{
	// 敵のポインター生成
	CEnemy2* pEnemy = NULL;

	// 動的メモリの確保
	pEnemy = new CEnemy2;

	// NULLチェック
	if (pEnemy != NULL)
	{
		pEnemy->Init(pos, pFileName);
	}
	return pEnemy;
}

	//=============================================================================
	// 敵のロード関数をオーバーロードした初期化処理
	//=============================================================================
HRESULT CEnemy2::Init(D3DXVECTOR3 pos, const char *pFileName)
{
	// 継承先の初期化処理を呼び出す
	CEnemy::Init(pos, pFileName);

	return S_OK;
}



//=============================================================================
// 敵の終了処理
//=============================================================================
void CEnemy2::Uninit(void)
{
	// 継承先の終了処理を呼び出す
	CEnemy::Uninit();
	Release();

}// ポリゴンの終了処理終了


 //=============================================================================
 // 敵の更新処理
 //=============================================================================
void CEnemy2::Update(void)
{
	////=============================================================================
	// 自機の弾と敵の当たり判定
	//=============================================================================
	for (int nPriority = 0; nPriority < PRIORITY_MAX; nPriority++)
	{
		CScene * pScene = NULL;

		pScene = CScene::GetScene(nPriority);

		if (pScene != NULL)
		{
			if (nPriority == CScene::PRIORITY_BULLET)
			{
				CBullet *pBullet = (CBullet*)pScene;

				if (m_pos.x+10 >= pBullet->GetPos().x - pBullet->GetSize().x&&
					m_pos.x - 10 <= pBullet->GetPos().x + pBullet->GetSize().x&&
					m_pos.y+50 >= pBullet->GetPos().y - pBullet->GetSize().y&&
					m_pos.y+50 <= pBullet->GetPos().y + pBullet->GetSize().y&&
					m_pos.z -10 <= pBullet->GetPos().z
					)
				{
					pBullet->SetUse(false);
					Uninit();
					return;
				}
			}
		}
	}
		static D3DXVECTOR3 m_Playerpos = CGame::GetPlayer()->GetPos();
		// プレイヤーとトンボの斜辺の距離を測るA＝√（三平方より(c2乗 = a2乗+b2乗)）
		m_fRange = sqrtf(powf((m_Playerpos.x - m_pos.x), 2.0f) + powf((m_Playerpos.z - m_pos.z), 2.0f));

	if (m_pos.x + (m_fRadius*powf(D3DX_PI,2)) >= m_fRange&&
		m_pos.x - (m_fRadius*powf(D3DX_PI,2)) >= m_fRange&&
		m_pos.z - (m_fRadius*powf(D3DX_PI,2)) >= m_fRange&&
		m_pos.z + (m_fRadius*powf(D3DX_PI,2)) >= m_fRange
		)
	{

		if (m_fRange != NULL)
		{
			m_Move.x = (m_Playerpos.x - m_pos.x) / m_fRange * 10;
			m_Move.z = (m_Playerpos.z - m_pos.z) / m_fRange * 10;
		}
		//else
		//{
		//	m_Move.z = 1;
		//}
	}

	m_pos += m_Move;

	SetPos(m_pos);

	// 継承先の更新処理を呼び出す
	CEnemy::Update();

}// ポリゴンの更新処理終了



 //=============================================================================
 // 敵の描画処理
 //=============================================================================
void CEnemy2::Draw(void)
{
	// 継承先の描画処理を呼び出す
	CEnemy::Draw();

}// ポリゴンの描画処理終了