//=============================================================================
//
// 時間の処理 [score.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include "timer.h"
#include"number.h"
#include"polygon.h"
#include"fade.h"

//=============================================================================
// 静的メンバ変数の宣言
//=============================================================================
int CTimer::m_nTimer = 0;
CPolygon * CTimer::m_apPolygon = NULL;

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
	// 時間のポインター生成
	CTimer *pTimer = NULL;

	// 動的メモリの確保
	pTimer = new CTimer;

	// NULLチェック
	if (pTimer != NULL)
	{
		// 時間の初期化処理の呼び出し
		pTimer->Init(pos, Size);		
		pTimer->m_nTimer = 60;

		// 時間の設定処理の呼び出し
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
	m_apPolygon = CPolygon::Create(pos, Size,18);

	// MAX_TIME分回す
	for (int nCntNum = 0; nCntNum < MAX_TIME; nCntNum++)
	{
		Pos.x += (Size.x * 2);
		// ナンバーの生成処理の呼び出し
		m_apNumber[nCntNum] = CNumber::Create(Pos, Size, 5);
	}
	return S_OK;
}

//=============================================================================
// 時間の終了処理
//=============================================================================
void CTimer::Uninit(void)
{
	// 時間の書き出し処理の呼び出し
	SeveTimer(m_nTimer);

	// MAX_TIME分回す
	for (int nCntNum = 0; nCntNum < MAX_TIME; nCntNum++)
	{
		// NULLチェック
		if (m_apNumber[nCntNum] != NULL)
		{
			// ナンバーの終了処理の呼び出し
			m_apNumber[nCntNum]->Uninit();
			m_apNumber[nCntNum] = NULL;
		}
	}
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

	if (m_nTimer >= 30)
	{
		// MAX_TIME分回す
		for (int nCntNum = 0; nCntNum < MAX_TIME; nCntNum++)
		{
			m_apNumber[nCntNum]->SetColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
		}
	}
	else if (m_nTimer <= 30 && m_nTimer > 10)
	{
		// MAX_TIME分回す
		for (int nCntNum = 0; nCntNum < MAX_TIME; nCntNum++)
		{
			m_apNumber[nCntNum]->SetColor(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
		}
	}
	else if (m_nTimer <= 10 && m_nTimer > 0)
	{
		// MAX_TIME分回す
		for (int nCntNum = 0; nCntNum < MAX_TIME; nCntNum++)
		{
			m_apNumber[nCntNum]->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		}
	}
	else if (m_nTimer < 0)
	{
		m_nTimer = 0;
		
		// リザルトに遷移
		CFade::SetFade(CManager::MODE_RESULT);		
	}

	// 時間のテクスチャ配置処理
	CTimer::SetTimer(m_nTimer);

}

//=============================================================================
// 時間の描画処理
//=============================================================================
void CTimer::Draw(void)
{
	// MAX_TIME分回す
	for (int nCntNum = 0; nCntNum < MAX_TIME; nCntNum++)
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

	static const int nData = 10;

	int nNum = MAX_TIME;
	int iNum = MAX_TIME - 1;

	// MAX_TIME分回す
	for (int nCnt = 0; nCnt < MAX_TIME; nCnt++,nNum--,iNum--)
	{		
		m_apNumber[nCnt]->SetNumber(m_nTimer % Exponentiation(nData, nNum) / Exponentiation(nData, iNum));
	}
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