//=============================================================================
//
// 背景の処理 [bg.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include"bg.h"
#include"renderer.h"
#include"manager.h"
#include"scene2D.h"

// 静的メンバ変数の宣言
LPDIRECT3DTEXTURE9 CBg::m_pTexture[3] = {};

//=============================================================================
// 背景のコンストラクタ
//=============================================================================
CBg::CBg(int nPriority) : CScene(nPriority)
{
	memset(&m_apScene2D[0], NULL, sizeof(m_apScene2D));
	memset(&m_fPosTexU[0], 0, sizeof(m_fPosTexU));
	memset(&m_fPosTexV[0], 0, sizeof(m_fPosTexV));
}

//=============================================================================
// 背景のデストラクタ
//=============================================================================
CBg::~CBg()
{

}

//=============================================================================
// 背景の生成処理
//=============================================================================																				
CBg *CBg::Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	CBg* pBg;

	pBg = new CBg(PRIORITY_BG);

	if (pBg != NULL)
	{
		pBg->Init(pos, Size);
	}
	return pBg;
}

//=============================================================================
// テクスチャの読み込み
//=============================================================================
HRESULT CBg::Load(void)
{
	CManager *pManager = NULL;

	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/woods000.png",
		&m_pTexture[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/woods001.png",
		&m_pTexture[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/forest.png",
		&m_pTexture[2]);


	return S_OK;
}

//=============================================================================
// テクスチャの破棄
//=============================================================================
void CBg::Unload(void)
{

	for (int nCntBg = 0; nCntBg < 3; nCntBg++)
	{
		if (m_pTexture[nCntBg] != NULL)
		{
			m_pTexture[nCntBg]->Release();
			m_pTexture[nCntBg] = NULL;
		}
	}

}

//=============================================================================
// 背景の初期化処理
//=============================================================================
HRESULT CBg::Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{

	for (int nCntBg = 0; nCntBg < 3; nCntBg++)
	{
		m_fPosTexU[nCntBg] = 0.0f;
		m_fPosTexV[nCntBg] = 1.0f;
		m_apScene2D[nCntBg] = new CScene2D(PRIORITY_BG);

		if (m_apScene2D[nCntBg] != NULL)
		{
			m_apScene2D[nCntBg]->Init(pos, Size);
			m_apScene2D[nCntBg]->BindTextuer(m_pTexture[nCntBg]);
		}
	}

	return S_OK;
}

//=============================================================================
// 背景の終了処理
//=============================================================================
void CBg::Uninit(void)
{
	//for (int nCnt = 0; nCnt < 1; nCnt++)
	//{
	for (int nCntBg = 0; nCntBg < 3; nCntBg++)
	{
		if (m_apScene2D[nCntBg] != NULL)
		{
			m_apScene2D[nCntBg]->Uninit();
			m_apScene2D[nCntBg] = NULL;
		}
	}
	//}
	Relese();
}

//=============================================================================
// 背景の更新処理
//=============================================================================
void CBg::Update(void)
{
	m_fPosTexU[2] += 0.001f;
	m_fPosTexU[1] += 0.002f;
	m_fPosTexU[0] += 0.003f;

	for (int nCntBg = 0; nCntBg < 3; nCntBg++)
	{
		if (m_fPosTexV[nCntBg] <= 0.0f)
		{
			m_fPosTexV[nCntBg] += 1.0f;
		}

		if (m_fPosTexU[nCntBg] <= 1.0f)
		{
			m_fPosTexU[nCntBg] -= 0.0f;
		}

		m_apScene2D[nCntBg]->SetTex(m_fPosTexU[nCntBg], 0);
	}

}

//=============================================================================
// 背景の描画処理
//=============================================================================
void CBg::Draw(void)
{
}
