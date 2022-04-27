//=============================================================================
//
// �~�`�̃G�t�F�N�g�̏��� [circle_effect.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include"circle_effect.h"
#include"renderer.h"
#include"manager.h"
#include"effect.h"

//=============================================================================
// �~�`�̃G�t�F�N�g�̃R���X�g���N�^
//=============================================================================
CCircle_Effect::CCircle_Effect(PRIORITY nPriority) : CBilleffect(nPriority)
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
// �~�`�̃G�t�F�N�g�̃f�X�g���N�^
//=============================================================================
CCircle_Effect::~CCircle_Effect()
{

}

//=============================================================================
// �~�`�̃G�t�F�N�g�̐�������
//=============================================================================
CCircle_Effect *CCircle_Effect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, CTexture::Tex type,
	D3DXVECTOR3 addmove, D3DXVECTOR3 addsize, D3DXCOLOR addcol, int nRadius, int nDensity, int nLife)
{
	//�C���X�^���X����
	CCircle_Effect *pCircle_Effect = new CCircle_Effect(CScene::PRIORITY_NOMAL);

	if (pCircle_Effect != NULL)
	{
		pCircle_Effect->Init(pos, move, size, col, type, addmove, addsize, addcol, nRadius,nDensity, nLife);
	}

	return pCircle_Effect;
}

//=============================================================================
// �~�`�̃G�t�F�N�g�̏���������
//=============================================================================
HRESULT CCircle_Effect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, CTexture::Tex type,
	D3DXVECTOR3 addmove, D3DXVECTOR3 addsize, D3DXCOLOR addcol, int nRadius, int nDensity, int nLife)
{
	CBilleffect::Init(pos, size);
	SetCircle(pos, move, size, col, type, addmove, addsize, addcol,nRadius, nDensity, nLife);

	return S_OK;
}

//=============================================================================
// �~�`�̃G�t�F�N�g�̏I������
//=============================================================================
void CCircle_Effect::Uninit(void)
{
	CBilleffect::Uninit();
}

//=============================================================================
// �~�`�̃G�t�F�N�g�̍X�V����
//=============================================================================
void CCircle_Effect::Update(void)
{
	if (m_bUse == true)
	{
		Uninit();
	}
}

//=============================================================================
// �~�`�̃G�t�F�N�g�̕`�揈��
//=============================================================================
void CCircle_Effect::Draw(void)
{
	CBilleffect::Draw();
}

//=============================================================================
// �~�`�̃G�t�F�N�g�̐ݒ菈��
//=============================================================================
void CCircle_Effect::SetCircle(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, CTexture::Tex type,
	D3DXVECTOR3 addmove, D3DXVECTOR3 addsize, D3DXCOLOR addcol, int nRadius, int nDensity, int nLife)
{
	for (int nCnt = 0; nCnt < nDensity; nCnt++)
	{
		float fAngle = CIRCLE;
		m_pEffect = CEffect::Create(D3DXVECTOR3(pos.x + (cosf(fAngle)*nRadius), pos.y, pos.z + (sinf(fAngle)*nRadius)),
			move, size, col, type, addmove, addsize, addcol, nLife);
		move = Addmove(move, D3DXVECTOR3(0,0.1f,0));
		//col = Addcol(col, addcol);
	}
}

//=============================================================================
// �~�`�̃G�t�F�N�g�̈ړ����Z����
//=============================================================================
D3DXVECTOR3 CCircle_Effect::Addmove(D3DXVECTOR3 move, D3DXVECTOR3 addmove)
{
	move -= addmove;

	return move;
}

//=============================================================================
// �~�`�̃G�t�F�N�g�̐F�̌��Z����
//=============================================================================
D3DXCOLOR CCircle_Effect::Addcol(D3DXCOLOR col, D3DXCOLOR addcol)
{
	col -= addcol;

	return col;
}