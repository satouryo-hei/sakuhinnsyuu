//=============================================================================
//
// �����̏��� [explosion.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include"explosion.h"
#include"renderer.h"
#include"manager.h"

// �ÓI�����o�ϐ��̐錾
LPDIRECT3DTEXTURE9 CExplosion::m_pTexture = NULL;

//=============================================================================
// �����̃R���X�g���N�^
//=============================================================================
CExplosion::CExplosion(int nPriority) : CScene2D(nPriority)
{	
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
}


//=============================================================================
// �����̃f�X�g���N�^
//=============================================================================
CExplosion::~CExplosion()
{

}


//=============================================================================
// �����̐�������
//=============================================================================
CExplosion *CExplosion::Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	CExplosion* pExplosion;

	pExplosion = new CExplosion;

	if (pExplosion != NULL)
	{
		pExplosion->Init(pos, Size);
		pExplosion->BindTextuer(m_pTexture);
	}
	return pExplosion;
}

//=============================================================================
// �e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CExplosion::Load(void)
{
	CManager *pManager = NULL;

	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/ex000.png",
		&m_pTexture);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���̔j��
//=============================================================================
void CExplosion::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// �����̏���������
//=============================================================================
HRESULT CExplosion::Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	CScene2D::Init(pos, Size);
	CScene2D::SetTexAnime(m_nPatternAnim,0.125f);

	return S_OK;
}	// �|���S���̏����������I��



//=============================================================================
// �����̏I������
//=============================================================================
void CExplosion::Uninit(void)
{
	CScene2D::Uninit();

}// �|���S���̏I�������I��


//=============================================================================
// �����̍X�V����
//=============================================================================
void CExplosion::Update(void)
{
	D3DXVECTOR3 pos = GetPosition();
	
	CScene2D::Update();

	SetPosition(pos);

	m_nCounterAnim++;

	if (m_nCounterAnim % 4 == 0)
	{
		m_nPatternAnim++;

		CScene2D::SetTexAnime(m_nPatternAnim,0.125f);

		if (m_nPatternAnim >= 8)
		{
			Uninit();
			return;
		}
	}


}// �|���S���̍X�V�����I��



 //=============================================================================
 // �����̕`�揈��
 //=============================================================================
void CExplosion::Draw(void)
{
	CScene2D::Draw();

}	// �|���S���̕`�揈���I��