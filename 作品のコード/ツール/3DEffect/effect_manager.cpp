//=============================================================================
//
// �G�t�F�N�g�̊Ǘ��^�̏��� [effect_manager.cpp]
// Author : �����ĕ�
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
// �ÓI�����o�ϐ��̐錾
//=============================================================================
CStraight_Effect	*	CEffect_Manager::m_pStraight_Effect		= NULL;
CCircle_Effect		*	CEffect_Manager::m_pCircle_Effect		= NULL;
CExplosion_Effect	*	CEffect_Manager::m_pExplosion_Effect	= NULL;
CDome_Effect		*	CEffect_Manager::m_pDome_Effect			= NULL;
CWater_Crest_Effect *	CEffect_Manager::m_pWater_Crest_Effect	= NULL;
CSmoke_Effect		*	CEffect_Manager::m_pSmoke_Effect		= NULL;
CLanding_Effect		*	CEffect_Manager::m_pLanding_Effect		= NULL;


//=============================================================================
// �G�t�F�N�g�̃R���X�g���N�^
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
// �G�t�F�N�g�̃f�X�g���N�^
//=============================================================================
CEffect_Manager::~CEffect_Manager()
{

}

//=============================================================================
// �G�t�F�N�g�̐�������
//=============================================================================
CEffect_Manager *CEffect_Manager::Create(EffectType EffectType)
{
	//�C���X�^���X����
	CEffect_Manager *pEffect_Manager = new CEffect_Manager(CScene::PRIORITY_NOMAL);

	if (pEffect_Manager != NULL)
	{
		pEffect_Manager->Init(EffectType);
	}

	return pEffect_Manager;
}

//=============================================================================
// �G�t�F�N�g�̏���������
//=============================================================================
HRESULT CEffect_Manager::Init(EffectType EffectType)
{
	CBilleffect::Init(m_pos, m_size);
	m_nEffectType = EffectType;

	return S_OK;
}

//=============================================================================
// �G�t�F�N�g�̏I������
//=============================================================================
void CEffect_Manager::Uninit(void)
{
	CBilleffect::Uninit();
}

