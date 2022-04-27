//=============================================================================
//
// �G(�g���{)�̏��� [enemy_doragonfly.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include"enemy_doragonfly.h"
#include"renderer.h"
#include"manager.h"
#include"player.h"
#include"game.h"

// �ÓI�����o�ϐ��̐錾
LPDIRECT3DTEXTURE9 CEnemy_Doragonfly::m_pTexture = NULL;

//=============================================================================
// �G(�g���{)�̃R���X�g���N�^
//=============================================================================
CEnemy_Doragonfly::CEnemy_Doragonfly(int nPriority) : CEnemy(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Size = D3DXVECTOR2(0.0f, 0.0f);
	m_Playerpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fRange = 0.0f;
	m_bUse = false;
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
	m_fSizeAnimU = 0.0f;
	m_fSizeMinV = 0.0f;
	m_fSizeMaxV = 0.5f;
	m_bAimPlayer = false;
}


//=============================================================================
// �G(�g���{)�̃f�X�g���N�^
//=============================================================================
CEnemy_Doragonfly::~CEnemy_Doragonfly()
{

}

//=============================================================================
// �G(�g���{)�̐�������
//=============================================================================
CEnemy_Doragonfly *CEnemy_Doragonfly::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size)
{
	CEnemy_Doragonfly* pEnemy_Doragonfly;

	pEnemy_Doragonfly = new CEnemy_Doragonfly;

	if (pEnemy_Doragonfly != NULL)
	{
		pEnemy_Doragonfly->Init(pos, move, Size);
		pEnemy_Doragonfly->BindTextuer(m_pTexture);
		pEnemy_Doragonfly->SetType(CScene::OBJTYPE_ENEMY);
	}
	return pEnemy_Doragonfly;
}

//=============================================================================
// �e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CEnemy_Doragonfly::Load(void)
{
	CManager *pManager = NULL;

	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/doragonflyAnime001.png",
		&m_pTexture);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���̔j��
//=============================================================================
void CEnemy_Doragonfly::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// �G(�g���{)�̏���������
//=============================================================================
HRESULT CEnemy_Doragonfly::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size)
{
	CScene2D::Init(pos, move, Size);

	m_pos = pos;
	m_Move = move;
	m_Size = Size;

	return S_OK;
}	// �v���C���[�̏����������I��



//=============================================================================
// �G(�g���{)�̏I������
//=============================================================================
void CEnemy_Doragonfly::Uninit(void)
{
	CEnemy::Uninit();

}// �v���C���[�̏I�������I��


//=============================================================================
// �G(�g���{)�̍X�V����
//=============================================================================
void CEnemy_Doragonfly::Update(void)
{
	if (m_pos.x - (m_Size.x / 2) > 0 &&
		m_pos.x < SCREEN_WIDTH &&
		m_pos.y > 0 &&
		m_pos.y < SCREEN_WIDTH)
	{
		m_bUse = true;
	}
	else
	{
		m_bUse = false;
	}

	m_fSizeAnimU = 0.25f;

	m_Playerpos = CGame::GetPlayer()->GetPosition();

	// �g���{�̌��݂̈ʒu��1100�𒴂�����
	if (m_pos.x > 1100)
	{
		m_fSizeMaxV = 1.0f;
		m_fSizeMinV = m_fSizeMaxV / 2;

		m_bAimPlayer = true;

		// �v���C���[�ƃg���{�̎Εӂ̋����𑪂�A����i�O�������(c2�� = a2��+b2��)�j
		m_fRange = sqrtf(powf((m_Playerpos.x - m_pos.x), 2.0f) + powf((m_Playerpos.y - m_pos.y), 2.0f));
		if (m_fRange != NULL)
		{
			m_Move.x = (m_Playerpos.x - m_pos.x) / m_fRange * 10;
			m_Move.y = (m_Playerpos.y - m_pos.y) / m_fRange * 10;
		}
		else
		{
			m_Move.y = 1;
		}
	}

	switch (m_bAimPlayer)
	{
	case TRUE:
		SetAnimesion(m_nPatternAnim, m_fSizeAnimU, m_fSizeMinV, m_fSizeMaxV);
		break;

	case FALSE:
		SetAnimesion(m_nPatternAnim, m_fSizeAnimU, m_fSizeMinV, m_fSizeMaxV);
		break;
	}

	m_pos += m_Move;

	if (m_bUse = false)
	{
		// ��ʊO�̓����蔻��
		if (m_pos.x + (m_Size.x / 2) <= 0)
		{
			Uninit();
			return;
		}

		if (m_pos.x - (m_Size.x / 2) >= SCREEN_WIDTH)
		{
			Uninit();
			return;
		}

		if (m_pos.y + (m_Size.y / 2) <= 0)
		{
			Uninit();
			return;
		}

		if (m_pos.y - (m_Size.y / 2) >= SCREEN_HEIGHT)
		{
			Uninit();
			return;
		}
	}
	SetPosition(m_pos);

	SetSize(m_Size);

	CScene2D::Update();


}// �v���C���[�̂̍X�V�����I��



 //=============================================================================
 // �G(�g���{)�̕`�揈��
 //=============================================================================
void CEnemy_Doragonfly::Draw(void)
{
	CEnemy::Draw();

}	// �v���C���[�̕`�揈���I��


//=============================================================================
// �G�̃A�j���[�V�����ݒ菈��
//=============================================================================
void CEnemy_Doragonfly::SetAnimesion(int nPatternAnim, float fSizeAnimU, float fSizeMinV, float fSizeMaxV)
{
	m_nCounterAnim++;

	if (m_nCounterAnim % 4 == 0)
	{
		m_nPatternAnim++;

		CScene2D::SetTexAnime(nPatternAnim, fSizeAnimU, fSizeMinV, fSizeMaxV);

		if (m_nPatternAnim >= 4)
		{
			m_nPatternAnim = 0;
			return;
		}
	}
}