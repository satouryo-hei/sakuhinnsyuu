//=============================================================================
//
// �e�̔j��̏��� [player.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include"rupture.h"
#include"renderer.h"
#include"manager.h"
#include"bullet _circle.h"

//=============================================================================
// �ÓI�����o�֐��̐錾
//=============================================================================
CBullet* CRupture::m_pBullet[MAX_BULLET] = {};

//=============================================================================
// �e�̔j��̃R���X�g���N�^
//=============================================================================
CRupture::CRupture(int nPriority) : CScene(PRIORITY_PLAYER)
{

}


//=============================================================================
// �e�̔j��̃f�X�g���N�^
//=============================================================================
CRupture::~CRupture()
{

}

//=============================================================================
// �e�̔j��̐�������
//=============================================================================
CRupture *CRupture::Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size, int nNum)
{
	CRupture* pRupture;

	pRupture = new CRupture;

	if (pRupture != NULL)
	{
		pRupture->Init(pos);		
		pRupture->m_Size = Size;
		pRupture->SetRupture(nNum);
	}
	return pRupture;
}

//=============================================================================
// �e�̔j��̏���������
//=============================================================================
HRESULT CRupture::Init(D3DXVECTOR3 pos)
{	
	m_Pos = pos;

	return S_OK;
}	// �v���C���[�̏����������I��



	//=============================================================================
	// �e�̔j��̏I������
	//=============================================================================
void CRupture::Uninit(void)
{
	// ���
	Release();

}// �v���C���[�̏I�������I��


 //=============================================================================
 // �e�̔j��̍X�V����
 //=============================================================================
void CRupture::Update(void)
{


}// �v���C���[�̍X�V�����I��

 //=============================================================================
 // �e�̔j��̕`�揈��
 //=============================================================================
void CRupture::Draw(void)
{

}	// �v���C���[�̕`�揈���I��

	//=============================================================================
	// �e�̔j��̐ݒ菈��
	//=============================================================================
void CRupture::SetRupture(int type)
{
	switch (type)
	{
	case RUPTURE_TYPE_SCOND:
		for (int nCntBullet = 0; nCntBullet < 2; nCntBullet++)
		{
			CBulletCircle::Create(m_Pos, D3DXVECTOR3(10.0f, 10.0f, 0.0f), D3DXVECTOR2(10.0f, 10.0f), 60 * (D3DX_PI / 60) * nCntBullet, true);
		}
		break;
	case RUPTURE_TYPE_FOURTH:		
		for (int nCntBullet = 0; nCntBullet < 4; nCntBullet++)
		{
			CBulletCircle::Create(m_Pos, D3DXVECTOR3(10.0f, 10.0f, 0.0f), D3DXVECTOR2(10.0f, 10.0f), 90 * (D3DX_PI / 180) * nCntBullet, true);
		}
		break;
	case RUPTURE_TYPE_SIXTH:
		for (int nCntBullet = 0; nCntBullet < 6; nCntBullet++)
		{
			CBulletCircle::Create(m_Pos, D3DXVECTOR3(10.0f, 10.0f, 0.0f), D3DXVECTOR2(10.0f, 10.0f), 10 * (D3DX_PI / 30) * nCntBullet, true);
		}
		break;
	case RUPTURE_TYPE_EIGHTH:
		for (int nCntBullet = 0; nCntBullet < 8; nCntBullet++)
		{
			CBulletCircle::Create(m_Pos, D3DXVECTOR3(10.0f, 10.0f, 0.0f), D3DXVECTOR2(10.0f, 10.0f), 15 * (D3DX_PI / 60) * nCntBullet, true);
		}
		break;
	default:
		break;
	}
}