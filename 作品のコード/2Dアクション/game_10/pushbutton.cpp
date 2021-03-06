//=============================================================================
//
// 押すボタンの表示処理 [score.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include "pushbutton.h"


//=============================================================================
// 静的メンバ変数の宣言
//=============================================================================
bool CPushButton::m_bUse = false;

//=============================================================================
// 押すボタンの表示のコンストラクタ
//=============================================================================
CPushButton::CPushButton(int nPriority) : CScene2D(PRIORITY_UI)
{

}

//=============================================================================
// 押すボタンの表示のデストラクタ
//=============================================================================
CPushButton::~CPushButton()
{

}

//=============================================================================
// 押すボタンの表示の生成処理
//=============================================================================
CPushButton *CPushButton::Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size,int nTex )
{
	CPushButton *pPushButton = NULL;
	pPushButton = new CPushButton;

	if (pPushButton != NULL)
	{
		pPushButton->Init(pos, Size);
		pPushButton->Bindtexture(nTex);
	}
	return pPushButton;
}

//=============================================================================
// 押すボタンの表示の初期化処理
//=============================================================================
HRESULT CPushButton::Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	m_Pos = pos;
	CScene2D::Init(pos, Size);
	// アニメーションのテクスチャ設定
	CScene2D::SetTexAnime(0, 0.5f, 0, 1);
	return S_OK;
}

//=============================================================================
// 押すボタンの表示の終了処理
//=============================================================================
void CPushButton::Uninit(void)
{
	//CScene2D::Uninit();
	Release();
}

//=============================================================================
// 押すボタンの表示の更新処理
//=============================================================================
void CPushButton::Update(void)
{
	if (!m_bUse)
	{
		Uninit();
		return;
	}

	// アニメーションのカウントを進める
	m_nCounterAnim++;

	// アニメーションのカウントがアニメーションの速さで割って余ったのが0だった時(割り切れた時)
	if (m_nCounterAnim % 30 == 0)
	{
		// アニメーションのパターン数を進める
		m_nPatternAnim++;

		// アニメーションのテクスチャ設定
		CScene2D::SetTexAnime(m_nPatternAnim, 0.5f, 0, 1);		

		// アニメーションのパターン数がパターンの最大数を超えたら
		if (m_nPatternAnim >= 2)
		{
			// アニメーションのパターン数の初期化
			m_nPatternAnim = 0;			
		}
	}
	CScene2D::Update();
}

//=============================================================================
// 押すボタンの表示の描画処理
//=============================================================================
void CPushButton::Draw(void)
{
	CScene2D::Draw();
}