//=============================================================================
//
// �G�t�F�N�g�̏��� [circle_effect.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include"circle_effect.h"
#include"renderer.h"
#include"manager.h"
#include"effect_sa.h"

//=============================================================================
// �G�t�F�N�g�̃R���X�g���N�^
//=============================================================================
CCircle_Effect::CCircle_Effect(CScene::OBJTYPE nPriority) : CBilleffect(nPriority)
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
CCircle_Effect::~CCircle_Effect()
{

}

//=============================================================================
// �G�t�F�N�g�̐�������
//=============================================================================
CCircle_Effect *CCircle_Effect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, CTexture::Type type, D3DXVECTOR3 addmove, int nDensity, int nRadius, int nLife)
{
	//�C���X�^���X����
	CCircle_Effect *pCircle_Effect = new CCircle_Effect(CScene::OBJTYPE_EFFECT);

	if (pCircle_Effect != NULL)
	{
		pCircle_Effect->Init(pos, move, size, col, type, addmove, nDensity, nRadius,nLife);
	}

	return pCircle_Effect;
}

//=============================================================================
// �G�t�F�N�g�̏���������
//=============================================================================
HRESULT CCircle_Effect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, CTexture::Type type, D3DXVECTOR3 addmove,int nDensity, int nRadius, int nLife)
{
	CBilleffect::Init(type);
	SetCircle(pos, move, size, col, addmove,nDensity, nRadius, nLife);
	m_bUse = false;

	return S_OK;
}

//=============================================================================
// �G�t�F�N�g�̏I������
//=============================================================================
void CCircle_Effect::Uninit(void)
{
	CBilleffect::Uninit();
}

//=============================================================================
// �G�t�F�N�g�̍X�V����
//=============================================================================
void CCircle_Effect::Update(void)
{
	if (m_bUse == true)
	{
		Uninit();
	}
}

//=============================================================================
// �G�t�F�N�g�̕`�揈��
//=============================================================================
void CCircle_Effect::Draw(void)
{
	CBilleffect::Draw();
}

//=============================================================================
// �G�t�F�N�g�̐ݒ菈��
//=============================================================================
void CCircle_Effect::SetCircle(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR3 addmove, int nDensity, int nRadius,int nLife)
{
	if (m_bUse == false)
	{
		for (int nCnt = 0; nCnt < nDensity; nCnt++)
		{
			float fAngle = CIRCLE;
			CEffect_sa::Create(D3DXVECTOR3(pos.x + (cosf(fAngle)*nRadius), pos.y, pos.z + (sinf(fAngle)*nRadius)), move, size, col, CTexture::Effect, nLife);
			move = Addmove(move, addmove);
		}
	}
}

//=============================================================================
// �G�t�F�N�g�̈ړ����Z����
//=============================================================================
D3DXVECTOR3 CCircle_Effect::Addmove(D3DXVECTOR3 move, D3DXVECTOR3 addmove)
{
	move -= addmove;

	if (move.x < 0)
	{
		move.x = 0;
	}
	if (move.y < 0)
	{
		move.y = 0;
	}
	if (move.z < 0)
	{
		move.z = 0;
	}

	return move;
}