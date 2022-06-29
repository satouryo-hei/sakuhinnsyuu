//---------------------------------------
//�T�[�o�[�̏���(���C��
//Author:�����@�ĕ�
//---------------------------------------
#include"main.h"
#include"tcp_client.h"
#include"tcp_listener.h"
#include"protocol_ranking.h"

//�O���[�o���ϐ�
int g_aRankData[MAX_RANKING];
int g_aRankingData[MAX_RANKING];

//�v���g�^�C�v�錾
void RequestProc(CTcpClient* pTcpClient);
void Ranking(int nTimer);

//���C���֐�
void main(void)
{
	//Winsock�̏������֐������s
	WSADATA wsaData;

	int nErr = WSAStartup(WINSOCK_VERSION, &wsaData);

	if (nErr != 0)
	{
		//�����Ɏ��s�����Ƃ�
		printf("�G���[���N���܂����B\n�v���O�������I�����܂��B\n");
		return;
	}

	//�����L���O�f�[�^������
	memset(&g_aRankingData[0], 0, sizeof(g_aRankingData));
	printf("���������s���܂����B\n");

	FILE *pFile = NULL;
	pFile = fopen(RANKING_TEXT, "r");

	if (pFile != NULL)
	{
		for (int nCount = 0; nCount < MAX_RANKING; nCount++)
		{
			fscanf(pFile, "%d", &g_aRankingData[nCount]);
			printf("%d��ǂݍ��݂܂����B\n", g_aRankingData[nCount]);
		}
	}
	else
	{
		printf("�t�@�C�����ǂݍ��܂�܂���ł����B");
	}

	fclose(pFile);


	CTcpListener*pTcpListener = new CTcpListener;

	if (pTcpListener != NULL&& pTcpListener->Init(PORT_NUMBER) == true)
	{
		while (1)
		{
			while (1)
			{
				printf("��M�ҋ@���E�E�E�ł�\n");

				CTcpClient*pTcpClient = pTcpListener->Accept();

				if (pTcpClient == NULL)
				{
					continue;
				}

				//�X���b�h�̐���
				std::thread th(RequestProc, pTcpClient);

				//�X���b�h��؂藣��
				th.detach();
			}
		}
	}

	//�ڑ���ؒf����	
	pTcpListener->Uninit();

	delete pTcpListener;
	pTcpListener = NULL;

	//Winsock�̏I������
	WSACleanup();

	//���͑҂�
	rewind(stdin);
	getchar();
}

// ���N�G�X�g���󂯂ă����L���O�����ʂ�Ԃ�����
void RequestProc(CTcpClient* pTcpClient)
{
	//���N�G�X�g��M����
	char aRecvData[256];
	pTcpClient->Recv(&aRecvData[0], sizeof(aRecvData));
	printf("��M���܂���\n");

	//��ʂ��擾����
	COMMAND_TYPE conmmand = (COMMAND_TYPE)aRecvData[0];

	char aSendData[256];
	memset(&aSendData[0], 0, sizeof(aSendData));

	int nRank = 0;
	int nScore = 0;				//�N���A�X�R�A������ϐ�
	
	switch (conmmand)
	{
	case COMMAND_TYPE_GET_RANKING:

		for (int nRankingData = 0; nRankingData < MAX_RANKING; nRankingData++)
		{
			int nData = htonl(g_aRankingData[nRankingData]);
			memcpy(&aSendData[nRankingData*sizeof(int)], &nData, sizeof(int));		
		}

		//���M
		pTcpClient->Send(&aSendData[0], MAX_RANKING * sizeof(int));

		printf("���M���܂���\n");

		break;

	case COMMAND_TYPE_SET_RANKING:		

		// �N���A�^�C����(�����^��)�G���f�B�A���ϊ�
		nScore = ntohl(*(int*)&aRecvData[1]);

		// ����ւ�����
		Ranking(nScore);

		for (int nRankingData = 0; nRankingData < MAX_RANKING; nRankingData++)
		{
			if (g_aRankingData[nRankingData] == nScore)
			{
				nRank = nRankingData+1;
				break;
			}
		}

		//���ʂ���
		//�G���f�B�A���ϊ�
		aSendData[0] = (char)nRank;

		//���ʂ𑗐M
		pTcpClient->Send(&aSendData[0], 1);
		printf("���M���܂���\n");

		break;

	default:
		break;
	}


	//�ڑ���ؒf����
	pTcpClient->Uninit();

	delete pTcpClient;
	pTcpClient = NULL;
}

//����ւ��ăt�@�C���֕ۑ�
void Ranking(int nTimer)
{
	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{
		if (g_aRankingData[nCnt] < nTimer)
		{
			swap(g_aRankingData[nCnt], nTimer);
			printf("%d��%d�����ւ��܂����B\n", g_aRankingData[nCnt],nTimer);
		}
	}

	FILE *pFile = NULL;

	pFile = fopen(RANKING_TEXT, "w");

	if (pFile != NULL)
	{
		for (int nCount = 0; nCount < MAX_RANKING; nCount++)
		{
			fprintf(pFile, "%d\n", g_aRankingData[nCount]);
			printf("%d���t�@�C���ɏ������݂܂����B\n", g_aRankingData[nCount]);
		}
	}
	else
	{
		printf("�t�@�C�����ǂݍ��܂�܂���ł����B");
	}

	fclose(pFile);
}