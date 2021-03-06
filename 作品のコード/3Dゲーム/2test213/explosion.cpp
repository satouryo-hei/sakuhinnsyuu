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
CExplosion::CExplosion(PRIORITY nPriority) : CBillboard(nPriority)
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
	// ビルボードのポインター生成
	CExplosion* pExplosion;

	// 動的メモリの確保
	pExplosion = new CExplosion;

	// NULLチェック
	if (pExplosion != NULL)
	{
		// 爆発の初期化処理の呼び出し
		pExplosion->Init(pos, Size);
		// 爆発のテクスチャの設定
		pExplosion->BindTextuer(17);
	}
	return pExplosion;
}

//=============================================================================
// 爆発の初期化処理
//=============================================================================
HRESULT CExplosion::Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	// 継承元の初期処理の呼び出し
	CBillboard::Init(pos, Size);
	//パターン数、アニメーションしたいU座標、アニメーションしたいV座標の最小の数、アニメーションしたいV座標の最大の数
	CBillboard::SetTexAnime(m_nPatternAnim, 0.125f, 0.0f, 1.0f);

	return S_OK;
}	// ポリゴンの初期化処理終了



	//=============================================================================
	// 爆発の終了処理
	//=============================================================================
void CExplosion::Uninit(void)
{
	// 継承元の終了処理の呼び出し
	CBillboard::Uninit();

}// ポリゴンの終了処理終了


 //=============================================================================
 // 爆発の更新処理
 //=============================================================================
void CExplosion::Update(void)
{
	// 継承元の更新処理の呼び出し
	CBillboard::Update();

	// アニメーションのカウンターを加算
	m_nCounterAnim++;

	// アニメーションのカウンターを/4して余った数が0だったら
	if (m_nCounterAnim % 4 == 0)
	{
		// パターンアニメーションを加算
		m_nPatternAnim++;

		//パターン数、アニメーションしたいU座標、アニメーションしたいV座標の最小の数、アニメーションしたいV座標の最大の数
		CBillboard::SetTexAnime(m_nPatternAnim, 0.125f, 0.0f, 1.0f);

		// パターンアニメーションが8以上だった時
		if (m_nPatternAnim >= 8)
		{
			// 終了処理の呼び出し
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
	// 継承元の描画処理の呼び出し
	CBillboard::Draw();

}	// ポリゴンの描画処理終了