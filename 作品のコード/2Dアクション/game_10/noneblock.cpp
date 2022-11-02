//=============================================================================
//
// ブロックの処理 [score.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include "noneblock.h"
#include"bullet.h"
#include"explosion.h"

//=============================================================================
// ブロックのコンストラクタ
//=============================================================================
CNoneBlock::CNoneBlock(int nPriority) : CScene2D(PRIORITY_BLOCK)
{
	m_pos = D3DXVECTOR3(0, 0, 0);
	m_size = D3DXVECTOR2(0, 0);
	m_bBreak = false;
	m_bUse = true;
}

//=============================================================================
// ブロックのデストラクタ
//=============================================================================
CNoneBlock::~CNoneBlock()
{

}

//=============================================================================
// ブロックの生成処理
//=============================================================================
CNoneBlock *CNoneBlock::Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size,bool bBreak ,int nTex)
{
	// 普通のブロックのポインター生成
	CNoneBlock *pNoneBlock = NULL;

	// 動的メモリの確保
	pNoneBlock = new CNoneBlock;

	// NULLじゃなかったら
	if (pNoneBlock != NULL)
	{
		pNoneBlock->Init(pos, Size);
		pNoneBlock->m_bBreak = bBreak;
		pNoneBlock->Bindtexture(nTex);
	}
	return pNoneBlock;
}

//=============================================================================
// ブロックの初期化処理
//=============================================================================
HRESULT CNoneBlock::Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	m_pos = pos;
	m_size = Size;

	// オブジェクト2Dの初期化処理の呼び出し
	CScene2D::Init(pos, Size);
	return S_OK;
}

//=============================================================================
// ブロックの終了処理
//=============================================================================
void CNoneBlock::Uninit(void)
{
	// 解放処理
	Release();
}

//=============================================================================
// ブロックの更新処理
//=============================================================================
void CNoneBlock::Update(void)
{
	// 使用してないなら
	if (!m_bUse)
	{
		Uninit();
		return;
	}

	// 弾との当たり判定
	Colision();

	// オブジェクト2Dの更新処理の呼び出し
	CScene2D::Update();
}

//=============================================================================
// ブロックの描画処理
//=============================================================================
void CNoneBlock::Draw(void)
{
	// オブジェクト2Dの描画処理の呼び出し
	CScene2D::Draw();
}

//=============================================================================
// ブロックと弾の当たり判定
//=============================================================================
void CNoneBlock::Colision()
{
	// 弾のオブジェクトを取得
	CScene * pScene = CScene::GetScene(CScene::PRIORITY_BULLET);

	// オブジェクトがNULLじゃない限り回す
	while (pScene != NULL)
	{
		// 取得したオブジェクトを弾に代入 
		CBullet *pBullet = (CBullet*)pScene;

		// 弾の現在の位置を取得
		D3DXVECTOR3 Bulletpos = pBullet->GetPosition();

		// 弾の大きさを取得
		D3DXVECTOR2 BulletSize = pBullet->GetSize();		

		// 当たっているかどうか
		if (m_pos.x + m_size.x >= Bulletpos.x &&	// ブロックの左端 <= 弾の右端
			m_pos.x - m_size.x <= Bulletpos.x &&	// ブロックの右端 >= 弾の左端
			m_pos.y + m_size.y >= Bulletpos.y &&	// ブロックの上端 <= 弾の下部
			m_pos.y - m_size.y <= Bulletpos.y)		// ブロックの下端 >= 弾の上部
		{
			// もしも壊れるブロックであるかどうか
			if (m_bBreak)
			{// 壊れるブロックであれば
				//爆発の生成
				CExplosion::Create(m_pos, m_size, 9);

				// 使わなくする
				m_bUse = false;
			}
			else // それ以外
			{
				// 前回の弾の位置を取得
				D3DXVECTOR3 BulletOldpos = pBullet->GetPosOld();

				//爆発の生成
				CExplosion::Create(BulletOldpos, BulletSize, 9);
			}
			// 弾の終了処理の呼び出し
			pBullet->Uninit();
		}

		// ブロックオブジェクトの次のオブジェクトを取得
		CScene * pSceneNext = CScene::GetNext(pScene);

		// 取得したオブジェクトを代入
		pScene = pSceneNext;
	}
}