//=============================================================================
//
// パーティクルの処理 [effect.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include "input.h"
#include "particle.h"
#include "camera.h"
#include"scene.h"
#include"manager.h"
#include"renderer.h"
#include"scene.h"

//=============================================================================
// パーティクルのコンストラクタ
//=============================================================================
CParticle::CParticle(PRIORITY nPriority) : CBilleffect(nPriority)
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
// パーティクルのデストラクタ
//=============================================================================
CParticle::~CParticle()
{

}


//=============================================================================
// パーティクルの生成処理
//=============================================================================
CParticle *CParticle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, int type,
	D3DXVECTOR3 addmove, D3DXVECTOR3 addsize, D3DXCOLOR addcol, int nLife)
{
	// パーティクルのポインター生成
	CParticle *pParticle = NULL;

	// 動的メモリの確保
	pParticle = new CParticle;

	// NULLチェック
	if (pParticle != NULL)
	{		
		// パーティクルの初期化処理の呼び出し
		pParticle->Init(pos, move, size, col, type, addmove,addsize, addcol, nLife);
	}

	return pParticle;
}

//=============================================================================
// パーティクルの初期化処理
//=============================================================================
HRESULT CParticle::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, int type,
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
// パーティクルの終了処理
//=============================================================================
void CParticle::Uninit(void)
{
	// 継承元の終了処理を呼び出す
	CBilleffect::Uninit();

	// 死亡フラグを立てるよ
	Release();
}

//=============================================================================
// パーティクルの更新処理
//=============================================================================
void CParticle::Update(void)
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
	// 継承元の更新処理を呼び出す
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
		// 終了処理の呼び出し
		Uninit();
	}
}
		

//=============================================================================
// パーティクルの描画処理
//=============================================================================
void CParticle::Draw(void)
{
	// 継承元の描画処理を呼び出す
	CBilleffect::Draw();
}