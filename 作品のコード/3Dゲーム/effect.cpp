//=============================================================================
//
// �Q�[���̑I���̏��� [effect.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include"effect.h"
#include"renderer.h"
#include"manager.h"
#include"input.h"
#include"polygon.h"
#include"fade.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
CPolygon *CEffect::m_pPolygon[POLYGON_MAX] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEffect::CEffect(PRIORITY Priority) :CScene(PRIORITY_EFFECT)
{
	m_bUse = true;
	m_Size = D3DXVECTOR2(100, 50);
	m_Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_nCnt = 0;
}


//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEffect::~CEffect()
{

}

//=============================================================================
// �Q�[���̑I���̐�������
//=============================================================================
CEffect *CEffect::Create(D3DXVECTOR3 pos)
{
	// �w�i�̃|�C���^�[����
	CEffect* pEffect = NULL;

	// ���I�������̊m��
	pEffect = new CEffect;

	// NULL�`�F�b�N
	if (pEffect != NULL)
	{
		pEffect->Init(pos);
	}
	return pEffect;
}

//=============================================================================
// �Q�[���̑I���̏���������
//=============================================================================
HRESULT CEffect::Init(D3DXVECTOR3 pos)
{
	for (int nCnt = 0; nCnt < POLYGON_MAX; nCnt++)
	{
		m_pPolygon[nCnt] = CPolygon::Create(pos, m_Size,10);
		m_pPolygon[nCnt]->SetAngle(D3DXVECTOR2(0.5f, 1), m_Size);
	}

	return S_OK;
}	// �Q�[���̑I���̏����������̏I��



	//=============================================================================
	// �Q�[���̑I���̏I������
	//=============================================================================
void CEffect::Uninit(void)
{
	//for (int nCnt = 0; nCnt < POLYGON_MAX; nCnt++)
	//{
	//	if (m_pPolygon[nCnt] != NULL)
	//	{
	//		m_pPolygon[nCnt]->SetUse(false);
	//		m_pPolygon[nCnt] = NULL;
	//	}
	//}
	CScene::Release();

}// �Q�[���̑I���̏I�������̏I��


 //=============================================================================
 // �Q�[���̑I���̍X�V����
 //=============================================================================
void CEffect::Update(void)
{
	m_pPolygon[0]->SetUpdateRoll(0.02f,true);
	m_pPolygon[0]->SetUpdateSize(150, 100);
	m_pPolygon[1]->SetUpdateRoll(0.01f, false);

	for (int nCnt = 0; nCnt < POLYGON_MAX; nCnt++)
	{
		m_pPolygon[nCnt]->SetRoll(true);
		//m_pPolygon[nCnt]->SetColor(m_Col);
	}
}// �Q�[���̑I���̍X�V�����I��



 //=============================================================================
 // �Q�[���̑I���̕`�揈��
 //=============================================================================
void CEffect::Draw(void)
{

}	// �Q�[���̑I���̕`�揈���I��

void CEffect::SetColor(D3DXCOLOR Col,int nNum)
{
	m_pPolygon[nNum]->SetColor(Col);	
}

void CEffect::Setpos(D3DXVECTOR3 pos)
{
	for (int nCnt = 0; nCnt < POLYGON_MAX; nCnt++)
	{
		m_pPolygon[nCnt]->SetPosition(pos);
	}
}