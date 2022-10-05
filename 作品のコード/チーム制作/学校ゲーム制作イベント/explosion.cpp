//=============================================================================
//
// 爆発の処理 [explosion.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include"explosion.h"
#include"renderer.h"
#include"manager.h"

//=============================================================================
// 爆発のコンストラクタ
//=============================================================================
CExplosion::CExplosion(int nPriority) : CScene2D(PRIORITY_EFFECT)
{	
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
	m_bUse = true;
}


//=============================================================================
// 爆発のデストラクタ
//=============================================================================
CExplosion::~CExplosion()
{

}


//=============================================================================
// 爆発の生成処理
//=============================================================================
CExplosion *CExplosion::Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size,int nTex)
{
	CExplosion* pExplosion = NULL;

	// ポインターの動的メモリの確保
	pExplosion = new CExplosion;

	//NULLチェック
	if (pExplosion != NULL)
	{
		// 初期化処理の呼び出し
		pExplosion->Init(pos, Size);

		// テクスチャの設定処理
		pExplosion->Bindtexture(nTex);
	}
	return pExplosion;
}

//=============================================================================
// 爆発の初期化処理
//=============================================================================
HRESULT CExplosion::Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	// 初期化処理の呼び出し
	CScene2D::Init(pos, Size);
	// アニメーションテクスチャの設定
	CScene2D::SetTexAnime(m_nPatternAnim,0.125f,0,1);

	return S_OK;
}	// ポリゴンの初期化処理終了



//=============================================================================
// 爆発の終了処理
//=============================================================================
void CExplosion::Uninit(void)
{
	//CScene2D::Uninit();
	Release();

}// ポリゴンの終了処理終了


//=============================================================================
// 爆発の更新処理
//=============================================================================
void CExplosion::Update(void)
{
	// 使われていなかったら
	if (!m_bUse)
	{
		Uninit();
		return;
	}

	D3DXVECTOR3 pos = GetPosition();

	m_nCounterAnim++;

	if (m_nCounterAnim % 4 == 0)
	{
		m_nPatternAnim++;

		CScene2D::SetTexAnime(m_nPatternAnim,0.125f, 0, 1);

		if (m_nPatternAnim >= 8)
		{
			m_nPatternAnim = 0;
			m_bUse = false;
		}
	}

	SetPosition(pos);
	CScene2D::Update();
}// ポリゴンの更新処理終了



 //=============================================================================
 // 爆発の描画処理
 //=============================================================================
void CExplosion::Draw(void)
{
	CScene2D::Draw();

}	// ポリゴンの描画処理終了