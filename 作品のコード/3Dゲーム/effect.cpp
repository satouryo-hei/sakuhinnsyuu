//=============================================================================
//
// ゲームの選択の処理 [effect.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include"effect.h"
#include"renderer.h"
#include"manager.h"
#include"input.h"
#include"polygon.h"
#include"fade.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
CPolygon *CEffect::m_pPolygon[POLYGON_MAX] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CEffect::CEffect(PRIORITY Priority) :CScene(PRIORITY_EFFECT)
{
	m_bUse = true;
	m_Size = D3DXVECTOR2(100, 50);
	m_Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_nCnt = 0;
}


//=============================================================================
// デストラクタ
//=============================================================================
CEffect::~CEffect()
{

}

//=============================================================================
// ゲームの選択の生成処理
//=============================================================================
CEffect *CEffect::Create(D3DXVECTOR3 pos)
{
	// 背景のポインター生成
	CEffect* pEffect = NULL;

	// 動的メモリの確保
	pEffect = new CEffect;

	// NULLチェック
	if (pEffect != NULL)
	{
		pEffect->Init(pos);
	}
	return pEffect;
}

//=============================================================================
// ゲームの選択の初期化処理
//=============================================================================
HRESULT CEffect::Init(D3DXVECTOR3 pos)
{
	for (int nCnt = 0; nCnt < POLYGON_MAX; nCnt++)
	{
		m_pPolygon[nCnt] = CPolygon::Create(pos, m_Size,10);
		m_pPolygon[nCnt]->SetAngle(D3DXVECTOR2(0.5f, 1), m_Size);
	}

	return S_OK;
}	// ゲームの選択の初期化処理の終了



	//=============================================================================
	// ゲームの選択の終了処理
	//=============================================================================
void CEffect::Uninit(void)
{
	//for (int nCnt = 0; nCnt < POLYGON_MAX; nCnt++)
	//{
	//	if (m_pPolygon[nCnt] != NULL)
	//	{
	//		m_pPolygon[nCnt]->SetUse(false);
	//		m_pPolygon[nCnt] = NULL;
	//	}
	//}
	CScene::Release();

}// ゲームの選択の終了処理の終了


 //=============================================================================
 // ゲームの選択の更新処理
 //=============================================================================
void CEffect::Update(void)
{
	m_pPolygon[0]->SetUpdateRoll(0.02f,true);
	m_pPolygon[0]->SetUpdateSize(150, 100);
	m_pPolygon[1]->SetUpdateRoll(0.01f, false);

	for (int nCnt = 0; nCnt < POLYGON_MAX; nCnt++)
	{
		m_pPolygon[nCnt]->SetRoll(true);
		//m_pPolygon[nCnt]->SetColor(m_Col);
	}
}// ゲームの選択の更新処理終了



 //=============================================================================
 // ゲームの選択の描画処理
 //=============================================================================
void CEffect::Draw(void)
{

}	// ゲームの選択の描画処理終了

void CEffect::SetColor(D3DXCOLOR Col,int nNum)
{
	m_pPolygon[nNum]->SetColor(Col);	
}

void CEffect::Setpos(D3DXVECTOR3 pos)
{
	for (int nCnt = 0; nCnt < POLYGON_MAX; nCnt++)
	{
		m_pPolygon[nCnt]->SetPosition(pos);
	}
}