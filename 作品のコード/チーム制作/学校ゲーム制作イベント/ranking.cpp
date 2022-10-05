//=============================================================================
//
// ランキングの処理 [score.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include "ranking.h"
#include"score.h"
#include"timer.h"
#include"uilode.h"
#include"tcp_client.h"
#include"protocol_ranking.h"

//=============================================================================
// 静的メンバ変数の宣言
//=============================================================================
CScore* CRanking::m_apScore[MAX_RANKING] = {};
const char * CRanking::m_apUIFlieName = "data/TEXT/RankingScoreUi.txt";

//=============================================================================
// ランキングのコンストラクタ
//=============================================================================
CRanking::CRanking(PRIORITY nPriority) : CScene(nPriority)
{
	m_bGamePlay = false;
}

//=============================================================================
// ランキングのデストラクタ
//=============================================================================
CRanking::~CRanking()
{

}

//=============================================================================
// ランキングの生成処理
//=============================================================================
CRanking *CRanking::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 Size)
{
	// ランキングのポインター生成
	CRanking * pRanking = NULL;

	// 動的メモリの確保
	pRanking = new CRanking;

	// ランキングになにか情報入っていたら
	if (pRanking != NULL)
	{
		pRanking->Init(pos);	// ランキングの初期化処理
		pRanking->m_Size = Size;	// ランキングの初期化処理
	}
	return pRanking;
}

//=============================================================================
// ランキングの初期化処理
//=============================================================================
HRESULT CRanking::Init(const D3DXVECTOR3 pos)
{
	CUilode *p = new CUilode(m_apUIFlieName);
	
	m_Pos = pos;
	// スコアをランキングにしたい分だけ回す
	for (int nNumRank = 0; nNumRank < MAX_RANKING; nNumRank++)
	{
		m_apScore[nNumRank] = CScore::Create(p->GetUIPos(nNumRank), p->GetUISize(nNumRank));
	}

	// スコアを入れとく用の変数
	int nScore = 0;

	
	// スコアを読み込むよ
	nScore = CScore::LodeScore();



	// オンラインになっているかどうか
	bool Online = LodeOnline();

	//　オフラインにする?オンラインにする?
	switch (false)
	{
	case false:
		/*オフラインのとき*/
		// 現在のランキングを読み込む
		LodeOfflineRnking();

		// ランキングの設定
		SetRanking(nScore);

		break;
	case true:
		/*オンラインのとき*/

		SetOnlineRanking(nScore); // オンラインランキングの設定	

		GetOnlineRanking();			  // オンラインランキングの取得
		break;
	}

	return S_OK;
}

//=============================================================================
// ランキングの終了処理
//=============================================================================
void CRanking::Uninit(void)
{
	Release();
}

//=============================================================================
// ランキングの更新処理
//=============================================================================
void CRanking::Update(void)
{
}

//=============================================================================
// ランキングの描画処理
//=============================================================================
void CRanking::Draw(void)
{

}

//=============================================================================
// 点数の配置処理
//=============================================================================
void CRanking::SetRanking(int nRanking)
{
	// ゲームをしている
	//if (m_bGamePlay)
	//{		
		//// クリアしている
		//if (bClear)
		//{
			// MAX_RANKING数分回す
			for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
			{
				// ランキングのデータが以前のデータより小さかったら
				if (m_aRankScore[nCnt] > nRanking)
				{
					// 入れ替え処理
					swap(m_aRankScore[nCnt], nRanking);
				}

				// ランキングのデータを設定する処理
				m_apScore[nCnt]->SetScore(m_aRankScore[nCnt]);
			}
		//}
		//// クリアしていない
		//else 
		//{
		//	// MAX_RANKING数分回す
		//	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
		//	{
		//		// ランキングのデータを設定する処理
		//		m_apScore[nCnt]->SetScore(m_aRankScore[nCnt]);
		//	}
		//}
	//}
	//// ゲームをしていない
	//else
	//{
	//	// MAX_RANKING数分回す
	//	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	//	{
	//		// ランキングのデータを設定する処理
	//		m_apScore[nCnt]->SetScore(m_aRankScore[nCnt]);
	//	}
	//}
	FILE *pFile = NULL;

	// テキストファイルの読み込み
	pFile = fopen(RANKING_TEXT, "w");

	// pFileになにか情報入っていたら
	if (pFile != NULL)
	{
		// MAX_RANKING数分回す
		for (int nCount = 0; nCount < MAX_RANKING; nCount++)
		{
			fprintf(pFile, "%d\n", m_aRankScore[nCount]);
		}
	}
	else
	{
		printf("ファイルが読み込まれませんでした。");
	}

	fclose(pFile);
}

//=============================================================================
// 時間とスコアの計算する処理
//=============================================================================
int CRanking::AddScoreTime(const int nScore)
{
	/*現在のタイマーを取得、点数にしてnScoreに入れる*/
	int nTime = CTimer::LodeTimer();

	// 時間/10して余ったものをnDataに入れる
	int nData = nTime % 10;

	// ポイントを入れる変数
	float fPoint = 0;

	// 時間/10して余ったものが3より小さい時
	if (nData < 3)
	{
		// 1.5ポイント入れる
		fPoint = 1.5f;
	}
	// 時間/10して余ったものが3より大きく5以下の時
	else if (nData <= 5)
	{
		// 1ポイント入れる
		fPoint = 1;
	}
	// nTimerにポイント分の2倍を引く
	nTime -= (int)(fPoint*2);

	//fPoint += nScore / 10;

	// ポイントを2倍したものと今のスコアを足して今回のスコアを出す
	//(int)nScore += (int)(fPoint * 2);

	if (nTime <= 0)
	{
		nTime = 0;
	}

	return nTime;
}

