//=============================================================================
//
// uiの管理型処理 [ui_manager.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include "ui_manager.h"
#include"input.h"
#include"manager.h"

/*
任意で種類選択をさせて、拡張性を上げる

今のやつをロードさせるやつと
すべてロードするものを作る
*/
//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
CUi*CUI_Manager::m_pUi[LIMITUI] = {};
int CUI_Manager::m_nAllui = 0;

//=============================================================================
// UIのコンストラクタ
//=============================================================================
CUI_Manager::CUI_Manager() : CScene(), m_nMaxUI(10), m_MinUI(0)
{
	memset(&m_SavePos, 0, sizeof(m_SavePos));
	memset(&m_SaveSize, 0, sizeof(m_SaveSize));
	memset(&m_LodePos, 0, sizeof(m_LodePos));
	memset(&m_LodeSize, 0, sizeof(m_LodeSize));
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Color = D3DXCOLOR(255, 255, 255, 255);
	m_nTex = 0;
	m_nLodeUI = 0;
	m_bUse = true;
}

//=============================================================================
// UIのデストラクタ
//=============================================================================
CUI_Manager::~CUI_Manager()
{

}

//=============================================================================
// UIの生成処理
//=============================================================================
CUI_Manager *CUI_Manager::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 Size)
{
	CUI_Manager *pUI_Manager = NULL;
	pUI_Manager = new CUI_Manager;

	// NULLチェック
	if (pUI_Manager != NULL)
	{
		pUI_Manager->Init(pos, move, Size);
	}
	return pUI_Manager;
}


//=============================================================================
// UIの初期化処理
//=============================================================================
HRESULT CUI_Manager::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	LodeUI();
	m_Pos = pos;
	m_Size = size;
	return S_OK;
}

//=============================================================================
// UIの初期化処理
//=============================================================================
HRESULT CUI_Manager::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 Size)
{
	CUI_Manager::Init(pos,Size);
	m_Move = move;
	m_pUi[m_nAllui] = CUi::Create(pos, move, Size, m_nTex);
	return S_OK;
}

//=============================================================================
// UIの終了処理
//=============================================================================
void CUI_Manager::Uninit(void)
{
	for (int nCnt = 0; nCnt < m_nAllui; nCnt++)
	{
		if (m_pUi[nCnt] != NULL)
		{
			delete m_pUi[nCnt];
			m_pUi[nCnt] = NULL;
		}
	}

}

//=============================================================================
// UIの更新処理
//=============================================================================
void CUI_Manager::Update(void)
{
	CManager * pManager = NULL;

	CInputKeyboard *pInputKeyboard = NULL;
	pInputKeyboard = CManager::GetInputKeyboard();

	if (m_bUse)
	{
		D3DXVECTOR3 pos = m_pUi[m_nAllui]->GetPos();
		D3DXVECTOR3 move = m_pUi[m_nAllui]->GetMove();
		D3DXVECTOR3 size = m_pUi[m_nAllui]->GetSize();
		m_Color = m_pUi[m_nAllui]->GetColor();


		m_pUi[m_nAllui]->SetPos(pos);
		m_pUi[m_nAllui]->SetSize(size);
		m_pUi[m_nAllui]->SetCol(m_Color);		
		m_pUi[m_nAllui]->Update();

		bool bMove= m_pUi[m_nAllui]->GetBoolMove();	
		bool bSize = m_pUi[m_nAllui]->GetBoolSize();
		bool bSpeed = m_pUi[m_nAllui]->GetBoolSpeed();
		bool bAnim = m_pUi[m_nAllui]->GetBoolAnim();

		// 最大値を増やす
		if (pInputKeyboard->GetTrigger(DIK_LEFT) == true)
		{
			int nMax = m_nMaxUI;
			nMax++;
			(int)m_nMaxUI = nMax;

			if (LIMITUI <=m_nMaxUI)
			{
				(int)m_nMaxUI = LIMITUI;
			}
		}

		// 最大値を減らす
		if (pInputKeyboard->GetTrigger(DIK_RIGHT) == true)
		{
			int nMin = m_nMaxUI;
			nMin--;
			(int)m_nMaxUI = nMin;

			if (m_MinUI>=m_nMaxUI)
			{
				(int)m_nMaxUI = m_MinUI;
			}
		}

		// 移動させるかどうか
		if (pInputKeyboard->GetTrigger(DIK_F1) == true)
		{
			if (bMove)
			{
				bMove = false;
			}
			else if (!bMove)
			{
				bMove = true;
			}
			m_pUi[m_nAllui]->SetBoolMove(bMove);
		}

		// 大きさ変更させるかどうか
		if (pInputKeyboard->GetTrigger(DIK_F2) == true)
		{
			if (bSize)
			{
				bSize = false;
			}
			else if (!bSize)
			{
				bSize = true;
			}
			m_pUi[m_nAllui]->SetBoolSize(bSize);
		}

		// 速さ変更させるかどうか
		if (pInputKeyboard->GetTrigger(DIK_F3) == true)
		{
			if (bSpeed)
			{
				bSpeed = false;
			}
			else if (!bSpeed)
			{
				bSpeed = true;
			}
			m_pUi[m_nAllui]->SetBoolSpeed(bSpeed);
		}

		// アニメーションさせるかどうか
		if (pInputKeyboard->GetTrigger(DIK_F4) == true)
		{
			if (bAnim)
			{
				bAnim = false;
			}
			else if (!bAnim)
			{
				bAnim = true;
			}
			m_pUi[m_nAllui]->SetBoolAnim(bAnim);
		}

		// ENTERを押したら
		if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
		{
			SetUI(pos, size);
		}		
	}

	// F9を押したら
	if (pInputKeyboard->GetTrigger(DIK_F9) == true)
	{
		SaveUI();
	}

	// F8を押したら
	if (pInputKeyboard->GetTrigger(DIK_F8) == true)
	{
		LodeUI();
	}

	// F7を押したら
	if (pInputKeyboard->GetTrigger(DIK_F7) == true)
	{
		LodeSetNow();
	}

	// F6を押したら
	if (pInputKeyboard->GetTrigger(DIK_F6) == true)
	{
		LodeSetAll();
	}
}

