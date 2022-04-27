//=============================================================================
//
// ���G�t�F�N�g�̏��� [smoke_effect.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include"smoke_effect.h"
#include"renderer.h"
#include"manager.h"
#include"effect.h"
#include"input.h"

//=============================================================================
// �G�t�F�N�g�̃R���X�g���N�^
//=============================================================================
CSmoke_Effect::CSmoke_Effect(PRIORITY nPriority) : CBilleffect(nPriority)
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
CSmoke_Effect::~CSmoke_Effect()
{

}


//=============================================================================
// �G�t�F�N�g�̃f�X�g���N�^
//=============================================================================
CSmoke_Effect *CSmoke_Effect::Create(D3DXVECTOR3 pos, float rotY, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, 
	CTexture::Tex type, D3DXVECTOR3 addmove, D3DXVECTOR3 addsize, D3DXCOLOR addcol, int nRadius, int nDensity, int nLife)
{
	//�C���X�^���X����
	CSmoke_Effect *pSmoke_Effect = new CSmoke_Effect(CScene::PRIORITY_NOMAL);

	if (pSmoke_Effect != NULL)
	{
		pSmoke_Effect->Init(pos, rotY, move, size, col, type, addmove, addsize, addcol, nRadius, nDensity, nLife);
	}

	return pSmoke_Effect;
}

//=============================================================================
// �G�t�F�N�g�̏���������
//=============================================================================
HRESULT CSmoke_Effect::Init(D3DXVECTOR3 pos, float rotY, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, CTexture::Tex type,
	D3DXVECTOR3 addmove, D3DXVECTOR3 addsize, D3DXCOLOR addcol, int nRadius, int nDensity, int nLife)
{
	CBilleffect::Init(pos, size);
	SetSmoke(pos, rotY, move, size, col, type, addmove, addsize, addcol, nRadius, nDensity, nLife);
	m_bUse = false;

	return S_OK;
}

//=============================================================================
// �G�t�F�N�g�̏I������
//=============================================================================
void CSmoke_Effect::Uninit(void)
{
	CBilleffect::Uninit();
}

//=============================================================================
// �G�t�F�N�g�̍X�V����
//=============================================================================
void CSmoke_Effect::Update(void)
{
	if (m_bUse == true)
	{
		Uninit();
	}
}

//=============================================================================
// �G�t�F�N�g�̕`�揈��
//=============================================================================
void CSmoke_Effect::Draw(void)
{
	CBilleffect::Draw();
}

//=============================================================================
// �G�t�F�N�g�̐ݒ菈��
//=============================================================================
void CSmoke_Effect::SetSmoke(D3DXVECTOR3 pos, float rotY, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, CTexture::Tex type,
	D3DXVECTOR3 addmove, D3DXVECTOR3 addsize, D3DXCOLOR addcol, int nRadius, int nDensity, int nLife)
{
	if (m_bUse == false)
	{
		for (int nCnt = 0; nCnt < nDensity; nCnt++)
		{
			float fAngle = CIRCLE_HALF;
			float rotX = cosf(fAngle) * rotY;
			float rotZ = sinf(fAngle) * rotY;
			CEffect::Create(D3DXVECTOR3((rotX*nRadius)+ pos.x, pos.y, (rotZ*nRadius) + pos.z),
				D3DXVECTOR3(rotX*move.x, move.y, rotZ * move.z), size, col, type,
				D3DXVECTOR3(rotX*addmove.x, addmove.y, rotZ * addmove.z), addsize, addcol, nLife);
			//move = Addmove(move, addmove);
		}
	}
}

//=============================================================================
// �G�t�F�N�g�̈ړ����Z����
//=============================================================================
D3DXVECTOR3 CSmoke_Effect::Addmove(D3DXVECTOR3 move, D3DXVECTOR3 addmove)
{
	move -= addmove;
	return move;
}