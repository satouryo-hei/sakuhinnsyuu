//=============================================================================
//
// �����L���O�̏��� [score.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include "ranking.h"
#include"score.h"
#include"protocol_ranking.h"
#include"tcp_client.h"
#include"timer.h"

// geme������bool�^�̎擾�֐�������Ă�����擾���āA�ݒ菈�����񂷂����f������
// strlen�Ƃ��g����new�`�Ƃ��ł�����

//=============================================================================
// �ÓI�����o�ϐ��̐錾
//=============================================================================
CScore* CRanking::m_apScore[MAX_RANKING] = {};

//=============================================================================
// �����L���O�̃R���X�g���N�^
//=============================================================================
CRanking::CRanking(int nPriority) : CScene2D(nPriority)
{
	memset(&m_apScore[0], NULL, sizeof(m_apScore));
	m_nNowScore = 0;
	memset(&m_aRankScore[0], NULL, sizeof(m_aRankScore[0]));

	m_bGameClear = false;		// �Q�[���N���A�������ǂ���
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
	CRanking * pRanking = NULL;	
	pRanking = new CRanking;

	// �����L���O�ɂȂɂ��������Ă�����
	if (pRanking != NULL)
	{
		pRanking->Init(pos, Size);	// �����L���O�̏���������
	}
	return pRanking;
}

//=============================================================================
// �����L���O�̏���������
//=============================================================================
HRESULT CRanking::Init(const D3DXVECTOR3 pos, const D3DXVECTOR2 Size)
{
	// �X�R�A�������L���O�ɂ�������������
	for ( int nNumRank = 0; nNumRank < MAX_RANKING; nNumRank++)
	{
		m_apScore[nNumRank] = CScore::Create(D3DXVECTOR3(pos.x, pos.y+ (Size.y+50.0f)*nNumRank, pos.z),Size);
	}

	LodeScore();

	// �X�R�A�����Ƃ��p�̕ϐ�
	int nScore = 0;

	bool Online = LodeOnline();

	//�@�I�t���C���ɂ���?�I�����C���ɂ���?
	switch (Online)
	{
	case false:
		/*�I�t���C���̂Ƃ�*/
		// ���݂̃����L���O��ǂݍ���
		LodeOfflineRnking();

		// AddScoreTime�֐����Ăяo���Ď��Ԃ�_���ɓ����
		nScore = AddScoreTime();	

		// �����L���O�̐ݒ�
		SetRanking(nScore);	

		break;
	case true:
		/*�I�����C���̂Ƃ�*/

		// AddScoreTime�֐����Ăяo����nScore�ɓ����
		nScore = AddScoreTime();

		SetOnlineRanking(nScore); // �I�����C�������L���O�̐ݒ�	
		
		GetOnlineRanking();			  // �I�����C�������L���O�̎擾
		break;
	}

	return S_OK;
}