//=============================================================================
// オフライン時のランキングの読み込み関数
//=============================================================================
void CRanking::LodeOfflineRnking(void)
{
	// 現在のランキングを読み込む
	FILE *pFile = fopen(RANKING_TEXT, "r");

	if (pFile != NULL)
	{
		// MAX_RANKING数分回す
		for (int nCount = 0; nCount < MAX_RANKING; nCount++)
		{
			// 現在のランキングのデータを読み込む
			fscanf(pFile, "%d", &m_aRankScore[nCount]);
		}
	}
	else
	{
		printf("ファイルが読み込まれませんでした。");
	}

	fclose(pFile);
}

//=============================================================================
// オンラインかどうかの読み込み関数
//=============================================================================
bool CRanking::LodeOnline(void)
{
	char aName[2][256] = {};
	char aData[64] = {};
	char aBooldata[64] = {};
	int nBoolData = 0;

	// 現在のランキングを読み込む
	FILE *pFile = fopen(ONLINE_TEXT, "r");

	if (pFile != NULL)
	{
		// 無限ループ
		while (1)
		{
			fscanf(pFile, "%s", &aName[0]);										// 1列を読み込み(2行目以降は上書きされる)
			if (strcmp(&aName[0][0], "SETONLINE") == 0)							// END_SCRIPTが見つかったら
			{
				fscanf(pFile, "%s", &aName[1]);										// 1列を読み込み(2行目以降は上書きされる)
				if (strcmp(&aName[1][0], "オンライン") == 0)							// END_SCRIPTが見つかったら
				{
					fscanf(pFile, "%s%s", &aData[0], &aBooldata[0]);						// オンラインかどうかを読み込む
				}
			}
			if (strcmp(&aName[0][0], "END_SCRIPT") == 0)							// END_SCRIPTが見つかったら
			{
				nBoolData = atoi(&aBooldata[0]);
				break;																// 無限ループを抜ける
			}
		}
	}
	else
	{
		printf("ファイルが読み込まれませんでした。");
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
// オンラインのランキング取得処理
//=============================================================================
void CRanking::GetOnlineRanking(void)
{
	CTcpClient * pTcpClient = NULL;

	pTcpClient = new CTcpClient;

	// 読み取る用の変数
	const char aName[MAX_NUM] = {};
	const char aIPAddress[MAX_NUM] = {};

	FILE *pFile = NULL;
	pFile = fopen(ID_TEXT, "r");

	// pFileになにか情報入っていたら
	if (pFile != NULL)
	{
		/*
		%[^=]		// =前まで読み込む
		= 　		// "="を読み込む
		%s　		// =の後から読み込む
		*/
		//一行読み込む
		fscanf(pFile, "%[^=] = %s\n", &aName[0], &aIPAddress[0]);
	}
	else
	{
		printf("ファイルが読み込まれませんでした。");
	}

	fclose(pFile);

	if (pTcpClient != NULL&&pTcpClient->Init(&aIPAddress[0], PORT_NUMBER) == TRUE)
	{
		//リクエスト受信判定
		char aRecvData[MAX_NUM];
		memset(&aRecvData[0], 0, sizeof(aRecvData));

		char aSendData[MAX_NUM];
		memset(&aSendData[0], 0, sizeof(aSendData));

		aSendData[0] = COMMAND_TYPE_GET_RANKING;

		//送信
		pTcpClient->Send(&aSendData[0], sizeof(char));

		//受信
		pTcpClient->Recv(&aRecvData[0], sizeof(aRecvData));

		for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
		{
			m_aRankScore[nCnt] = *(int*)&aRecvData[nCnt * sizeof(int)];

			// エンディアン変換(ネットワーク→ホスト）
			m_aRankScore[nCnt] = ntohl(m_aRankScore[nCnt]);
		}
		for (int nCont = 0; nCont < MAX_RANKING; nCont++)
		{
			m_apScore[nCont]->SetScore(m_aRankScore[nCont]);
		}
	}
	else
	{
		//接続を切断する
		pTcpClient->Uninit();

		delete pTcpClient;
		pTcpClient = NULL;
	}
}


//=============================================================================
// オンラインのランキング設定処理
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
		printf("ファイルが読み込まれませんでした。");
	}

	fclose(pFile);

	int nData = 0;

	if (pTcpClient != NULL&&pTcpClient->Init(&aIPAddress[0], PORT_NUMBER) == TRUE)
	{

		//リクエスト受信判定
		char aRecvData[MAX_NUM];
		memset(&aRecvData[0], 0, sizeof(aRecvData));

		char aSendData[MAX_NUM];
		memset(&aSendData[0], 0, sizeof(aSendData));

		aSendData[0] = COMMAND_TYPE_SET_RANKING;

		// エンディアン変換(ネットワーク→ホスト）
		nScore = ntohl(nScore);

		memcpy(&aSendData[1], &nScore, sizeof(int));

		//送信
		pTcpClient->Send(&aSendData[0], sizeof(char) + sizeof(int));

		//受信
		pTcpClient->Recv(&aRecvData[0], sizeof(aRecvData));

		for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
		{
			memcpy(&nData, &aRecvData[sizeof(int)], sizeof(int));
			nData = ntohl(nData);
		}
	}
	else
	{
		//接続を切断する
		pTcpClient->Uninit();

		delete pTcpClient;
		pTcpClient = NULL;
	}

	return nData;
}