//=============================================================================
//
// カットインの処理 [cutin.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include"cutin.h"
#include"renderer.h"
#include"scene2D.h"

// 静的メンバ変数の宣言
LPDIRECT3DTEXTURE9 CCutin::m_pTexture[CUTTYP_MAX] = {};
CCutin::CUTTYP CCutin::m_Cuttyp = CUTTYP_BG;
CCutin::CUTIN CCutin::m_Cutin = CUTIN_NONE;
D3DXVECTOR3 CCutin::m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

//=============================================================================
// カットインのコンストラクタ
//=============================================================================
CCutin::CCutin(int nPriority)
{
	memset(&m_apScene2D[0], 0, sizeof(m_apScene2D));
}

//=============================================================================
// カットインのデストラクタ
//=============================================================================
CCutin::~CCutin()
{

}

//=============================================================================
// カットインの生成処理
//=============================================================================
CCutin *CCutin::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size, CUTTYP CutTyp)
{
	CCutin* pCutin;

	pCutin = new CCutin(PRIORITY_BG);

	if (pCutin != NULL)
	{
		pCutin->Init(pos,Size);
	}
	m_move = move;
	return pCutin;
}

//=============================================================================
// カットインの読み込み
//=============================================================================
HRESULT CCutin::Load(void)
{
	CManager *pManager = NULL;

	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/effect000.jpg",
		&m_pTexture[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/effect000.jpg",
		&m_pTexture[1]);

	return S_OK;
}

//=============================================================================
// カットインの破棄
//=============================================================================
void CCutin::Unload(void)
{
	for (int nCntCutin = 0; nCntCutin < CUTTYP_MAX; nCntCutin++)
	{
		if (m_pTexture[nCntCutin] != NULL)
		{
			m_pTexture[nCntCutin]->Release();
			m_pTexture[nCntCutin] = NULL;
		}
	}
}

//=============================================================================
// カットインの初期化処理
//=============================================================================
HRESULT CCutin::Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	for (int nCntCutin = 0; nCntCutin < CUTTYP_MAX; nCntCutin++)
	{
		m_apScene2D[nCntCutin] = new CScene2D(PRIORITY_UI);

		if (m_apScene2D[nCntCutin] != NULL)
		{
			m_apScene2D[nCntCutin]->Init(pos, Size);
			m_apScene2D[nCntCutin]->BindTextuer(m_pTexture[nCntCutin]);
		}
	}
	return S_OK;
}


//=============================================================================
// カットインの終了処理
//=============================================================================
void CCutin::Uninit(void)
{
	for (int nCntnCntCutin = 0; nCntnCntCutin < CUTTYP_MAX; nCntnCntCutin++)
	{
		if (m_apScene2D[nCntnCntCutin] != NULL)
		{
			m_apScene2D[nCntnCntCutin]->Uninit();
			m_apScene2D[nCntnCntCutin] = NULL;
		}
	}
	Relese();
}


//=============================================================================
// カットインの更新処理
//=============================================================================
void CCutin::Update(void)
{
	switch (m_Cutin)
	{
	case CUTTYP_BG:
		break;
	case CUTTYP_ANIME:
		break;
	default:
		break;
	}
}

//=============================================================================
// カットインの描画処理
//=============================================================================
void CCutin::Draw(void)
{

}