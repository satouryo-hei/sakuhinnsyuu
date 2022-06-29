//=============================================================================
//
//  2Dエフェクトの処理 [effect.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include"explanation.h"
#include"renderer.h"
#include"manager.h"
#include"input.h"
#include"polygon.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
CPolygon *CExplanation::m_pPolygon[EXPLANATION_MAX] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CExplanation::CExplanation(PRIORITY Priority) :CScene(PRIORITY_EFFECT)
{
	m_Size = D3DXVECTOR2(100, 50);
	m_Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}


//=============================================================================
// デストラクタ
//=============================================================================
CExplanation::~CExplanation()
{

}

//=============================================================================
// 2Dエフェクトの生成処理
//=============================================================================
CExplanation *CExplanation::Create(D3DXVECTOR3 pos, int nTex)
{
	// 背景のポインター生成
	CExplanation* pExplanation = NULL;

	// 動的メモリの確保
	pExplanation = new CExplanation;

	// NULLチェック
	if (pExplanation != NULL)
	{
		pExplanation->m_nTex = nTex;
		pExplanation->Init(pos);
	}
	return pExplanation;
}

//=============================================================================
//  2Dエフェクトの初期化処理
//=============================================================================
HRESULT CExplanation::Init(D3DXVECTOR3 pos)
{	
	m_pPolygon[EXPLANATION_SPEECH_BUBBLE] = CPolygon::Create(pos, m_Size, 23);

	for (int nCnt = 1; nCnt < EXPLANATION_MAX; nCnt++)
	{
		m_pPolygon[nCnt] = CPolygon::Create(pos, m_Size, m_nTex+ nCnt);
	}

	return S_OK;
}	//  2Dエフェクトの初期化処理の終了



	//=============================================================================
	//  2Dエフェクトの終了処理
	//=============================================================================
void CExplanation::Uninit(void)
{
	for (int nCnt = 0; nCnt < EXPLANATION_MAX; nCnt++)
	{
		if (m_pPolygon[nCnt] != NULL)
		{
			m_pPolygon[nCnt]->SetUse(false);
			m_pPolygon[nCnt] = NULL;
		}
	}
	CScene::Release();

}// 2Dエフェクトの終了処理の終了


 //=============================================================================
 //  2Dエフェクトの更新処理
 //=============================================================================
void CExplanation::Update(void)
{

}// 2Dエフェクトの更新処理終了



 //=============================================================================
 // 2Dエフェクトの描画処理
 //=============================================================================
void CExplanation::Draw(void)
{

}	// 2Dエフェクトの描画処理終了

	//=============================================================================
	// 2Dエフェクトの大きさ設定処理
	//=============================================================================
void CExplanation::SetSize(D3DXVECTOR2 Size, int nNum)
{
	m_pPolygon[nNum]->SetSize(Size);
}

//=============================================================================
// 2Dエフェクトの色設定処理
//=============================================================================
void CExplanation::SetColor(D3DXCOLOR Col, int nNum)
{
	m_pPolygon[nNum]->SetColor(Col);	
}