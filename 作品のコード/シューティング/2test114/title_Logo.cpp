//=============================================================================
//
// タイトルロゴの処理 [bg.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include"title_logo.h"
#include"renderer.h"
#include"manager.h"
#include"scene2D.h"

// 静的メンバ変数の宣言
LPDIRECT3DTEXTURE9 CTitle_Logo::m_pTexture = NULL;

//=============================================================================
// タイトルロゴのコンストラクタ
//=============================================================================
CTitle_Logo::CTitle_Logo(int nPriority) : CScene(nPriority)
{
	m_apScene2D = NULL;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// タイトルロゴのデストラクタ
//=============================================================================
CTitle_Logo::~CTitle_Logo()
{

}

//=============================================================================
// タイトルロゴの生成処理
//=============================================================================																				
CTitle_Logo *CTitle_Logo::Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	CTitle_Logo* pTitle_Logo;

	pTitle_Logo = new CTitle_Logo(PRIORITY_BG);

	if (pTitle_Logo != NULL)
	{
		pTitle_Logo->Init(pos, Size);
	}
	return pTitle_Logo;
}

//=============================================================================
// テクスチャの読み込み
//=============================================================================
HRESULT CTitle_Logo::Load(void)
{
	CManager *pManager = NULL;

	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/title002.png",
		&m_pTexture);

	return S_OK;
}

//=============================================================================
// テクスチャの破棄
//=============================================================================
void CTitle_Logo::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

}

//=============================================================================
// タイトルロゴの初期化処理
//=============================================================================
HRESULT CTitle_Logo::Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	m_apScene2D = new CScene2D(PRIORITY_BG);

	if (m_apScene2D != NULL)
	{
		m_apScene2D->Init(pos, Size);
		m_apScene2D->BindTextuer(m_pTexture);
	}

	m_pos = pos;
	m_Size = Size;
	return S_OK;
}

//=============================================================================
// タイトルロゴの終了処理
//=============================================================================
void CTitle_Logo::Uninit(void)
{
	//for (int nCntLogo = 0; nCntLogo < 1; nCntLogo++)
	//{
		if (m_apScene2D != NULL)
		{
			m_apScene2D->Uninit();
			m_apScene2D = NULL;
		}
	//}
	Relese();
}

//=============================================================================
// タイトルロゴの更新処理
//=============================================================================
void CTitle_Logo::Update(void)
{
	if (m_pos.y < 320)
	{
		m_pos.y++;
		m_apScene2D->SetPosition(m_pos);
	}
	m_apScene2D->Update();
}

//=============================================================================
// タイトルロゴの描画処理
//=============================================================================
void CTitle_Logo::Draw(void)
{
}