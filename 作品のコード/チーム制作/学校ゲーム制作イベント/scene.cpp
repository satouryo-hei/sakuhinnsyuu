//=============================================================================
//
// ポリゴンの処理 [scene.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include"scene.h"

//=============================================================================
// 静的メンバ変数の宣言
//=============================================================================
CScene*CScene::m_pTop[PRIORITY_MAX] = {};
CScene*CScene::m_pCur[PRIORITY_MAX] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CScene::CScene(PRIORITY Priority)
{
	// 1個目のポリゴン
	if (m_pTop[Priority] == NULL)
	{
		m_pTop[Priority] = this;			//先頭(1個目)にタスキを渡す
		m_pCur[Priority] = this;			//後ろ(1個目)に看板を渡す
		m_pPrev = NULL;						//前(の人はいない)
		m_pNext = NULL;						//次(の人はいない)
	}
	else
	{		
		// 2個目以降
		m_pPrev = m_pCur[Priority];		//(元々後ろにいた人が前の人になる）
		m_pCur[Priority]->m_pNext = this;	//(元々後ろにいた人が次の人に看板を渡す）
		m_pCur[Priority] = this;			//(一番後ろが自分だと気づく)
		m_pNext = NULL;			//次(の人はいない)
	}
	m_bDeath = false;

	//自分の番号を設定
	m_nPriority = Priority;
}

//=============================================================================
//　デストラクタ
//=============================================================================
CScene::~CScene()
{
	// thisがm_Topだったら
	if (this == m_pTop[m_nPriority])
	{
		// トップ(m_pTop)の情報にある変数{this(今のポリゴン)の次(m_pNext)}の情報を入れる
		m_pTop[m_nPriority] = this->m_pNext;

		// {this(今のポリゴン)の次(m_pNext)}の情報になにか情報が入っていたら
		if (this->m_pNext != NULL)
		{
			// {this(今のポリゴン)の次(m_pNext)}の前(m_pPrev)の情報にNULLを入れて情報を無くす
			this->m_pNext->m_pPrev = NULL;
		}

	}
	// thisがm_pCurだったら
	else if (this == m_pCur[m_nPriority])
	{
		// 一番最後(m_pCur)の情報に{this(今のポリゴン)の前(m_pPrev)}の情報を変数に入れる
		m_pCur[m_nPriority] = this->m_pPrev;

		// {this(今のポリゴン)の前(m_pPrev)}の情報になにか情報が入っていたら
		if (this->m_pPrev != NULL)
		{
			// {this(今のポリゴン)の前(m_pPrev)}の次(m_pNext)の情報にNULLを入れて情報を無くす
			this->m_pPrev->m_pNext = NULL;
		}
	}
	// thisがそれ以外だったら
	else if (this != m_pTop[m_nPriority]&&this != m_pCur[m_nPriority])
	{
		// pSceneに真ん中の情報を入れる
		CScene * pScene = this;		//pSceneはそれ以外の代わりになる

		if (pScene != NULL)
		{
			// 現在の前の情報をpScenePrevの変数に入れる
			pScene->m_pPrev->m_pNext = pScene->m_pNext;

			// 現在の次の情報をpSceneNextの変数に入れる
			pScene->m_pNext->m_pPrev = pScene->m_pPrev;
		}
	}
	else
	{
		m_pTop[m_nPriority] = NULL;
		m_pCur[m_nPriority] = NULL;

	}
}

//=============================================================================
// すべてのオブジェクトの開放処理
//=============================================================================
void CScene::ReleaseAll(void)
{
	for (int nPriority = 0; nPriority < PRIORITY_MAX; nPriority++)
	{
		//もしnPriorityがフェードじゃなかったら
		if (nPriority != PRIORITY_FADE)
		{
			// pSceneにm_pTopの情報を入れる
			CScene * pScene = m_pTop[nPriority];		//pSceneはm_Topの代わりになる

			//　次がNULLじゃないなら続く
			while (pScene != NULL)
			{
				// 現在の次の情報をpSceneNextの変数に入れる
				CScene * pSceneNext = pScene->m_pNext;

				pScene->Uninit();

				if (pScene->m_bDeath)
				{
					// 現在の情報を開放する
					delete pScene;
					pScene = NULL;
				}

				// 現在の情報を次の情報に更新する
				pScene = pSceneNext;
			}
		}
	}
}



//=============================================================================
// すべてのオブジェクトの更新処理
//=============================================================================
void CScene::UpdateAll(void)
{
	for (int nPriority = 0; nPriority < PRIORITY_MAX; nPriority++)
	{
		//もしnPriorityがフェードじゃなかったら
		if (nPriority != PRIORITY_FADE)
		{
			// pSceneにm_pTopの情報を入れる
			CScene * pScene = m_pTop[nPriority];		//pSceneはm_Topの代わりになる

			// 次がNULLじゃない状態なら続く
			while (pScene != NULL)
			{
				// 現在の次の情報をpSceneNextの変数に入れる
				CScene * pSceneNext = pScene->m_pNext;

				if (pScene->m_bDeath)
				{
					delete pScene;
					//pScene = NULL;
				}
				else
				{
					// 現在の情報を更新する
					pScene->Update();
				}

				// 現在の情報を次の情報に更新する
				pScene = pSceneNext;
			}
		}
		else if (nPriority == PRIORITY_FADE)
		{
			// pSceneにm_pTopの情報を入れる
			CScene * pScene = m_pTop[nPriority];		//pSceneはm_Topの代わりになる

														// 現在の次の情報をpSceneNextの変数に入れる
			CScene * pSceneNext = pScene->m_pNext;
			if (pScene != NULL)
			{
				// 現在の情報を更新する
				pScene->Update();
			}

			// 現在の情報を次の情報に更新する
			pScene = pSceneNext;

		}
	}
}

//=============================================================================
// すべてのオブジェクトの描画処理
//=============================================================================
void CScene::DrawAll(void)
{
	for (int nPriority = 0; nPriority < PRIORITY_MAX; nPriority++)
	{
		//もしnPriorityがフェードじゃなかったら
		if (nPriority != PRIORITY_FADE)
		{
			// pSceneにm_pTopの情報を入れる
			CScene * pScene = m_pTop[nPriority];		//pSceneはm_Topの代わりになる

			//　次がNULLじゃないなら続く
			while (pScene != NULL)
			{
				// 現在の次の情報をpSceneNextの変数に入れる
				CScene * pSceneNext = pScene->m_pNext;

				// 現在の情報を描画する
				pScene->Draw();

				// 現在の情報を次の情報に更新する
				pScene = pSceneNext;
			}
		}
		else if (nPriority == PRIORITY_FADE)
		{
			// pSceneにm_pTopの情報を入れる
			CScene * pScene = m_pTop[nPriority];		//pSceneはm_Topの代わりになる

														// 現在の次の情報をpSceneNextの変数に入れる
			CScene * pSceneNext = pScene->m_pNext;
			if (pScene != NULL)
			{
				// 現在の情報を更新する
				pScene->Draw();
			}

			// 現在の情報を次の情報に更新する
			pScene = pSceneNext;

		}
	}
}


//=============================================================================
// 一つのオブジェクトの開放処理
//=============================================================================
void  CScene::Release(void)
{
	// 現在のオブジェクトに死亡フラグが立つ
	m_bDeath = true;
}