//=============================================================================
// UIの描画処理
//=============================================================================
void CUI_Manager::Draw(void)
{
}

//=============================================================================
// UIの配置関数
//=============================================================================
void CUI_Manager::SetUI(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	if (m_bUse)
	{
		m_SavePos[m_nAllui] = pos;							// posを保存する
		m_SaveSize[m_nAllui] = size;						// sizeを保存する
		m_pUi[m_nAllui]->SetPos(pos);						// posを設定する
		m_pUi[m_nAllui]->SetSize(size);						// sizeを設定する
		m_Color.a = 0.5f;									// 半透明にする
		m_pUi[m_nAllui]->SetCol(m_Color);					// 色を保存
		m_pUi[m_nAllui]->Update();							// 更新する
		m_pUi[m_nAllui]->SetBoolUse(false);					// 使い終わったよ～って返す
		m_nAllui++;											// 次のUIを呼び出す
		m_nTex++;											// 次のテクスチャを設定

		if (m_nAllui < m_nMaxUI)								// マックス値までいってなかったら
		{
			// UI生成
			m_pUi[m_nAllui] = CUi::Create(m_Pos, m_Move, m_Size, m_nTex);
		}
		else
		{
			// UI_managerを使わなくする
			m_bUse = false;
		}
	}
}

//=============================================================================
// UIの書き出し処理
//=============================================================================
void CUI_Manager::SaveUI(void)
{
	// 開け～ファイル！
	FILE *pFile = fopen(SETUITEXT, "w");

	// ファイルがあったら
	if (pFile != NULL)
	{
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "# UI設定ファイル[Setui.txt]\n");
		fprintf(pFile, "# Author : 佐藤瞭平\n");
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "# セットしたUIをこのテキストファイルに書き出します\n");
		fprintf(pFile, "# UI情報\n");
		fprintf(pFile, "#==============================================================================\n");		
		fprintf(pFile, "SCRIPT\t\t# この行は絶対消さないこと！\n");
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "# 読み込むUIの数\n");
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "NUM_UI = %d\n", m_nAllui);
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "# 表示するUIの配置情報\n");
		fprintf(pFile, "#==============================================================================\n");

		// UIの数分回す
		for (int nCnt = 0; nCnt < m_nAllui; nCnt++)
		{
			fprintf(pFile, "#%d個目\n", nCnt + 1);
			fprintf(pFile, "SETUI\n");
			fprintf(pFile, "\tPOS = %.1f %.1f %.1f\n", m_SavePos[nCnt].x, m_SavePos[nCnt].y, m_SavePos[nCnt].z);	//現在の位置を書き込み
			fprintf(pFile, "\tSIZE = %.1f %.1f\n", m_SaveSize[nCnt].x, m_SaveSize[nCnt].y);							//現在の大きさを書き込み
			fprintf(pFile, "END_SETUI\n\n");
		}
		fprintf(pFile, "END_SCRIPT\t\t# この行は絶対消さないこと！\n");
	}
	else
	{
		printf("ファイルが読み込まれませんでした。");
	}
	// 閉じれ～ファイル！
	fclose(pFile);
}

//=============================================================================
// UIの読み込み処理
//=============================================================================
void CUI_Manager::LodeUI(void)
{
	// 開け～ファイル！
	FILE *pFile = fopen(SETUITEXT, "r");
	//--------------------------
	// 読み込む用の変数
	//--------------------------
	char aFile[3][128] = {};
	char aName[128] = {};
	int nSetCnt = 0;
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// ファイルがあったら
	if (pFile != NULL)
	{
		// 無限ループ
		while (1)
		{
			fscanf(pFile, "%s", &aFile[0][0]);										// 1列を読み込み(2行目以降は上書きされる)

			if (strcmp(&aFile[0][0], "NUM_UI") == 0)								// NUM_UIが見つかったら
			{
				fscanf(pFile, "%s%d", &aName[0], &m_nLodeUI);						// UIの数を読み込む
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

//=============================================================================
// 読み込みんだすべてのUIを設置処理
//=============================================================================
void CUI_Manager::LodeSetAll(void)
{
	// m_nLodeUI分回す
	for (int nCnt = 0; nCnt < m_nLodeUI; nCnt++)
	{
		SetUI(m_LodePos[nCnt], m_LodeSize[nCnt]);
	}
}

//=============================================================================
// 読み込みんだ今のUIを設置処理
//=============================================================================
void CUI_Manager::LodeSetNow(void)
{
	m_pUi[m_nAllui]->SetPos(m_LodePos[m_nAllui]);
	m_pUi[m_nAllui]->SetSize(m_LodeSize[m_nAllui]);
}
