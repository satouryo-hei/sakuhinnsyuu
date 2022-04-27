//=============================================================================
//
// �^�������̃G�t�F�N�g�̏��� [siraight_effect.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include"straight_effect.h"
#include"renderer.h"
#include"manager.h"
#include"effect.h"

//=============================================================================
// �^�������̃G�t�F�N�g�̃R���X�g���N�^
//=============================================================================
CStraight_Effect::CStraight_Effect(PRIORITY nPriority) : CBilleffect(nPriority)
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
// �^�������̃G�t�F�N�g�̃f�X�g���N�^
//=============================================================================
CStraight_Effect::~CStraight_Effect()
{

}

//=============================================================================
// �^�������̃G�t�F�N�g�̐�������
//=============================================================================
CStraight_Effect *CStraight_Effect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move ,D3DXVECTOR3 size, D3DXCOLOR col,
	CTexture::Tex type, D3DXVECTOR3 addmove, D3DXVECTOR3 addsize, D3DXCOLOR addcol, int nDensity, int nLife)
{
	//�C���X�^���X����
	CStraight_Effect *pStraight_Effect = new CStraight_Effect(CScene::PRIORITY_NOMAL);

	if (pStraight_Effect != NULL)
	{
		pStraight_Effect->Init(pos, move, size, col, type, addmove, addsize, addcol, nDensity, nLife);
	}

	return pStraight_Effect;
}

//=============================================================================
// �^�������̃G�t�F�N�g�̏���������
//=============================================================================
HRESULT CStraight_Effect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, CTexture::Tex type,
	 D3DXVECTOR3 addmove, D3DXVECTOR3 addsize, D3DXCOLOR addcol, int nDensity, int nLife)
{
	CBilleffect::Init(pos, size);
	SetStraight(pos, move, size, col, type,addmove, addsize, addcol, nDensity, nLife);

	return S_OK;
}

//=============================================================================
// �^�������̃G�t�F�N�g�̏I������
//=============================================================================
void CStraight_Effect::Uninit(void)
{
	CBilleffect::Uninit();
}

//=============================================================================
// �^�������̃G�t�F�N�g�̍X�V����
//=============================================================================
void CStraight_Effect::Update(void)
{
	if (m_bUse == true)
	{
		Uninit();
	}

	//m_size.x += 1;
	//m_size.y -= 1;
	//m_size.z -= 1;
	//
	//if (m_size.x <= 1 || m_size.y <= 1 || m_size.z <= 1)
	//{
	//	m_size.x = 1;
	//	m_size.y = 1;
	//	m_size.z = 1;
	//}


}

//=============================================================================
// �^�������̃G�t�F�N�g�̕`�揈��
//=============================================================================
void CStraight_Effect::Draw(void)
{
	CBilleffect::Draw();
}

//=============================================================================
// �^�������̃G�t�F�N�g�̐ݒ菈��
//=============================================================================
void CStraight_Effect::SetStraight(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, CTexture::Tex type,
	D3DXVECTOR3 addmove, D3DXVECTOR3 addsize, D3DXCOLOR addcol, int nDensity,int nLife)
{
	if (m_bUse == false)
	{
		for (int nCnt = 0; nCnt < nDensity; nCnt++)
		{
			m_pEffect = CEffect::Create(pos, move, size, col, type, addmove, addsize, addcol, nLife);
			//move = Addmove(move, addmove);
			//col = Addcol(col, addcol);
		}
	}
}

//=============================================================================
// �^�������̃G�t�F�N�g�̈ړ����Z����
//=============================================================================
D3DXVECTOR3 CStraight_Effect::Addmove(D3DXVECTOR3 move, D3DXVECTOR3 addmove)
{
	move -= addmove;
	return move;
}

//=============================================================================
// �^�������̃G�t�F�N�g�̐F�̌��Z����
//=============================================================================
D3DXCOLOR CStraight_Effect::Addcol(D3DXCOLOR col, D3DXCOLOR addcol)
{
	col -= addcol;

	return col;
}