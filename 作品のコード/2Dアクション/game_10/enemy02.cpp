//=============================================================================
//
// 敵の処理 [enemy.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include"enemy02.h"
#include"renderer.h"
#include"manager.h"
#include"player.h"
#include"game.h"
#include"noneblock.h"

#include"input.h"

//=============================================================================
// 敵のコンストラクタ
//=============================================================================
CEnemy02::CEnemy02(int nPriority) : CEnemy(PRIORITY_ENEMY)
{
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_OldPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Size = D3DXVECTOR2(0.0f, 0.0f);
}


//=============================================================================
// 敵のデストラクタ
//=============================================================================
CEnemy02::~CEnemy02()
{

}

//=============================================================================
// 敵の生成処理
//=============================================================================
CEnemy02 *CEnemy02::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size)
{
	CEnemy02* pEnemy;

	pEnemy = new CEnemy02;

	if (pEnemy != NULL)
	{		
		pEnemy->Bindtexture(0);
		pEnemy->Init(pos, move,Size);
	}
	return pEnemy;	
}

//=============================================================================
// 敵の初期化処理
//=============================================================================
HRESULT CEnemy02::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size)
{
	m_Pos = pos;
	m_OldPos = pos;
	m_Move = move;
	m_Size = Size;
	CEnemy::Init(pos, move, Size);

	return S_OK;
}	// 敵の初期化処理終了



	//=============================================================================
	// 敵の終了処理
	//=============================================================================
void CEnemy02::Uninit(void)
{
	CEnemy::Uninit();

}// 敵の終了処理終了


 //=============================================================================
 // 敵の更新処理
 //=============================================================================
void CEnemy02::Update(void)
{	
	m_OldPos = m_Pos;
	D3DXVECTOR3 Playerpos = CGame::GetPlayer()->GetPos();
	D3DXVECTOR2 PlayerSize = CGame::GetPlayer()->GetSize();

	// プレイヤーと敵の斜辺の距離を測るA＝絶対値(a-b)
	float fRange = fabs(Playerpos.x - m_Pos.x);		// fabs = 絶対値
	
	if (fRange != 0)
	{
		// 現在の位置+円の面積がプレイヤーと敵の斜辺の距離が円の面積以上(右の場合)or以下（左の場合）に入っていたら
		if (100.0f >= fRange)
		{
			m_Move.x = ((Playerpos.x - m_Pos.x) / (fRange/2));
		}
	}
			
	// 重力
	m_Move.y++;

	m_Pos += m_Move;

	BlockCollision();
	SetPos(m_Pos);

	CEnemy::Update();

}// 敵の更新処理終了



 //=============================================================================
 // 敵の描画処理
 //=============================================================================
void CEnemy02::Draw(void)
{
	CEnemy::Draw();

}	// 敵の描画処理終了

//=============================================================================
// 敵とブロックの当たり判定処理
//=============================================================================
void CEnemy02::BlockCollision()
{
	CScene * pScene = CScene::GetScene(CScene::PRIORITY_BLOCK);

	while (pScene != NULL)
	{
		// 取得したオブジェクトを普通のブロックに代入
		CNoneBlock *pBlock = (CNoneBlock*)pScene;

		D3DXVECTOR3 Blockpos = pBlock->GetPosition();
		D3DXVECTOR2 Blocksize = pBlock->GetSize();

		if (m_Pos.x - m_Size.x < Blockpos.x + Blocksize.x &&				//ブロックの右端
			m_Pos.x + m_Size.x > Blockpos.x - Blocksize.x &&				//ブロックの左端
			m_Pos.y - m_Size.y < Blockpos.y + Blocksize.y &&							//ブロックの下部
			m_Pos.y + m_Size.y > Blockpos.y - Blocksize.y)						//ブロックの上部
		{
			if (m_OldPos.y + m_Size.y <= Blockpos.y - Blocksize.y)			//ブロックの上部			
			{
				m_Pos.y = Blockpos.y - m_Size.y - Blocksize.y;
				m_Move.y = 0.0f;
			}
			else if (m_OldPos.y - m_Size.y >= Blockpos.y + Blocksize.y)			//ブロックの下部			
			{
				m_Pos.y = Blockpos.y + Blocksize.y + m_Size.y;
			}
			else if (m_OldPos.x - m_Size.x >= Blockpos.x + Blocksize.x)		//ブロックの右端			
			{
				m_Pos.x = Blockpos.x + m_Size.x + Blocksize.x;
				m_Move.x = 1;
			}
			else if (m_OldPos.x + m_Size.x <= Blockpos.x - Blocksize.x)		//ブロックの左端			
			{
				m_Pos.x = Blockpos.x - m_Size.x - Blocksize.x;
				m_Move.x = -1;
			}
		}
		// ブロックオブジェクトの次のオブジェクトを取得
		CScene * pSceneNext = CScene::GetNext(pScene);
		pScene = pSceneNext;
	}
}