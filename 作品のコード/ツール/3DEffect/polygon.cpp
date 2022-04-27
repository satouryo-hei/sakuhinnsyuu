//=============================================================================
//
// ポリゴンの処理 [polygon.h]
// Author : 佐藤瞭平
//
//=============================================================================
#include"polygon.h"
#include"manager.h"
#include"renderer.h"
#include"input.h"

//=============================================================================
// 静的メンバ変数の宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CPolygon::m_pTexture[POLYGON_TYPE_MAX] = {};

//=============================================================================
// ポリゴンのコンストラクタ
//=============================================================================
CPolygon::CPolygon()
{
	m_Size = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Porigon_Type = POLYGON_TYPE_MAX;
	m_pPorigon = NULL;
	m_nNumPorigon = 0;
}


//=============================================================================
// ポリゴンのデストラクタ
//=============================================================================
CPolygon::~CPolygon()
{

}

//=============================================================================
// ポリゴンの生成処理
//=============================================================================
CPolygon *CPolygon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 Size)
{
	CPolygon* pPolygon;

	pPolygon = new CPolygon;

	if (pPolygon != NULL)
	{
		pPolygon->Init(pos, Size);
	}
	return pPolygon;
}

//=============================================================================
// テクスチャの読み込み
//=============================================================================
HRESULT CPolygon::Load(void)
{
	CManager *pManager = NULL;

	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/PlayerAnim002.png",
		&m_pTexture[0]);

	return S_OK;
}

//=============================================================================
// テクスチャの破棄
//=============================================================================
void CPolygon::Unload(void)
{
	for (int nCnt = 0; nCnt < POLYGON_TYPE_MAX; nCnt++)
	{
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}

//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
HRESULT CPolygon::Init(D3DXVECTOR3 pos, D3DXVECTOR3 Size)
{
	CScene2D::Init(pos,Size);

	return S_OK;
}	// ポリゴンの初期化処理終了



	//=============================================================================
	// ポリゴンの終了処理
	//=============================================================================
void CPolygon::Uninit(void)
{
	CScene2D::Uninit();

}// ポリゴンの終了処理終了


 //=============================================================================
 // ポリゴンの更新処理
 //=============================================================================
void CPolygon::Update(void)
{
	//CInputKeyboard *pInputKeyboard;

	//pInputKeyboard = CManager::GetInputKeyboard();


	//if (pInputKeyboard->GetTrigger(DIK_LEFT) == true)//左を押した
	//{
	//	m_nNumPorigon--;
	//	if (m_nNumPorigon < 0)
	//	{
	//		m_nNumPorigon = POLYGON_TYPE_MAX - 1;
	//	}

	//	m_Porigon_Type = (POLYGON_TYPE)m_nNumPorigon;
	//}
	//else if (pInputKeyboard->GetTrigger(DIK_RIGHT) == true)//左を押した
	//{
	//	m_nNumPorigon++;
	//	if (m_nNumPorigon >= POLYGON_TYPE_MAX)
	//	{
	//		m_nNumPorigon = 0;
	//	}

	//	m_Porigon_Type = (POLYGON_TYPE)m_nNumPorigon;
	//}

	//if (pInputKeyboard->GetPress(DIK_RETURN) == true)
	//{
	//	switch (m_Porigon_Type)
	//	{
	//	case POLYGON_TYPE_FIRST:
	//		if (m_pPorigon == NULL)
	//		{
	//			m_pPorigon->Create(D3DXVECTOR3(100.0f, 320.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f));
	//		}
	//		break;

	//	case POLYGON_TYPE_SECOND:
	//		if (m_pPorigon == NULL)
	//		{
	//			m_pPorigon->Create(D3DXVECTOR3(500.0f, 320.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f));;
	//		}
	//		break;

	//	case POLYGON_TYPE_THIRD:
	//		if (m_pPorigon == NULL)
	//		{
	//			m_pPorigon->Create(D3DXVECTOR3(1000.0f, 320.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f));
	//		}
	//		break;

	//	default:
	//		break;
	//	}
	//}
	//if (pInputKeyboard->GetPress(DIK_SPACE) == true)
	//{
	//	if (m_pPorigon != NULL)
	//	{
	//		m_pPorigon->Uninit();
	//		m_pPorigon = NULL;
	//		return;
	//	}
	//}

	CScene2D::Update();

}// ポリゴンの更新処理終了



 //=============================================================================
 // ポリゴンの描画処理
 //=============================================================================
void CPolygon::Draw(void)
{
	CScene2D::Draw();

}	// ポリゴンの描画処理終了