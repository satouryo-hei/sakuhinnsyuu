//=============================================================================
//
// オブジェクト処理 [scene.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include"scene.h"

// 静的メンバ変数の宣言
CScene *CScene::m_apScene[PRIORITY_MAX][MAX_DATA] = {};
int CScene::m_nNumAll = 0;

//=============================================================================
// オブジェクトのコンストラクタ
//=============================================================================
CScene::CScene(int nPriority)
{
	m_nID = 0;

	m_nPriority = 0;

	for (int nCntScene = 0; nCntScene < MAX_DATA; nCntScene++)
	{
		if (m_apScene[nPriority][nCntScene] == NULL)
		{
			m_apScene[nPriority][nCntScene] = this;

			//自分の番号を設定
			m_nID = nCntScene;
			m_nPriority = nPriority;
			m_nNumAll++;
			break;
		}
	}
}

//=============================================================================
//　オブジェクトのデストラクタ
//=============================================================================
CScene::~CScene()
{

}

//=============================================================================
// すべてのオブジェクトの開放処理
//=============================================================================
void CScene::ReleseAll(void)
{
	for (int nCnt = 0; nCnt < PRIORITY_MAX; nCnt++)
	{
		for (int nCntScene = 0; nCntScene < MAX_DATA; nCntScene++)
		{
			if (m_apScene[nCnt][nCntScene] != NULL)
			{
				if (nCnt != PRIORITY_FADE)
				{
					m_apScene[nCnt][nCntScene]->Uninit();
				}
			}
		}
	}
}

//=============================================================================
// すべてのオブジェクトの更新処理
//=============================================================================
void CScene::UpdateAll(void)
{
	for (int nCnt = 0; nCnt < PRIORITY_MAX; nCnt++)
	{
		for (int nCntScene = 0; nCntScene < MAX_DATA; nCntScene++)
		{
			if (m_apScene[nCnt][nCntScene] != NULL)
			{
				m_apScene[nCnt][nCntScene]->Update();
			}
		}
	}
}

//=============================================================================
// すべてのオブジェクトの描画処理
//=============================================================================
void CScene::DrawAll(void)
{
	for (int nCnt = 0; nCnt < PRIORITY_MAX; nCnt++)
	{
		for (int nCntScene = 0; nCntScene < MAX_DATA; nCntScene++)
		{
			if (m_apScene[nCnt][nCntScene] != NULL)
			{
				m_apScene[nCnt][nCntScene]->Draw();
			}
		}
	}
}


//=============================================================================
// 一つのオブジェクトの開放処理
//=============================================================================
void  CScene::Relese(void)
{
		if (m_apScene[m_nPriority][m_nID] != NULL)
		{
			int nID = m_nID;
			int nPriority = m_nPriority;
			m_apScene[nPriority][nID] = this;
			delete m_apScene[nPriority][nID];
			m_apScene[nPriority][nID] = NULL;
			m_nNumAll--;
		}
}