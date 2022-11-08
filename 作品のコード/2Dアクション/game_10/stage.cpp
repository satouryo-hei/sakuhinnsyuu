///=============================================================================
//
// �X�e�[�W���� [bg.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include"stage.h"
#include"block.h"
#include"moveblock.h"
#include"stage_top.h"
#include"stage_tutorial.h"

//=============================================================================
// �ÓI�����o�֐��̐錾
//=============================================================================
CBlock* CStage::m_pBlock[256] = {};

//=============================================================================
// �X�e�[�W�̃R���X�g���N�^
//=============================================================================
CStage::CStage(int nPriority) : CScene(PRIORITY_NOMAL)
{
	m_nNum = 0;
}

//=============================================================================
// �X�e�[�W�̃f�X�g���N�^
//=============================================================================
CStage::~CStage()
{

}

//=============================================================================
// �X�e�[�W�̐�������
//=============================================================================																				
CStage *CStage::Create(STAGE stage, D3DXVECTOR3 pos, const char * pStageFileNamee)
{
	// �X�e�[�W�g�b�v�̃|�C���^�[����
	CStage* pStage = NULL;


	switch (stage)
	{
	case STAGE_TOP:
		pStage = new CStage_Top;
		break;

	case STAGE_TUTORIAL:
		pStage = new CStage_Tutorial;
		break;

	default:
		break;
	}
	pStage->LodeStage(pStageFileNamee);
	pStage->Init(pos);

	return pStage;
}

//=============================================================================
// �X�e�[�W�̏���������
//=============================================================================
HRESULT CStage::Init(D3DXVECTOR3 pos)
{
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

	return S_OK;
}


//=============================================================================
// �X�e�[�W�̏I������
//=============================================================================
void CStage::Uninit(void)
{
	// �������
	Release();
}

//=============================================================================
// �X�e�[�W�̍X�V����
//=============================================================================
void CStage::Update(void)
{

}

//=============================================================================
// �X�e�[�W�̕`�揈��
//=============================================================================
void CStage::Draw(void)
{

}

//=============================================================================
// �X�e�[�W�̕`�揈��
//=============================================================================
void CStage::LodeStage(const char * pStageFileName)
{
	// �J���`�t�@�C���I
	FILE *pFile = fopen(pStageFileName, "r");

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
