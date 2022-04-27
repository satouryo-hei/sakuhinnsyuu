//=============================================================================
//
// エフェクトの処理 [effect_sa.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include "input.h"
#include "effect_sa.h"
#include "camera.h"
#include"scene.h"
#include"manager.h"
#include"renderer.h"
#include"scene.h"

// //静的メンバ変数の宣言
LPDIRECT3DTEXTURE9 m_pTexture = NULL;//テクスチャへのポインタ


//=============================================================================
// エフェクトのコンストラクタ
//=============================================================================
CEffect_sa::CEffect_sa(OBJTYPE nPriority) : CBilleffect(nPriority)
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
CEffect_sa::~CEffect_sa()
{

}


//=============================================================================
// エフェクトの生成処理
//=============================================================================
CEffect_sa *CEffect_sa::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, CTexture::Type type, int nLife)
{
	//インスタンス生成
	CEffect_sa *pEffect_sa = new CEffect_sa(CScene::OBJTYPE_EFFECT);

	if (pEffect_sa != NULL)
	{		
		pEffect_sa->Init(pos, move, size, col, type, nLife);
	}

	return pEffect_sa;
}

//=============================================================================
// エフェクトの初期化処理
//=============================================================================
HRESULT CEffect_sa::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, CTexture::Type type, int nLife)
{
	CBilleffect::Init(type);
	m_pos = pos;
	m_move = move;
	m_size = size;
	m_col = col;
	m_nLife = nLife;
	m_bUse = false;

	return S_OK;
}


//=============================================================================
// エフェクトの終了処理
//=============================================================================
void CEffect_sa::Uninit(void)
{
	CBilleffect::Uninit();
}

//=============================================================================
// エフェクトの更新処理
//=============================================================================
void CEffect_sa::Update(void)
{	
	m_pos += m_move;

	CBilleffect::Setposition(m_pos, m_size);//頂点情報の設定
	CBilleffect::SetColor(m_col);
	CBilleffect::Update();

	m_nLife -= 1;
	if (m_nLife <= 0)
	{
		m_nLife = 0;
		//エフェクトを消す
		m_col.a -= 0.08f;
		if (m_col.a <= 0.0f)
		{
			m_bUse = true;
		}
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
void CEffect_sa::Draw(void)
{
	CBilleffect::Draw();
}

//void SaveEffect(void)
//{
//	FILE *pFile = fopen(SAVEFILENAME, "w");
//
//	if (pFile != NULL)
//	{
//		fprintf(pFile, "#========================================================================\n");
//		fprintf(pFile, "#セットしたエフェクトのステータスをこのテキストファイルに書き出します\n");
//		fprintf(pFile, "#読み込むテキストファイルにコピペするなりして下さい\n");
//		fprintf(pFile, "#========================================================================\n\n\n");
//
//		fprintf(pFile, "EFFECTTYPE\n");
//		fprintf(pFile, "	EFFECTSTATE\n");
//		fprintf(pFile, "		DENSITY = %d\n", g_Effectstate.nDensity);
//		fprintf(pFile, "		TYPE = %d\n", g_Effectstate.SerectType);
//		fprintf(pFile, "		COLOR = %d %d %d %d\n", g_Effectstate.colorR, g_Effectstate.colorG, g_Effectstate.colorB, g_Effectstate.colorA);
//		fprintf(pFile, "		COLORMIN = %d %d %d %d\n", g_Effectstate.MinColorR, g_Effectstate.MinColorG, g_Effectstate.MinColorB, g_Effectstate.MinColorA);
//		fprintf(pFile, "		LIFE = %d\n", g_Effectstate.nLifeSerect);
//		fprintf(pFile, "		SIZE = %.1f %.1f\n", g_Effectstate.fWhidth, g_Effectstate.fHight);
//		fprintf(pFile, "		SIZEMIN = %.1f %.1f\n", g_Effectstate.fMinWhidth, g_Effectstate.fMinHight);
//
//		if (g_Effectstate.SerectType == EFFECTTYPE_CIRCLE)
//		{
//			fprintf(pFile, "		RADIUS = %d\n", g_Effectstate.nRadius);
//		}
//
//		fprintf(pFile, "	EFFECTSTATE_END\n");
//		fprintf(pFile, "EFFECTTYPE_END\n");
//
//	}
//	fclose(pFile);
//}