//=============================================================================
//
// 爆発のエフェクトの処理 [Explosion_effect.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include "explosion_effect.h"
#include"renderer.h"
#include"manager.h"
#include"effect.h"
#include"input.h"

//=============================================================================
// 爆発のエフェクトのコンストラクタ
//=============================================================================
CExplosion_Effect::CExplosion_Effect(PRIORITY nPriority) : CBilleffect(nPriority)
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
// 爆発のエフェクトのデストラクタ
//=============================================================================
CExplosion_Effect::~CExplosion_Effect()
{

}

//=============================================================================
// 爆発のエフェクトの生成処理
//=============================================================================
CExplosion_Effect *CExplosion_Effect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, CTexture::Tex type,
	D3DXVECTOR3 addmove, D3DXVECTOR3 addsize, D3DXCOLOR addcol, int nDensity, int nLife)
{
	//インスタンス生成
	CExplosion_Effect *pExplosion_Effect = new CExplosion_Effect(CScene::PRIORITY_NOMAL);

	if (pExplosion_Effect != NULL)
	{
		pExplosion_Effect->Init(pos, move, size, col, type, addmove, addsize, addcol, nDensity, nLife);
	}

	return pExplosion_Effect;
}

//=============================================================================
// 爆発のエフェクトの初期化処理
//=============================================================================
HRESULT CExplosion_Effect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, CTexture::Tex type,
	D3DXVECTOR3 addmove, D3DXVECTOR3 addsize, D3DXCOLOR addcol, int nDensity, int nLife)
{
	CBilleffect::Init(pos, size);
	SetExplosion(pos, move, size, col, type, addsize, addmove, addcol, nDensity, nLife);
	m_move = move;
	m_addmove = addmove;
	m_col = col;
	m_addcol = addcol;

	return S_OK;
}

//=============================================================================
// 爆発のエフェクトの終了処理
//=============================================================================
void CExplosion_Effect::Uninit(void)
{
	m_pEffect->Uninit();
	CBilleffect::Uninit();
}

//=============================================================================
// 爆発のエフェクトの更新処理
//=============================================================================
void CExplosion_Effect::Update(void)
{
	//m_move = Addmove(m_move, m_pullmove);

	//m_col = Addcol(m_col, m_pullcol);

	if (m_bUse == true)
	{
		Uninit();
	}
}

//=============================================================================
// 爆発のエフェクトの描画処理
//=============================================================================
void CExplosion_Effect::Draw(void)
{
	CBilleffect::Draw();
}

//=============================================================================
// 爆発のエフェクトの設定処理
//=============================================================================
void CExplosion_Effect::SetExplosion(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, CTexture::Tex type,
	D3DXVECTOR3 addmove, D3DXVECTOR3 addsize, D3DXCOLOR addcol,int nDensity, int nLife)
{
	for (int nCnt = 0; nCnt < nDensity; nCnt++)
	{
		m_pEffect = CEffect::Create(pos, D3DXVECTOR3(CIRCLE*move.x, CIRCLE*move.y, CIRCLE*move.z),
			size, col, type, D3DXVECTOR3(CIRCLE*addmove.x, CIRCLE*addmove.y, CIRCLE*addmove.z), addsize, addcol, nLife);
		//move = Addmove(move, addmove);
	}
}

//=============================================================================
// 爆発のエフェクトの移動減算処理
//=============================================================================
D3DXVECTOR3 CExplosion_Effect::Addmove(D3DXVECTOR3 move, D3DXVECTOR3 addmove)
{
	move -= addmove;

	return move;
}

//=============================================================================
// 爆発のエフェクトの色の減算処理
//=============================================================================
D3DXCOLOR CExplosion_Effect::Addcol(D3DXCOLOR col, D3DXCOLOR addcol)
{
	col -= addcol;

	return col;
}