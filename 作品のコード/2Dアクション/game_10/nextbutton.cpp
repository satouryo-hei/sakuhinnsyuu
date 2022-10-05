//=============================================================================
//
// 次に行くボタンのUIの処理 [nextbutton.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include"nextbutton.h"
#include"renderer.h"
#include"manager.h"
#include"polygon.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
CPolygon *CNextBotton::m_pPolygon = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CNextBotton::CNextBotton(PRIORITY Priority) :CScene(PRIORITY_UI), m_fHeight(600.0f), m_nColMax(255)
{
	m_Pos = D3DXVECTOR3(100.0f, 50.0f, 0);
	m_Move = D3DXVECTOR3(0, 5.0f, 0);
	m_Size = D3DXVECTOR2(100.0f, 50.0f);
	m_Col = D3DXCOLOR(m_nColMax, m_nColMax, m_nColMax, m_nColMax);
	m_bAdditionCol = true;
}


//=============================================================================
// デストラクタ
//=============================================================================
CNextBotton::~CNextBotton()
{

}

//=============================================================================
// 次に行くボタンのUIの生成処理
//=============================================================================
CNextBotton *CNextBotton::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	// 2Dエフェクトのポインター生成
	CNextBotton* pNextBotton = NULL;

	// 動的メモリの確保
	pNextBotton = new CNextBotton;

	// NULLチェック
	if (pNextBotton != NULL)
	{
		pNextBotton->m_Size = size;

		// 次に行くボタンのUIの初期化処理
		pNextBotton->Init(pos);
	}
	return pNextBotton;
}

//=============================================================================
//  次に行くボタンのUIの初期化処理
//=============================================================================
HRESULT CNextBotton::Init(D3DXVECTOR3 pos)
{
	m_Pos = pos;
	m_pPolygon = CPolygon::Create(pos, m_Size, 13);

	return S_OK;
} //  ロゴの初期化処理の終了



	//=============================================================================
	//  次に行くボタンのUIの終了処理
	//=============================================================================
void CNextBotton::Uninit(void)
{
	// シーンの解放処理
	CScene::Release();

} // 次に行くボタンのUIの終了処理の終了


 //=============================================================================
 //  次に行くボタンのUIの更新処理
 //=============================================================================
void CNextBotton::Update(void)
{
	// 加算する場合
	if (m_bAdditionCol)
	{
		m_Col.a--;

		if (m_Col.a <= m_nColMax/2)
		{
			m_bAdditionCol = false;
		}
	}
	else // それ以外
	{
		m_Col.a++;

		if (m_Col.a >= m_nColMax)
		{
			m_bAdditionCol = true;
		}
	}
	
	// ポリゴンの色を設定
	m_pPolygon->SetRgba(m_Col.r, m_Col.g, m_Col.b, m_Col.a);

	// m_fHeightの高さまでm_Posが行ったら
	if (m_Pos.y >= m_fHeight)
	{
		// 現在の位置に移動値を減算
		m_Pos -= m_Move;

		// ポリゴンのm_Posを設定
		m_pPolygon->SetPosition(m_Pos);
	}
} // 次に行くボタンのUIの更新処理終了



 //=============================================================================
 // 次に行くボタンのUIの描画処理
 //=============================================================================
void CNextBotton::Draw(void)
{

} // 次に行くボタンのUIの描画処理終了
