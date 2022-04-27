//=============================================================================
//
// エフェクトの管理型の処理 [effect_manager.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include"effect_manager.h"
#include"renderer.h"
#include"manager.h"
#include"input.h"
#include"effect.h"
#include"straight_effect.h"
#include"circle_effect.h"
#include"explosion_effect.h"
#include"dome_effect.h"
#include"water_crest_effect.h"
#include"smoke_effect.h"
#include"landing_effect.h"

//=============================================================================
// 静的メンバ変数の宣言
//=============================================================================
CStraight_Effect	*	CEffect_Manager::m_pStraight_Effect		= NULL;
CCircle_Effect		*	CEffect_Manager::m_pCircle_Effect		= NULL;
CExplosion_Effect	*	CEffect_Manager::m_pExplosion_Effect	= NULL;
CDome_Effect		*	CEffect_Manager::m_pDome_Effect			= NULL;
CWater_Crest_Effect *	CEffect_Manager::m_pWater_Crest_Effect	= NULL;
CSmoke_Effect		*	CEffect_Manager::m_pSmoke_Effect		= NULL;
CLanding_Effect		*	CEffect_Manager::m_pLanding_Effect		= NULL;


//=============================================================================
// エフェクトのコンストラクタ
//=============================================================================
CEffect_Manager::CEffect_Manager(PRIORITY nPriority) : CBilleffect(nPriority), m_fMaxSize(10), m_fMaxAddSize(1.0f)
{
	m_pos = D3DXVECTOR3(0.0f,0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Addmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_AddSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(255, 255, 255, 255);
	m_AddColor = D3DXCOLOR(0, 0, 0, 0);
	m_nColorType = 0;
	m_bColorTrigger = false;
	m_nLife = 10;
	m_nDensity = 20;
	m_nRadius = 10;
	m_bEffectTrigger = false;
}

//=============================================================================
// エフェクトのデストラクタ
//=============================================================================
CEffect_Manager::~CEffect_Manager()
{

}

//=============================================================================
// エフェクトの生成処理
//=============================================================================
CEffect_Manager *CEffect_Manager::Create(EffectType EffectType)
{
	//インスタンス生成
	CEffect_Manager *pEffect_Manager = new CEffect_Manager(CScene::PRIORITY_NOMAL);

	if (pEffect_Manager != NULL)
	{
		pEffect_Manager->Init(EffectType);
	}

	return pEffect_Manager;
}

//=============================================================================
// エフェクトの初期化処理
//=============================================================================
HRESULT CEffect_Manager::Init(EffectType EffectType)
{
	CBilleffect::Init(m_pos, m_size);
	m_nEffectType = EffectType;

	return S_OK;
}

//=============================================================================
// エフェクトの終了処理
//=============================================================================
void CEffect_Manager::Uninit(void)
{
	CBilleffect::Uninit();
}

//=============================================================================
// エフェクトの更新処理
//=============================================================================
void CEffect_Manager::Update(void)
{
	//-----------------------------------------------------------------------------
	// 色の加減値を押し続けても変更できるようにするか
	//-----------------------------------------------------------------------------
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_1) == true)
	{
		if (m_bColorTrigger)
		{
			m_bColorTrigger = false;
		}
		else if (!m_bColorTrigger)
		{
			m_bColorTrigger = true;
		}
	}

	//-----------------------------------------------------------------------------
	// 位置や大きさ,移動量の加減値を押し続けても変更できるようにするか
	//-----------------------------------------------------------------------------
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_2) == true)
	{
		if (m_bVecTrigger)
		{
			m_bVecTrigger = false;
		}
		else if (!m_bVecTrigger)
		{
			m_bVecTrigger = true;
		}
	}

	//-----------------------------------------------------------------------------
	// 水紋をトリガーにする
	//-----------------------------------------------------------------------------
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_3) == true)
	{
		if (m_bEffectTrigger)
		{
			m_bEffectTrigger = false;
		}
		else if (!m_bEffectTrigger)
		{
			m_bEffectTrigger = true;
		}
	}

	//-----------------------------------------------------------------------------
	// 寿命の変更
	//-----------------------------------------------------------------------------
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_F1) == true)
	{
		m_nLife++;
	}
	else if (CManager::GetInputKeyboard()->GetTrigger(DIK_F2) == true)
	{
		m_nLife--;
	}

	//-----------------------------------------------------------------------------
	// 密度の変更
	//-----------------------------------------------------------------------------
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_F3) == true)
	{
		m_nDensity++;
	}
	else if (CManager::GetInputKeyboard()->GetTrigger(DIK_F4) == true)
	{
		m_nDensity--;
	}

	//-----------------------------------------------------------------------------
	// 半径の変更
	//-----------------------------------------------------------------------------
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_F5) == true)
	{
		m_nRadius++;
	}
	else if (CManager::GetInputKeyboard()->GetTrigger(DIK_F6) == true)
	{
		m_nRadius--;
	}

	//-----------------------------------------------------------------------------
	// エフェクトの変更
	//-----------------------------------------------------------------------------
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_UP) == true)
	{
		m_nEffectType++;
		if (m_nEffectType > EffectType_MAX - 1)
		{
			m_nEffectType = 0;
		}

		Reset();
	}
	else if (CManager::GetInputKeyboard()->GetTrigger(DIK_DOWN) == true)
	{
		m_nEffectType--;
		if (m_nEffectType < 0)
		{
			m_nEffectType = EffectType_MAX - 1;
		}

		Reset();
	}

	//-----------------------------------------------------------------------------
	// 色の変更
	//-----------------------------------------------------------------------------
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_RIGHT) == true)
	{
		m_nColorType++;
		if (m_nColorType > ColorType_MAX - 1)
		{
			m_nColorType = 0;
		}
	}
	else if (CManager::GetInputKeyboard()->GetTrigger(DIK_LEFT) == true)
	{
		m_nColorType--;
		if (m_nColorType < 0)
		{
			m_nColorType = ColorType_MAX - 1;
		}
	}

	//-----------------------------------------------------------------------------
	// 位置や移動量の変更
	//-----------------------------------------------------------------------------
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_T) == true)
	{
		m_nVecType++;
		if (m_nVecType > Vector_MAX - 1)
		{
			m_nVecType = 0;
		}
	}
	else if (CManager::GetInputKeyboard()->GetTrigger(DIK_G) == true)
	{
		m_nVecType--;
		if (m_nVecType < 0)
		{
			m_nVecType = Vector_MAX - 1;
		}
	}

	//-----------------------------------------------------------------------------
	// 大きさの加減値を押し続けても変更
	//-----------------------------------------------------------------------------
	if (m_bVecTrigger)
	{
		//---------------------------------------------------------
		// 大きさの値の増減
		//---------------------------------------------------------
		if (CManager::GetInputKeyboard()->GetTrigger(DIK_Y) == true)
		{
			m_size.x += 0.01f;
			m_size.y += 0.01f;
			m_size.z += 0.01f;
		}
		else if (CManager::GetInputKeyboard()->GetTrigger(DIK_H) == true)
		{
			m_size.x -= 0.01f;
			m_size.y -= 0.01f;
			m_size.z -= 0.01f;
		}

		//---------------------------------------------------------
		// 大きさの減算値の増減
		//---------------------------------------------------------
		if (CManager::GetInputKeyboard()->GetTrigger(DIK_V) == true)
		{
			m_AddSize.x += 0.01f;
			m_AddSize.y += 0.01f;
			m_AddSize.z += 0.01f;
		}
		else if (CManager::GetInputKeyboard()->GetTrigger(DIK_B) == true)
		{
			m_AddSize.x -= 0.01f;
			m_AddSize.y -= 0.01f;
			m_AddSize.z -= 0.01f;
		}
	}
	//-----------------------------------------------------------------------------
	// 大きさの加減値を押し続けても変更できない
	//-----------------------------------------------------------------------------
	else if (!m_bVecTrigger)
	{
		//---------------------------------------------------------
		// 大きさの値の増減
		//---------------------------------------------------------
		if (CManager::GetInputKeyboard()->GetPress(DIK_Y) == true)
		{
			m_size.x += 0.01f;
			m_size.y += 0.01f;
			m_size.z += 0.01f;
		}
		else if (CManager::GetInputKeyboard()->GetPress(DIK_H) == true)
		{
			m_size.x -= 0.01f;
			m_size.y -= 0.01f;
			m_size.z -= 0.01f;
		}

		//---------------------------------------------------------
		// 大きさの減算値の増減
		//---------------------------------------------------------
		if (CManager::GetInputKeyboard()->GetPress(DIK_V) == true)
		{
			m_AddSize.x += 0.01f;
			m_AddSize.y += 0.01f;
			m_AddSize.z += 0.01f;
		}
		else if (CManager::GetInputKeyboard()->GetPress(DIK_B) == true)
		{
			m_AddSize.x -= 0.01f;
			m_AddSize.y -= 0.01f;
			m_AddSize.z -= 0.01f;
		}
	}

	//-----------------------------------------------------------------------------
	// エフェクトの切り替え処理
	//-----------------------------------------------------------------------------
	switch (m_nEffectType)
	{
	case EffectType_NOMAL:
		if (m_pLanding_Effect != NULL)
		{
			delete m_pLanding_Effect;
			m_pLanding_Effect = NULL;
		}
		else if (m_pStraight_Effect != NULL)
		{
			delete m_pStraight_Effect;
			m_pStraight_Effect = NULL;
		}
		break;

	case EffectType_STRAIGHT:
		if (m_pCircle_Effect != NULL)
		{
			delete m_pCircle_Effect;
			m_pCircle_Effect = NULL;
		}
		m_pStraight_Effect = CStraight_Effect::Create(
			m_pos,											// 現在の位置
			m_move,											// 移動量
			m_size,											// 大きさ
			m_col,CTexture::Tex_Effect,						// 色,Texture
			D3DXVECTOR3(0.0f, 0.0f, 0.1f), 					// 計算する移動量
			m_AddSize,										// 計算する大きさ
			m_AddColor, m_nDensity, m_nLife);				// 色の減算値,密度,寿命
		break;

	case EffectType_CIRCLE:
		if (m_pStraight_Effect != NULL)
		{
			delete m_pStraight_Effect;
			m_pStraight_Effect = NULL;
		}
		else if (m_pExplosion_Effect != NULL)
		{
			delete m_pExplosion_Effect;
			m_pExplosion_Effect = NULL;
		}
		m_pCircle_Effect = CCircle_Effect::Create(
			m_pos,											// 現在の位置
			m_move, 										// 移動量
			m_size,											// 大きさ
			m_col, CTexture::Tex_Effect,					// 色,Texture
			D3DXVECTOR3(0.0f, 0.05f, 0.0f),					// 計算する移動量
			m_AddSize,										// 計算する大きさ
			m_AddColor, m_nRadius, m_nDensity, m_nLife);	// 色の減算値,半径,密度,寿命
		break;

	case EffectType_EXPLOSIN:
		if (m_pCircle_Effect != NULL)
		{
			delete m_pCircle_Effect;
			m_pCircle_Effect = NULL;
		}
		else if (m_pDome_Effect != NULL)
		{
			delete m_pDome_Effect;
			m_pDome_Effect = NULL;
		}
		m_pExplosion_Effect = CExplosion_Effect::Create(
			m_pos,											// 現在の位置
			m_move,											// 移動量
			m_size,											// 大きさ
			m_col, CTexture::Tex_Effect,					// 色,Texture
			D3DXVECTOR3(0.05f, 0.05f, 0.05f), 				// 計算する移動量
			m_AddSize,										// 計算する大きさ
			m_AddColor, m_nDensity, m_nLife);				// 色の減算値,密度,寿命
		break;
		
	case EffectType_DOME:
		if (m_pExplosion_Effect != NULL)
		{
			delete m_pExplosion_Effect;
			m_pExplosion_Effect = NULL;
		}
		else if (m_pWater_Crest_Effect != NULL)
		{
			delete m_pWater_Crest_Effect;
			m_pWater_Crest_Effect = NULL;
		}
		m_pDome_Effect = CDome_Effect::Create(
			m_pos,											// 現在の位置
			m_move,											// 移動量
			m_size,											// 大きさ
			m_col, CTexture::Tex_Effect, 					// 色,Texture
			D3DXVECTOR3(0.0f, 0.1f, 0.0f), 					// 計算する移動量
			m_AddSize,										// 計算する大きさ
			m_AddColor, m_nRadius, m_nDensity, m_nLife);	// 色の減算値,半径,密度,寿命
		break;
		
	case EffectType_WATER_CREST:
		if (m_pDome_Effect != NULL)
		{
			delete m_pDome_Effect;
			m_pDome_Effect = NULL;
		}
		else if (m_pSmoke_Effect != NULL)
		{
			delete m_pSmoke_Effect;
			m_pSmoke_Effect = NULL;
		}
		if (m_bEffectTrigger)
		{
			if (CManager::GetInputKeyboard()->GetTrigger(DIK_4) == true)
			{
				m_pWater_Crest_Effect = CWater_Crest_Effect::Create(
					m_pos,											// 現在の位置			
					m_move,											// 移動量
					m_size,											// 大きさ
					m_col, CTexture::Tex_Effect,					// 色,Texture
					D3DXVECTOR3(0.2f, 0.0f, 0.2f), 					// 計算する移動量
					m_AddSize,						 				// 計算する大きさ
					m_AddColor, m_nRadius, m_nDensity, m_nLife);	// 色の減算値,半径,密度,寿命
			}
		}
		else if (!m_bEffectTrigger)
		{
			m_pWater_Crest_Effect = CWater_Crest_Effect::Create(
				m_pos,											// 現在の位置			
				m_move,											// 移動量
				m_size,											// 大きさ
				m_col, CTexture::Tex_Effect,					// 色,Texture
				D3DXVECTOR3(0.2f, 0.0f, 0.2f), 					// 計算する移動量
				m_AddSize,						 				// 計算する大きさ
				m_AddColor, m_nRadius, m_nDensity, m_nLife);	// 色の減算値,半径,密度,寿命
		}
		break;

	case EffectType_SMOKE:
		if (m_pWater_Crest_Effect != NULL)
		{
			delete m_pWater_Crest_Effect;
			m_pWater_Crest_Effect = NULL;
		}
		else if (m_pLanding_Effect != NULL)
		{
			delete m_pLanding_Effect;
			m_pLanding_Effect = NULL;
		}
		m_pSmoke_Effect = CSmoke_Effect::Create(
			m_pos,											// 現在の位置
			1.0f,											// 回転値
			m_move,											// 移動量
			m_size,											// 大きさ
			m_col, CTexture::Tex_Effect,					// 色,Texture
			D3DXVECTOR3(0.2f, 0.0f, 0.2f), 					// 計算する移動量
			m_AddSize,										// 計算する大きさ
			m_AddColor, m_nRadius, m_nDensity, m_nLife);	// 色の減算値,半径,密度,寿命

		break;

	case EffectType_LANDING:
		if (m_pSmoke_Effect != NULL)
		{
			delete m_pSmoke_Effect;
			m_pSmoke_Effect = NULL;
		}
		m_pLanding_Effect = CLanding_Effect::Create(
			m_pos,											// 現在の位置
			m_move,											// 移動量
			m_size,											// 大きさ
			m_col, CTexture::Tex_Effect,					// 色,Texture
			D3DXVECTOR3(0.2f, 0.0f, 0.2f), 					// 計算する移動量
			m_AddSize, 										// 計算する大きさ
			m_AddColor, m_nRadius, m_nDensity, m_nLife);	// 色の減算値,半径,密度,寿命
		break;
	default:
		break;
	}

	//-----------------------------------------------------------------------------
	// 色の切り替え処理
	//-----------------------------------------------------------------------------
	switch (m_nColorType)
	{
	case ColorType_RED:
		if (m_bColorTrigger)
		{
			//---------------------------------------------------------
			// 色の値の増減
			//---------------------------------------------------------
			if (CManager::GetInputKeyboard()->GetTrigger(DIK_I) == true)
			{
				m_col.r += 0.01f;
			}
			else if (CManager::GetInputKeyboard()->GetTrigger(DIK_K) == true)
			{
				m_col.r -= 0.01f;
			}

			//---------------------------------------------------------
			// 色の減算値の増減
			//---------------------------------------------------------
			if (CManager::GetInputKeyboard()->GetTrigger(DIK_U) == true)
			{
				m_AddColor.r += 0.01f;
			}
			else if (CManager::GetInputKeyboard()->GetTrigger(DIK_J) == true)
			{
				m_AddColor.r -= 0.01f;
			}			
		}
		else if (!m_bColorTrigger)
		{
			//---------------------------------------------------------
			// 色の値の増減
			//---------------------------------------------------------
			if (CManager::GetInputKeyboard()->GetPress(DIK_I) == true)
			{
				m_col.r += 0.01f;
			}
			else if (CManager::GetInputKeyboard()->GetPress(DIK_K) == true)
			{
				m_col.r -= 0.01f;
			}

			//---------------------------------------------------------
			// 色の減算値の増減
			//---------------------------------------------------------
			if (CManager::GetInputKeyboard()->GetPress(DIK_U) == true)
			{
				m_AddColor.r += 0.01f;
			}
			else if (CManager::GetInputKeyboard()->GetPress(DIK_J) == true)
			{
				m_AddColor.r -= 0.01f;
			}
		}
		break;

	case ColorType_GREEN:
		if (m_bColorTrigger)
		{
			//---------------------------------------------------------
			// 色の値の増減
			//---------------------------------------------------------
			if (CManager::GetInputKeyboard()->GetTrigger(DIK_I) == true)
			{
				m_col.g += 0.01f;
			}
			else if (CManager::GetInputKeyboard()->GetTrigger(DIK_K) == true)
			{
				m_col.g -= 0.01f;
			}

			//---------------------------------------------------------
			// 色の減算値の増減
			//---------------------------------------------------------
			if (CManager::GetInputKeyboard()->GetTrigger(DIK_U) == true)
			{
				m_AddColor.g += 0.01f;
			}
			else if (CManager::GetInputKeyboard()->GetTrigger(DIK_J) == true)
			{
				m_AddColor.g -= 0.01f;
			}
		}
		else if (!m_bColorTrigger)
		{
			//---------------------------------------------------------
			// 色の値の増減
			//---------------------------------------------------------
			if (CManager::GetInputKeyboard()->GetPress(DIK_I) == true)
			{
				m_col.g += 0.01f;
			}
			else if (CManager::GetInputKeyboard()->GetPress(DIK_K) == true)
			{
				m_col.g -= 0.01f;
			}

			//---------------------------------------------------------
			// 色の減算値の増減
			//---------------------------------------------------------
			if (CManager::GetInputKeyboard()->GetPress(DIK_U) == true)
			{
				m_AddColor.g += 0.01f;
			}
			else if (CManager::GetInputKeyboard()->GetPress(DIK_J) == true)
			{
				m_AddColor.g -= 0.01f;
			}
		}
		break;

	case ColorType_BLUE:
		if (m_bColorTrigger)
		{
			//---------------------------------------------------------
			// 色の値の増減
			//---------------------------------------------------------
			if (CManager::GetInputKeyboard()->GetTrigger(DIK_I) == true)
			{
				m_col.b += 0.01f;
			}
			else if (CManager::GetInputKeyboard()->GetTrigger(DIK_K) == true)
			{
				m_col.b -= 0.01f;
			}

			//---------------------------------------------------------
			// 色の減算値の増減
			//---------------------------------------------------------
			if (CManager::GetInputKeyboard()->GetTrigger(DIK_U) == true)
			{
				m_AddColor.b += 0.01f;
			}
			else if (CManager::GetInputKeyboard()->GetTrigger(DIK_J) == true)
			{
				m_AddColor.b -= 0.01f;
			}
		}
		else if (!m_bColorTrigger)
		{
			//---------------------------------------------------------
			// 色の値の増減
			//---------------------------------------------------------
			if (CManager::GetInputKeyboard()->GetPress(DIK_I) == true)
			{
				m_col.b += 0.01f;
			}
			else if (CManager::GetInputKeyboard()->GetPress(DIK_K) == true)
			{
				m_col.b -= 0.01f;
			}

			//---------------------------------------------------------
			// 色の減算値の増減
			//---------------------------------------------------------
			if (CManager::GetInputKeyboard()->GetPress(DIK_U) == true)
			{
				m_AddColor.b += 0.01f;
			}
			else if (CManager::GetInputKeyboard()->GetPress(DIK_J) == true)
			{
				m_AddColor.b -= 0.01f;
			}
		}
		break;

	case ColorType_ARUFA:
		if (m_bColorTrigger)
		{
			//---------------------------------------------------------
			// 色の値の増減
			//---------------------------------------------------------
			if (CManager::GetInputKeyboard()->GetTrigger(DIK_I) == true)
			{
				m_col.a += 0.01f;
			}
			else if (CManager::GetInputKeyboard()->GetTrigger(DIK_K) == true)
			{
				m_col.a -= 0.01f;
			}

			//---------------------------------------------------------
			// 色の減算値の増減
			//---------------------------------------------------------
			if (CManager::GetInputKeyboard()->GetTrigger(DIK_U) == true)
			{
				m_AddColor.a += 0.01f;
			}
			else if (CManager::GetInputKeyboard()->GetTrigger(DIK_J) == true)
			{
				m_AddColor.a -= 0.01f;
			}
		}
		else if (!m_bColorTrigger)
		{
			//---------------------------------------------------------
			// 色の値の増減
			//---------------------------------------------------------
			if (CManager::GetInputKeyboard()->GetPress(DIK_I) == true)
			{
				m_col.a += 0.01f;
			}
			else if (CManager::GetInputKeyboard()->GetPress(DIK_K) == true)
			{
				m_col.a -= 0.01f;
			}

			//---------------------------------------------------------
			// 色の減算値の増減
			//---------------------------------------------------------
			if (CManager::GetInputKeyboard()->GetPress(DIK_U) == true)
			{
				m_AddColor.a += 0.01f;
			}
			else if (CManager::GetInputKeyboard()->GetPress(DIK_J) == true)
			{
				m_AddColor.a -= 0.01f;
			}
		}
		break;

	default:
		break;
	}

	//-----------------------------------------------------------------------------
	// 位置や移動量の切り替え処理
	//-----------------------------------------------------------------------------
	switch (m_nVecType)
	{
	case Vector_X:
		if (m_bVecTrigger)
		{			
			//---------------------------------------------------------
			// 位置の値の増減
			//---------------------------------------------------------
			if (CManager::GetInputKeyboard()->GetTrigger(DIK_X) == true)
			{
				m_pos.x += 0.01f;
			}
			else if (CManager::GetInputKeyboard()->GetTrigger(DIK_P) == true)
			{
				m_pos.x -= 0.01f;
			}

			//---------------------------------------------------------
			// 位置の値の増減
			//---------------------------------------------------------
			if (CManager::GetInputKeyboard()->GetTrigger(DIK_O) == true)
			{
				m_move.x += 0.01f;
			}
			else if (CManager::GetInputKeyboard()->GetTrigger(DIK_L) == true)
			{
				m_move.x -= 0.01f;
			}

			//---------------------------------------------------------
			// 移動量の値の増減
			//---------------------------------------------------------
			if (CManager::GetInputKeyboard()->GetTrigger(DIK_N) == true)
			{
				m_Addmove.x += 0.01f;
			}
			else if (CManager::GetInputKeyboard()->GetTrigger(DIK_M) == true)
			{
				m_Addmove.x -= 0.01f;
			}
		}
		else if (!m_bVecTrigger)
		{
			//---------------------------------------------------------
			// 位置の値の増減
			//---------------------------------------------------------
			if (CManager::GetInputKeyboard()->GetPress(DIK_X) == true)
			{
				m_pos.x += 0.01f;
			}
			else if (CManager::GetInputKeyboard()->GetPress(DIK_P) == true)
			{
				m_pos.x -= 0.01f;
			}

			//---------------------------------------------------------
			// 位置の値の増減
			//---------------------------------------------------------
			if (CManager::GetInputKeyboard()->GetPress(DIK_O) == true)
			{
				m_move.x += 0.01f;
			}
			else if (CManager::GetInputKeyboard()->GetPress(DIK_L) == true)
			{
				m_move.x -= 0.01f;
			}

			//---------------------------------------------------------
			// 移動量の値の増減
			//---------------------------------------------------------
			if (CManager::GetInputKeyboard()->GetPress(DIK_N) == true)
			{
				m_Addmove.x += 0.01f;
			}
			else if (CManager::GetInputKeyboard()->GetPress(DIK_M) == true)
			{
				m_Addmove.x -= 0.01f;
			}			
		}
		break;

	case Vector_Y:
		if (m_bVecTrigger)
		{
			//---------------------------------------------------------
			// 位置の値の増減
			//---------------------------------------------------------
			if (CManager::GetInputKeyboard()->GetTrigger(DIK_X) == true)
			{
				m_pos.y += 0.01f;
			}
			else if (CManager::GetInputKeyboard()->GetTrigger(DIK_P) == true)
			{
				m_pos.y -= 0.01f;
			}

			//---------------------------------------------------------
			// 位置の値の増減
			//---------------------------------------------------------
			if (CManager::GetInputKeyboard()->GetTrigger(DIK_O) == true)
			{
				m_move.y += 0.01f;
			}
			else if (CManager::GetInputKeyboard()->GetTrigger(DIK_L) == true)
			{
				m_move.y -= 0.01f;
			}

			//---------------------------------------------------------
			// 移動量の値の増減
			//---------------------------------------------------------
			if (CManager::GetInputKeyboard()->GetTrigger(DIK_N) == true)
			{
				m_Addmove.y += 0.01f;
			}
			else if (CManager::GetInputKeyboard()->GetTrigger(DIK_M) == true)
			{
				m_Addmove.y -= 0.01f;
			}
		}
		else if (!m_bVecTrigger)
		{
			//---------------------------------------------------------
			// 位置の値の増減
			//---------------------------------------------------------
			if (CManager::GetInputKeyboard()->GetPress(DIK_X) == true)
			{
				m_pos.y += 0.01f;
			}
			else if (CManager::GetInputKeyboard()->GetPress(DIK_P) == true)
			{
				m_pos.y -= 0.01f;
			}

			//---------------------------------------------------------
			// 位置の値の増減
			//---------------------------------------------------------
			if (CManager::GetInputKeyboard()->GetPress(DIK_O) == true)
			{
				m_move.y += 0.01f;
			}
			else if (CManager::GetInputKeyboard()->GetPress(DIK_L) == true)
			{
				m_move.y -= 0.01f;
			}

			//---------------------------------------------------------
			// 移動量の値の増減
			//---------------------------------------------------------
			if (CManager::GetInputKeyboard()->GetPress(DIK_N) == true)
			{
				m_Addmove.y += 0.01f;
			}
			else if (CManager::GetInputKeyboard()->GetPress(DIK_M) == true)
			{
				m_Addmove.y -= 0.01f;
			}
		}
		break;

	case Vector_Z:
		if (m_bVecTrigger)
		{
			//---------------------------------------------------------
			// 位置の値の増減
			//---------------------------------------------------------
			if (CManager::GetInputKeyboard()->GetTrigger(DIK_X) == true)
			{
				m_pos.z += 0.01f;
			}
			else if (CManager::GetInputKeyboard()->GetTrigger(DIK_P) == true)
			{
				m_pos.z -= 0.01f;
			}

			//---------------------------------------------------------
			// 位置の値の増減
			//---------------------------------------------------------
			if (CManager::GetInputKeyboard()->GetTrigger(DIK_O) == true)
			{
				m_move.z += 0.01f;
			}
			else if (CManager::GetInputKeyboard()->GetTrigger(DIK_L) == true)
			{
				m_move.z -= 0.01f;
			}

			//---------------------------------------------------------
			// 移動量の値の増減
			//---------------------------------------------------------
			if (CManager::GetInputKeyboard()->GetTrigger(DIK_N) == true)
			{
				m_Addmove.z += 0.01f;
			}
			else if (CManager::GetInputKeyboard()->GetTrigger(DIK_M) == true)
			{
				m_Addmove.z -= 0.01f;
			}
		}
		else if (!m_bVecTrigger)
		{
			//---------------------------------------------------------
			// 位置の値の増減
			//---------------------------------------------------------
			if (CManager::GetInputKeyboard()->GetPress(DIK_X) == true)
			{
				m_pos.z += 0.01f;
			}
			else if (CManager::GetInputKeyboard()->GetPress(DIK_P) == true)
			{
				m_pos.z -= 0.01f;
			}

			//---------------------------------------------------------
			// 位置の値の増減
			//---------------------------------------------------------
			if (CManager::GetInputKeyboard()->GetPress(DIK_O) == true)
			{
				m_move.z += 0.01f;
			}
			else if (CManager::GetInputKeyboard()->GetPress(DIK_L) == true)
			{
				m_move.z -= 0.01f;
			}

			//---------------------------------------------------------
			// 移動量の値の増減
			//---------------------------------------------------------
			if (CManager::GetInputKeyboard()->GetPress(DIK_N) == true)
			{
				m_Addmove.z += 0.01f;
			}
			else if (CManager::GetInputKeyboard()->GetPress(DIK_M) == true)
			{
				m_Addmove.z -= 0.01f;
			}
		}
		break;

	default:
		break;
	}

	//-----------------------------------------------------------------------------
	// 色が最小値になったら
	//-----------------------------------------------------------------------------
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

	//-----------------------------------------------------------------------------
	// 色が最大値になったら
	//-----------------------------------------------------------------------------
	if (m_col.r > 1.0f)
	{
		m_col.r = 1.0f;
	}
	else if (m_col.g > 1.0f)
	{
		m_col.g = 1.0f;
	}
	else if (m_col.b > 1.0f)
	{
		m_col.b = 1.0f;
	}
	else if (m_col.a > 1.0f)
	{
		m_col.a = 1.0f;
	}

	//-----------------------------------------------------------------------------
	// 色の加減値が最小値になったら
	//-----------------------------------------------------------------------------
	if (m_AddColor.r < 0)
	{
		m_AddColor.r = 0;
	}
	else if (m_AddColor.g < 0)
	{
		m_AddColor.g = 0;
	}
	else if (m_AddColor.b < 0)
	{
		m_AddColor.b = 0;
	}
	else if (m_AddColor.a < 0)
	{
		m_AddColor.a = 0;
	}

	//-----------------------------------------------------------------------------
	// 色の加減値が最大値になったら
	//-----------------------------------------------------------------------------
	if (m_AddColor.r > 1.0f)
	{
		m_AddColor.r = 1.0f;
	}
	else if (m_AddColor.g > 1.0f)
	{
		m_AddColor.g = 1.0f;
	}
	else if (m_AddColor.b > 1.0f)
	{
		m_AddColor.b = 1.0f;
	}
	else if (m_AddColor.a > 1.0f)
	{
		m_AddColor.a = 1.0f;
	}

	//-----------------------------------------------------------------------------
	// 大きさが最小値になったら
	//-----------------------------------------------------------------------------
	if (m_size.x < 0.0f &&m_size.y < 0.0f&&m_size.z < 0.0f)
	{
		m_size.x = 0;
		m_size.y = 0;
		m_size.z = 0;
	}

	//-----------------------------------------------------------------------------
	// 大きさが最大値になったら
	//-----------------------------------------------------------------------------
	if (m_size.x > m_fMaxSize &&m_size.y > m_fMaxSize &&m_size.z > m_fMaxSize)
	{
		m_size.x = m_fMaxSize;
		m_size.y = m_fMaxSize;
		m_size.z = m_fMaxSize;
	}

	//-----------------------------------------------------------------------------
	// 大きさの加減値が最小値になったら
	//-----------------------------------------------------------------------------
	if (m_AddSize.x < 0.0f &&m_AddSize.y < 0.0f&&m_AddSize.z < 0.0f)
	{
		m_AddSize.x = 0;
		m_AddSize.y = 0;
		m_AddSize.z = 0;
	}

	//-----------------------------------------------------------------------------
	// 大きさの加減値が最大値になったら
	//-----------------------------------------------------------------------------
	if (m_AddSize.x > m_fMaxAddSize && m_AddSize.y > m_fMaxAddSize && m_AddSize.z > m_fMaxAddSize)
	{
		m_AddSize.x = m_fMaxAddSize;
		m_AddSize.y = m_fMaxAddSize;
		m_AddSize.z = m_fMaxAddSize;
	}

	//-----------------------------------------------------------------------------
	// 書き込み処理
	//-----------------------------------------------------------------------------
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_F9) == true)
	{
		Save();
	}

	//-----------------------------------------------------------------------------
	// 読み込み処理
	//-----------------------------------------------------------------------------
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_F8) == true)
	{
		Lode();
	}
}

