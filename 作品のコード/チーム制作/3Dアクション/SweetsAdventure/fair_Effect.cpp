//=============================================================================
//
// エフェクトの処理 [Explosion_effect.cpp](木くず）
// Author : 藤田育昂
//
//=============================================================================
#include "fair_effect.h"
#include"Renderer.h"
#include"manager.h"
#include"effect.h"
#include "effect_sa.h"
//=============================================================================
// エフェクトのコンストラクタ
//=============================================================================
Cfair_Effect::Cfair_Effect(CScene::OBJTYPE nPriority) : CBilleffect(nPriority)
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
Cfair_Effect::~Cfair_Effect()
{
	
}

Cfair_Effect *Cfair_Effect::Create(D3DXVECTOR3 pos, CTexture::Type type)
{
	//インスタンス生成
	Cfair_Effect *pCircle_Effect = new Cfair_Effect(CScene::OBJTYPE_EFFECT);
	if (pCircle_Effect != NULL)
	{
		pCircle_Effect->Init(pos,type);
	}
	return pCircle_Effect;
}

//=============================================================================
// エフェクトの初期化処理
//=============================================================================
HRESULT Cfair_Effect::Init(D3DXVECTOR3 pos,CTexture::Type type)
{
	CBilleffect::Init(type);
	m_pos = pos;
	m_pos.y += 20.0f;
	m_move = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_size = D3DXVECTOR3(3.0f,3.0f,3.0f);
	m_col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	m_nLife = 50;
	m_bUse = false;
	return S_OK;
}

//=============================================================================
// エフェクトの終了処理
//=============================================================================
void Cfair_Effect::Uninit(void)
{
	CBilleffect::Uninit();
}

//=============================================================================
// エフェクトの更新処理
//=============================================================================
void Cfair_Effect::Update(void)
{
	
	int nCnt = 0;
	float  nRadius = 2.0f;//範囲
	if (m_bUse == false)
	{
		for (nCnt = 0; nCnt < 100; nCnt++)
		{
			m_move = D3DXVECTOR3((cosf(CIRCLE)*nRadius), 0.0f, (sinf(CIRCLE)*nRadius));
			CEffect_sa::Create(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z), m_move, m_size, m_col, CTexture::Effect, m_nLife);
			if (nCnt <= 99)
			{
				m_bUse = true;
			}
		}

	}

	if (m_bUse == true)
	{
		Uninit();
	}

}

//=============================================================================
// エフェクトの描画処理
//=============================================================================
void Cfair_Effect::Draw(void)
{
	CBilleffect::Draw();
}