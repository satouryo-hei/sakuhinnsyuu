//=============================================================================
//
// エフェクトの処理 [Explosion_effect.cpp]
// Author : 佐藤瞭平　
//
//=============================================================================
#include "explosion_effect.h"
#include"renderer.h"
#include"manager.h"
#include"effect_sa.h"
#include"input.h"

//=============================================================================
// エフェクトのコンストラクタ
//=============================================================================
CExplosion_Effect::CExplosion_Effect(CScene::OBJTYPE nPriority) : CBilleffect(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(10.0f, 10.0f, 0.0f);
	m_col = D3DXCOLOR(255, 255, 255, 255);
	m_nLife = 30;
	m_bUse = false;
	nNum = 0;
}

//=============================================================================
// エフェクトのデストラクタ
//=============================================================================
CExplosion_Effect::~CExplosion_Effect()
{

}

//=============================================================================
// エフェクトの生成処理
//=============================================================================
CExplosion_Effect *CExplosion_Effect::Create(D3DXVECTOR3 pos, int nMaxLife, int nMinLife, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, CTexture::Type type, int nDensity, D3DXVECTOR3 addmove)
{
	//インスタンス生成
	CExplosion_Effect *pCircle_Effect = new CExplosion_Effect(CScene::OBJTYPE_EFFECT);

	if (pCircle_Effect != NULL)
	{
		pCircle_Effect->Init(pos, nMaxLife, nMinLife,move, size,col, type, nDensity,addmove);
	}

	return pCircle_Effect;
}

//=============================================================================
// エフェクトの初期化処理
//=============================================================================
HRESULT CExplosion_Effect::Init(D3DXVECTOR3 pos, int nMaxLife, int nMinLife, D3DXVECTOR3 move,D3DXVECTOR3 size, D3DXCOLOR col, CTexture::Type type, int nDensity, D3DXVECTOR3 addmove)
{
	CBilleffect::Init(type);
	SetExplosion(pos,nMaxLife, nMinLife, move,size, col, nDensity, addmove);
	m_bUse = false;

	return S_OK;
}

//=============================================================================
// エフェクトの終了処理
//=============================================================================
void CExplosion_Effect::Uninit(void)
{
	CBilleffect::Uninit();
}

//=============================================================================
// エフェクトの更新処理
//=============================================================================
void CExplosion_Effect::Update(void)
{
	if (m_bUse == true)
	{
		Uninit();
	}
}

//=============================================================================
// エフェクトの描画処理
//=============================================================================
void CExplosion_Effect::Draw(void)
{
	CBilleffect::Draw();
}

//=============================================================================
// エフェクトの設定処理
//=============================================================================
void CExplosion_Effect::SetExplosion(D3DXVECTOR3 pos, int nMaxLife,int nMinLife, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, int nDensity , D3DXVECTOR3 addmove)
{
	if (m_bUse == false)
	{
		for (int nCnt = 0; nCnt < nDensity; nCnt++)
		{
			int nLife = rand() % nMaxLife + nMinLife;
			CEffect_sa::Create(pos, D3DXVECTOR3(CIRCLE*move.x, CIRCLE*move.y, CIRCLE*move.z), size, col, CTexture::Effect, nLife);
			move = Addmove(move, addmove);
		}
		m_bUse = true;
	}
}

//=============================================================================
// エフェクトの移動減算処理
//=============================================================================
D3DXVECTOR3 CExplosion_Effect::Addmove(D3DXVECTOR3 move , D3DXVECTOR3 addmove)
{
	move -= addmove;
  
	return move;
}