//=============================================================================
//
// 時間の処理 [score.cpp]
// Author : 佐藤瞭平
// Author : 青木睦浩
//
//=============================================================================
#include "timer.h"
#include"number.h"
#include "fade.h"

//=============================================================================
// 静的メンバ関数の宣言
//=============================================================================
int CTimer::m_nTimer = 0;

//=============================================================================
// 時間のコンストラクタ
//=============================================================================
CTimer::CTimer(int nPriority) : CScene2D(PRIORITY_UI)
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
		pTimer->m_nTimer = 60;
		pTimer->SetTimer(m_nTimer);
	}
	return pTimer;
}

//=============================================================================
// 時間の初期化処理
//=============================================================================
HRESULT CTimer::Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	D3DXVECTOR3 Pos = pos;
	for (int nCntNum = 0; nCntNum < MAX_TIME; nCntNum++)
	{
		Pos.x += (Size.x * 2);

		m_apNumber[nCntNum] = CNumber::Create(Pos, Size, 3);
	}
	return S_OK;
}

//=============================================================================
// 時間の終了処理
//=============================================================================
void CTimer::Uninit(void)
{
	SaveTimer(m_nTimer);
	Release();
}

//=============================================================================
// 時間の更新処理
//=============================================================================
void CTimer::Update(void)
{
	m_nCntTimer++;

	if (m_nCntTimer % 60 == 0)
	{
		m_nTimer--;
	}
	if (m_nTimer < 0)
	{
		m_nTimer = 0;
		CFade::SetFade(CManager::MODE_RESULT);
	}
	CTimer::SetTimer(m_nTimer);

}

//=============================================================================
// 時間の描画処理
//=============================================================================
void CTimer::Draw(void)
{
	for (int nCntNum = 0; nCntNum < MAX_TIME; nCntNum++)
	{
		m_apNumber[nCntNum]->Draw();
	}
}

//=============================================================================
// 時間の設定処理
//=============================================================================
void CTimer::SetTimer(int nTimer)
{	
	static const int nData = 10;

	int nNum = MAX_TIME;
	int iNum = MAX_TIME - 1;

	// NUMSCORE分回す
	for (int nCnt = 0; nCnt < MAX_TIME; nCnt++, nNum--, iNum--)
	{		
		m_apNumber[nCnt]->SetNumber(nTimer % Exponentiation(nData, nNum) / Exponentiation(nData, iNum));
	}	

}


//=============================================================================
// 時間の読み込み処理
//=============================================================================
int CTimer::LodeTimer()
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


//=============================================================================
// 時間の書き込み処理
//=============================================================================
void CTimer::SaveTimer(const int nTime)
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