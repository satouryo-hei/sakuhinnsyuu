//=============================================================================
//
// �����L���O�̏��� [score.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include "ranking.h"
#include"score.h"
#include"timer.h"
#include"choose_game.h"
#include"goal.h"

//=============================================================================
// �ÓI�����o�ϐ��̐錾
//=============================================================================
CScore* CRanking::m_apScore[MAX_RANKING] = {};
const char * CRanking::m_apUIFlieName = "data/TEXT/RankingScoreUi.txt";

//=============================================================================
// �����L���O�̃R���X�g���N�^
//=============================================================================
CRanking::CRanking(PRIORITY nPriority) : CScene(nPriority)
{
	m_bGamePlay = false;
}

//=============================================================================
// �����L���O�̃f�X�g���N�^
//=============================================================================
CRanking::~CRanking()
{

}

//=============================================================================
// �����L���O�̐�������
//=============================================================================
CRanking *CRanking::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 Size)
{
	// �����L���O�̃|�C���^�[����
	CRanking * pRanking = NULL;

	// ���I�������̊m��
	pRanking = new CRanking;

	// �����L���O�ɂȂɂ��������Ă�����
	if (pRanking != NULL)
	{
		pRanking->Init(pos);	// �����L���O�̏���������
		pRanking->m_Size = Size;	// �����L���O�̏���������
	}
	return pRanking;
}

//=============================================================================
// �����L���O�̏���������
//=============================================================================
HRESULT CRanking::Init(const D3DXVECTOR3 pos)
{
	m_bGamePlay = CChoose_Game::GetGame();
	LodeRankingUI();
	m_Pos = pos;
	// �X�R�A�������L���O�ɂ�������������
	for (int nNumRank = 0; nNumRank < MAX_RANKING; nNumRank++)
	{
		m_apScore[nNumRank] = CScore::Create(m_LodePos[nNumRank], m_LodeSize[nNumRank]);
	}

	// �X�R�A�����Ƃ��p�̕ϐ�
	int nScore = 0;

	// �Q�[����V�΂�Ă�����
	if (m_bGamePlay)
	{
		// �X�R�A��ǂݍ��ނ�
		nScore = CScore::LodeScore();
	}

		/*�I�t���C���̂Ƃ�*/
		// ���݂̃����L���O��ǂݍ���
		LodeOfflineRnking();

		// �Q�[����V�΂�Ă�����
		if (m_bGamePlay)
		{
			// AddScoreTime�֐����Ăяo���Ď��Ԃ�_���ɓ����
			nScore = AddScoreTime(nScore);
		}

		// �����L���O�̐ݒ�
		SetRanking(nScore);

	return S_OK;
}

//=============================================================================
// �����L���O�̏I������
//=============================================================================
void CRanking::Uninit(void)
{
	Release();
}

//=============================================================================
// �����L���O�̍X�V����
//=============================================================================
void CRanking::Update(void)
{
}

//=============================================================================
// �����L���O�̕`�揈��
//=============================================================================
void CRanking::Draw(void)
{

}

//=============================================================================
// �_���̔z�u����
//=============================================================================
void CRanking::SetRanking(int nRanking)
{
	// �Q�[�������Ă���
	if (m_bGamePlay)
	{
		bool bClear = CGoal::GetClear();
		// �N���A���Ă���
		if (bClear)
		{
			// MAX_RANKING������
			for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
			{
				// �����L���O�̃f�[�^���ȑO�̃f�[�^��菬����������
				if (m_aRankScore[nCnt] > nRanking)
				{
					// ����ւ�����
					swap(m_aRankScore[nCnt], nRanking);
				}

				// �����L���O�̃f�[�^��ݒ肷�鏈��
				m_apScore[nCnt]->SetScore(m_aRankScore[nCnt]);
			}
		}
		// �N���A���Ă��Ȃ�
		else 
		{
			// MAX_RANKING������
			for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
			{
				// �����L���O�̃f�[�^��ݒ肷�鏈��
				m_apScore[nCnt]->SetScore(m_aRankScore[nCnt]);
			}
		}
	}
	// �Q�[�������Ă��Ȃ�
	else
	{
		// MAX_RANKING������
		for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
		{
			// �����L���O�̃f�[�^��ݒ肷�鏈��
			m_apScore[nCnt]->SetScore(m_aRankScore[nCnt]);
		}
	}

	FILE *pFile = NULL;

	// �e�L�X�g�t�@�C���̓ǂݍ���
	pFile = fopen(RANKING_TEXT, "w");

	// pFile�ɂȂɂ��������Ă�����
	if (pFile != NULL)
	{
		// MAX_RANKING������
		for (int nCount = 0; nCount < MAX_RANKING; nCount++)
		{
			fprintf(pFile, "%d\n", m_aRankScore[nCount]);
		}
	}
	else
	{
		printf("�t�@�C�����ǂݍ��܂�܂���ł����B");
	}

	fclose(pFile);
}

