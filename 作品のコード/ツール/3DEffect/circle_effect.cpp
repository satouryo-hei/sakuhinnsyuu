//=============================================================================
//
// 円形のエフェクトの処理 [circle_effect.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include"circle_effect.h"
#include"renderer.h"
#include"manager.h"
#include"effect.h"

//=============================================================================
// 円形のエフェクトのコンストラクタ
//=============================================================================
CCircle_Effect::CCircle_Effect(PRIORITY nPriority) : CBilleffect(nPriority)
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
// 円形のエフェクトのデストラクタ
//=============================================================================
CCircle_Effect::~CCircle_Effect()
{

}

//=============================================================================
// 円形のエフェクトの生成処理
//=============================================================================
CCircle_Effect *CCircle_Effect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, CTexture::Tex type,
	D3DXVECTOR3 addmove, D3DXVECTOR3 addsize, D3DXCOLOR addcol, int nRadius, int nDensity, int nLife)
{
	//インスタンス生成
	CCircle_Effect *pCircle_Effect = new CCircle_Effect(CScene::PRIORITY_NOMAL);

	if (pCircle_Effect != NULL)
	{
		pCircle_Effect->Init(pos, move, size, col, type, addmove, addsize, addcol, nRadius,nDensity, nLife);
	}

	return pCircle_Effect;
}

//=============================================================================
// 円形のエフェクトの初期化処理
//=============================================================================
HRESULT CCircle_Effect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, CTexture::Tex type,
	D3DXVECTOR3 addmove, D3DXVECTOR3 addsize, D3DXCOLOR addcol, int nRadius, int nDensity, int nLife)
{
	CBilleffect::Init(pos, size);
	SetCircle(pos, move, size, col, type, addmove, addsize, addcol,nRadius, nDensity, nLife);

	return S_OK;
}

//=============================================================================
// 円形のエフェクトの終了処理
//=============================================================================
void CCircle_Effect::Uninit(void)
{
	CBilleffect::Uninit();
}

//=============================================================================
// 円形のエフェクトの更新処理
//=============================================================================
void CCircle_Effect::Update(void)
{
	if (m_bUse == true)
	{
		Uninit();
	}
}

//=============================================================================
// 円形のエフェクトの描画処理
//=============================================================================
void CCircle_Effect::Draw(void)
{
	CBilleffect::Draw();
}

//=============================================================================
// 円形のエフェクトの設定処理
//=============================================================================
void CCircle_Effect::SetCircle(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, CTexture::Tex type,
	D3DXVECTOR3 addmove, D3DXVECTOR3 addsize, D3DXCOLOR addcol, int nRadius, int nDensity, int nLife)
{
	for (int nCnt = 0; nCnt < nDensity; nCnt++)
	{
		float fAngle = CIRCLE;
		m_pEffect = CEffect::Create(D3DXVECTOR3(pos.x + (cosf(fAngle)*nRadius), pos.y, pos.z + (sinf(fAngle)*nRadius)),
			move, size, col, type, addmove, addsize, addcol, nLife);
		move = Addmove(move, D3DXVECTOR3(0,0.1f,0));
		//col = Addcol(col, addcol);
	}
}

//=============================================================================
// 円形のエフェクトの移動減算処理
//=============================================================================
D3DXVECTOR3 CCircle_Effect::Addmove(D3DXVECTOR3 move, D3DXVECTOR3 addmove)
{
	move -= addmove;

	return move;
}

//=============================================================================
// 円形のエフェクトの色の減算処理
//=============================================================================
D3DXCOLOR CCircle_Effect::Addcol(D3DXCOLOR col, D3DXCOLOR addcol)
{
	col -= addcol;

	return col;
}