//=============================================================================
//
// �G�t�F�N�g�̏��� [Explosion_effect.cpp](�؂����j
// Author : ���c��V
//
//=============================================================================
#include "fair_effect.h"
#include"Renderer.h"
#include"manager.h"
#include"effect.h"
#include "effect_sa.h"
//=============================================================================
// �G�t�F�N�g�̃R���X�g���N�^
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
// �G�t�F�N�g�̃f�X�g���N�^
//=============================================================================
Cfair_Effect::~Cfair_Effect()
{
	
}

Cfair_Effect *Cfair_Effect::Create(D3DXVECTOR3 pos, CTexture::Type type)
{
	//�C���X�^���X����
	Cfair_Effect *pCircle_Effect = new Cfair_Effect(CScene::OBJTYPE_EFFECT);
	if (pCircle_Effect != NULL)
	{
		pCircle_Effect->Init(pos,type);
	}
	return pCircle_Effect;
}

//=============================================================================
// �G�t�F�N�g�̏���������
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
// �G�t�F�N�g�̏I������
//=============================================================================
void Cfair_Effect::Uninit(void)
{
	CBilleffect::Uninit();
}

//=============================================================================
// �G�t�F�N�g�̍X�V����
//=============================================================================
void Cfair_Effect::Update(void)
{
	
	int nCnt = 0;
	float  nRadius = 2.0f;//�͈�
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
// �G�t�F�N�g�̕`�揈��
//=============================================================================
void Cfair_Effect::Draw(void)
{
	CBilleffect::Draw();
}