//=============================================================================
//
// �_���̏��� [score.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include "score.h"
#include"number.h"

//=============================================================================
// �_���̃R���X�g���N�^
//=============================================================================
CScore::CScore(int nPriority) : CScene2D(nPriority)
{	
	memset(&m_apNumber[0], NULL, sizeof(m_apNumber));
	m_nScore = 0;
}

//=============================================================================
// �_���̃f�X�g���N�^
//=============================================================================
CScore::~CScore()
{

}

//=============================================================================
// �_���̐�������
//=============================================================================
CScore *CScore::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 Size)
{
	CScore *pScore = NULL;
	pScore = new CScore;

	if (pScore != NULL)
	{
		pScore->Init(pos, Size);		
		pScore->SetScore(0);
	}
	return pScore;
}

//=============================================================================
// �_���̏���������
//=============================================================================
HRESULT CScore::Init(const D3DXVECTOR3 pos, const D3DXVECTOR2 Size)
{
	D3DXVECTOR3 Pos = pos;
	for (int nCntNum = 0; nCntNum < 8; nCntNum++)
	{
		Pos.x += (Size.x * 2);
	
		m_apNumber[nCntNum] = CNumber::Create(Pos, Size);
	}

	m_nScore = 0;

	return S_OK;
}

//=============================================================================
// �_���̏I������
//=============================================================================
void CScore::Uninit(void)
{
	SaveScore();

	for (int nCntNum = 0; nCntNum < 8; nCntNum++)
	{
		if (m_apNumber[nCntNum] != NULL)
		{
			m_apNumber[nCntNum]->Uninit();
			delete m_apNumber[nCntNum];
		}
	}
	Relese();
}

//=============================================================================
// �_���̍X�V����
//=============================================================================
void CScore::Update(void)
{
	CScore::SetScore(m_nScore);
}

//=============================================================================
// �_���̕`�揈��
//=============================================================================
void CScore::Draw(void)
{
	for (int nCntNum = 0; nCntNum < 8; nCntNum++)
	{
		m_apNumber[nCntNum]->Draw();
	}
}

//=============================================================================
// �_���̔z�u����
//=============================================================================
void CScore::SetScore(const int nScore)
{
	m_nScore = nScore;
	
	m_apNumber[0]->SetNumber(m_nScore % 100000000 / 10000000);
	m_apNumber[1]->SetNumber(m_nScore % 10000000 / 1000000);
	m_apNumber[2]->SetNumber(m_nScore % 1000000 / 100000);
	m_apNumber[3]->SetNumber(m_nScore % 100000 / 10000);
	m_apNumber[4]->SetNumber(m_nScore % 10000 / 1000);
	m_apNumber[5]->SetNumber(m_nScore % 1000 / 100);
	m_apNumber[6]->SetNumber(m_nScore % 100 / 10);
	m_apNumber[7]->SetNumber(m_nScore % 10 / 1);	
}

//=============================================================================
// �_���̌v�Z����
//=============================================================================
void CScore::AddScore(const int nValue)
{
	m_nScore += nValue;
}

//=============================================================================
// �_���̏������ݏ���
//=============================================================================
void CScore::SaveScore(void)
{
	FILE *pFile = NULL;

	pFile = fopen(SCORE_TEXT, "w");

	if (pFile != NULL)
	{
		fprintf(pFile, "%d\n", m_nScore);
	}
	else
	{
		printf("�t�@�C�����ǂݍ��܂�܂���ł����B");
	}

	fclose(pFile);
}