//=============================================================================
// �G�t�F�N�g�̍X�V����
//=============================================================================
void CEffect_Manager::Update(void)
{
	//-----------------------------------------------------------------------------
	// �F�̉����l�����������Ă��ύX�ł���悤�ɂ��邩
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
	// �ʒu��傫��,�ړ��ʂ̉����l�����������Ă��ύX�ł���悤�ɂ��邩
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
	// ������g���K�[�ɂ���
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
	// �����̕ύX
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
	// ���x�̕ύX
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
	// ���a�̕ύX
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
	// �G�t�F�N�g�̕ύX
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
	// �F�̕ύX
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
	// �ʒu��ړ��ʂ̕ύX
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
	// �傫���̉����l�����������Ă��ύX
	//-----------------------------------------------------------------------------
	if (m_bVecTrigger)
	{
		//---------------------------------------------------------
		// �傫���̒l�̑���
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
		// �傫���̌��Z�l�̑���
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
	// �傫���̉����l�����������Ă��ύX�ł��Ȃ�
	//-----------------------------------------------------------------------------
	else if (!m_bVecTrigger)
	{
		//---------------------------------------------------------
		// �傫���̒l�̑���
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
		// �傫���̌��Z�l�̑���
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
	// �G�t�F�N�g�̐؂�ւ�����
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
			m_pos,											// ���݂̈ʒu
			m_move,											// �ړ���
			m_size,											// �傫��
			m_col,CTexture::Tex_Effect,						// �F,Texture
			D3DXVECTOR3(0.0f, 0.0f, 0.1f), 					// �v�Z����ړ���
			m_AddSize,										// �v�Z����傫��
			m_AddColor, m_nDensity, m_nLife);				// �F�̌��Z�l,���x,����
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
			m_pos,											// ���݂̈ʒu
			m_move, 										// �ړ���
			m_size,											// �傫��
			m_col, CTexture::Tex_Effect,					// �F,Texture
			D3DXVECTOR3(0.0f, 0.05f, 0.0f),					// �v�Z����ړ���
			m_AddSize,										// �v�Z����傫��
			m_AddColor, m_nRadius, m_nDensity, m_nLife);	// �F�̌��Z�l,���a,���x,����
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
			m_pos,											// ���݂̈ʒu
			m_move,											// �ړ���
			m_size,											// �傫��
			m_col, CTexture::Tex_Effect,					// �F,Texture
			D3DXVECTOR3(0.05f, 0.05f, 0.05f), 				// �v�Z����ړ���
			m_AddSize,										// �v�Z����傫��
			m_AddColor, m_nDensity, m_nLife);				// �F�̌��Z�l,���x,����
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
			m_pos,											// ���݂̈ʒu
			m_move,											// �ړ���
			m_size,											// �傫��
			m_col, CTexture::Tex_Effect, 					// �F,Texture
			D3DXVECTOR3(0.0f, 0.1f, 0.0f), 					// �v�Z����ړ���
			m_AddSize,										// �v�Z����傫��
			m_AddColor, m_nRadius, m_nDensity, m_nLife);	// �F�̌��Z�l,���a,���x,����
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
					m_pos,											// ���݂̈ʒu			
					m_move,											// �ړ���
					m_size,											// �傫��
					m_col, CTexture::Tex_Effect,					// �F,Texture
					D3DXVECTOR3(0.2f, 0.0f, 0.2f), 					// �v�Z����ړ���
					m_AddSize,						 				// �v�Z����傫��
					m_AddColor, m_nRadius, m_nDensity, m_nLife);	// �F�̌��Z�l,���a,���x,����
			}
		}
		else if (!m_bEffectTrigger)
		{
			m_pWater_Crest_Effect = CWater_Crest_Effect::Create(
				m_pos,											// ���݂̈ʒu			
				m_move,											// �ړ���
				m_size,											// �傫��
				m_col, CTexture::Tex_Effect,					// �F,Texture
				D3DXVECTOR3(0.2f, 0.0f, 0.2f), 					// �v�Z����ړ���
				m_AddSize,						 				// �v�Z����傫��
				m_AddColor, m_nRadius, m_nDensity, m_nLife);	// �F�̌��Z�l,���a,���x,����
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
			m_pos,											// ���݂̈ʒu
			1.0f,											// ��]�l
			m_move,											// �ړ���
			m_size,											// �傫��
			m_col, CTexture::Tex_Effect,					// �F,Texture
			D3DXVECTOR3(0.2f, 0.0f, 0.2f), 					// �v�Z����ړ���
			m_AddSize,										// �v�Z����傫��
			m_AddColor, m_nRadius, m_nDensity, m_nLife);	// �F�̌��Z�l,���a,���x,����

		break;

	case EffectType_LANDING:
		if (m_pSmoke_Effect != NULL)
		{
			delete m_pSmoke_Effect;
			m_pSmoke_Effect = NULL;
		}
		m_pLanding_Effect = CLanding_Effect::Create(
			m_pos,											// ���݂̈ʒu
			m_move,											// �ړ���
			m_size,											// �傫��
			m_col, CTexture::Tex_Effect,					// �F,Texture
			D3DXVECTOR3(0.2f, 0.0f, 0.2f), 					// �v�Z����ړ���
			m_AddSize, 										// �v�Z����傫��
			m_AddColor, m_nRadius, m_nDensity, m_nLife);	// �F�̌��Z�l,���a,���x,����
		break;
	default:
		break;
	}

	//-----------------------------------------------------------------------------
	// �F�̐؂�ւ�����
	//-----------------------------------------------------------------------------
	switch (m_nColorType)
	{
	case ColorType_RED:
		if (m_bColorTrigger)
		{
			//---------------------------------------------------------
			// �F�̒l�̑���
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
			// �F�̌��Z�l�̑���
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
			// �F�̒l�̑���
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
			// �F�̌��Z�l�̑���
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
			// �F�̒l�̑���
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
			// �F�̌��Z�l�̑���
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
			// �F�̒l�̑���
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
			// �F�̌��Z�l�̑���
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
			// �F�̒l�̑���
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
			// �F�̌��Z�l�̑���
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
			// �F�̒l�̑���
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
			// �F�̌��Z�l�̑���
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
			// �F�̒l�̑���
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
			// �F�̌��Z�l�̑���
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
			// �F�̒l�̑���
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
			// �F�̌��Z�l�̑���
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
	// �ʒu��ړ��ʂ̐؂�ւ�����
	//-----------------------------------------------------------------------------
	switch (m_nVecType)
	{
	case Vector_X:
		if (m_bVecTrigger)
		{			
			//---------------------------------------------------------
			// �ʒu�̒l�̑���
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
			// �ʒu�̒l�̑���
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
			// �ړ��ʂ̒l�̑���
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
			// �ʒu�̒l�̑���
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
			// �ʒu�̒l�̑���
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
			// �ړ��ʂ̒l�̑���
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
			// �ʒu�̒l�̑���
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
			// �ʒu�̒l�̑���
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
			// �ړ��ʂ̒l�̑���
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
			// �ʒu�̒l�̑���
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
			// �ʒu�̒l�̑���
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
			// �ړ��ʂ̒l�̑���
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
			// �ʒu�̒l�̑���
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
			// �ʒu�̒l�̑���
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
			// �ړ��ʂ̒l�̑���
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
			// �ʒu�̒l�̑���
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
			// �ʒu�̒l�̑���
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
			// �ړ��ʂ̒l�̑���
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
	// �F���ŏ��l�ɂȂ�����
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
	// �F���ő�l�ɂȂ�����
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
	// �F�̉����l���ŏ��l�ɂȂ�����
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
	// �F�̉����l���ő�l�ɂȂ�����
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
	// �傫�����ŏ��l�ɂȂ�����
	//-----------------------------------------------------------------------------
	if (m_size.x < 0.0f &&m_size.y < 0.0f&&m_size.z < 0.0f)
	{
		m_size.x = 0;
		m_size.y = 0;
		m_size.z = 0;
	}

	//-----------------------------------------------------------------------------
	// �傫�����ő�l�ɂȂ�����
	//-----------------------------------------------------------------------------
	if (m_size.x > m_fMaxSize &&m_size.y > m_fMaxSize &&m_size.z > m_fMaxSize)
	{
		m_size.x = m_fMaxSize;
		m_size.y = m_fMaxSize;
		m_size.z = m_fMaxSize;
	}

	//-----------------------------------------------------------------------------
	// �傫���̉����l���ŏ��l�ɂȂ�����
	//-----------------------------------------------------------------------------
	if (m_AddSize.x < 0.0f &&m_AddSize.y < 0.0f&&m_AddSize.z < 0.0f)
	{
		m_AddSize.x = 0;
		m_AddSize.y = 0;
		m_AddSize.z = 0;
	}

	//-----------------------------------------------------------------------------
	// �傫���̉����l���ő�l�ɂȂ�����
	//-----------------------------------------------------------------------------
	if (m_AddSize.x > m_fMaxAddSize && m_AddSize.y > m_fMaxAddSize && m_AddSize.z > m_fMaxAddSize)
	{
		m_AddSize.x = m_fMaxAddSize;
		m_AddSize.y = m_fMaxAddSize;
		m_AddSize.z = m_fMaxAddSize;
	}

	//-----------------------------------------------------------------------------
	// �������ݏ���
	//-----------------------------------------------------------------------------
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_F9) == true)
	{
		Save();
	}

	//-----------------------------------------------------------------------------
	// �ǂݍ��ݏ���
	//-----------------------------------------------------------------------------
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_F8) == true)
	{
		Lode();
	}
}

