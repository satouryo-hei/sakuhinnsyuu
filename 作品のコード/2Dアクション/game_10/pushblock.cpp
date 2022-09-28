//=============================================================================
//
// ブロックの処理 [score.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include "pushblock.h"
#include"noneblock.h"

//=============================================================================
// ブロックのコンストラクタ
//=============================================================================
CPushBlock::CPushBlock(int nPriority) : CScene2D(PRIORITY_PUSHBLOCK)
{
	m_pos = D3DXVECTOR3(0, 0, 0);
	m_move = D3DXVECTOR3(0, 0, 0);
	m_size = D3DXVECTOR2(0, 0);
}

//=============================================================================
// ブロックのデストラクタ
//=============================================================================
CPushBlock::~CPushBlock()
{

}

//=============================================================================
// ブロックの生成処理
//=============================================================================
CPushBlock *CPushBlock::Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size, D3DXVECTOR3 move, int nTex)
{
	CPushBlock *pBlock = NULL;
	pBlock = new CPushBlock;

	if (pBlock != NULL)
	{
		pBlock->Init(pos, Size);
		pBlock->m_move = move;
		pBlock->Bindtexture(0);
	}
	return pBlock;
}

//=============================================================================
// ブロックの初期化処理
//=============================================================================
HRESULT CPushBlock::Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	m_pos = pos;
	m_size = Size;
	CScene2D::Init(pos, Size);
	return S_OK;
}

//=============================================================================
// ブロックの終了処理
//=============================================================================
void CPushBlock::Uninit(void)
{
	//CScene2D::Uninit();
	Release();
}

//=============================================================================
// ブロックの更新処理
//=============================================================================
void CPushBlock::Update(void)
{
	m_posOld = m_pos;
	m_move.y ++;
	m_pos.y += m_move.y;	

	if (m_pos.x + m_size.x >= SCREEN_WIDTH)
	{
		m_pos.x = SCREEN_WIDTH - m_size.x;
	}
	else if (m_pos.x <= m_size.x)
	{
		m_pos.x = m_size.x;
	}

	if (m_pos.y + m_size.y >= SCREEN_HEIGHT)
	{
		m_pos.y = SCREEN_HEIGHT - m_size.y;	
	}
	else if (m_pos.y <= m_size.y)
	{
		m_pos.y = m_size.y;
	}

	NoneColision();

	CScene2D::SetPosition(m_pos);

	CScene2D::Update();
}

//=============================================================================
// ブロックの描画処理
//=============================================================================
void CPushBlock::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// ブロックの描画処理
//=============================================================================
void CPushBlock::NoneColision(void)
{
	// ブロックオブジェクトを取得
	CScene * pScene = CScene::GetScene(CScene::PRIORITY_BLOCK);

	while (pScene != NULL)
	{
		// 取得したオブジェクトを普通のブロックに代入
		CNoneBlock *pNoneBlock = (CNoneBlock*)pScene;

		D3DXVECTOR3 Nonepos = pNoneBlock->GetPosition();
		D3DXVECTOR2 Nonesize = pNoneBlock->GetSize();

		if (m_pos.x - m_size.x < Nonepos.x + Nonesize.x &&				//ブロックの右端
			m_pos.x + m_size.x > Nonepos.x - Nonesize.x &&				//ブロックの左端
			m_pos.y - m_size.y < Nonepos.y + Nonesize.y &&							//ブロックの下部
			m_pos.y + m_size.y > Nonepos.y - Nonesize.y)						//ブロックの上部
		{
			if (m_posOld.y + m_size.y <= Nonepos.y - Nonesize.y)			//ブロックの上部			
			{
				m_pos.y = Nonepos.y - m_size.y - Nonesize.y;	
				m_move.y = 0;
			}
			else if (m_posOld.x - m_size.x <= Nonepos.x + Nonesize.x)		//ブロックの右端			
			{
				m_pos.x = Nonepos.x + m_size.x + Nonesize.x;
			}
			else if (m_posOld.x + m_size.x >= Nonepos.x - Nonesize.x)		//ブロックの左端			
			{
				m_pos.x = Nonepos.x - m_size.x - Nonesize.x;
			}
		}
		// ブロックオブジェクトの次のオブジェクトを取得
		CScene * pSceneNext = CScene::GetNext(pScene);
		pScene = pSceneNext;
	}
}