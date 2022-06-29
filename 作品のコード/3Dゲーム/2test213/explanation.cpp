//=============================================================================
//
//  2D�G�t�F�N�g�̏��� [effect.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include"explanation.h"
#include"renderer.h"
#include"manager.h"
#include"input.h"
#include"polygon.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
CPolygon *CExplanation::m_pPolygon[EXPLANATION_MAX] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CExplanation::CExplanation(PRIORITY Priority) :CScene(PRIORITY_EFFECT)
{
	m_Size = D3DXVECTOR2(100, 50);
	m_Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}


//=============================================================================
// �f�X�g���N�^
//=============================================================================
CExplanation::~CExplanation()
{

}

//=============================================================================
// 2D�G�t�F�N�g�̐�������
//=============================================================================
CExplanation *CExplanation::Create(D3DXVECTOR3 pos, int nTex)
{
	// �w�i�̃|�C���^�[����
	CExplanation* pExplanation = NULL;

	// ���I�������̊m��
	pExplanation = new CExplanation;

	// NULL�`�F�b�N
	if (pExplanation != NULL)
	{
		pExplanation->m_nTex = nTex;
		pExplanation->Init(pos);
	}
	return pExplanation;
}

//=============================================================================
//  2D�G�t�F�N�g�̏���������
//=============================================================================
HRESULT CExplanation::Init(D3DXVECTOR3 pos)
{	
	m_pPolygon[EXPLANATION_SPEECH_BUBBLE] = CPolygon::Create(pos, m_Size, 23);

	for (int nCnt = 1; nCnt < EXPLANATION_MAX; nCnt++)
	{
		m_pPolygon[nCnt] = CPolygon::Create(pos, m_Size, m_nTex+ nCnt);
	}

	return S_OK;
}	//  2D�G�t�F�N�g�̏����������̏I��



	//=============================================================================
	//  2D�G�t�F�N�g�̏I������
	//=============================================================================
void CExplanation::Uninit(void)
{
	for (int nCnt = 0; nCnt < EXPLANATION_MAX; nCnt++)
	{
		if (m_pPolygon[nCnt] != NULL)
		{
			m_pPolygon[nCnt]->SetUse(false);
			m_pPolygon[nCnt] = NULL;
		}
	}
	CScene::Release();

}// 2D�G�t�F�N�g�̏I�������̏I��


 //=============================================================================
 //  2D�G�t�F�N�g�̍X�V����
 //=============================================================================
void CExplanation::Update(void)
{

}// 2D�G�t�F�N�g�̍X�V�����I��



 //=============================================================================
 // 2D�G�t�F�N�g�̕`�揈��
 //=============================================================================
void CExplanation::Draw(void)
{

}	// 2D�G�t�F�N�g�̕`�揈���I��

	//=============================================================================
	// 2D�G�t�F�N�g�̑傫���ݒ菈��
	//=============================================================================
void CExplanation::SetSize(D3DXVECTOR2 Size, int nNum)
{
	m_pPolygon[nNum]->SetSize(Size);
}

//=============================================================================
// 2D�G�t�F�N�g�̐F�ݒ菈��
//=============================================================================
void CExplanation::SetColor(D3DXCOLOR Col, int nNum)
{
	m_pPolygon[nNum]->SetColor(Col);	
}