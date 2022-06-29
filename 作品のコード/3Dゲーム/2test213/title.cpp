//=============================================================================
//
// タイトルの処理 [title.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include "title.h"
#include "scene2D.h"
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"bg.h"
#include"fade.h"
#include"title_logo.h"
#include"press_next.h"

//=============================================================================
// 静的メンバ変数の宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CTitle::m_pTexture = NULL;
CBg * CTitle::m_pBg = NULL;
CTitle_Logo* CTitle::m_pTitle_Logo = NULL;
CPress_Next* CTitle::m_pPress_Next = NULL;

//=============================================================================
// タイトルのコンストラクタ
//=============================================================================
CTitle::CTitle(int nPriority) : CScene(PRIORITY_NOMAL)
{
	m_bFade = true;
}

//=============================================================================
// タイトルのデストラクタ
//=============================================================================
CTitle::~CTitle()
{

}

//=============================================================================
// タイトルの初期化処理
//=============================================================================
HRESULT CTitle::Init(D3DXVECTOR3 pos)
{
	m_pBg = CBg::Create(pos, D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), 0);
	m_pTitle_Logo = CTitle_Logo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 100.0f, 0.0f), D3DXVECTOR2(SCREEN_WIDTH / 2, 320.0f));
	m_pPress_Next = CPress_Next::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 740.0f, 0.0f), D3DXVECTOR3(0.0f, 5.0f, 0.0f), D3DXVECTOR2(300.0f, 100.0f), 540.0f); 

	return S_OK;
}

//=============================================================================
// タイトルの終了処理
//=============================================================================
void CTitle::Uninit(void)
{
	CScene::Release();

	//if (m_pBg != NULL)
	//{
	//	m_pBg->Uninit();
	//	m_pBg = NULL;
	//}
}

//=============================================================================
// タイトルの更新処理
//=============================================================================
void CTitle::Update(void)
{
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN) == true && m_bFade)
	{	
		CFade::SetFade(CManager::MODE_SELECT);
		m_bFade = false;
	}
}

//=============================================================================
// タイトルの描画処理
//=============================================================================
void CTitle::Draw(void)
{

}