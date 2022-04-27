//=============================================================================
//
// 着地エフェクトの処理 [landing_effect.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include"landing_effect.h"
#include"renderer.h"
#include"manager.h"
#include"effect.h"

//=============================================================================
// エフェクトのコンストラクタ
//=============================================================================
CLanding_Effect::CLanding_Effect(PRIORITY nPriority) : CBilleffect(nPriority)
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
CLanding_Effect::~CLanding_Effect()
{

}

//=============================================================================
// エフェクトの生成処理
//=============================================================================
CLanding_Effect *CLanding_Effect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, CTexture::Tex type, 
	D3DXVECTOR3 addmove, D3DXVECTOR3 addsize, D3DXCOLOR addcol, int nRadius, int nDensity, int nLife)
{
	//インスタンス生成
	CLanding_Effect *pCircle_Effect = new CLanding_Effect(CScene::PRIORITY_NOMAL);

	if (pCircle_Effect != NULL)
	{
		pCircle_Effect->Init(pos, move, size, col, type,addmove, addsize, addcol, nRadius, nDensity, nLife);
	}

	return pCircle_Effect;
}

//=============================================================================
// エフェクトの初期化処理
//=============================================================================
HRESULT CLanding_Effect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, CTexture::Tex type,
	D3DXVECTOR3 addmove, D3DXVECTOR3 addsize, D3DXCOLOR addcol, int nRadius, int nDensity, int nLife)
{
	CBilleffect::Init(pos, size);
	m_bUse = false;
	SetLanding(pos, move, size, col, type, addmove, addsize, addcol, nRadius, nDensity, nLife);

	return S_OK;
}

//=============================================================================
// エフェクトの終了処理
//=============================================================================
void CLanding_Effect::Uninit(void)
{
	CBilleffect::Uninit();
}

//=============================================================================
// エフェクトの更新処理
//=============================================================================
void CLanding_Effect::Update(void)
{
	if (m_bUse == true)
	{
		Uninit();
	}
}

//=============================================================================
// エフェクトの描画処理
//=============================================================================
void CLanding_Effect::Draw(void)
{
	CBilleffect::Draw();
}

//=============================================================================
// エフェクトの設定処理
//=============================================================================
void CLanding_Effect::SetLanding(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, CTexture::Tex type,
	D3DXVECTOR3 addmove, D3DXVECTOR3 addsize, D3DXCOLOR addcol, int nRadius, int nDensity, int nLife)
{
	if (m_bUse == false)
	{
		for (int nCnt = 0; nCnt < nDensity; nCnt++)
		{
			float fAngle = CIRCLE;			
			CEffect::Create(D3DXVECTOR3((cosf(fAngle)*nRadius) + pos.x, pos.y, (sinf(fAngle)*nRadius) + pos.z),
				D3DXVECTOR3(cosf(fAngle)*move.x, move.y, sinf(fAngle) * move.z), 
				size, col, type, addmove, addsize, addcol, nLife);
			move = Addmove(move, addmove);
		}
	}
}

//=============================================================================
// エフェクトの移動減算処理
//=============================================================================
D3DXVECTOR3 CLanding_Effect::Addmove(D3DXVECTOR3 move, D3DXVECTOR3 addmove)
{
	move -= addmove;

	return move;
}
