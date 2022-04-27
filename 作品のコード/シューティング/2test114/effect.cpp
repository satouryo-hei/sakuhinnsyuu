//=============================================================================
//
// エフェクトの処理 [effect.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include"effect.h"
#include"renderer.h"
#include"manager.h"

// 静的メンバ変数の宣言
LPDIRECT3DTEXTURE9 CEffect::m_pTexture = NULL;

//=============================================================================
// エフェクトのコンストラクタ
//=============================================================================
CEffect::CEffect(int nPriority) : CScene2D(nPriority)
{
	m_Size = D3DXVECTOR2(0.0f, 0.0f);
	m_nRed = 255;
	m_nGreen = 255;
	m_nBlue = 255;
	m_nAlpha = 255;
}

//=============================================================================
// エフェクトのデストラクタ
//=============================================================================
CEffect::~CEffect()
{

}

//=============================================================================
// エフェクトの生成処理
//=============================================================================
CEffect *CEffect::Create(D3DXVECTOR3 pos,  D3DXVECTOR2 Size)
{
	CEffect* pEffect;

	pEffect = new CEffect;

	if (pEffect != NULL)
	{
		pEffect->Init(pos, Size);
		pEffect->BindTextuer(m_pTexture);
		pEffect->SetType(CScene::OBJTYPE_PLAYERBULLET);

	}
	return pEffect;
}

//=============================================================================
// テクスチャの読み込み
//=============================================================================
HRESULT CEffect::Load(void)
{
	CManager *pManager = NULL;

	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/effect000.jpg",
		&m_pTexture);

	return S_OK;
}

//=============================================================================
// テクスチャの破棄
//=============================================================================
void CEffect::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// エフェクトの初期化処理
//=============================================================================
HRESULT CEffect::Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	CScene2D::Init(pos, Size);

	m_Size = Size;

	return S_OK;
}	// ポリゴンの初期化処理終了



//=============================================================================
// エフェクトの終了処理
//=============================================================================
void CEffect::Uninit(void)
{
	CScene2D::Uninit();

}// ポリゴンの終了処理終了


//=============================================================================
// エフェクトの更新処理
//=============================================================================
void CEffect::Update(void)
{
	D3DXVECTOR3 pos = GetPosition();

	m_Size.x -= 2.0f;
	m_Size.y -= 2.0f;

	CScene2D::Update();

	m_nAlpha -= 10;

	//m_nGreen = 0;

	//m_nRed = 0;

	SetSize(m_Size);

	SetPosition(pos);

 	SetColor(m_nRed, m_nGreen, m_nBlue, m_nAlpha);

	if (m_nRed < 0)
	{
		m_nRed = 0;
	}
	if (m_nGreen < 0)
	{
		m_nGreen = 0;
	}
	if (m_nBlue < 0)
	{
		m_nBlue = 0;
	}
	if (m_nAlpha < 0)
	{
		m_nAlpha = 0;
	}

	if (m_Size.x <= 0.0f || m_Size.y <= 0.0f)
	{
		m_Size.x = 0.0f;
		m_Size.y = 0.0f;

		Uninit();
		return;
	}

}// ポリゴンの更新処理終了



//=============================================================================
// エフェクトの描画処理
//=============================================================================
void CEffect::Draw(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice = NULL;

	CManager*pManager = NULL;

	pDevice = pManager->GetRenderer()->GetDevice();

	//αブレンディング加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CScene2D::Draw();

	//αブレンディング加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}	// ポリゴンの描画処理終了