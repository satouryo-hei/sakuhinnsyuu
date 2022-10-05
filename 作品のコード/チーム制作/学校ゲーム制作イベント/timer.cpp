//=============================================================================
//
// ���Ԃ̏��� [score.cpp]
// Author : �����ĕ�
// Author : �ؖr�_
//
//=============================================================================
#include "timer.h"
#include"number.h"
#include "fade.h"

//=============================================================================
// �ÓI�����o�֐��̐錾
//=============================================================================
int CTimer::m_nTimer = 0;

//=============================================================================
// ���Ԃ̃R���X�g���N�^
//=============================================================================
CTimer::CTimer(int nPriority) : CScene2D(PRIORITY_UI)
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
		pTimer->m_nTimer = 60;
		pTimer->SetTimer(m_nTimer);
	}
	return pTimer;
}

//=============================================================================
// ���Ԃ̏���������
//=============================================================================
HRESULT CTimer::Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	D3DXVECTOR3 Pos = pos;
	for (int nCntNum = 0; nCntNum < MAX_TIME; nCntNum++)
	{
		Pos.x += (Size.x * 2);

		m_apNumber[nCntNum] = CNumber::Create(Pos, Size, 3);
	}
	return S_OK;
}

//=============================================================================
// ���Ԃ̏I������
//=============================================================================
void CTimer::Uninit(void)
{
	SaveTimer(m_nTimer);
	Release();
}

//=============================================================================
// ���Ԃ̍X�V����
//=============================================================================
void CTimer::Update(void)
{
	m_nCntTimer++;

	if (m_nCntTimer % 60 == 0)
	{
		m_nTimer--;
	}
	if (m_nTimer < 0)
	{
		m_nTimer = 0;
		CFade::SetFade(CManager::MODE_RESULT);
	}
	CTimer::SetTimer(m_nTimer);

}

//=============================================================================
// ���Ԃ̕`�揈��
//=============================================================================
void CTimer::Draw(void)
{
	for (int nCntNum = 0; nCntNum < MAX_TIME; nCntNum++)
	{
		m_apNumber[nCntNum]->Draw();
	}
}

//=============================================================================
// ���Ԃ̐ݒ菈��
//=============================================================================
void CTimer::SetTimer(int nTimer)
{	
	static const int nData = 10;

	int nNum = MAX_TIME;
	int iNum = MAX_TIME - 1;

	// NUMSCORE����
	for (int nCnt = 0; nCnt < MAX_TIME; nCnt++, nNum--, iNum--)
	{		
		m_apNumber[nCnt]->SetNumber(nTimer % Exponentiation(nData, nNum) / Exponentiation(nData, iNum));
	}	

}


//=============================================================================
// ���Ԃ̓ǂݍ��ݏ���
//=============================================================================
int CTimer::LodeTimer()
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


//=============================================================================
// ���Ԃ̏������ݏ���
//=============================================================================
void CTimer::SaveTimer(const int nTime)
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