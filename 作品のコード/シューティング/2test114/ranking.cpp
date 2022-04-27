//=============================================================================
//
// ランキングの処理 [score.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include "ranking.h"
#include"score.h"
#include"protocol_ranking.h"
#include"tcp_client.h"
#include"timer.h"

// geme処理にbool型の取得関数を作ってそれを取得して、設定処理を回すか判断させる
// strlenとか使えばnew～とかできそう

//=============================================================================
// 静的メンバ変数の宣言
//=============================================================================
CScore* CRanking::m_apScore[MAX_RANKING] = {};

//=============================================================================
// ランキングのコンストラクタ
//=============================================================================
CRanking::CRanking(int nPriority) : CScene2D(nPriority)
{
	memset(&m_apScore[0], NULL, sizeof(m_apScore));
	m_nNowScore = 0;
	memset(&m_aRankScore[0], NULL, sizeof(m_aRankScore[0]));

	m_bGameClear = false;		// ゲームクリアしたかどうか
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
	CRanking * pRanking = NULL;	
	pRanking = new CRanking;

	// ランキングになにか情報入っていたら
	if (pRanking != NULL)
	{
		pRanking->Init(pos, Size);	// ランキングの初期化処理
	}
	return pRanking;
}

//=============================================================================
// ランキングの初期化処理
//=============================================================================
HRESULT CRanking::Init(const D3DXVECTOR3 pos, const D3DXVECTOR2 Size)
{
	// スコアをランキングにしたい分だけ回す
	for ( int nNumRank = 0; nNumRank < MAX_RANKING; nNumRank++)
	{
		m_apScore[nNumRank] = CScore::Create(D3DXVECTOR3(pos.x, pos.y+ (Size.y+50.0f)*nNumRank, pos.z),Size);
	}

	LodeScore();

	// スコアを入れとく用の変数
	int nScore = 0;

	bool Online = LodeOnline();

	//　オフラインにする?オンラインにする?
	switch (Online)
	{
	case false:
		/*オフラインのとき*/
		// 現在のランキングを読み込む
		LodeOfflineRnking();

		// AddScoreTime関数を呼び出して時間を点数に入れる
		nScore = AddScoreTime();	

		// ランキングの設定
		SetRanking(nScore);	

		break;
	case true:
		/*オンラインのとき*/

		// AddScoreTime関数を呼び出してnScoreに入れる
		nScore = AddScoreTime();

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
	CScene2D::Uninit();
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
	// MAX_RANKING数分回す
	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{
		// ランキングのデータが以前のデータより大きかったら
		if (m_aRankScore[nCnt] < nRanking)
		{
			// 入れ替え処理
			swap(m_aRankScore[nCnt], nRanking);
		}

		// ランキングのデータを設定する処理
		m_apScore[nCnt]->SetScore(m_aRankScore[nCnt]);
	}

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

//=============================================================================
// 時間とスコアの計算する処理
//=============================================================================
int CRanking::AddScoreTime(void)
{
	/*現在のタイマーを取得、点数にしてm_nNowScoreに入れる*/
	int nTime = CTimer::LodeTimer();

	// (時間/10)して余った時間を点数に変えて今の点数と足し合わせる
	const int nScore = nTime % 10 + m_nNowScore;

	return nScore;
}

//=============================================================================
// スコアの読み込み処理
//=============================================================================
void CRanking::LodeScore(void)
{
	// 現在のスコアを読み込む
	FILE *pFile = fopen(SCORE_TEXT, "r");

	// pFileになにか情報入っていたら
	if (pFile != NULL)
	{
		fscanf(pFile, "%d", &m_nNowScore);
	}
	else
	{
		printf("ファイルが読み込まれませんでした。");
	}

	fclose(pFile);
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
// オフライン時のランキングの読み込み関数
//=============================================================================
bool CRanking::LodeOnline(void)
{
	char aName[2][256] = {};
	char aData[64] = {};
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
					fscanf(pFile, "%s%d", &aData[0], &nBoolData);						// オンラインかどうかを読み込む
				}
			}
			if (strcmp(&aName[0][0], "END_SCRIPT") == 0)							// END_SCRIPTが見つかったら
			{
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