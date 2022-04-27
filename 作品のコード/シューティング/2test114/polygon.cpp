//=============================================================================
//
// ポリゴンの処理 [polygon.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include"polygon.h"
#include"manager.h"
#include"renderer.h"
#include"scene2D.h"

// 静的メンバ変数の宣言
LPDIRECT3DTEXTURE9 CPolygon::m_pTexture[SETTEX_MAX] = {};
CPolygon::SETTEX CPolygon::m_SetTex = SETTEX_PLAYER;

//=============================================================================
// ポリゴンのコンストラクタ
//=============================================================================
CPolygon::CPolygon(int nPriority) : CScene(nPriority)
{
	memset(&m_apScene2D[0], NULL, sizeof(m_apScene2D));
	m_Size = D3DXVECTOR2(0.0f, 0.0f);
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
CPolygon *CPolygon::Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size, int SetTex)
{
	CPolygon *pPolygon = NULL;
	pPolygon = new CPolygon;

	if (pPolygon != NULL)
	{
		pPolygon->Init(pos, Size);
		pPolygon->SetTex(SetTex);
	}
	return pPolygon;
}

//=============================================================================
// テクスチャの読み込み
//=============================================================================
HRESULT CPolygon::Load()
{
	CManager *pManager = NULL;

	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/Player000.png",
		&m_pTexture[SETTEX_PLAYER]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/kakeru.png",
		&m_pTexture[SETTEX_KAKERU]);

	return S_OK;
}

//=============================================================================
// テクスチャの破棄
//=============================================================================
void CPolygon::Unload(void)
{
	for (int nCntPlygon = 0; nCntPlygon < SETTEX_MAX; nCntPlygon++)
	{
		if (m_pTexture[nCntPlygon] != NULL)
		{
			m_pTexture[nCntPlygon]->Release();
			m_pTexture[nCntPlygon] = NULL;
		}
	}
}

//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
HRESULT CPolygon::Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	for (int nCntBg = 0; nCntBg < SETTEX_MAX; nCntBg++)
	{
		m_apScene2D[nCntBg] = new CScene2D(PRIORITY_UI);

		if (m_apScene2D[nCntBg] != NULL)
		{
			m_apScene2D[nCntBg]->Init(pos, Size);
			m_apScene2D[nCntBg]->BindTextuer(m_pTexture[nCntBg]);
		}
	}

	m_Size = Size;

	return S_OK;
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CPolygon::Uninit(void)
{
	for (int nCntBg = 0; nCntBg < SETTEX_MAX; nCntBg++)
	{
		if (m_apScene2D[nCntBg] != NULL)
		{
			m_apScene2D[nCntBg]->Uninit();
			m_apScene2D[nCntBg] = NULL;
		}
	}
	Relese();
}

//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CPolygon::Update(void)
{

}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CPolygon::Draw(void)
{
}

//=============================================================================
// テクスチャの配置処理
//=============================================================================
void CPolygon::SetTex(int SetTex)
{
	for (int nCntTex = 0; nCntTex < SETTEX_MAX; nCntTex++)
	{
		switch (SetTex)
		{
		case SETTEX_PLAYER:
			m_apScene2D[nCntTex]->BindTextuer(m_pTexture[SETTEX_PLAYER]);		
			break;

		case SETTEX_KAKERU:
			m_apScene2D[nCntTex]->BindTextuer(m_pTexture[SETTEX_KAKERU]);			
			break;
		default:
			break;
		}
	}
}