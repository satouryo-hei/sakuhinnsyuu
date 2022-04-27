//=============================================================================
//
// �e�̏��� [bullet.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include"beam.h"
#include"manager.h"
#include"renderer.h"

// �ÓI�����o�ϐ��̐錾
LPDIRECT3DTEXTURE9 CBeam::m_pTexture = NULL;

//=============================================================================
// �e�̃R���X�g���N�^
//=============================================================================
CBeam::CBeam(int nPriority) : CBullet(nPriority)
{
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Size = D3DXVECTOR2(0.0f, 0.0f);
	m_Timer = 0;
}

//=============================================================================
// �e�̃f�X�g���N�^
//=============================================================================
CBeam::~CBeam()
{

}

//=============================================================================
// �e�̐�������
//=============================================================================
CBeam *CBeam::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size)
{
	CBeam* pBeam;

	pBeam = new CBeam;

	if (pBeam != NULL)
	{
		pBeam->Init(pos, move, Size);
		pBeam->BindTextuer(m_pTexture);
		pBeam->SetType(CScene::OBJTYPE_PLAYERBULLET);
	}
	return pBeam;
}

//=============================================================================
// �e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CBeam::Load(void)
{
	CManager *pManager = NULL;

	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();


	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/beam001.png",
		&m_pTexture);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���̔j��
//=============================================================================
void CBeam::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// �e�̏���������
//=============================================================================
HRESULT CBeam::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size)
{
	CBullet::Init(pos, move, Size);
	m_Pos = pos;
	m_Move = move;
	m_Size = Size;
	m_Timer = 0;
	return S_OK;
}

//=============================================================================
// �e�̏I���֐�
//=============================================================================
void CBeam::Uninit(void)
{
	CBullet::Uninit();
}

//=============================================================================
// �e�̍X�V�֐�
//=============================================================================
void CBeam::Update(void)
{
	m_Pos.x += m_Move.x;

	D3DXVECTOR3 pos = m_Pos;

	CScene2D::Update();

	SetPosition(m_Pos);

	// ��ʊO����
	if (m_Pos.x >= SCREEN_WIDTH - (m_Size.x / 2))
	{
		Uninit();
		return;
	}
	else if (m_Pos.x <= (m_Size.x / 2))
	{
		Uninit();
		return;
	}
	if (m_Pos.y >= SCREEN_HEIGHT - (m_Size.y / 2))
	{
		Uninit();
		return;
	}
	else if (m_Pos.y <= (m_Size.y / 2))
	{
		Uninit();
		return;
	}
}

//=============================================================================
// �e�̕`��֐�
//=============================================================================
void CBeam::Draw(void)
{
	CBullet::Draw();
}