//=============================================================================
// エフェクトの描画処理
//=============================================================================
void CEffect_Manager::Draw(void)
{
	CBilleffect::Draw();
}


//=============================================================================
// エフェクトを切り替るときにリセットする
//=============================================================================
void CEffect_Manager::Reset(void)
{
	//-----------------------------------------------------------------------------
	// 色のリセット
	//-----------------------------------------------------------------------------
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_AddColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

	//-----------------------------------------------------------------------------
	// それぞれのエフェクトの種類の初期化
	//-----------------------------------------------------------------------------
	switch (m_nEffectType)
	{
	case EffectType_NOMAL:
		m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_nLife = 0;
		m_nDensity = 0;
		m_nRadius = 0;
		break;

	case EffectType_STRAIGHT:
		m_pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
		m_move = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		m_size = D3DXVECTOR3(1.5f, 1.5f, 1.5f);
		m_nLife = 20;
		m_nDensity = 10;
		m_nRadius = 0;
		break;

	case EffectType_CIRCLE:
		m_pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
		m_move = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		m_size = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		m_nLife = 15;
		m_nDensity = 10;
		m_nRadius = 10;
		break;

	case EffectType_EXPLOSIN:
		m_pos = D3DXVECTOR3(0.0f, 60.0f, 0.0f);
		m_move = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		m_size = D3DXVECTOR3(2.0f, 2.0f, 2.0f);
		m_nLife = 10;
		m_nDensity = 20;
		m_nRadius = 0;
		break;

	case EffectType_DOME:
		m_pos = D3DXVECTOR3(0.0f, 100.0f, 0.0f);
		m_move = D3DXVECTOR3(0.0f, -6.0f, 0.0f);
		m_size = D3DXVECTOR3(1.5f, 1.5f, 1.5f);
		m_nLife = 10;
		m_nDensity = 10;
		m_nRadius = 10;
		break;

	case EffectType_WATER_CREST:
		m_pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
		m_move = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		m_size = D3DXVECTOR3(2.0f, 2.0f, 2.0f);
		m_nLife = 5;
		m_nDensity = 20;
		m_nRadius = 5;
		break;

	case EffectType_SMOKE:
		m_pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
		m_move = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		m_size = D3DXVECTOR3(1.5f, 1.5f, 1.5f);
		m_nLife = 10;
		m_nDensity = 5;
		m_nRadius = 20;
		break;

	case EffectType_LANDING:
		m_pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
		m_move = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		m_size = D3DXVECTOR3(1.5f, 1.5f, 1.5f);
		m_nLife = 10;
		m_nDensity = 5;
		m_nRadius = 20;
		break;

	default:
		break;
	}
}