//=============================================================================
// �G�t�F�N�g�̕`�揈��
//=============================================================================
void CEffect_Manager::Draw(void)
{
	CBilleffect::Draw();
}


//=============================================================================
// �G�t�F�N�g��؂�ւ�Ƃ��Ƀ��Z�b�g����
//=============================================================================
void CEffect_Manager::Reset(void)
{
	//-----------------------------------------------------------------------------
	// �F�̃��Z�b�g
	//-----------------------------------------------------------------------------
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_AddColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

	//-----------------------------------------------------------------------------
	// ���ꂼ��̃G�t�F�N�g�̎�ނ̏�����
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
// �������ݏ���
//=============================================================================
void CEffect_Manager::Save(void)
{
	// �J���`�t�@�C���I
	FILE *pFile = fopen(EFFECTTEXT, "w");

	// �t�@�C������������
	if (pFile != NULL)
	{
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "# �G�t�F�N�g�t�@�C��[3DEffect.txt]\n");
		fprintf(pFile, "# Author : �����ĕ�\n");
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "# �Z�b�g�����G�t�F�N�g�����̃e�L�X�g�t�@�C���ɏ����o���܂�\n");
		fprintf(pFile, "# EFFECT���\n");
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "SCRIPT\t\t# ���̍s�͐�Ώ����Ȃ����ƁI\n");
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "# �ǂݍ��ރG�t�F�N�g�̎��\n");
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "TYPE = %d\n", m_nEffectType);
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "# �\������G�t�F�N�g�̔z�u���\n");
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
		fprintf(pFile, "END_SCRIPT\t\t# ���̍s�͐�Ώ����Ȃ����ƁI\n");
	}
	else
	{
		printf("�t�@�C�����ǂݍ��܂�܂���ł����B");
	}
	// ����`�t�@�C���I
	fclose(pFile);
}

