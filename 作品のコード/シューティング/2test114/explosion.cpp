//=============================================================================
//
// 爆発の処理 [explosion.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include"explosion.h"
#include"renderer.h"
#include"manager.h"

// 静的メンバ変数の宣言
LPDIRECT3DTEXTURE9 CExplosion::m_pTexture = NULL;

//=============================================================================
// 爆発のコンストラクタ
//=============================================================================
CExplosion::CExplosion(int nPriority) : CScene2D(nPriority)
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
CExplosion *CExplosion::Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	CExplosion* pExplosion;

	pExplosion = new CExplosion;

	if (pExplosion != NULL)
	{
		pExplosion->Init(pos, Size);
		pExplosion->BindTextuer(m_pTexture);
	}
	return pExplosion;
}

//=============================================================================
// テクスチャの読み込み
//=============================================================================
HRESULT CExplosion::Load(void)
{
	CManager *pManager = NULL;

	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/ex000.png",
		&m_pTexture);

	return S_OK;
}

//=============================================================================
// テクスチャの破棄
//=============================================================================
void CExplosion::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// 爆発の初期化処理
//=============================================================================
HRESULT CExplosion::Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	CScene2D::Init(pos, Size);
	CScene2D::SetTexAnime(m_nPatternAnim,0.125f);

	return S_OK;
}	// ポリゴンの初期化処理終了



//=============================================================================
// 爆発の終了処理
//=============================================================================
void CExplosion::Uninit(void)
{
	CScene2D::Uninit();

}// ポリゴンの終了処理終了


//=============================================================================
// 爆発の更新処理
//=============================================================================
void CExplosion::Update(void)
{
	D3DXVECTOR3 pos = GetPosition();
	
	CScene2D::Update();

	SetPosition(pos);

	m_nCounterAnim++;

	if (m_nCounterAnim % 4 == 0)
	{
		m_nPatternAnim++;

		CScene2D::SetTexAnime(m_nPatternAnim,0.125f);

		if (m_nPatternAnim >= 8)
		{
			Uninit();
			return;
		}
	}


}// ポリゴンの更新処理終了



 //=============================================================================
 // 爆発の描画処理
 //=============================================================================
void CExplosion::Draw(void)
{
	CScene2D::Draw();

}	// ポリゴンの描画処理終了