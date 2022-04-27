//=============================================================================
//
// エフェクトの処理 [effect.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include "input.h"
#include "Effect.h"
#include "camera.h"
#include"scene.h"
#include"manager.h"
#include"renderer.h"
#include"scene.h"

//=============================================================================
// 静的メンバ変数の宣言
//=============================================================================
LPDIRECT3DTEXTURE9 m_pTexture = NULL;//テクスチャへのポインタ

//=============================================================================
// エフェクトのコンストラクタ
//=============================================================================
CEffect::CEffect(PRIORITY nPriority) : CBilleffect(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(10.0f, 10.0f, 0.0f);
	m_col = D3DXCOLOR(255, 255, 255, 255);
	m_nLife = 30;
	m_bUse = false;

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
CEffect *CEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, CTexture::Tex type,
	D3DXVECTOR3 addmove, D3DXVECTOR3 addsize, D3DXCOLOR addcol, int nLife)
{
	//インスタンス生成
	CEffect *pEffect = new CEffect(CScene::PRIORITY_NOMAL);

	if (pEffect != NULL)
	{		
		pEffect->Init(pos, move, size, col, type, addmove,addsize, addcol, nLife);
	}

	return pEffect;
}

//=============================================================================
// エフェクトの初期化処理
//=============================================================================
HRESULT CEffect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, CTexture::Tex type,
	D3DXVECTOR3 addmove, D3DXVECTOR3 addsize, D3DXCOLOR addcol, int nLife)
{
	CBilleffect::Init(pos,size);
	CBilleffect::BindTextuer(type);
	m_pos = pos;
	m_move = move;
	m_Addmove = addmove;
	m_size = size;
	m_col = col;
	m_AddSize = addsize;
	m_addcol = addcol;
	m_nLife = nLife;
	m_bUse = false;

	return S_OK;
}


//=============================================================================
// エフェクトの終了処理
//=============================================================================
void CEffect::Uninit(void)
{
	CBilleffect::Uninit();
}

//=============================================================================
// エフェクトの更新処理
//=============================================================================
void CEffect::Update(void)
{	
	m_pos += m_move;

	//m_move -= m_Addmove;

	m_size -= m_AddSize;	

	if (m_size.x < 0)
	{
		m_size.x = 0;
	}
	else if (m_size.y < 0)
	{
		m_size.y = 0;
	}
	else if (m_size.z < 0)
	{
		m_size.z = 0;
	}

	m_col -= m_addcol;

	if (m_col.r < 0)
	{
		m_col.r = 0;
	}
	else if (m_col.g < 0)
	{
		m_col.g = 0;
	}
	else if (m_col.b < 0)
	{
		m_col.b = 0;
	}
	else if (m_col.a < 0)
	{
		m_col.a = 0;
	}

	if (m_col.r > 255)
	{
		m_col.r = 255;
	}
	else if (m_col.g > 255)
	{
		m_col.g = 255;
	}
	else if (m_col.b > 255)
	{
		m_col.b = 255;
	}
	else if (m_col.a > 255)
	{
		m_col.a = 255;
	}

	CBilleffect::Setposition(m_pos, m_size);//頂点情報の設定
	CBilleffect::SetColor(m_col);
	CBilleffect::Update();

	m_nLife -= 1;
	if (m_nLife <= 0)
	{
		m_nLife = 0;
		m_bUse = true;
	}
	else if (m_col <= 0)
	{
		m_col.a = 0;
		m_bUse = true;
	}

	if (m_bUse == true)
	{
		m_bUse = false;
		Uninit();
	}
}
		

//=============================================================================
// エフェクトの描画処理
//=============================================================================
void CEffect::Draw(void)
{
	CBilleffect::Draw();
}