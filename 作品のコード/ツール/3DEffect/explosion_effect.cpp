//=============================================================================
//
// �����̃G�t�F�N�g�̏��� [Explosion_effect.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include "explosion_effect.h"
#include"renderer.h"
#include"manager.h"
#include"effect.h"
#include"input.h"

//=============================================================================
// �����̃G�t�F�N�g�̃R���X�g���N�^
//=============================================================================
CExplosion_Effect::CExplosion_Effect(PRIORITY nPriority) : CBilleffect(nPriority)
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
// �����̃G�t�F�N�g�̃f�X�g���N�^
//=============================================================================
CExplosion_Effect::~CExplosion_Effect()
{

}

//=============================================================================
// �����̃G�t�F�N�g�̐�������
//=============================================================================
CExplosion_Effect *CExplosion_Effect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, CTexture::Tex type,
	D3DXVECTOR3 addmove, D3DXVECTOR3 addsize, D3DXCOLOR addcol, int nDensity, int nLife)
{
	//�C���X�^���X����
	CExplosion_Effect *pExplosion_Effect = new CExplosion_Effect(CScene::PRIORITY_NOMAL);

	if (pExplosion_Effect != NULL)
	{
		pExplosion_Effect->Init(pos, move, size, col, type, addmove, addsize, addcol, nDensity, nLife);
	}

	return pExplosion_Effect;
}

//=============================================================================
// �����̃G�t�F�N�g�̏���������
//=============================================================================
HRESULT CExplosion_Effect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, CTexture::Tex type,
	D3DXVECTOR3 addmove, D3DXVECTOR3 addsize, D3DXCOLOR addcol, int nDensity, int nLife)
{
	CBilleffect::Init(pos, size);
	SetExplosion(pos, move, size, col, type, addsize, addmove, addcol, nDensity, nLife);
	m_move = move;
	m_addmove = addmove;
	m_col = col;
	m_addcol = addcol;

	return S_OK;
}

//=============================================================================
// �����̃G�t�F�N�g�̏I������
//=============================================================================
void CExplosion_Effect::Uninit(void)
{
	m_pEffect->Uninit();
	CBilleffect::Uninit();
}

//=============================================================================
// �����̃G�t�F�N�g�̍X�V����
//=============================================================================
void CExplosion_Effect::Update(void)
{
	//m_move = Addmove(m_move, m_pullmove);

	//m_col = Addcol(m_col, m_pullcol);

	if (m_bUse == true)
	{
		Uninit();
	}
}

//=============================================================================
// �����̃G�t�F�N�g�̕`�揈��
//=============================================================================
void CExplosion_Effect::Draw(void)
{
	CBilleffect::Draw();
}

//=============================================================================
// �����̃G�t�F�N�g�̐ݒ菈��
//=============================================================================
void CExplosion_Effect::SetExplosion(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, CTexture::Tex type,
	D3DXVECTOR3 addmove, D3DXVECTOR3 addsize, D3DXCOLOR addcol,int nDensity, int nLife)
{
	for (int nCnt = 0; nCnt < nDensity; nCnt++)
	{
		m_pEffect = CEffect::Create(pos, D3DXVECTOR3(CIRCLE*move.x, CIRCLE*move.y, CIRCLE*move.z),
			size, col, type, D3DXVECTOR3(CIRCLE*addmove.x, CIRCLE*addmove.y, CIRCLE*addmove.z), addsize, addcol, nLife);
		//move = Addmove(move, addmove);
	}
}

//=============================================================================
// �����̃G�t�F�N�g�̈ړ����Z����
//=============================================================================
D3DXVECTOR3 CExplosion_Effect::Addmove(D3DXVECTOR3 move, D3DXVECTOR3 addmove)
{
	move -= addmove;

	return move;
}

//=============================================================================
// �����̃G�t�F�N�g�̐F�̌��Z����
//=============================================================================
D3DXCOLOR CExplosion_Effect::Addcol(D3DXCOLOR col, D3DXCOLOR addcol)
{
	col -= addcol;

	return col;
}