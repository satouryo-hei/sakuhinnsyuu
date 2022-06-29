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
CScore::CScore(PRIORITY nPriority) : CScene2D(nPriority)
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
	// �_���̃|�C���^�[����
	CScore *pScore = NULL;

	// ���I�������̊m��
	pScore = new CScore;

	// NULL�`�F�b�N
	if (pScore != NULL)
	{
		// �_���̏����������̌Ăяo��
		pScore->Init(pos, Size);
		// �_���̐ݒ菈���̌Ăяo��
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

	// NUMSCORE����
	for (int nCntNum = 0; nCntNum < NUMSCORE; nCntNum++)
	{	
		// �i���o�[�̐��������̌Ăяo��
		m_apNumber[nCntNum] = CNumber::Create(Pos, Size, 5);
		Pos.x += (Size.x * 2);
	}

	return S_OK;
}

//=============================================================================
// �_���̏I������
//=============================================================================
void CScore::Uninit(void)
{
	// �X�R�A�̏������ݏ���
	SaveScore();

	// NUMSCORE����
	for (int nCntNum = 0; nCntNum < NUMSCORE; nCntNum++)
	{
		// NULL�`�F�b�N
		if (m_apNumber[nCntNum] != NULL)
		{
			// �i���o�[�̏I�������̌Ăяo��
			m_apNumber[nCntNum]->Uninit();
			delete m_apNumber[nCntNum];
		}
	}
	// �������
	Release();
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
	// NUMSCORE����
	for (int nCntNum = 0; nCntNum < NUMSCORE; nCntNum++)
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

	static const int nData = 10;

	int nNum = NUMSCORE;
	int iNum = NUMSCORE - 1;

	// NUMSCORE����
	for (int nCnt = 0; nCnt < NUMSCORE; nCnt++, nNum--, iNum--)
	{		
		m_apNumber[nCnt]->SetNumber(m_nScore % Exponentiation(nData, nNum) / Exponentiation(nData, iNum));
	}	
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
	FILE * pFile = NULL;

	pFile = fopen(SCORE_TEXT, "w");

	// NULL�`�F�b�N
	if (pFile != NULL)
	{
		fprintf(pFile, "%d\n", m_nScore);
	}
	else
	{
		printf("�t�@�C�����ǂݍ��܂�܂���ł����B");
	}

	fclose(pFile);

	m_nScore = 0;
}