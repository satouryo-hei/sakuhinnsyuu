//---------------------------------------
//サーバーの処理(メイン
//Author:佐藤　瞭平
//---------------------------------------
#include"main.h"
#include"tcp_client.h"
#include"tcp_listener.h"
#include"protocol_ranking.h"

//グローバル変数
int g_aRankData[MAX_RANKING];
int g_aRankingData[MAX_RANKING];

//プロトタイプ宣言
void RequestProc(CTcpClient* pTcpClient);
void Ranking(int nTimer);

//メイン関数
void main(void)
{
	//Winsockの初期化関数を実行
	WSADATA wsaData;

	int nErr = WSAStartup(WINSOCK_VERSION, &wsaData);

	if (nErr != 0)
	{
		//初期に失敗したとき
		printf("エラーが起きました。\nプログラムを終了します。\n");
		return;
	}

	//ランキングデータ初期化
	memset(&g_aRankingData[0], 0, sizeof(g_aRankingData));
	printf("初期化を行いました。\n");

	FILE *pFile = NULL;
	pFile = fopen(RANKING_TEXT, "r");

	if (pFile != NULL)
	{
		for (int nCount = 0; nCount < MAX_RANKING; nCount++)
		{
			fscanf(pFile, "%d", &g_aRankingData[nCount]);
			printf("%dを読み込みました。\n", g_aRankingData[nCount]);
		}
	}
	else
	{
		printf("ファイルが読み込まれませんでした。");
	}

	fclose(pFile);


	CTcpListener*pTcpListener = new CTcpListener;

	if (pTcpListener != NULL&& pTcpListener->Init(PORT_NUMBER) == true)
	{
		while (1)
		{
			while (1)
			{
				printf("受信待機中・・・です\n");

				CTcpClient*pTcpClient = pTcpListener->Accept();

				if (pTcpClient == NULL)
				{
					continue;
				}

				//スレッドの生成
				std::thread th(RequestProc, pTcpClient);

				//スレッドを切り離す
				th.detach();
			}
		}
	}

	//接続を切断する	
	pTcpListener->Uninit();

	delete pTcpListener;
	pTcpListener = NULL;

	//Winsockの終了処理
	WSACleanup();

	//入力待ち
	rewind(stdin);
	getchar();
}

// リクエストを受けてランキングか順位を返す処理
void RequestProc(CTcpClient* pTcpClient)
{
	//リクエスト受信判定
	char aRecvData[256];
	pTcpClient->Recv(&aRecvData[0], sizeof(aRecvData));
	printf("受信しました\n");

	//種別を取得する
	COMMAND_TYPE conmmand = (COMMAND_TYPE)aRecvData[0];

	char aSendData[256];
	memset(&aSendData[0], 0, sizeof(aSendData));

	int nRank = 0;
	int nScore = 0;				//クリアスコアを入れる変数
	
	switch (conmmand)
	{
	case COMMAND_TYPE_GET_RANKING:

		for (int nRankingData = 0; nRankingData < MAX_RANKING; nRankingData++)
		{
			int nData = htonl(g_aRankingData[nRankingData]);
			memcpy(&aSendData[nRankingData*sizeof(int)], &nData, sizeof(int));		
		}

		//送信
		pTcpClient->Send(&aSendData[0], MAX_RANKING * sizeof(int));

		printf("送信しました\n");

		break;

	case COMMAND_TYPE_SET_RANKING:		

		// クリアタイムを(整数型に)エンディアン変換
		nScore = ntohl(*(int*)&aRecvData[1]);

		// 入れ替え処理
		Ranking(nScore);

		for (int nRankingData = 0; nRankingData < MAX_RANKING; nRankingData++)
		{
			if (g_aRankingData[nRankingData] == nScore)
			{
				nRank = nRankingData+1;
				break;
			}
		}

		//順位を代入
		//エンディアン変換
		aSendData[0] = (char)nRank;

		//順位を送信
		pTcpClient->Send(&aSendData[0], 1);
		printf("送信しました\n");

		break;

	default:
		break;
	}


	//接続を切断する
	pTcpClient->Uninit();

	delete pTcpClient;
	pTcpClient = NULL;
}

//入れ替えてファイルへ保存
void Ranking(int nTimer)
{
	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{
		if (g_aRankingData[nCnt] < nTimer)
		{
			swap(g_aRankingData[nCnt], nTimer);
			printf("%dと%dを入れ替えました。\n", g_aRankingData[nCnt],nTimer);
		}
	}

	FILE *pFile = NULL;

	pFile = fopen(RANKING_TEXT, "w");

	if (pFile != NULL)
	{
		for (int nCount = 0; nCount < MAX_RANKING; nCount++)
		{
			fprintf(pFile, "%d\n", g_aRankingData[nCount]);
			printf("%dをファイルに書き込みました。\n", g_aRankingData[nCount]);
		}
	}
	else
	{
		printf("ファイルが読み込まれませんでした。");
	}

	fclose(pFile);
}