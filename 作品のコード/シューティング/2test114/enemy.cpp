//=============================================================================
//
// �G�̏��� [enemy.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include"enemy.h"
#include"renderer.h"
#include"manager.h"

// �ÓI�����o�ϐ��̐錾
LPDIRECT3DTEXTURE9 CEnemy::m_pTexture = NULL;

//=============================================================================
// �G�̃R���X�g���N�^
//=============================================================================
CEnemy::CEnemy(int nPriority) : CScene2D(nPriority)
{
	m_Move = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Size = D3DXVECTOR2(0.0f,0.0f);
}


//=============================================================================
// �G�̃f�X�g���N�^
//=============================================================================
CEnemy::~CEnemy()
{

}

//=============================================================================
// �G�̐�������
//=============================================================================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size)
{
	CEnemy* pEnemy;

	pEnemy = new CEnemy;

	if (pEnemy != NULL)
	{
		pEnemy->Init(pos, move, Size);
		pEnemy->BindTextuer(m_pTexture);
		pEnemy->SetType(CScene::OBJTYPE_ENEMY);
	}
	return pEnemy;
}

//=============================================================================
// �e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CEnemy::Load(void)
{
	CManager *pManager = NULL;

	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/komoko000.png",
		&m_pTexture);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���̔j��
//=============================================================================
void CEnemy::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// �G�̏���������
//=============================================================================
HRESULT CEnemy::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size)
{
	int m_Life = 2;
	float m_fSpeed = 0;

	CScene2D::Init(pos, move, Size);

	m_Move = move;

	return S_OK;
}	// �v���C���[�̏����������I��



//=============================================================================
// �G�̏I������
//=============================================================================
void CEnemy::Uninit(void)
{
	CScene2D::Uninit();

}// �v���C���[�̏I�������I��


//=============================================================================
// �G�̍X�V����
//=============================================================================
void CEnemy::Update(void)
{	

	D3DXVECTOR3 pos = GetPosition();

	D3DXVECTOR2 size = GetSize();

	pos.x -= m_Move.x;

	CScene2D::Update();

	SetPosition(pos);
	SetSize(size);

	// ��ʊO�̓����蔻��
	if (pos.x + (size.x / 2) <= 0)
	{
		Uninit();
		return;
	}
	if (pos.x - (size.x / 2) >= SCREEN_WIDTH)
	{
		Uninit();
		return;
	}
	if (pos.y + (size.y / 2) <= 0)
	{
		Uninit();
		return;
	}
	if (pos.y - (size.y / 2) >= SCREEN_HEIGHT)
	{
		Uninit();
		return;
	}


}// �v���C���[�̂̍X�V�����I��



//=============================================================================
// �G�̕`�揈��
//=============================================================================
void CEnemy::Draw(void)
{
	CScene2D::Draw();

}	// �v���C���[�̕`�揈���I��