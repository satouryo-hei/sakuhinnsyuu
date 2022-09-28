//=============================================================================
//
// エフェクトの処理 [effect.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include"effect.h"
#include"renderer.h"
#include"manager.h"
#include"scene2D.h"

//=============================================================================
// エフェクトのコンストラクタ
//=============================================================================
CEffect::CEffect(int nPriority) : CScene2D(PRIORITY_EFFECT)
{
	m_Size = D3DXVECTOR2(0.0f, 0.0f);
	m_AddSize = D3DXVECTOR2(0.0f, 0.0f);
	m_nRed = 255;
	m_nGreen = 255;
	m_nBlue = 255;
	m_nAlpha = 255;
	m_bUse = true;
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
CEffect *CEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size, D3DXVECTOR2 AddSize, D3DXCOLOR AddCol,int nTex)
{
	CEffect* pEffect;

	pEffect = new CEffect;

	if (pEffect != NULL)
	{
		pEffect->m_AddSize = AddSize;
		pEffect->Init(pos, Size);
		pEffect->Bindtexture(nTex);
		pEffect->m_AddCol = AddCol;
	}
	return pEffect;
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
	//CScene2D::Uninit();
	Release();

}// ポリゴンの終了処理終了


 //=============================================================================
 // エフェクトの更新処理
 //=============================================================================
void CEffect::Update(void)
{
	m_Size.x -= m_AddSize.x;
	m_Size.y -= m_AddSize.y;


	AddColor((int)m_AddCol.r, (int)m_AddCol.g, (int)m_AddCol.b, (int)m_AddCol.a);

	SetSize(m_Size);

	SetRgba(m_nRed, m_nGreen, m_nBlue, m_nAlpha);

	CScene2D::Update();

	if (m_Size.x <= 0.0f || m_Size.y <= 0.0f)
	{
		m_Size.x = 0.0f;
		m_Size.y = 0.0f;

		m_bUse = false;
	}

	if (!m_bUse)
	{
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

//=============================================================================
// エフェクトの色の計算処理
//=============================================================================
void CEffect::AddColor(int nRed, int nGreen, int nBlue, int nAlpha)
{
	m_nRed -= nRed;
	m_nGreen -= nGreen;
	m_nBlue -= nBlue;
	m_nAlpha -= nAlpha;

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

		m_bUse = false;
	}
}