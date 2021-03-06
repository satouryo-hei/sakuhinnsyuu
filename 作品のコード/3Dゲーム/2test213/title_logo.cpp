//=============================================================================
//
// タイトルロゴの処理 [bg.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include"title_logo.h"
#include"renderer.h"
#include"manager.h"
#include"polygon.h"

//=============================================================================
// 静的メンバ変数の宣言
//=============================================================================
CPolygon * CTitle_Logo::m_Polygon = NULL;

//=============================================================================
// タイトルロゴのコンストラクタ
//=============================================================================
CTitle_Logo::CTitle_Logo(PRIORITY nPriority) : CScene(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// タイトルロゴのデストラクタ
//=============================================================================
CTitle_Logo::~CTitle_Logo()
{

}

//=============================================================================
// タイトルロゴの生成処理
//=============================================================================																				
CTitle_Logo *CTitle_Logo::Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	// 時間のポインター生成
	CTitle_Logo* pTitle_Logo = NULL;

	// 動的メモリの確保
	pTitle_Logo = new CTitle_Logo;

	// NULLチェック
	if (pTitle_Logo != NULL)
	{
		// サイズに入れる(サイズの設定)
		pTitle_Logo->m_Size = Size;

		// タイトルロゴの初期化処理の呼び出し
		pTitle_Logo->Init(pos);
	}
	return pTitle_Logo;
}

//=============================================================================
// タイトルロゴの初期化処理
//=============================================================================
HRESULT CTitle_Logo::Init(D3DXVECTOR3 pos)
{
	// ポリゴンの生成処理
	m_Polygon = CPolygon::Create(pos, m_Size, 11);
	m_pos = pos;
	return S_OK;
}

//=============================================================================
// タイトルロゴの終了処理
//=============================================================================
void CTitle_Logo::Uninit(void)
{
	// 解放処理
	Release();
}

//=============================================================================
// タイトルロゴの更新処理
//=============================================================================
void CTitle_Logo::Update(void)
{
	// 現在位置が320よりも小さかったら
	if (m_pos.y < 320)
	{
		// 現在位置のY座標を下に下げる
		m_pos.y++;
		// 現在位置の更新
		m_Polygon->SetPosition(m_pos);
	}
	// ポリゴンの更新処理の呼び出し
	m_Polygon->Update();
}

//=============================================================================
// タイトルロゴの描画処理
//=============================================================================
void CTitle_Logo::Draw(void)
{
}