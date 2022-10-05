//=============================================================================
//
// 点数の処理 [score.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include "score.h"
#include"number.h"

//=============================================================================
// 点数のコンストラクタ
//=============================================================================
CScore::CScore(PRIORITY nPriority) : CScene2D(nPriority)
{	
	memset(&m_apNumber[0], NULL, sizeof(m_apNumber));
	m_nScore = 0;
}

//=============================================================================
// 点数のデストラクタ
//=============================================================================
CScore::~CScore()
{

}

//=============================================================================
// 点数の生成処理
//=============================================================================
CScore *CScore::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 Size)
{
	// 点数のポインター生成
	CScore *pScore = NULL;

	// 動的メモリの確保
	pScore = new CScore;

	// NULLチェック
	if (pScore != NULL)
	{
		// 点数の初期化処理の呼び出し
		pScore->Init(pos, Size);
		// 点数の設定処理の呼び出し
		pScore->SetScore(0);
	}
	return pScore;
}

//=============================================================================
// 点数の初期化処理
//=============================================================================
HRESULT CScore::Init(const D3DXVECTOR3 pos, const D3DXVECTOR2 Size)
{
	D3DXVECTOR3 Pos = pos;

	// NUMSCORE分回す
	for (int nCntNum = 0; nCntNum < NUMSCORE; nCntNum++)
	{	
		// ナンバーの生成処理の呼び出し
		m_apNumber[nCntNum] = CNumber::Create(Pos, Size, 5);
		Pos.x += (Size.x * 2);
	}

	return S_OK;
}

//=============================================================================
// 点数の終了処理
//=============================================================================
void CScore::Uninit(void)
{
	// スコアの書き込み処理
	SaveScore();

	// NUMSCORE分回す
	for (int nCntNum = 0; nCntNum < NUMSCORE; nCntNum++)
	{
		// NULLチェック
		if (m_apNumber[nCntNum] != NULL)
		{
			// ナンバーの終了処理の呼び出し
			m_apNumber[nCntNum]->Uninit();			
			m_apNumber[nCntNum] = NULL;
		}
	}
	// 解放処理
	Release();
}

//=============================================================================
// 点数の更新処理
//=============================================================================
void CScore::Update(void)
{
	CScore::SetScore(m_nScore);
}

//=============================================================================
// 点数の描画処理
//=============================================================================
void CScore::Draw(void)
{
	// NUMSCORE分回す
	for (int nCntNum = 0; nCntNum < NUMSCORE; nCntNum++)
	{
		m_apNumber[nCntNum]->Draw();
	}
}

//=============================================================================
// 点数の配置処理
//=============================================================================
void CScore::SetScore(const int nScore)
{
	m_nScore = nScore;

	static const int nData = 10;

	int nNum = NUMSCORE;
	int iNum = NUMSCORE - 1;

	// NUMSCORE分回す
	for (int nCnt = 0; nCnt < NUMSCORE; nCnt++, nNum--, iNum--)
	{		
		m_apNumber[nCnt]->SetNumber(m_nScore % Exponentiation(nData, nNum) / Exponentiation(nData, iNum));
	}	
}

//=============================================================================
// 点数の計算処理
//=============================================================================
void CScore::AddScore(const int nValue)
{
	m_nScore += nValue;
}

//=============================================================================
// 点数の書き込み処理
//=============================================================================
void CScore::SaveScore(void)
{
	FILE * pFile = NULL;

	pFile = fopen(SCORE_TEXT, "w");

	// NULLチェック
	if (pFile != NULL)
	{
		fprintf(pFile, "%d\n", m_nScore);
	}
	else
	{
		printf("ファイルが読み込まれませんでした。");
	}

	fclose(pFile);

	m_nScore = 0;
}

//=============================================================================
// スコアの読み込み処理
//=============================================================================
int CScore::LodeScore(void)
{
	// 点数の一時的格納変数
	int nScore = 0;

	// 現在のスコアを読み込む
	FILE *pFile = fopen(SCORE_TEXT, "r");
	// pFileになにか情報入っていたら
	if (pFile != NULL)
	{// 点数の読み込み処理
		fscanf(pFile, "%d", &nScore);
	}
	else
	{
		printf("ファイルが読み込まれませんでした。");
	}

	fclose(pFile);

	return nScore;
}