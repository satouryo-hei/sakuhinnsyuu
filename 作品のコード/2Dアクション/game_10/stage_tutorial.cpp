//=============================================================================
//
// ステージ処理 [bg.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include"stage_tutorial.h"
#include"renderer.h"
#include"manager.h"
#include"goal.h"

//=============================================================================
// ステージのコンストラクタ
//=============================================================================
CStage_Tutorial::CStage_Tutorial() 
{	
	
}

//=============================================================================
// ステージのデストラクタ
//=============================================================================
CStage_Tutorial::~CStage_Tutorial()
{

}


//=============================================================================
// ステージの初期化処理
//=============================================================================
HRESULT CStage_Tutorial::Init(D3DXVECTOR3 pos)
{
	// ステージの初期化処理の呼び出し
	CStage::Init(pos);

	// ゴールの生成処理の呼び出し
	CGoal::Create(D3DXVECTOR3(1020.0f, 630.0f, 0.0f), D3DXVECTOR2(100.0f, 50.0f), CManager::MODE_SELECT);	

	return S_OK;
}

//=============================================================================
// ステージの終了処理
//=============================================================================
void CStage_Tutorial::Uninit(void)
{
	// ステージの終了処理の呼び出し
	CStage::Uninit();
}

//=============================================================================
// ステージの更新処理
//=============================================================================
void CStage_Tutorial::Update(void)
{

}

//=============================================================================
// ステージの描画処理
//=============================================================================
void CStage_Tutorial::Draw(void)
{

}
