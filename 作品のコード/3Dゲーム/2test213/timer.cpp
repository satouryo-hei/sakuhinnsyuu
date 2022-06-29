//=============================================================================
//
// ���Ԃ̏��� [score.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include "timer.h"
#include"number.h"
#include"polygon.h"
#include"fade.h"

//=============================================================================
// �ÓI�����o�ϐ��̐錾
//=============================================================================
int CTimer::m_nTimer = 0;
CPolygon * CTimer::m_apPolygon = NULL;

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
	// ���Ԃ̃|�C���^�[����
	CTimer *pTimer = NULL;

	// ���I�������̊m��
	pTimer = new CTimer;

	// NULL�`�F�b�N
	if (pTimer != NULL)
	{
		// ���Ԃ̏����������̌Ăяo��
		pTimer->Init(pos, Size);		
		pTimer->m_nTimer = 60;

		// ���Ԃ̐ݒ菈���̌Ăяo��
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
	m_apPolygon = CPolygon::Create(pos, Size,18);

	// MAX_TIME����
	for (int nCntNum = 0; nCntNum < MAX_TIME; nCntNum++)
	{
		Pos.x += (Size.x * 2);
		// �i���o�[�̐��������̌Ăяo��
		m_apNumber[nCntNum] = CNumber::Create(Pos, Size, 5);
	}
	return S_OK;
}

//=============================================================================
// ���Ԃ̏I������
//=============================================================================
void CTimer::Uninit(void)
{
	// ���Ԃ̏����o�������̌Ăяo��
	SeveTimer(m_nTimer);

	// MAX_TIME����
	for (int nCntNum = 0; nCntNum < MAX_TIME; nCntNum++)
	{
		// NULL�`�F�b�N
		if (m_apNumber[nCntNum] != NULL)
		{
			// �i���o�[�̏I�������̌Ăяo��
			m_apNumber[nCntNum]->Uninit();
			m_apNumber[nCntNum] = NULL;
		}
	}
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

	if (m_nTimer >= 30)
	{
		// MAX_TIME����
		for (int nCntNum = 0; nCntNum < MAX_TIME; nCntNum++)
		{
			m_apNumber[nCntNum]->SetColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
		}
	}
	else if (m_nTimer <= 30 && m_nTimer > 10)
	{
		// MAX_TIME����
		for (int nCntNum = 0; nCntNum < MAX_TIME; nCntNum++)
		{
			m_apNumber[nCntNum]->SetColor(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
		}
	}
	else if (m_nTimer <= 10 && m_nTimer > 0)
	{
		// MAX_TIME����
		for (int nCntNum = 0; nCntNum < MAX_TIME; nCntNum++)
		{
			m_apNumber[nCntNum]->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		}
	}
	else if (m_nTimer < 0)
	{
		m_nTimer = 0;
		
		// ���U���g�ɑJ��
		CFade::SetFade(CManager::MODE_RESULT);		
	}

	// ���Ԃ̃e�N�X�`���z�u����
	CTimer::SetTimer(m_nTimer);

}

//=============================================================================
// ���Ԃ̕`�揈��
//=============================================================================
void CTimer::Draw(void)
{
	// MAX_TIME����
	for (int nCntNum = 0; nCntNum < MAX_TIME; nCntNum++)
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

	static const int nData = 10;

	int nNum = MAX_TIME;
	int iNum = MAX_TIME - 1;

	// MAX_TIME����
	for (int nCnt = 0; nCnt < MAX_TIME; nCnt++,nNum--,iNum--)
	{		
		m_apNumber[nCnt]->SetNumber(m_nTimer % Exponentiation(nData, nNum) / Exponentiation(nData, iNum));
	}
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