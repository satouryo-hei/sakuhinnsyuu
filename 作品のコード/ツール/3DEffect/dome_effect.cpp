//=============================================================================
//
// �h�[���^�̃G�t�F�N�g�̏��� [dome_effect.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include"dome_effect.h"
#include"renderer.h"
#include"manager.h"
#include"effect.h"
#include"input.h"

//=============================================================================
// �h�[���^�̃G�t�F�N�g�̃R���X�g���N�^
//=============================================================================
CDome_Effect::CDome_Effect(PRIORITY nPriority) : CBilleffect(nPriority)
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
// �h�[���^�̃G�t�F�N�g�̃f�X�g���N�^
//=============================================================================
CDome_Effect::~CDome_Effect()
{

}


//=============================================================================
// �h�[���^�̃G�t�F�N�g�̃f�X�g���N�^
//=============================================================================
CDome_Effect *CDome_Effect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, CTexture::Tex type,
	 D3DXVECTOR3 addmove, D3DXVECTOR3 addsize, D3DXCOLOR addcol, int nRadius, int nDensity, int nLife)
{
	//�C���X�^���X����
	CDome_Effect *pDome_Effect = new CDome_Effect(CScene::PRIORITY_NOMAL);

	if (pDome_Effect != NULL)
	{
		pDome_Effect->Init(pos, move, size, col, type, addmove, addsize, addcol, nRadius, nDensity, nLife);
	}

	return pDome_Effect;
}

//=============================================================================
// �h�[���^�̃G�t�F�N�g�̏���������
//=============================================================================
HRESULT CDome_Effect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, CTexture::Tex type,
	D3DXVECTOR3 addmove, D3DXVECTOR3 addsize, D3DXCOLOR addcol, int nRadius,int nDensity, int nLife)
{
	CBilleffect::Init(pos, size);
	SetDome(pos, move, size, col, type, addmove, addsize, addcol, nRadius, nDensity, nLife);

	return S_OK;
}

//=============================================================================
// �h�[���^�̃G�t�F�N�g�̏I������
//=============================================================================
void CDome_Effect::Uninit(void)
{
	CBilleffect::Uninit();
}

//=============================================================================
// �h�[���^�̃G�t�F�N�g�̍X�V����
//=============================================================================
void CDome_Effect::Update(void)
{
	if (m_bUse == true)
	{
		Uninit();
	}
}

//=============================================================================
// �h�[���^�̃G�t�F�N�g�̕`�揈��
//=============================================================================
void CDome_Effect::Draw(void)
{
	CBilleffect::Draw();
}

//=============================================================================
// �h�[���^�̃G�t�F�N�g�̐ݒ菈��
//=============================================================================
void CDome_Effect::SetDome(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, CTexture::Tex type,
	D3DXVECTOR3 addmove, D3DXVECTOR3 addsize, D3DXCOLOR addcol, int nRadius,int nDensity, int nLife)
{
	for (int nCnt = 0; nCnt < nDensity; nCnt++)
	{
		float fAngle = CIRCLE;
		m_pEffect = CEffect::Create(pos, D3DXVECTOR3(move.x + cosf(fAngle), move.y, move.z + sinf(fAngle)),
			size, col, type, addmove, addsize, addcol, nLife);
		move = Addmove(move, D3DXVECTOR3(0,0.8f,0));
		//CEffect::Create(pos, D3DXVECTOR3((cosf(fAngle)*nRadius)*move.x, move.y, (sinf(fAngle)*nRadius)*move.z), size, col, type, nLife);
		
	}
}

//=============================================================================
// �h�[���^�̃G�t�F�N�g�̈ړ����Z����
//=============================================================================
D3DXVECTOR3 CDome_Effect::Addmove(D3DXVECTOR3 move, D3DXVECTOR3 addmove)
{
	move -= addmove;

	return move;
}

//=============================================================================
// �h�[���^�̃G�t�F�N�g�̐F�̌��Z����
//=============================================================================
D3DXCOLOR CDome_Effect::Addcol(D3DXCOLOR col, D3DXCOLOR addcol)
{
	col -= addcol;

	return col;
}