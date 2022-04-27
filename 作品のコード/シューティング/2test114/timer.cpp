//=============================================================================
//
// ���Ԃ̏��� [score.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include "timer.h"
#include"number.h"

// �ÓI�����o�ϐ��̐錾
int CTimer::m_nTimer = 0;

//=============================================================================
// ���Ԃ̃R���X�g���N�^
//=============================================================================
CTimer::CTimer(int nPriority) : CScene2D(nPriority)
{
	memset(&m_apNumber[0], NULL, sizeof(m_apNumber));
	m_nCntTimer = 0;
}

//=============================================================================
// ���Ԃ̃f�X�g���N�^
//=============================================================================
CTimer::~CTimer()
{

}

//=============================================================================
// ���Ԃ̐�������
//=============================================================================
CTimer *CTimer::Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	CTimer *pTimer = NULL;
	pTimer = new CTimer;

	if (pTimer != NULL)
	{
		pTimer->Init(pos, Size);
		pTimer->SetTimer(0);
	}
	return pTimer;
}

//=============================================================================
// ���Ԃ̏���������
//=============================================================================
HRESULT CTimer::Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	D3DXVECTOR3 Pos = pos;
	for (int nCntNum = 0; nCntNum < 8; nCntNum++)
	{
		Pos.x += (Size.x * 2);

		m_apNumber[nCntNum] = CNumber::Create(Pos, Size);
	}

	m_nTimer = 0;

	m_nCntTimer = 0;

	return S_OK;
}

//=============================================================================
// ���Ԃ̏I������
//=============================================================================
void CTimer::Uninit(void)
{
	SeveTimer(m_nTimer);

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
// ���Ԃ̍X�V����
//=============================================================================
void CTimer::Update(void)
{
	m_nCntTimer++;

	if (m_nCntTimer % 60 == 0)
	{
		m_nTimer++;
	}

	CTimer::SetTimer(m_nTimer);

}

//=============================================================================
// ���Ԃ̕`�揈��
//=============================================================================
void CTimer::Draw(void)
{
	for (int nCntNum = 0; nCntNum < 8; nCntNum++)
	{
		m_apNumber[nCntNum]->Draw();
	}
}

//=============================================================================
// ���Ԃ̔z�u����
//=============================================================================
void CTimer::SetTimer(int nTimer)
{
	m_nTimer = nTimer;

	m_apNumber[0]->SetNumber(m_nTimer % 100000000 / 10000000);
	m_apNumber[1]->SetNumber(m_nTimer % 10000000 / 1000000);
	m_apNumber[2]->SetNumber(m_nTimer % 1000000 / 100000);
	m_apNumber[3]->SetNumber(m_nTimer % 100000 / 10000);
	m_apNumber[4]->SetNumber(m_nTimer % 10000 / 1000);
	m_apNumber[5]->SetNumber(m_nTimer % 1000 / 100);
	m_apNumber[6]->SetNumber(m_nTimer % 100 / 10);
	m_apNumber[7]->SetNumber(m_nTimer % 10 / 1);
}

//=============================================================================
// ���Ԃ̕ۑ�����
//=============================================================================
void CTimer::SeveTimer(int nTime)
{
	// ���݂̎��Ԃ�ۑ�

	FILE *pFile = fopen(TIMETEXT, "w");

	if (pFile != NULL)
	{
		fprintf(pFile, "%d", nTime);
	}
	else
	{
		printf("�t�@�C�����ǂݍ��܂�܂���ł����B");
	}

	fclose(pFile);
}

//=============================================================================
// ���Ԃ̓ǂݍ��ݏ���
//=============================================================================
int CTimer::LodeTimer(void)
{
	int nTime = 0;

	// ���݂̎��Ԃ�ǂݍ���

	FILE *pFile = fopen(TIMETEXT, "r");

	if (pFile != NULL)
	{
		fscanf(pFile, "%d", &nTime);
	}
	else
	{
		printf("�t�@�C�����ǂݍ��܂�܂���ł����B");
	}

	fclose(pFile);

	return nTime;
}