//=============================================================================
//
// ステータスのUIの処理 [result.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include "status_ui.h"
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"bg.h"
#include"fade.h"
#include"ranking.h"
#include"polygon.h"
#include"number.h"

//=============================================================================
// 静的メンバ変数の宣言
//=============================================================================
CPolygon * CStatus_UI::m_pPolygon[3] = {};
CNumber * CStatus_UI::m_apNumber[2] = {};
const char * CStatus_UI::m_pStatusUIFlieName = "data/TEXT/StatusUI.txt";
const int CStatus_UI::m_nStatusNumber = 2;

//=============================================================================
// ステータスのUIのコンストラクタ
//=============================================================================
CStatus_UI::CStatus_UI(int nPriority) : CScene(PRIORITY_NOMAL)
{
	m_nStatus = 0;
}

//=============================================================================
// ステータスのUIのデストラクタ
//=============================================================================
CStatus_UI::~CStatus_UI()
{

}

//=============================================================================
// ステータスのUIの初期化処理
//=============================================================================
CStatus_UI *CStatus_UI::Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	// ランキングのポインター生成
	CStatus_UI * pStatus_UI = NULL;

	// 動的メモリの確保
	pStatus_UI = new CStatus_UI;

	// ランキングになにか情報入っていたら
	if (pStatus_UI != NULL)
	{
		pStatus_UI->m_Size = Size;	// ランキングの大きさを設定
		pStatus_UI->Init(pos);	// ランキングの初期化処理
	}
	return pStatus_UI;
}

//=============================================================================
// ステータスのUIの初期化処理
//=============================================================================
HRESULT CStatus_UI::Init(D3DXVECTOR3 pos)
{
	D3DXVECTOR3 Pos = pos;

	// UIの読み込み処理の呼び出し
	LodeStatusUI();

	// STAUI_MAX分回す
	for (int nCnt = 0; nCnt < STAUI_MAX; nCnt++)
	{
		// ポリゴンの生成の呼び出し
		m_pPolygon[nCnt] = CPolygon::Create(m_LodePos[nCnt], m_LodeSize[nCnt], nCnt + 14);
	}

	// m_nStatusNumber分回す
	for (int nCnt = 0; nCnt < m_nStatusNumber; nCnt++)
	{
		// ナンバーの生成処理の呼び出し
		m_apNumber[nCnt] = CNumber::Create(Pos, m_Size, 5);
		Pos.x += (m_Size.x * m_nStatusNumber);
		
	}
	return S_OK;
}

//=============================================================================
// ステータスのUIの終了処理
//=============================================================================
void CStatus_UI::Uninit(void)
{
	// m_nStatusNumber分回す
	for (int nCntNum = 0; nCntNum < m_nStatusNumber; nCntNum++)
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
	CScene::Release();
}

//=============================================================================
// ステータスのUIの更新処理
//=============================================================================
void CStatus_UI::Update(void)
{

}

//=============================================================================
// ステータスのUIの描画処理
//=============================================================================
void CStatus_UI::Draw(void)
{
	// m_nStatusNumber分回す
	for (int nCntNum = 0; nCntNum < m_nStatusNumber; nCntNum++)
	{
		m_apNumber[nCntNum]->Draw();
	}
}

//=============================================================================
// ステータスのUIのナンバーの配置処理
//=============================================================================
void CStatus_UI::SetStatusNumber(const int nStatus)
{
	m_nStatus = nStatus;

	static const int nData = 10;

	int nNum = m_nStatusNumber;
	int iNum = m_nStatusNumber - 1;

	// m_nStatusNumber分回す
	for (int nCnt = 0; nCnt < m_nStatusNumber; nCnt++, nNum--, iNum--)
	{
		m_apNumber[nCnt]->SetNumber(m_nStatus % Exponentiation(nData, nNum) / Exponentiation(nData, iNum));
	}
}

//=============================================================================
// UIの読み込み処理
//=============================================================================
void CStatus_UI::LodeStatusUI(void)
{
	// 開け～ファイル！
	FILE *pFile = fopen(m_pStatusUIFlieName, "r");
	//--------------------------
	// 読み込む用の変数
	//--------------------------
	char aFile[3][128] = {};
	char aName[128] = {};
	int nSetCnt = 0;
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR2 size = D3DXVECTOR2(0.0f, 0.0f);
	int nLodeUI = 0;

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


