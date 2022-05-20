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
		pTimer->Init(pos, Size);
		pTimer->m_nTimer = 100;
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

		m_apNumber[nCntNum] = CNumber::Create(Pos, Size, 5);
	}
	return S_OK;
}

//=============================================================================
// 時間の終了処理
//=============================================================================
void CTimer::Uninit(void)
{
	for (int nCntNum = 0; nCntNum < MAX_TIME; nCntNum++)
	{
		if (m_apNumber[nCntNum] != NULL)
		{
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
	if (m_nTimer < 0)
	{
		m_nTimer = 0;
	}

	// 時間のテクスチャ配置処理
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


	//static const int nData = 10;

	//m_apNumber[0]->SetNumber(m_nTimer % Exponentiation(nData, 8) / Exponentiation(nData, 7));
	//m_apNumber[1]->SetNumber(m_nTimer % Exponentiation(nData, 7) / Exponentiation(nData, 6));
	//m_apNumber[2]->SetNumber(m_nTimer % Exponentiation(nData, 6) / Exponentiation(nData, 5));
	//m_apNumber[3]->SetNumber(m_nTimer % Exponentiation(nData, 5) / Exponentiation(nData, 4));
	//m_apNumber[4]->SetNumber(m_nTimer % Exponentiation(nData, 4) / Exponentiation(nData, 3));
	//m_apNumber[5]->SetNumber(m_nTimer % Exponentiation(nData, 3) / Exponentiation(nData, 2));
	//m_apNumber[6]->SetNumber(m_nTimer % Exponentiation(nData, 2) / Exponentiation(nData, 1));
	//m_apNumber[7]->SetNumber(m_nTimer % Exponentiation(nData, 1) / Exponentiation(nData, 0));

}