//=============================================================================
// �G�t�F�N�g�̓ǂݍ��ݏ���
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

	if (pFile != NULL)//��x�t�@�C����ǂݍ���ŕK�v�ȏ��𔲂�
	{
		while (true)
		{
			fscanf(pFile, "%s", &aFile[0]);

			if (strcmp(&aFile[0], "TYPE") == 0) //END_SCRIPT�̕��������������
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &nType);
			}
			if (strcmp(&aFile[0], "POS") == 0) //END_SCRIPT�̕��������������
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%f%f%f", &pos.x, &pos.y,&pos.z);
			}
			if (strcmp(&aFile[0], "MOVE") == 0) //END_SCRIPT�̕��������������
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%f%f%f", &move.x, &move.y, &move.z);
			}
			if (strcmp(&aFile[0], "SIZE") == 0) //END_SCRIPT�̕��������������
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%f%f%f", &size.x, &size.y, &size.z);
			}				
			if (strcmp(&aFile[0], "ADDSIZE") == 0) //END_SCRIPT�̕��������������
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%f%f%f", &addsize.x, &addsize.y, &addsize.z);
			}
			if (strcmp(&aFile[0], "COLOR") == 0) //END_SCRIPT�̕��������������
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%f%f%f%f", &col.r, &col.g, &col.b, &col.a);
			}
			if (strcmp(&aFile[0], "ADDCOLOR") == 0) //END_SCRIPT�̕��������������
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%f%f%f%f", &addcol.r, &addcol.g, &addcol.b,  &addcol.a);
			}											
			if (strcmp(&aFile[0], "LIFE") == 0) //END_SCRIPT�̕��������������
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &m_nLife);
			}
			if (strcmp(&aFile[0], "DENSDITY") == 0) //END_SCRIPT�̕��������������
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &m_nDensity);
			}
			if (strcmp(&aFile[0], "RADIUS") == 0) //END_SCRIPT�̕��������������
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &m_nRadius);
			}
			if (strcmp(&aFile[0], "END_SCRIPT") == 0) //END_SCRIPT�̕��������������
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