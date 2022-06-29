//=============================================================================
//
// リザルトの処理 [result.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include "result.h"
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"bg.h"
#include"fade.h"
#include"ranking.h"

//=============================================================================
// 静的メンバ変数の宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CResult::m_pTexture = NULL;
CBg* CResult::m_pBg = NULL;
CRanking* CResult::m_pRanking = NULL;

//=============================================================================
// リザルトのコンストラクタ
//=============================================================================
CResult::CResult(int nPriority) : CScene(PRIORITY_NOMAL)
{
	m_bFade = true;
}

//=============================================================================
// リザルトのデストラクタ
//=============================================================================
CResult::~CResult()
{

}
//=============================================================================
// リザルトの初期化処理
//=============================================================================
HRESULT CResult::Init(D3DXVECTOR3 pos)
{
	m_pBg = CBg::Create(pos, D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), 3);
	m_pRanking = CRanking::Create(pos, D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT));
	return S_OK;
}

//=============================================================================
// リザルトの終了処理
//=============================================================================
void CResult::Uninit(void)
{
	//if (m_pBg != NULL)
	//{
	//	m_pBg->Uninit();
	//	m_pBg = NULL;
	//}

	CScene::Release();
}

//=============================================================================
// リザルトの更新処理
//=============================================================================
void CResult::Update(void)
{
	CInputKeyboard *pInputKeyboard = NULL;
	pInputKeyboard = CManager::GetInputKeyboard();

	//任意で押されたかどうか
	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true && m_bFade)//ENTERを押した
	{
		//CManager::SetMode(CManager::MODE_TITLE);
		CFade::SetFade(CManager::MODE_TITLE);
		m_bFade = false;
	}
}

//=============================================================================
// リザルトの描画処理
//=============================================================================
void CResult::Draw(void)
{

}