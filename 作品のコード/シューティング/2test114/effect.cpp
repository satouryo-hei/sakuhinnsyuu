//=============================================================================
//
// �G�t�F�N�g�̏��� [effect.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include"effect.h"
#include"renderer.h"
#include"manager.h"

// �ÓI�����o�ϐ��̐錾
LPDIRECT3DTEXTURE9 CEffect::m_pTexture = NULL;

//=============================================================================
// �G�t�F�N�g�̃R���X�g���N�^
//=============================================================================
CEffect::CEffect(int nPriority) : CScene2D(nPriority)
{
	m_Size = D3DXVECTOR2(0.0f, 0.0f);
	m_nRed = 255;
	m_nGreen = 255;
	m_nBlue = 255;
	m_nAlpha = 255;
}

//=============================================================================
// �G�t�F�N�g�̃f�X�g���N�^
//=============================================================================
CEffect::~CEffect()
{

}

//=============================================================================
// �G�t�F�N�g�̐�������
//=============================================================================
CEffect *CEffect::Create(D3DXVECTOR3 pos,  D3DXVECTOR2 Size)
{
	CEffect* pEffect;

	pEffect = new CEffect;

	if (pEffect != NULL)
	{
		pEffect->Init(pos, Size);
		pEffect->BindTextuer(m_pTexture);
		pEffect->SetType(CScene::OBJTYPE_PLAYERBULLET);

	}
	return pEffect;
}

//=============================================================================
// �e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CEffect::Load(void)
{
	CManager *pManager = NULL;

	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/effect000.jpg",
		&m_pTexture);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���̔j��
//=============================================================================
void CEffect::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// �G�t�F�N�g�̏���������
//=============================================================================
HRESULT CEffect::Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	CScene2D::Init(pos, Size);

	m_Size = Size;

	return S_OK;
}	// �|���S���̏����������I��



//=============================================================================
// �G�t�F�N�g�̏I������
//=============================================================================
void CEffect::Uninit(void)
{
	CScene2D::Uninit();

}// �|���S���̏I�������I��


//=============================================================================
// �G�t�F�N�g�̍X�V����
//=============================================================================
void CEffect::Update(void)
{
	D3DXVECTOR3 pos = GetPosition();

	m_Size.x -= 2.0f;
	m_Size.y -= 2.0f;

	CScene2D::Update();

	m_nAlpha -= 10;

	//m_nGreen = 0;

	//m_nRed = 0;

	SetSize(m_Size);

	SetPosition(pos);

 	SetColor(m_nRed, m_nGreen, m_nBlue, m_nAlpha);

	if (m_nRed < 0)
	{
		m_nRed = 0;
	}
	if (m_nGreen < 0)
	{
		m_nGreen = 0;
	}
	if (m_nBlue < 0)
	{
		m_nBlue = 0;
	}
	if (m_nAlpha < 0)
	{
		m_nAlpha = 0;
	}

	if (m_Size.x <= 0.0f || m_Size.y <= 0.0f)
	{
		m_Size.x = 0.0f;
		m_Size.y = 0.0f;

		Uninit();
		return;
	}

}// �|���S���̍X�V�����I��



//=============================================================================
// �G�t�F�N�g�̕`�揈��
//=============================================================================
void CEffect::Draw(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = NULL;

	CManager*pManager = NULL;

	pDevice = pManager->GetRenderer()->GetDevice();

	//���u�����f�B���O���Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CScene2D::Draw();

	//���u�����f�B���O���Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}	// �|���S���̕`�揈���I��