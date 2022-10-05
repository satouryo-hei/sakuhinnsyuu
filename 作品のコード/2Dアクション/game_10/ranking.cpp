//=============================================================================
//
// ランキングの処理 [score.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include "ranking.h"
#include"score.h"
#include"timer.h"
#include"choose_game.h"
#include"goal.h"

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
	m_bGamePlay = CChoose_Game::GetGame();
	LodeRankingUI();
	m_Pos = pos;
	// スコアをランキングにしたい分だけ回す
	for (int nNumRank = 0; nNumRank < MAX_RANKING; nNumRank++)
	{
		m_apScore[nNumRank] = CScore::Create(m_LodePos[nNumRank], m_LodeSize[nNumRank]);
	}

	// スコアを入れとく用の変数
	int nScore = 0;

	// ゲームを遊ばれていたら
	if (m_bGamePlay)
	{
		// スコアを読み込むよ
		nScore = CScore::LodeScore();
	}

		/*オフラインのとき*/
		// 現在のランキングを読み込む
		LodeOfflineRnking();

		// ゲームを遊ばれていたら
		if (m_bGamePlay)
		{
			// AddScoreTime関数を呼び出して時間を点数に入れる
			nScore = AddScoreTime(nScore);
		}

		// ランキングの設定
		SetRanking(nScore);

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
	if (m_bGamePlay)
	{
		bool bClear = CGoal::GetClear();
		// クリアしている
		if (bClear)
		{
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
		}
		// クリアしていない
		else 
		{
			// MAX_RANKING数分回す
			for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
			{
				// ランキングのデータを設定する処理
				m_apScore[nCnt]->SetScore(m_aRankScore[nCnt]);
			}
		}
	}
	// ゲームをしていない
	else
	{
		// MAX_RANKING数分回す
		for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
		{
			// ランキングのデータを設定する処理
			m_apScore[nCnt]->SetScore(m_aRankScore[nCnt]);
		}
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
// 時間とスコアの計算する処理
//=============================================================================
int CRanking::AddScoreTime(const int nScore)
{
	/*遊べば遊ぶほど0秒に近づかさせて何度も遊ばせる方がいいかも
	0秒→パーフェクトクリア画面とか？
	*/

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
// UIの読み込み処理
//=============================================================================
void CRanking::LodeRankingUI(void)
{
	// 開け～ファイル！
	FILE *pFile = fopen(m_apUIFlieName, "r");
	//--------------------------
	// 読み込む用の変数
	//--------------------------
	char aFile[3][128] = {};
	char aName[128] = {};
	int nSetCnt = 0;
	int nLodeUI = 0;
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR2 size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// ファイルがあったら
	if (pFile != NULL)
	{
		// 無限ループ
		while (1)
		{
			fscanf(pFile, "%s", &aFile[0][0]);										// 1列を読み込み(2行目以降は上書きされる)

			if (strcmp(&aFile[0][0], "NUM_UI") == 0)								// NUM_UIが見つかったら
			{
				fscanf(pFile, "%s%d", &aName[0], &nLodeUI);						// UIの数を読み込む
			}

			while (strcmp(&aFile[0][0], "SETUI") == 0)								// SETUIが見つかったら
			{
				fscanf(pFile, "%s", &aFile[1]);										// 1列を読み込み(2行目以降は上書きされる)
				if (strcmp(&aFile[1][0], "POS") == 0)								// POSが見つかったら
				{
					fscanf(pFile, "%s%f%f%f", &aName[0], &pos.x, &pos.y, &pos.z);	// 現在の位置を読み込む
				}
				else if (strcmp(&aFile[1][0], "SIZE") == 0)							// SIZEが見つかったら
				{
					fscanf(pFile, "%s%f%f", &aName[0], &size.x, &size.y);			// 現在の大きさを読み込む
				}
				else if (strcmp(&aFile[1][0], "END_SETUI") == 0)					// END_SETUIが見つかったら
				{
					m_LodePos[nSetCnt] = pos;										// 読み込んだ位置情報をメンバのSetPosに移す
					m_LodeSize[nSetCnt] = size;										// 読み込んだ大きさ情報をメンバのSetSizeに移す
					nSetCnt++;														// 次の方
					break;															// 無限ループを抜ける
				}
			}
			if (strcmp(&aFile[0][0], "END_SCRIPT") == 0)							// END_SCRIPTが見つかったら
			{
				break;																// 無限ループを抜ける
			}
		}
	}
	else
	{
		printf("ファイルが読み込まれませんでした。");
	}

	// 閉じれ～ファイル！
	fclose(pFile);
}