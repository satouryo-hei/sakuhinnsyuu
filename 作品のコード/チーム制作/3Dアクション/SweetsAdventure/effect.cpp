#include "main.h"
#include "effect.h"
#include "manager.h"
#include "renderer.h"
#include <stdio.h>
#include <stdlib.h> // move, smove関数
#include <time.h>   // time関数

CEffect::CEffect(OBJTYPE nPriority) : CBillboard(nPriority)
{
}

CEffect::~CEffect()
{

}

//---------------------------------------------------
//インスタンス生成
//---------------------------------------------------
CEffect * CEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col,float ScaleSpeed,CTexture::Type type)
{//	位置, 移動量, サイズ,色, 小さくなるスピード
	//インスタンス生成
	CEffect *pEffect = new CEffect(OBJTYPE_EFFECT);
	pEffect->m_pos = pos;
	pEffect->m_move = move;
	pEffect->m_size = size;
	pEffect->m_col = col;
	pEffect->m_fScaleSpeed = ScaleSpeed;

	if (pEffect != NULL)
	{
		//画像読み込み
		pEffect->Init(type);
	}

	return pEffect;
}

//----------------------------------------------------
//初期化処理
//-----------------------------------------------------
HRESULT CEffect::Init(CTexture::Type type)
{
	CBillboard::Init(type);
	m_fRand = float(rand() %314/100.0f) - float(rand() % 314 + 314/100.0f);//z軸ランダム移動用
	return S_OK;
}

HRESULT CEffect::Init()
{
	return S_OK;
}

//---------------------------------------------------------
//終了処理
//---------------------------------------------------------
void CEffect::Uninit()
{
	CBillboard::Uninit();
}

void CEffect::Update()
{
	CBillboard::Setpos(m_pos, m_size);//頂点情報の設定
	CBillboard::SetColor(m_col);

	
	//移動処理
	m_pos.x += m_move.x;
	m_pos.y += m_move.y;
	m_pos.z += cosf(m_fRand);

	//フレーム回ルごとにサイズを小さくなる
	m_size.x -= m_fScaleSpeed;
	m_size.y -= m_fScaleSpeed;

	//明るさを下げる
	m_col.a -= 0.01;
	//m_col.g += 0.005;

	//XとYのサイズが0になったら消す
	if (m_size.x <= 0 && m_size.y <=0)
	{
		Uninit();
	}
	//α値が0以下になったら消える
	if (m_col.a <= 0.0)
	{
		Uninit();
	}
}

void CEffect::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//αブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CBillboard::Draw();

	//αブレンディングを通常に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

