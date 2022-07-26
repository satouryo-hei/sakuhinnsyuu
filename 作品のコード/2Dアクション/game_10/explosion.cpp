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
	CExplosion* pExplosion;

	pExplosion = new CExplosion;

	if (pExplosion != NULL)
	{
		pExplosion->Init(pos, Size);
		pExplosion->Bindtexture(nTex);
	}
	return pExplosion;
}

//=============================================================================
// 爆発の初期化処理
//=============================================================================
HRESULT CExplosion::Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	CScene2D::Init(pos, Size);
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
	D3DXVECTOR3 pos = GetPosition();

	m_nCounterAnim++;

	if (m_nCounterAnim % 4 == 0)
	{
		m_nPatternAnim++;

		CScene2D::SetTexAnime(m_nPatternAnim,0.125f, 0, 1);

		if (m_nPatternAnim >= 8)
		{
			Uninit();
			return;
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