//=============================================================================
// 書き込み処理
//=============================================================================
void CEffect_Manager::Save(void)
{
	// 開け～ファイル！
	FILE *pFile = fopen(EFFECTTEXT, "w");

	// ファイルがあったら
	if (pFile != NULL)
	{
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "# エフェクトファイル[3DEffect.txt]\n");
		fprintf(pFile, "# Author : 佐藤瞭平\n");
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "# セットしたエフェクトをこのテキストファイルに書き出します\n");
		fprintf(pFile, "# EFFECT情報\n");
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "SCRIPT\t\t# この行は絶対消さないこと！\n");
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "# 読み込むエフェクトの種類\n");
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "TYPE = %d\n", m_nEffectType);
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "# 表示するエフェクトの配置情報\n");
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "SET3DEFFECT\n");
		fprintf(pFile, "\tPOS = %.2f %.2f %.2f\n", m_pos.x, m_pos.y, m_pos.z);
		fprintf(pFile, "\tMOVE = %.2f %.2f %.2f\n", m_move.x, m_move.y, m_move.z);
		fprintf(pFile, "\tSIZE = %.2f %.2f %.2f\n", m_size.x, m_size.y, m_size.z);
		fprintf(pFile, "\tADDSIZE = %.2f %.2f %.2f\n", m_AddSize.x, m_AddSize.y, m_AddSize.z);
		fprintf(pFile, "\tCOLOR = %.2f %.2f %.2f %.2f\n", m_col.r, m_col.g, m_col.b, m_col.a);
		fprintf(pFile, "\tADDCOLOR = %.2f %.2f %.2f %.2f\n", m_AddColor.r, m_AddColor.g, m_AddColor.b, m_AddColor.a);
		fprintf(pFile, "\tLIFE = %d\n", m_nLife);
		fprintf(pFile, "\tDENSDITY = %d\n", m_nDensity);
		fprintf(pFile, "\tRADIUS = %d\n", m_nRadius);
		fprintf(pFile, "END_3DEFFECT\n\n");
		fprintf(pFile, "END_SCRIPT\t\t# この行は絶対消さないこと！\n");
	}
	else
	{
		printf("ファイルが読み込まれませんでした。");
	}
	// 閉じれ～ファイル！
	fclose(pFile);
}

