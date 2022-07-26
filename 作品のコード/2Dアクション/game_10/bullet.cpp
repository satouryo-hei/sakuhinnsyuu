//=============================================================================
//
// 弾の処理 [bullet.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include"bullet.h"
#include"renderer.h"
#include"manager.h"
#include"input.h"
#include"player.h"
#include"effect.h"
#include"noneblock.h"
#include"explosion.h"

/*やりたいこと*/
/*弾の回転　←いるのか？
チャージショット
チャージショットで弾の拡大*/

////=============================================================================
//// 静的メンバ関数の宣言
////=============================================================================
//bool CBullet::m_bUse = false;

//=============================================================================
// 弾のコンストラクタ
//=============================================================================
CBullet::CBullet(int nPriority) : CScene2D(PRIORITY_BULLET)
{
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Size = D3DXVECTOR2(0.0f, 0.0f);
	m_nLife = 0;
	m_bEffect = true;
	//m_bUse = false;
}


//=============================================================================
// 弾のデストラクタ
//=============================================================================
CBullet::~CBullet()
{

}


//=============================================================================
// 弾の生成処理
//=============================================================================
CBullet *CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size, int nLife, bool bEffect)
{
	CBullet* pBullet = NULL;

	pBullet = new CBullet;

	if (pBullet != NULL)
	{
		pBullet->Init(pos, Size);
		pBullet->m_Move = move;
		pBullet->m_nLife = nLife;
		pBullet->m_bEffect = bEffect;
		pBullet->Bindtexture(6);
		pBullet->m_bUse = false;
	}

	return pBullet;
}

//=============================================================================
// 弾の初期化処理
//=============================================================================
HRESULT CBullet::Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	CScene2D::Init(pos, Size);
	
	int nItem = CPlayer::GetItem();
	m_nLife += nItem;
	m_Pos = pos;
	m_Size = Size;	

	return S_OK;
}	// ポリゴンの初期化処理終了



//=============================================================================
// 弾の終了処理
//=============================================================================
void CBullet::Uninit(void)
{
	//CScene2D::Uninit();

	Release();

}// ポリゴンの終了処理終了


//=============================================================================
// 弾の更新処理
//=============================================================================
void CBullet::Update(void)
{
	if (m_bUse)
	{
		Uninit();
		return;
	}

	m_PosOld = m_Pos;
	
	if (m_bEffect)
	{
		CEffect::Create(m_Pos, m_Size, D3DXVECTOR2(1.0f, 1.0f), D3DXCOLOR(0, 0, 0, 20));
	}

	m_Pos += m_Move;

	SetPosition(m_Pos);

	m_nLife -= 5;
	if (m_nLife < 0)
	{
		m_nLife = 0;
		m_bUse = true;
	}

	// 画面外処理
	if (m_Pos.x >= SCREEN_WIDTH - (m_Size.x / 2))
	{
		m_bUse = true;
	}
	else if (m_Pos.x <= (m_Size.x / 2))
	{
		m_bUse = true;
	}
	//if (m_Pos.y >= SCREEN_HEIGHT - (m_Size.y / 2))
	//{
	//	m_bUse = true;
	//}
	//else if (m_Pos.y <= (m_Size.y / 2))
	//{
	//	m_bUse = true;
	//}

	////=============================================================================
	//// 自機の弾と敵の当たり判定
	////=============================================================================
	//for (int nPriority = 0; nPriority < PRIORITY_MAX; nPriority++)
	//{
	//	CScene * pScene = NULL;

	//	pScene = CScene::GetScene(nPriority);

	//	if (pScene != NULL)
	//	{
	//		CScene::OBJTYPE objType;
	//		objType = pScene->GetOnjType();

	//		if (objType == CScene::OBJTYPE_ENEMY &&m_ObjType == CScene::OBJTYPE_PLAYERBULLET)
	//		{
	//			CEnemy *pEnemy = (CEnemy*)pScene;

	//			if (pos.x + (m_Size.x / 2) >= pEnemy->GetPosition().x - pEnemy->GetSize().x &&
	//				pos.x - (m_Size.x / 2) <= pEnemy->GetPosition().x + pEnemy->GetSize().x &&
	//				pos.y + (m_Size.y / 2) >= pEnemy->GetPosition().y - pEnemy->GetSize().y &&
	//				pos.y - (m_Size.y / 2) <= pEnemy->GetPosition().y + pEnemy->GetSize().y)
	//			{
	//				//爆発の生成
	//				CExplosion::Create(pos, D3DXVECTOR2(100.0f, 100.0f));
	//				pScore->AddScore(100);
	//				Uninit();
	//				pEnemy->Uninit();
	//				return;
	//			}
	//		}
	//	}
	//}
	//BlockColision();

	CScene2D::Update();

}// ポリゴンの更新処理終了



//=============================================================================
// 弾の描画処理
//=============================================================================
void CBullet::Draw(void)
{
	CScene2D::Draw();

}	// ポリゴンの描画処理終了

	//=============================================================================
	// ブロックと弾の当たり判定
	//=============================================================================
void CBullet::BlockColision()
{
	CScene * pScene = CScene::GetScene(CScene::PRIORITY_BLOCK);

	if(pScene != NULL)
	{
		CNoneBlock *pBlock = (CNoneBlock*)pScene;

		if (m_Pos.x >= pBlock->GetPosition().x - pBlock->GetSize().x &&
			m_Pos.x <= pBlock->GetPosition().x + pBlock->GetSize().x &&
			m_Pos.y >= pBlock->GetPosition().y - pBlock->GetSize().y &&
			m_Pos.y <= pBlock->GetPosition().y + pBlock->GetSize().y)
		{
			if (pBlock->GetPosition().y - pBlock->GetSize().y >= m_PosOld.y + m_Size.y)						//ブロックの上部
			{
				m_bUse = true;
			}			
		}
	}
}
