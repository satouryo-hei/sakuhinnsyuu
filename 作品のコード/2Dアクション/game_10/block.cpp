//=============================================================================
//
// ブロックの処理 [score.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include "block.h"

#include"noneblock.h"
#include"moveblock.h"
#include"pushblock.h"

//=============================================================================
// 静的メンバ変数の宣言
//=============================================================================
CNoneBlock * CBlock::m_pNone = NULL;
CMoveBlock * CBlock::m_pMove = NULL;
CPushBlock * CBlock::m_pPush = NULL;

//=============================================================================
// ブロックのコンストラクタ
//=============================================================================
CBlock::CBlock(int nPriority) : CScene(PRIORITY_NOMAL)
{
	m_pos = D3DXVECTOR3(0, 0, 0);
}

//=============================================================================
// ブロックのデストラクタ
//=============================================================================
CBlock::~CBlock()
{

}

//=============================================================================
// ブロックの生成処理
//=============================================================================
CBlock *CBlock::Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size, D3DXVECTOR3 move,
	int nBlockType, int nMovetype, float fMin, float fMax,bool bBreak ,int nTex)
{
	CBlock *pBlock = NULL;
	pBlock = new CBlock;

	if (pBlock != NULL)
	{
		pBlock->Init(pos);
		pBlock->SetBlock(pos, Size, move,nBlockType, nMovetype, 
			fMin, fMax, bBreak, nTex);
	}
	return pBlock;
}

//=============================================================================
// ブロックの初期化処理
//=============================================================================
HRESULT CBlock::Init(D3DXVECTOR3 pos)
{
	m_pos = pos;	

	return S_OK;
}

//=============================================================================
// ブロックの終了処理
//=============================================================================
void CBlock::Uninit(void)
{
	Release();
}

//=============================================================================
// ブロックの更新処理
//=============================================================================
void CBlock::Update(void)
{

}

//=============================================================================
// ブロックの描画処理
//=============================================================================
void CBlock::Draw(void)
{

}

//=============================================================================
// ブロックの設定処理
//=============================================================================
void CBlock::SetBlock(D3DXVECTOR3 pos, D3DXVECTOR2 Size, D3DXVECTOR3 move,
	int nBlockType, int nMovetype, float fMin, float fMax, bool bBreak,int nTex)
{
	// ブロックの状態の遷移
	switch (nBlockType)
	{
		// ブロックが移動をしないとき
	case BLOCKTYPE_NOME:
		m_pNone = CNoneBlock::Create(pos, Size, bBreak, nTex);
		break;

		// ブロックがの移動をしているとき
	case BLOCKTYPE_MOVEING:		
		m_pMove = CMoveBlock::Create(pos, Size, move,
			nMovetype, fMin, fMax, nTex);
		break;

		// ブロックが押されるとき
	case BLOCKTYPE_PUSH:
		m_pPush = CPushBlock::Create(pos, Size, move, nTex);
		break;

	default:
		break;
	}	
}
