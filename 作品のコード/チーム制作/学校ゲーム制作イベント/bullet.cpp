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

//=============================================================================
// 弾のコンストラクタ
//=============================================================================
CBullet::CBullet(int nPriority) : CScene2D(PRIORITY_BULLET), m_AddSize(D3DXVECTOR2(1.0f, 1.0f)), m_AddColor(D3DXCOLOR(0, 0, 0, 20))
{
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Size = D3DXVECTOR2(0.0f, 0.0f);	
	m_bEffect = true;		
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
CBullet *CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size, bool bEffect)
{
	CBullet* pBullet = NULL;

	pBullet = new CBullet;

	if (pBullet != NULL)
	{
		pBullet->Init(pos, Size);
		pBullet->m_Move = move;		
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
	m_Pos = pos;
	m_Size = Size;	

	return S_OK;
}	// ポリゴンの初期化処理終了



//=============================================================================
// 弾の終了処理
//=============================================================================
void CBullet::Uninit(void)
{
	// 解放処理
	Release();

}// ポリゴンの終了処理終了


//=============================================================================
// 弾の更新処理
//=============================================================================
void CBullet::Update(void)
{
	m_PosOld = m_Pos;
	
	if (m_bEffect)
	{
		CEffect::Create(m_Pos, m_Size, m_AddSize, m_AddColor,0);
	}

	m_Pos += m_Move;

	SetPosition(m_Pos);	

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
	//	m_bAlive = true;
	//}
	//else if (m_Pos.y <= (m_Size.y / 2))
	//{
	//	m_bAlive = true;
	//}


//	EnemyColision();

	if (m_bUse)
	{
		Uninit();
		return;
	}
	CScene2D::Update();

}// ポリゴンの更新処理終了



//=============================================================================
// 弾の描画処理
//=============================================================================
void CBullet::Draw(void)
{
	CScene2D::Draw();

}	// ポリゴンの描画処理終了

//	//=============================================================================
//	// ブロックと弾の当たり判定
//	//=============================================================================
//void CBullet::EnemyColision()
//{
//	CScene * pScene = CScene::GetScene(CScene::PRIORITY_ENEMY);
//
//	while (pScene != NULL)
//	{
//		CEnemy02 *pBlock = (CEnemy02*)pScene;
//
//		if (m_Pos.x + m_Size.x >= pBlock->GetPosition().x - pBlock->GetSize().x &&
//			m_Pos.x - m_Size.x <= pBlock->GetPosition().x + pBlock->GetSize().x &&
//			m_Pos.y + m_Size.y >= pBlock->GetPosition().y - pBlock->GetSize().y &&
//			m_Pos.y - m_Size.y <= pBlock->GetPosition().y + pBlock->GetSize().y)
//		{			
//			m_bUse = true;					
//		}
//		// ブロックオブジェクトの次のオブジェクトを取得
//		CScene * pSceneNext = CScene::GetNext(pScene);
//		pScene = pSceneNext;
//	}
//}
