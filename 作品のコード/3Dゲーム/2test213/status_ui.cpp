//=============================================================================
//
// �X�e�[�^�X��UI�̏��� [result.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include "status_ui.h"
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"bg.h"
#include"fade.h"
#include"ranking.h"
#include"polygon.h"
#include"number.h"

//=============================================================================
// �ÓI�����o�ϐ��̐錾
//=============================================================================
CPolygon * CStatus_UI::m_pPolygon[3] = {};
CNumber * CStatus_UI::m_apNumber[2] = {};
const char * CStatus_UI::m_pStatusUIFlieName = "data/TEXT/StatusUI.txt";
const int CStatus_UI::m_nStatusNumber = 2;

//=============================================================================
// �X�e�[�^�X��UI�̃R���X�g���N�^
//=============================================================================
CStatus_UI::CStatus_UI(int nPriority) : CScene(PRIORITY_NOMAL)
{
	m_nStatus = 0;
}

//=============================================================================
// �X�e�[�^�X��UI�̃f�X�g���N�^
//=============================================================================
CStatus_UI::~CStatus_UI()
{

}

//=============================================================================
// �X�e�[�^�X��UI�̏���������
//=============================================================================
CStatus_UI *CStatus_UI::Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	// �����L���O�̃|�C���^�[����
	CStatus_UI * pStatus_UI = NULL;

	// ���I�������̊m��
	pStatus_UI = new CStatus_UI;

	// �����L���O�ɂȂɂ��������Ă�����
	if (pStatus_UI != NULL)
	{
		pStatus_UI->m_Size = Size;	// �����L���O�̑傫����ݒ�
		pStatus_UI->Init(pos);	// �����L���O�̏���������
	}
	return pStatus_UI;
}

//=============================================================================
// �X�e�[�^�X��UI�̏���������
//=============================================================================
HRESULT CStatus_UI::Init(D3DXVECTOR3 pos)
{
	D3DXVECTOR3 Pos = pos;

	// UI�̓ǂݍ��ݏ����̌Ăяo��
	LodeStatusUI();

	// STAUI_MAX����
	for (int nCnt = 0; nCnt < STAUI_MAX; nCnt++)
	{
		// �|���S���̐����̌Ăяo��
		m_pPolygon[nCnt] = CPolygon::Create(m_LodePos[nCnt], m_LodeSize[nCnt], nCnt + 14);
	}

	// m_nStatusNumber����
	for (int nCnt = 0; nCnt < m_nStatusNumber; nCnt++)
	{
		// �i���o�[�̐��������̌Ăяo��
		m_apNumber[nCnt] = CNumber::Create(Pos, m_Size, 5);
		Pos.x += (m_Size.x * m_nStatusNumber);
		
	}
	return S_OK;
}

//=============================================================================
// �X�e�[�^�X��UI�̏I������
//=============================================================================
void CStatus_UI::Uninit(void)
{
	// m_nStatusNumber����
	for (int nCntNum = 0; nCntNum < m_nStatusNumber; nCntNum++)
	{
		// NULL�`�F�b�N
		if (m_apNumber[nCntNum] != NULL)
		{
			// �i���o�[�̏I�������̌Ăяo��
			m_apNumber[nCntNum]->Uninit();
			m_apNumber[nCntNum] = NULL;
		}
	}
	// �������
	CScene::Release();
}

//=============================================================================
// �X�e�[�^�X��UI�̍X�V����
//=============================================================================
void CStatus_UI::Update(void)
{

}

//=============================================================================
// �X�e�[�^�X��UI�̕`�揈��
//=============================================================================
void CStatus_UI::Draw(void)
{
	// m_nStatusNumber����
	for (int nCntNum = 0; nCntNum < m_nStatusNumber; nCntNum++)
	{
		m_apNumber[nCntNum]->Draw();
	}
}

//=============================================================================
// �X�e�[�^�X��UI�̃i���o�[�̔z�u����
//=============================================================================
void CStatus_UI::SetStatusNumber(const int nStatus)
{
	m_nStatus = nStatus;

	static const int nData = 10;

	int nNum = m_nStatusNumber;
	int iNum = m_nStatusNumber - 1;

	// m_nStatusNumber����
	for (int nCnt = 0; nCnt < m_nStatusNumber; nCnt++, nNum--, iNum--)
	{
		m_apNumber[nCnt]->SetNumber(m_nStatus % Exponentiation(nData, nNum) / Exponentiation(nData, iNum));
	}
}

//=============================================================================
// UI�̓ǂݍ��ݏ���
//=============================================================================
void CStatus_UI::LodeStatusUI(void)
{
	// �J���`�t�@�C���I
	FILE *pFile = fopen(m_pStatusUIFlieName, "r");
	//--------------------------
	// �ǂݍ��ޗp�̕ϐ�
	//--------------------------
	char aFile[3][128] = {};
	char aName[128] = {};
	int nSetCnt = 0;
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR2 size = D3DXVECTOR2(0.0f, 0.0f);
	int nLodeUI = 0;

	// �t�@�C������������
	if (pFile != NULL)
	{
		// �������[�v
		while (1)
		{
			fscanf(pFile, "%s", &aFile[0][0]);										// 1���ǂݍ���(2�s�ڈȍ~�͏㏑�������)

			if (strcmp(&aFile[0][0], "NUM_UI") == 0)								// NUM_UI������������
			{
				fscanf(pFile, "%s%d", &aName[0], &nLodeUI);						// UI�̐���ǂݍ���
			}

			while (strcmp(&aFile[0][0], "SETUI") == 0)								// SETUI������������
			{
				fscanf(pFile, "%s", &aFile[1]);										// 1���ǂݍ���(2�s�ڈȍ~�͏㏑�������)
				if (strcmp(&aFile[1][0], "POS") == 0)								// POS������������
				{
					fscanf(pFile, "%s%f%f%f", &aName[0], &pos.x, &pos.y, &pos.z);	// ���݂̈ʒu��ǂݍ���
				}
				else if (strcmp(&aFile[1][0], "SIZE") == 0)							// SIZE������������
				{
					fscanf(pFile, "%s%f%f", &aName[0], &size.x, &size.y);			// ���݂̑傫����ǂݍ���
				}
				else if (strcmp(&aFile[1][0], "END_SETUI") == 0)					// END_SETUI������������
				{
					m_LodePos[nSetCnt] = pos;										// �ǂݍ��񂾈ʒu���������o��SetPos�Ɉڂ�
					m_LodeSize[nSetCnt] = size;										// �ǂݍ��񂾑傫�����������o��SetSize�Ɉڂ�
					nSetCnt++;														// ���̕�
					break;															// �������[�v�𔲂���
				}
			}
			if (strcmp(&aFile[0][0], "END_SCRIPT") == 0)							// END_SCRIPT������������
			{
				break;																// �������[�v�𔲂���
			}
		}
	}
	else
	{
		printf("�t�@�C�����ǂݍ��܂�܂���ł����B");
	}

	// ����`�t�@�C���I
	fclose(pFile);
}


