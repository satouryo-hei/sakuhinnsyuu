//=============================================================================
//
//  2Dエフェクトの処理 [effect.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include"polygoneffect.h"
#include"renderer.h"
#include"manager.h"
#include"polygon.h"
#include"input.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
CPolygon *CPolygonEffect::m_pPolygon[POLYGON_MAX] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CPolygonEffect::CPolygonEffect(PRIORITY Priority) :CScene(PRIORITY_EFFECT)
{
	m_Size = D3DXVECTOR2(100, 50);
}


//=============================================================================
// デストラクタ
//=============================================================================
CPolygonEffect::~CPolygonEffect()
{

}

//=============================================================================
// 2Dエフェクトの生成処理
//=============================================================================
CPolygonEffect *CPolygonEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	// 2Dエフェクトのポインター生成
	CPolygonEffect* pEffect = NULL;

	// 動的メモリの確保
	pEffect = new CPolygonEffect;

	// NULLチェック
	if (pEffect != NULL)
	{
		pEffect->m_Size = size;
		// 2Dエフェクトの初期化処理
		pEffect->Init(pos);
	}
	return pEffect;
}

//=============================================================================
//  2Dエフェクトの初期化処理
//=============================================================================
HRESULT CPolygonEffect::Init(D3DXVECTOR3 pos)
{
	// POLYGON_MAX分回す
	for (int nCnt = 0; nCnt < POLYGON_MAX; nCnt++)
	{
		// ポリゴンの生成処理
		m_pPolygon[nCnt] = CPolygon::Create(pos, m_Size, 100);

		// ポリゴンの斜辺の設定処理
		m_pPolygon[nCnt]->SetAngle(D3DXVECTOR2(0.5f, 1), m_Size);
	}

	return S_OK;
}	//  2Dエフェクトの初期化処理の終了



	//=============================================================================
	//  2Dエフェクトの終了処理
	//=============================================================================
void CPolygonEffect::Uninit(void)
{
	// POLYGON_MAX分回す
	for (int nCnt = 0; nCnt < POLYGON_MAX; nCnt++)
	{
		if (m_pPolygon[nCnt] != NULL)
		{
			m_pPolygon[nCnt]->SetUse(false);
			m_pPolygon[nCnt] = NULL;
		}

	}
	// シーンの解放処理
	CScene::Release();

}// 2Dエフェクトの終了処理の終了


 //=============================================================================
 //  2Dエフェクトの更新処理
 //=============================================================================
void CPolygonEffect::Update(void)
{
	// ポリゴンの回転の更新処理
	m_pPolygon[POLYGON_BACK]->SetRolling(0.02f, D3DX_PI / 2.5, D3DX_PI / 1.5);

	// ポリゴンの拡大縮小の更新処理
	m_pPolygon[POLYGON_BACK]->SetUpdateSize(150, 100);

	// ポリゴンの回転の更新処理
	m_pPolygon[POLYGON_BEFORE]->SetUpdateRoll(0.01f, false);

	// POLYGON_MAX分回す
	for (int nCnt = 0; nCnt < POLYGON_MAX; nCnt++)
	{
		// 回転させるかどうか
		m_pPolygon[nCnt]->SetRoll(true);		
	}
}// 2Dエフェクトの更新処理終了



 //=============================================================================
 // 2Dエフェクトの描画処理
 //=============================================================================
void CPolygonEffect::Draw(void)
{

}	// 2Dエフェクトの描画処理終了

	//=============================================================================
	// 2Dエフェクトの色設定処理
	//=============================================================================
void CPolygonEffect::SetColor(D3DXCOLOR Col, int nNum)
{
	m_pPolygon[nNum]->SetColor(Col);
}

//=============================================================================
// 2Dエフェクトの頂点ごとの色設定処理
//=============================================================================
void CPolygonEffect::SetVtxBuffColor(D3DXCOLOR Col, int nNum, int nVtxBuff)
{
	// 何番目のポリゴンのどこの頂点の色を変えるか
	m_pPolygon[nNum]->SetVtxBuffColor(Col, nVtxBuff);
}

//=============================================================================
// 2Dエフェクトの位置設定処理
//=============================================================================
void CPolygonEffect::SetPos(D3DXVECTOR3 pos)
{
	// POLYGON_MAX分回す
	for (int nCnt = 0; nCnt < POLYGON_MAX; nCnt++)
	{
		// ポリゴンの位置の設定処理を呼び出す
		m_pPolygon[nCnt]->SetPosition(pos);
	}
}