//=============================================================================
//
// タイトルの処理 [title.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include "title.h"
#include "scene2D.h"
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"bg.h"
#include"fade.h"
#include"game.h"
#include"nextbutton.h"
#include"logo.h"

//=============================================================================
// 静的メンバ変数の宣言
//=============================================================================
CBg* CTitle::m_pBg = NULL;
CLogo* CTitle::m_pLogo = NULL;
CNextBotton* CTitle::m_pNextBotton = NULL;

//=============================================================================
// タイトルのコンストラクタ
//=============================================================================
CTitle::CTitle(int nPriority) : CScene(PRIORITY_NOMAL), m_pTitleUiFile("data/TEXT/TitleUI.txt")
{
	m_bFade = false;
}

//=============================================================================
// タイトルのデストラクタ
//=============================================================================
CTitle::~CTitle()
{

}

//=============================================================================
// タイトルの初期化処理
//=============================================================================
HRESULT CTitle::Init(D3DXVECTOR3 pos)
{
	UILode();
	m_pBg = CBg::Create(pos, D3DXVECTOR2(SCREEN_WIDTH/2, SCREEN_HEIGHT/2), 14);
	m_pLogo = CLogo::Create(m_LodePos[0], m_LodeSize[0]);
	m_pNextBotton = CNextBotton::Create(m_LodePos[1], m_LodeSize[1]);
	return S_OK;
}

//=============================================================================
// タイトルの終了処理
//=============================================================================
void CTitle::Uninit(void)
{
	CScene::Release();

	if (m_pBg != NULL)
	{
		m_pBg->Uninit();
		m_pBg = NULL;
	}
}

//=============================================================================
// タイトルの更新処理
//=============================================================================
void CTitle::Update(void)
{
	CInputKeyboard *pInputKeyboard = NULL;
	pInputKeyboard = CManager::GetInputKeyboard();


	//任意で押されたかどうか
	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true && !m_bFade)//ENTERを押した
	{				
		CFade::SetFade(CManager::MODE_SELECT);
		m_bFade = true;
	}
}

//=============================================================================
// タイトルの描画処理
//=============================================================================
void CTitle::Draw(void)
{

}

//=============================================================================
// タイトルのUIロード処理
//=============================================================================
void CTitle::UILode(void)
{
	// 開け～ファイル！
	FILE *pFile = fopen(m_pTitleUiFile, "r");
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