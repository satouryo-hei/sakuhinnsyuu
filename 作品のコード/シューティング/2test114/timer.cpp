//=============================================================================
//
// 時間の処理 [score.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include "timer.h"
#include"number.h"

// 静的メンバ変数の宣言
int CTimer::m_nTimer = 0;

//=============================================================================
// 時間のコンストラクタ
//=============================================================================
CTimer::CTimer(int nPriority) : CScene2D(nPriority)
{
	memset(&m_apNumber[0], NULL, sizeof(m_apNumber));
	m_nCntTimer = 0;
}

//=============================================================================
// 時間のデストラクタ
//=============================================================================
CTimer::~CTimer()
{

}

//=============================================================================
// 時間の生成処理
//=============================================================================
CTimer *CTimer::Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	CTimer *pTimer = NULL;
	pTimer = new CTimer;

	if (pTimer != NULL)
	{
		pTimer->Init(pos, Size);
		pTimer->SetTimer(0);
	}
	return pTimer;
}

//=============================================================================
// 時間の初期化処理
//=============================================================================
HRESULT CTimer::Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	D3DXVECTOR3 Pos = pos;
	for (int nCntNum = 0; nCntNum < 8; nCntNum++)
	{
		Pos.x += (Size.x * 2);

		m_apNumber[nCntNum] = CNumber::Create(Pos, Size);
	}

	m_nTimer = 0;

	m_nCntTimer = 0;

	return S_OK;
}

//=============================================================================
// 時間の終了処理
//=============================================================================
void CTimer::Uninit(void)
{
	SeveTimer(m_nTimer);

	for (int nCntNum = 0; nCntNum < 8; nCntNum++)
	{
		if (m_apNumber[nCntNum] != NULL)
		{
			m_apNumber[nCntNum]->Uninit();
			delete m_apNumber[nCntNum];
		}
	}
	Relese();
}

//=============================================================================
// 時間の更新処理
//=============================================================================
void CTimer::Update(void)
{
	m_nCntTimer++;

	if (m_nCntTimer % 60 == 0)
	{
		m_nTimer++;
	}

	CTimer::SetTimer(m_nTimer);

}

//=============================================================================
// 時間の描画処理
//=============================================================================
void CTimer::Draw(void)
{
	for (int nCntNum = 0; nCntNum < 8; nCntNum++)
	{
		m_apNumber[nCntNum]->Draw();
	}
}

//=============================================================================
// 時間の配置処理
//=============================================================================
void CTimer::SetTimer(int nTimer)
{
	m_nTimer = nTimer;

	m_apNumber[0]->SetNumber(m_nTimer % 100000000 / 10000000);
	m_apNumber[1]->SetNumber(m_nTimer % 10000000 / 1000000);
	m_apNumber[2]->SetNumber(m_nTimer % 1000000 / 100000);
	m_apNumber[3]->SetNumber(m_nTimer % 100000 / 10000);
	m_apNumber[4]->SetNumber(m_nTimer % 10000 / 1000);
	m_apNumber[5]->SetNumber(m_nTimer % 1000 / 100);
	m_apNumber[6]->SetNumber(m_nTimer % 100 / 10);
	m_apNumber[7]->SetNumber(m_nTimer % 10 / 1);
}

//=============================================================================
// 時間の保存処理
//=============================================================================
void CTimer::SeveTimer(int nTime)
{
	// 現在の時間を保存

	FILE *pFile = fopen(TIMETEXT, "w");

	if (pFile != NULL)
	{
		fprintf(pFile, "%d", nTime);
	}
	else
	{
		printf("ファイルが読み込まれませんでした。");
	}

	fclose(pFile);
}

//=============================================================================
// 時間の読み込み処理
//=============================================================================
int CTimer::LodeTimer(void)
{
	int nTime = 0;

	// 現在の時間を読み込む

	FILE *pFile = fopen(TIMETEXT, "r");

	if (pFile != NULL)
	{
		fscanf(pFile, "%d", &nTime);
	}
	else
	{
		printf("ファイルが読み込まれませんでした。");
	}

	fclose(pFile);

	return nTime;
}