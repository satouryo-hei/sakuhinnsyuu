//=============================================================================
//
// �X�e�[�W���� [bg.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include"stage_top.h"
#include"renderer.h"
#include"manager.h"
#include"block.h"
#include"moveblock.h"
#include"goal.h"
#include"player.h"

//=============================================================================
// �ÓI�����o�֐��̐錾
//=============================================================================
CBlock* CStage_Top::m_pBlock[256] = {};

const char * CStage_Top::m_pTutorial_StageFileName = "data/STAGE/stazi_Top.csv";
CGoal * CStage_Top::m_pGoal = NULL;
CPlayer * CStage_Top::m_pPlayer = NULL;
//=============================================================================
// �X�e�[�W�̃R���X�g���N�^
//=============================================================================
CStage_Top::CStage_Top(int nPriority) : CScene(PRIORITY_NOMAL)
{
	m_nNum = 0;
}

//=============================================================================
// �X�e�[�W�̃f�X�g���N�^
//=============================================================================
CStage_Top::~CStage_Top()
{

}

//=============================================================================
// �X�e�[�W�̐�������
//=============================================================================																				
CStage_Top *CStage_Top::Create(D3DXVECTOR3 pos)
{
	// �X�e�[�W�g�b�v�̃|�C���^�[����
	CStage_Top* pStage_Top = NULL;

	pStage_Top = new CStage_Top;

	if (pStage_Top != NULL)
	{
		pStage_Top->Init(pos);
	}

	return pStage_Top;
}

//=============================================================================
// �X�e�[�W�̏���������
//=============================================================================
HRESULT CStage_Top::Init(D3DXVECTOR3 pos)
{
	LodeStage();

	for (int nCntY = 0; nCntY < m_nColumn; nCntY++)
	{
		for (int nCntX = 0; nCntX < m_nLine; nCntX++)
		{
			if (m_aMap[nCntY][nCntX] == 1)
			{
				// ���ʂ̃u���b�N�̐���
				m_pBlock[m_nNum] = CBlock::Create(D3DXVECTOR3(20 + 40 * nCntX, -20 + 40 * nCntY, 0), D3DXVECTOR2(20, 20), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					CBlock::BLOCKTYPE_NOME, 0, 0, 0, false, 7);
				m_nNum++;
			}

			if (m_aMap[nCntY][nCntX] == 2)
			{
				// ����̃u���b�N�̐���
				m_pBlock[m_nNum] = CBlock::Create(D3DXVECTOR3(20 + 40 * nCntX, -20 + 40 * nCntY, 0), D3DXVECTOR2(20, 20), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					CBlock::BLOCKTYPE_NOME, 0, 0, 0, true, 7);
				m_nNum++;
			}
			if (m_aMap[nCntY][nCntX] == 3)
			{
				// ���ړ��u���b�N�̐���
				m_pBlock[m_nNum] = CBlock::Create(D3DXVECTOR3(30 + 60 * nCntX, 0 + 60 * nCntY, 0), D3DXVECTOR2(30, 60), D3DXVECTOR3(1.0f, 1.0f, 0.0f),
					CBlock::BLOCKTYPE_MOVEING, CMoveBlock::MOVE_LEFT, 600, 800, false, 7);
				m_nNum++;
			}
			if (m_aMap[nCntY][nCntX] == 4)
			{
				// �c�ړ��u���b�N�̐���
				m_pBlock[m_nNum] = CBlock::Create(D3DXVECTOR3(20 + 40 * nCntX, -20 + 40 * nCntY, 0), D3DXVECTOR2(60, 30), D3DXVECTOR3(0.0f, 1.0f, 0.0f),
					CBlock::BLOCKTYPE_MOVEING, CMoveBlock::MOVE_UP, 100, 300, false, 7);
				m_nNum++;
			}
			if (m_aMap[nCntY][nCntX] == 5)
			{
				// �������u���b�N�̐���
				m_pBlock[m_nNum] = CBlock::Create(D3DXVECTOR3(20 + 40 * nCntX, 60 * nCntY, 0), D3DXVECTOR2(30, 20), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					CBlock::BLOCKTYPE_PUSH, 0, 600, 800, false, 7);
				m_nNum++;
			}
		}
	}

	m_pGoal = CGoal::Create(D3DXVECTOR3(1020.0f,630.0f, 0.0f), D3DXVECTOR2(100.0f, 50.0f),CManager::MODE_RESULT);

	m_pPlayer = CPlayer::Create(D3DXVECTOR3(100.0f, 200.0f, 0.0f), D3DXVECTOR3(5, 10, 0), D3DXVECTOR2(20, 30));

	return S_OK;
}

//=============================================================================
// �X�e�[�W�̏I������
//=============================================================================
void CStage_Top::Uninit(void)
{
	// �������
	Release();
}

//=============================================================================
// �X�e�[�W�̍X�V����
//=============================================================================
void CStage_Top::Update(void)
{

}

//=============================================================================
// �X�e�[�W�̕`�揈��
//=============================================================================
void CStage_Top::Draw(void)
{

}

//=============================================================================
// �X�e�[�W�̕`�揈��
//=============================================================================
void CStage_Top::LodeStage(void)
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