//=============================================================================
// �����L���O�̏I������
//=============================================================================
void CRanking::Uninit(void)
{
	CScene2D::Uninit();
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
	// MAX_RANKING������
	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{
		// �����L���O�̃f�[�^���ȑO�̃f�[�^���傫��������
		if (m_aRankScore[nCnt] < nRanking)
		{
			// ����ւ�����
			swap(m_aRankScore[nCnt], nRanking);
		}

		// �����L���O�̃f�[�^��ݒ肷�鏈��
		m_apScore[nCnt]->SetScore(m_aRankScore[nCnt]);
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
// �I�����C���̃����L���O�擾����
//=============================================================================
void CRanking::GetOnlineRanking(void)
{
	CTcpClient * pTcpClient = NULL;

	pTcpClient = new CTcpClient;

	// �ǂݎ��p�̕ϐ�
	const char aName[MAX_NUM] = {};
	const char aIPAddress[MAX_NUM] = {};

	FILE *pFile = NULL;
	pFile = fopen(ID_TEXT, "r");

	// pFile�ɂȂɂ��������Ă�����
	if (pFile != NULL)
	{
		/*
		%[^=]		// =�O�܂œǂݍ���
		= �@		// "="��ǂݍ���
		%s�@		// =�̌ォ��ǂݍ���
		*/
		//��s�ǂݍ���
		fscanf(pFile, "%[^=] = %s\n", &aName[0], &aIPAddress[0]);
	}
	else
	{
		printf("�t�@�C�����ǂݍ��܂�܂���ł����B");
	}

	fclose(pFile);

	if (pTcpClient != NULL&&pTcpClient->Init(&aIPAddress[0], PORT_NUMBER) == TRUE)
	{
		//���N�G�X�g��M����
		char aRecvData[MAX_NUM];
		memset(&aRecvData[0], 0, sizeof(aRecvData));

		char aSendData[MAX_NUM];
		memset(&aSendData[0], 0, sizeof(aSendData));

		aSendData[0] = COMMAND_TYPE_GET_RANKING;

		//���M
		pTcpClient->Send(&aSendData[0], sizeof(char));

		//��M
		pTcpClient->Recv(&aRecvData[0], sizeof(aRecvData));

		for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
		{
			m_aRankScore[nCnt] = *(int*)&aRecvData[nCnt * sizeof(int)];

			// �G���f�B�A���ϊ�(�l�b�g���[�N���z�X�g�j
			m_aRankScore[nCnt] = ntohl(m_aRankScore[nCnt]);
		}
		for (int nCont = 0; nCont < MAX_RANKING; nCont++)
		{
			m_apScore[nCont]->SetScore(m_aRankScore[nCont]);
		}
	}
	else
	{
		//�ڑ���ؒf����
		pTcpClient->Uninit();

		delete pTcpClient;
		pTcpClient = NULL;
	}
}


//=============================================================================
// �I�����C���̃����L���O�ݒ菈��
//=============================================================================
int CRanking::SetOnlineRanking(int nScore)
{
	CTcpClient * pTcpClient = NULL;
	pTcpClient = new CTcpClient;

	const char aName[MAX_NUM] = {};
	const char aIPAddress[MAX_NUM] = {};

	FILE *pFile = NULL;
	pFile = fopen(ID_TEXT, "r");

	if (pFile != NULL)
	{
		fscanf(pFile, "%[^=] = %s\n", &aName[0], &aIPAddress[0]);
	}
	else
	{
		printf("�t�@�C�����ǂݍ��܂�܂���ł����B");
	}

	fclose(pFile);

	int nData = 0;

	if (pTcpClient != NULL&&pTcpClient->Init(&aIPAddress[0], PORT_NUMBER) == TRUE)
	{

		//���N�G�X�g��M����
		char aRecvData[MAX_NUM];
		memset(&aRecvData[0], 0, sizeof(aRecvData));

		char aSendData[MAX_NUM];
		memset(&aSendData[0], 0, sizeof(aSendData));

		aSendData[0] = COMMAND_TYPE_SET_RANKING;

		// �G���f�B�A���ϊ�(�l�b�g���[�N���z�X�g�j
		nScore = ntohl(nScore);

		memcpy(&aSendData[1], &nScore, sizeof(int));

		//���M
		pTcpClient->Send(&aSendData[0], sizeof(char) + sizeof(int));

		//��M
		pTcpClient->Recv(&aRecvData[0], sizeof(aRecvData));

		for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
		{
			memcpy(&nData, &aRecvData[sizeof(int)], sizeof(int));
			nData = ntohl(nData);
		}
	}
	else
	{
		//�ڑ���ؒf����
		pTcpClient->Uninit();

		delete pTcpClient;
		pTcpClient = NULL;
	}

	return nData;
}

//=============================================================================
// ���ԂƃX�R�A�̌v�Z���鏈��
//=============================================================================
int CRanking::AddScoreTime(void)
{
	/*���݂̃^�C�}�[���擾�A�_���ɂ���m_nNowScore�ɓ����*/
	int nTime = CTimer::LodeTimer();

	// (����/10)���ė]�������Ԃ�_���ɕς��č��̓_���Ƒ������킹��
	const int nScore = nTime % 10 + m_nNowScore;

	return nScore;
}

//=============================================================================
// �X�R�A�̓ǂݍ��ݏ���
//=============================================================================
void CRanking::LodeScore(void)
{
	// ���݂̃X�R�A��ǂݍ���
	FILE *pFile = fopen(SCORE_TEXT, "r");

	// pFile�ɂȂɂ��������Ă�����
	if (pFile != NULL)
	{
		fscanf(pFile, "%d", &m_nNowScore);
	}
	else
	{
		printf("�t�@�C�����ǂݍ��܂�܂���ł����B");
	}

	fclose(pFile);
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
// �I�t���C�����̃����L���O�̓ǂݍ��݊֐�
//=============================================================================
bool CRanking::LodeOnline(void)
{
	char aName[2][256] = {};
	char aData[64] = {};
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
					fscanf(pFile, "%s%d", &aData[0], &nBoolData);						// �I�����C�����ǂ�����ǂݍ���
				}
			}
			if (strcmp(&aName[0][0], "END_SCRIPT") == 0)							// END_SCRIPT������������
			{
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