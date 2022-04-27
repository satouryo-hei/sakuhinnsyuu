//=============================================================================
//
// �G�t�F�N�g�̏��� [Explosion_effect.cpp]
// Author : �����ĕ��@
//
//=============================================================================
#include "explosion_effect.h"
#include"renderer.h"
#include"manager.h"
#include"effect_sa.h"
#include"input.h"

//=============================================================================
// �G�t�F�N�g�̃R���X�g���N�^
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
// �G�t�F�N�g�̃f�X�g���N�^
//=============================================================================
CExplosion_Effect::~CExplosion_Effect()
{

}

//=============================================================================
// �G�t�F�N�g�̐�������
//=============================================================================
CExplosion_Effect *CExplosion_Effect::Create(D3DXVECTOR3 pos, int nMaxLife, int nMinLife, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, CTexture::Type type, int nDensity, D3DXVECTOR3 addmove)
{
	//�C���X�^���X����
	CExplosion_Effect *pCircle_Effect = new CExplosion_Effect(CScene::OBJTYPE_EFFECT);

	if (pCircle_Effect != NULL)
	{
		pCircle_Effect->Init(pos, nMaxLife, nMinLife,move, size,col, type, nDensity,addmove);
	}

	return pCircle_Effect;
}

//=============================================================================
// �G�t�F�N�g�̏���������
//=============================================================================
HRESULT CExplosion_Effect::Init(D3DXVECTOR3 pos, int nMaxLife, int nMinLife, D3DXVECTOR3 move,D3DXVECTOR3 size, D3DXCOLOR col, CTexture::Type type, int nDensity, D3DXVECTOR3 addmove)
{
	CBilleffect::Init(type);
	SetExplosion(pos,nMaxLife, nMinLife, move,size, col, nDensity, addmove);
	m_bUse = false;

	return S_OK;
}

//=============================================================================
// �G�t�F�N�g�̏I������
//=============================================================================
void CExplosion_Effect::Uninit(void)
{
	CBilleffect::Uninit();
}

//=============================================================================
// �G�t�F�N�g�̍X�V����
//=============================================================================
void CExplosion_Effect::Update(void)
{
	if (m_bUse == true)
	{
		Uninit();
	}
}

//=============================================================================
// �G�t�F�N�g�̕`�揈��
//=============================================================================
void CExplosion_Effect::Draw(void)
{
	CBilleffect::Draw();
}

//=============================================================================
// �G�t�F�N�g�̐ݒ菈��
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
// �G�t�F�N�g�̈ړ����Z����
//=============================================================================
D3DXVECTOR3 CExplosion_Effect::Addmove(D3DXVECTOR3 move , D3DXVECTOR3 addmove)
{
	move -= addmove;
  
	return move;
}