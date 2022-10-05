//=============================================================================
//
// �X�e�[�W���� [bg.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include"stage_tutorial.h"
#include"renderer.h"
#include"manager.h"
#include"block.h"
#include"moveblock.h"
#include"noneblock.h"
#include"pushblock.h"
#include"goal.h"

//=============================================================================
// �ÓI�����o�֐��̐錾
//=============================================================================
CBlock* CStage_Tutorial::m_pBlock[256] = {};

CGoal * CStage_Tutorial::m_pGoal = NULL;
CMoveBlock * CStage_Tutorial::m_pMove[128] = {};
CPushBlock * CStage_Tutorial::m_pPush[128] = {};
const char * CStage_Tutorial::m_pTutorial_StageFileName = "data/STAGE/stazi_test.csv";
//=============================================================================
// �X�e�[�W�̃R���X�g���N�^
//=============================================================================
CStage_Tutorial::CStage_Tutorial(int nPriority) : CScene(PRIORITY_NOMAL)
{	
	m_nNum = 0;
}

//=============================================================================
// �X�e�[�W�̃f�X�g���N�^
//=============================================================================
CStage_Tutorial::~CStage_Tutorial()
{

}

//=============================================================================
// �X�e�[�W�̐�������
//=============================================================================																				
CStage_Tutorial *CStage_Tutorial::Create(D3DXVECTOR3 pos)
{
	CStage_Tutorial* pStage_Tutorial;

	pStage_Tutorial = new CStage_Tutorial;

	if (pStage_Tutorial !=NULL)
	{
		pStage_Tutorial->Init(pos);
	}

	return pStage_Tutorial;
}

//=============================================================================
// �X�e�[�W�̏���������
//=============================================================================
HRESULT CStage_Tutorial::Init(D3DXVECTOR3 pos)
{
	int nNoneCnt = 0;
	int nMoveCnt = 0;
	int nPushCnt = 0;

	LodeStage();	

	for (int nCntY = 0; nCntY < m_nColumn; nCntY++)
	{
		for (int nCntX = 0; nCntX < m_nLine; nCntX++)
		{
			if (m_aMap[nCntY][nCntX] == 1)
			{
				m_pBlock[m_nNum] = CBlock::Create(D3DXVECTOR3(20 + 40 * nCntX, -20 + 40 * nCntY, 0), D3DXVECTOR2(20, 20), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					CBlock::BLOCKTYPE_NOME, 0, 0, 0, false, 7);
				m_nNum++;
			}

			if (m_aMap[nCntY][nCntX] == 2)
			{
				m_pBlock[m_nNum] = CBlock::Create(D3DXVECTOR3(20 + 40 * nCntX, -20 + 40 * nCntY, 0), D3DXVECTOR2(20, 20), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					CBlock::BLOCKTYPE_NOME, 0, 0, 0, true, 7);
				m_nNum++;
			}
			if (m_aMap[nCntY][nCntX] == 3)
			{
				m_pBlock[m_nNum] = CBlock::Create(D3DXVECTOR3(30 + 60 * nCntX, 0 + 60 * nCntY, 0), D3DXVECTOR2(30, 60), D3DXVECTOR3(1.0f, 1.0f, 0.0f),
					CBlock::BLOCKTYPE_MOVEING, CMoveBlock::MOVE_LEFT, 600, 800, false, 7);
				m_nNum++;
			}
			if (m_aMap[nCntY][nCntX] == 4)
			{				
				m_pBlock[m_nNum] = CBlock::Create(D3DXVECTOR3(20 + 40 * nCntX, -20 + 40 * nCntY, 0), D3DXVECTOR2(60, 30), D3DXVECTOR3(0.0f, 1.0f, 0.0f),
					CBlock::BLOCKTYPE_MOVEING, CMoveBlock::MOVE_UP, 100, 300, false, 7);
				m_nNum++;
			}
			if (m_aMap[nCntY][nCntX] == 5)
			{
				m_pBlock[m_nNum] = CBlock::Create(D3DXVECTOR3(20 + 40 * nCntX, 60 * nCntY, 0), D3DXVECTOR2(50, 20), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					CBlock::BLOCKTYPE_PUSH, 0, 600, 800, false, 7);
				m_nNum++;
			}			
		}
	}

	m_pGoal = CGoal::Create(D3DXVECTOR3(1020.0f, 630.0f, 0.0f), D3DXVECTOR2(100.0f, 50.0f), CManager::MODE_SELECT);	

	return S_OK;
}

//=============================================================================
// �X�e�[�W�̏I������
//=============================================================================
void CStage_Tutorial::Uninit(void)
{
	Release();
}

//=============================================================================
// �X�e�[�W�̍X�V����
//=============================================================================
void CStage_Tutorial::Update(void)
{

}

//=============================================================================
// �X�e�[�W�̕`�揈��
//=============================================================================
void CStage_Tutorial::Draw(void)
{

}

//=============================================================================
// �X�e�[�W�̕`�揈��
//=============================================================================
void CStage_Tutorial::LodeStage(void)
{	
	// �J���`�t�@�C���I
	FILE *pFile = fopen(m_pTutorial_StageFileName, "r");

	// �t�@�C������������
	if (pFile != NULL)
	{
		int nCntX = 0, nCntY = 0;
		char aLine[128];
		//char *fgets(char *s, int n, FILE *fp); n�͍ő吔��(n-1)�����-1�̐��l��NULL(\0)���܂܂�邽��
		while (fgets(aLine, sizeof(aLine), pFile) != NULL)
		{
			nCntX = 0;
			// ����̃g�[�N��[,.]�Ȃǂŋ�؂�
			char *pKanma = strtok(aLine, ",");
			while (pKanma != NULL)
			{
				// �������int�^�ɕϊ�
				int nNum = atoi(pKanma);

				// int�^�ɕϊ��������̂�aMapData�ɑ��
				m_aMap[nCntY][nCntX] = nNum;

				// ����̃g�[�N��[,.]�Ȃǂ�����������NULL������
				pKanma = strtok(NULL, ","); // [,]����������NULL�����Ă�������
				nCntX++;
			}
			m_nLine = nCntX;
			nCntY++;
		}
		m_nColumn = nCntY;
	}
	fclose(pFile);
}