//=============================================================================
// エフェクトの読み込み処理
//=============================================================================
void CEffect_Manager::Lode(void)
{
	CManager * pManager = NULL;
	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();

	char aFile[256];
	int nType;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXVECTOR3 size;
	D3DXVECTOR3 addsize;
	D3DXCOLOR col;
	D3DXCOLOR addcol;

	FILE *pFile = fopen(EFFECTTEXT, "r");

	if (pFile != NULL)//一度ファイルを読み込んで必要な情報を抜く
	{
		while (true)
		{
			fscanf(pFile, "%s", &aFile[0]);

			if (strcmp(&aFile[0], "TYPE") == 0) //END_SCRIPTの文字列を見つけたら
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &nType);
			}
			if (strcmp(&aFile[0], "POS") == 0) //END_SCRIPTの文字列を見つけたら
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%f%f%f", &pos.x, &pos.y,&pos.z);
			}
			if (strcmp(&aFile[0], "MOVE") == 0) //END_SCRIPTの文字列を見つけたら
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%f%f%f", &move.x, &move.y, &move.z);
			}
			if (strcmp(&aFile[0], "SIZE") == 0) //END_SCRIPTの文字列を見つけたら
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%f%f%f", &size.x, &size.y, &size.z);
			}				
			if (strcmp(&aFile[0], "ADDSIZE") == 0) //END_SCRIPTの文字列を見つけたら
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%f%f%f", &addsize.x, &addsize.y, &addsize.z);
			}
			if (strcmp(&aFile[0], "COLOR") == 0) //END_SCRIPTの文字列を見つけたら
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%f%f%f%f", &col.r, &col.g, &col.b, &col.a);
			}
			if (strcmp(&aFile[0], "ADDCOLOR") == 0) //END_SCRIPTの文字列を見つけたら
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%f%f%f%f", &addcol.r, &addcol.g, &addcol.b,  &addcol.a);
			}											
			if (strcmp(&aFile[0], "LIFE") == 0) //END_SCRIPTの文字列を見つけたら
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &m_nLife);
			}
			if (strcmp(&aFile[0], "DENSDITY") == 0) //END_SCRIPTの文字列を見つけたら
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &m_nDensity);
			}
			if (strcmp(&aFile[0], "RADIUS") == 0) //END_SCRIPTの文字列を見つけたら
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &m_nRadius);
			}
			if (strcmp(&aFile[0], "END_SCRIPT") == 0) //END_SCRIPTの文字列を見つけたら
			{
				break;
			}
		}
	}
	fclose(pFile);

	m_nEffectType = nType;
	m_pos = pos;
	m_move = move;
	m_size = size;
	m_AddSize = addsize;
	m_AddColor = addcol;

}