//=============================================================================
//
// �����̏��� [explosion.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include"explosion.h"
#include"renderer.h"
#include"manager.h"

//=============================================================================
// �����̃R���X�g���N�^
//=============================================================================
CExplosion::CExplosion(int nPriority) : CScene2D(PRIORITY_EFFECT)
{	
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
	m_bUse = true;
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
CExplosion *CExplosion::Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size,int nTex)
{
	CExplosion* pExplosion = NULL;

	// �|�C���^�[�̓��I�������̊m��
	pExplosion = new CExplosion;

	//NULL�`�F�b�N
	if (pExplosion != NULL)
	{
		// �����������̌Ăяo��
		pExplosion->Init(pos, Size);

		// �e�N�X�`���̐ݒ菈��
		pExplosion->Bindtexture(nTex);
	}
	return pExplosion;
}

//=============================================================================
// �����̏���������
//=============================================================================
HRESULT CExplosion::Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	// �����������̌Ăяo��
	CScene2D::Init(pos, Size);
	// �A�j���[�V�����e�N�X�`���̐ݒ�
	CScene2D::SetTexAnime(m_nPatternAnim,0.125f,0,1);

	return S_OK;
}	// �|���S���̏����������I��



//=============================================================================
// �����̏I������
//=============================================================================
void CExplosion::Uninit(void)
{
	//CScene2D::Uninit();
	Release();

}// �|���S���̏I�������I��


//=============================================================================
// �����̍X�V����
//=============================================================================
void CExplosion::Update(void)
{
	// �g���Ă��Ȃ�������
	if (!m_bUse)
	{
		Uninit();
		return;
	}

	D3DXVECTOR3 pos = GetPosition();

	m_nCounterAnim++;

	if (m_nCounterAnim % 4 == 0)
	{
		m_nPatternAnim++;

		CScene2D::SetTexAnime(m_nPatternAnim,0.125f, 0, 1);

		if (m_nPatternAnim >= 8)
		{
			m_nPatternAnim = 0;
			m_bUse = false;
		}
	}

	SetPosition(pos);
	CScene2D::Update();
}// �|���S���̍X�V�����I��



 //=============================================================================
 // �����̕`�揈��
 //=============================================================================
void CExplosion::Draw(void)
{
	CScene2D::Draw();

}	// �|���S���̕`�揈���I��