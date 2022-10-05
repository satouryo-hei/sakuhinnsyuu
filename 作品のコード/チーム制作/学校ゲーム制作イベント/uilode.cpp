//=============================================================================
//
// UIの読み込み処理 [uilode.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include "uilode.h"
#include "renderer.h"
#include "manager.h"

//=============================================================================
// 静的メンバ変数の宣言
//=============================================================================
int CUilode::m_nMaxUI = 0;

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CUilode::CUilode(const char * pFileNeme)
{
	memset(&m_LodePos[0], NULL, sizeof(m_LodePos));
	memset(&m_LodeSize[0], NULL, sizeof(m_LodeSize));
	Lode(pFileNeme);
}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CUilode::~CUilode()
{
	memset(&m_LodePos[0], NULL, sizeof(m_LodePos));
	memset(&m_LodeSize[0], NULL, sizeof(m_LodeSize));
}

//=============================================================================
// UIの読み込み処理
//=============================================================================
void CUilode::Lode(const char * pFileNeme)
{
	// 開け～ファイル！
	FILE *pFile = fopen(pFileNeme, "r");
	//--------------------------
	// 読み込む用の変数
	//--------------------------
	char aFile[3][128] = {};
	char aName[128] = {};
	int nSetCnt = 0;
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
				fscanf(pFile, "%s%d", &aName[0], &m_nMaxUI);						// UIの数を読み込む
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