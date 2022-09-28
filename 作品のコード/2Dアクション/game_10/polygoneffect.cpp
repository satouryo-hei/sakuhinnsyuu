//=============================================================================
//
//  2D�G�t�F�N�g�̏��� [effect.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include"polygoneffect.h"
#include"renderer.h"
#include"manager.h"
#include"polygon.h"
#include"input.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
CPolygon *CPolygonEffect::m_pPolygon[POLYGON_MAX] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPolygonEffect::CPolygonEffect(PRIORITY Priority) :CScene(PRIORITY_EFFECT)
{
	m_Size = D3DXVECTOR2(100, 50);
}


//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPolygonEffect::~CPolygonEffect()
{

}

//=============================================================================
// 2D�G�t�F�N�g�̐�������
//=============================================================================
CPolygonEffect *CPolygonEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	// 2D�G�t�F�N�g�̃|�C���^�[����
	CPolygonEffect* pEffect = NULL;

	// ���I�������̊m��
	pEffect = new CPolygonEffect;

	// NULL�`�F�b�N
	if (pEffect != NULL)
	{
		pEffect->m_Size = size;
		// 2D�G�t�F�N�g�̏���������
		pEffect->Init(pos);
	}
	return pEffect;
}

//=============================================================================
//  2D�G�t�F�N�g�̏���������
//=============================================================================
HRESULT CPolygonEffect::Init(D3DXVECTOR3 pos)
{
	// POLYGON_MAX����
	for (int nCnt = 0; nCnt < POLYGON_MAX; nCnt++)
	{
		// �|���S���̐�������
		m_pPolygon[nCnt] = CPolygon::Create(pos, m_Size, 100);

		// �|���S���̎Εӂ̐ݒ菈��
		m_pPolygon[nCnt]->SetAngle(D3DXVECTOR2(0.5f, 1), m_Size);
	}

	return S_OK;
}	//  2D�G�t�F�N�g�̏����������̏I��



	//=============================================================================
	//  2D�G�t�F�N�g�̏I������
	//=============================================================================
void CPolygonEffect::Uninit(void)
{
	// POLYGON_MAX����
	for (int nCnt = 0; nCnt < POLYGON_MAX; nCnt++)
	{
		if (m_pPolygon[nCnt] != NULL)
		{
			m_pPolygon[nCnt]->SetUse(false);
			m_pPolygon[nCnt] = NULL;
		}

	}
	// �V�[���̉������
	CScene::Release();

}// 2D�G�t�F�N�g�̏I�������̏I��


 //=============================================================================
 //  2D�G�t�F�N�g�̍X�V����
 //=============================================================================
void CPolygonEffect::Update(void)
{
	// �|���S���̉�]�̍X�V����
	m_pPolygon[POLYGON_BACK]->SetRolling(0.02f, D3DX_PI / 2.5, D3DX_PI / 1.5);

	// �|���S���̊g��k���̍X�V����
	m_pPolygon[POLYGON_BACK]->SetUpdateSize(150, 100);

	// �|���S���̉�]�̍X�V����
	m_pPolygon[POLYGON_BEFORE]->SetUpdateRoll(0.01f, false);

	// POLYGON_MAX����
	for (int nCnt = 0; nCnt < POLYGON_MAX; nCnt++)
	{
		// ��]�����邩�ǂ���
		m_pPolygon[nCnt]->SetRoll(true);		
	}
}// 2D�G�t�F�N�g�̍X�V�����I��



 //=============================================================================
 // 2D�G�t�F�N�g�̕`�揈��
 //=============================================================================
void CPolygonEffect::Draw(void)
{

}	// 2D�G�t�F�N�g�̕`�揈���I��

	//=============================================================================
	// 2D�G�t�F�N�g�̐F�ݒ菈��
	//=============================================================================
void CPolygonEffect::SetColor(D3DXCOLOR Col, int nNum)
{
	m_pPolygon[nNum]->SetColor(Col);
}

//=============================================================================
// 2D�G�t�F�N�g�̒��_���Ƃ̐F�ݒ菈��
//=============================================================================
void CPolygonEffect::SetVtxBuffColor(D3DXCOLOR Col, int nNum, int nVtxBuff)
{
	// ���Ԗڂ̃|���S���̂ǂ��̒��_�̐F��ς��邩
	m_pPolygon[nNum]->SetVtxBuffColor(Col, nVtxBuff);
}

//=============================================================================
// 2D�G�t�F�N�g�̈ʒu�ݒ菈��
//=============================================================================
void CPolygonEffect::SetPos(D3DXVECTOR3 pos)
{
	// POLYGON_MAX����
	for (int nCnt = 0; nCnt < POLYGON_MAX; nCnt++)
	{
		// �|���S���̈ʒu�̐ݒ菈�����Ăяo��
		m_pPolygon[nCnt]->SetPosition(pos);
	}
}