//=============================================================================
// ���ԂƃX�R�A�̌v�Z���鏈��
//=============================================================================
int CRanking::AddScoreTime(const int nScore)
{
	/*�V�ׂΗV�Ԃق�0�b�ɋ߂Â������ĉ��x���V�΂��������������
	0�b���p�[�t�F�N�g�N���A��ʂƂ��H
	*/

	/*���݂̃^�C�}�[���擾�A�_���ɂ���nScore�ɓ����*/
	int nTime = CTimer::LodeTimer();

	// ����/10���ė]�������̂�nData�ɓ����
	int nData = nTime % 10;

	// �|�C���g������ϐ�
	float fPoint = 0;

	// ����/10���ė]�������̂�3��菬������
	if (nData < 3)
	{
		// 1.5�|�C���g�����
		fPoint = 1.5f;
	}
	// ����/10���ė]�������̂�3���傫��5�ȉ��̎�
	else if (nData <= 5)
	{
		// 1�|�C���g�����
		fPoint = 1;
	}
	// nTimer�Ƀ|�C���g����2�{������
	nTime -= (int)(fPoint*2);

	//fPoint += nScore / 10;

	// �|�C���g��2�{�������̂ƍ��̃X�R�A�𑫂��č���̃X�R�A���o��
	//(int)nScore += (int)(fPoint * 2);

	if (nTime <= 0)
	{
		nTime = 0;
	}

	return nTime;
}

//=============================================================================
// �I�t���C�����̃����L���O�̓ǂݍ��݊֐�
//=============================================================================
void CRanking::LodeOfflineRnking(void)
{
	// ���݂̃����L���O��ǂݍ���
	FILE *pFile = fopen(RANKING_TEXT, "r");

	if (pFile != NULL)
	{
		// MAX_RANKING������
		for (int nCount = 0; nCount < MAX_RANKING; nCount++)
		{
			// ���݂̃����L���O�̃f�[�^��ǂݍ���
			fscanf(pFile, "%d", &m_aRankScore[nCount]);
		}
	}
	else
	{
		printf("�t�@�C�����ǂݍ��܂�܂���ł����B");
	}

	fclose(pFile);
}

//=============================================================================
// �I�����C�����ǂ����̓ǂݍ��݊֐�
//=============================================================================
bool CRanking::LodeOnline(void)
{
	char aName[2][256] = {};
	char aData[64] = {};
	char aBooldata[64] = {};
	int nBoolData = 0;

	// ���݂̃����L���O��ǂݍ���
	FILE *pFile = fopen(ONLINE_TEXT, "r");

	if (pFile != NULL)
	{
		// �������[�v
		while (1)
		{
			fscanf(pFile, "%s", &aName[0]);										// 1���ǂݍ���(2�s�ڈȍ~�͏㏑�������)
			if (strcmp(&aName[0][0], "SETONLINE") == 0)							// END_SCRIPT������������
			{
				fscanf(pFile, "%s", &aName[1]);										// 1���ǂݍ���(2�s�ڈȍ~�͏㏑�������)
				if (strcmp(&aName[1][0], "�I�����C��") == 0)							// END_SCRIPT������������
				{
					fscanf(pFile, "%s%s", &aData[0], &aBooldata[0]);						// �I�����C�����ǂ�����ǂݍ���
				}
			}
			if (strcmp(&aName[0][0], "END_SCRIPT") == 0)							// END_SCRIPT������������
			{
				nBoolData = atoi(&aBooldata[0]);
				break;																// �������[�v�𔲂���
			}
		}
	}
	else
	{
		printf("�t�@�C�����ǂݍ��܂�܂���ł����B");
	}

	fclose(pFile);

	bool bOnline;

	if (nBoolData == 0)
	{
		bOnline = false;
	}
	else
	{
		bOnline = true;
	}

	return bOnline;
}

//=============================================================================
// UI�̓ǂݍ��ݏ���
//=============================================================================
void CRanking::LodeRankingUI(void)
{
	// �J���`�t�@�C���I
	FILE *pFile = fopen(m_apUIFlieName, "r");
	//--------------------------
	// �ǂݍ��ޗp�̕ϐ�
	//--------------------------
	char aFile[3][128] = {};
	char aName[128] = {};
	int nSetCnt = 0;
	int nLodeUI = 0;
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR2 size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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