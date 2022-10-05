//=============================================================================
//
// チュートリアルの処理 [title.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include "turorial.h"
#include "scene2D.h"
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"bg.h"
#include"fade.h"
#include"game.h"
#include"logo.h"
#include"nextbutton.h"

//=============================================================================
// 静的メンバ変数の宣言
//=============================================================================
CBg* CTutorial::m_pBg = NULL;
CLogo* CTutorial::m_pLogo = NULL;
CNextBotton* CTutorial::m_pNextBotton = NULL;

//=============================================================================
// タイトルのコンストラクタ
//=============================================================================
CTutorial::CTutorial(int nPriority) : CScene(PRIORITY_NOMAL)
{
	m_bFade = false;
}

//=============================================================================
// タイトルのデストラクタ
//=============================================================================
CTutorial::~CTutorial()
{

}

//=============================================================================
// タイトルの初期化処理
//=============================================================================
HRESULT CTutorial::Init(D3DXVECTOR3 pos)
{
	m_pBg = CBg::Create(pos, D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 18);

	/*m_pLogo = CLogo::Create(pos, D3DXVECTOR2(100, 600));
	m_pNextBotton = CNextBotton::Create(pos, D3DXVECTOR2(500, 500));*/
	return S_OK;
}

//=============================================================================
// タイトルの終了処理
//=============================================================================
void CTutorial::Uninit(void)
{
	CScene::Release();

	if (m_pBg != NULL)
	{
		m_pBg->Uninit();
		m_pBg = NULL;
	}
}

//=============================================================================
// タイトルの更新処理
//=============================================================================
void CTutorial::Update(void)
{
	CInputKeyboard *pInputKeyboard = NULL;
	pInputKeyboard = CManager::GetInputKeyboard();


	//任意で押されたかどうか
	if (pInputKeyboard->GetTrigger(DIK_SPACE) && !m_bFade)//ENTERを押した
	{
		CFade::SetFade(CManager::MODE_GAME);
		m_bFade = true;
	}
}

//=============================================================================
// タイトルの描画処理
//=============================================================================
void CTutorial::Draw(void)
{

}