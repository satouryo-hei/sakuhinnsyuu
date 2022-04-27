//=============================================================================
//
// ポリゴンの処理 [scene.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include"scene.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
CScene*CScene::m_pTop = NULL;
CScene*CScene::m_pCur = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CScene::CScene()
{
	// 1個目のポリゴン
	if (m_pTop == NULL)
	{
		m_pTop = this;			//先頭(1個目)にタスキを渡す
		m_pCur = this;			//後ろ(1個目)に看板を渡す
		m_pPrev = NULL;			//前(の人はいない)
		m_pNext = NULL;			//次(の人はいない)
	}
	else
	{
		// 2個目以降
		m_pPrev = m_pCur;		//(元々後ろにいた人が前の人になる）
		m_pCur->m_pNext = this;	//(元々後ろにいた人が次の人に看板を渡す）
		m_pCur = this;			//(一番後ろが自分だと気づく)
		m_pNext = NULL;			//次(の人はいない)
	}
	// 死亡フラグがない
	m_bDeath = false;
}

//=============================================================================
//　デストラクタ
//=============================================================================
CScene::~CScene()
{
	// thisがm_Topだったら
	if (this == m_pTop)
	{
		// トップ(m_pTop)の情報にある変数{this(今のポリゴン)の次(m_pNext)}の情報を入れる
		m_pTop = this->m_pNext;

		// {this(今のポリゴン)の次(m_pNext)}の情報になにか情報が入っていたら
		if (this->m_pNext != NULL)
		{
			// {this(今のポリゴン)の次(m_pNext)}の前(m_pPrev)の情報にNULLを入れて情報を無くす
			this->m_pNext->m_pPrev = NULL;
		}

	}
	// thisがm_pCurだったら
	else if (this == m_pCur)
	{
		// 一番最後(m_pCur)の情報に{this(今のポリゴン)の前(m_pPrev)}の情報を変数に入れる
		m_pCur = this->m_pPrev;

		// {this(今のポリゴン)の前(m_pPrev)}の情報になにか情報が入っていたら
		if (this->m_pPrev != NULL)
		{
			// {this(今のポリゴン)の前(m_pPrev)}の次(m_pNext)の情報にNULLを入れて情報を無くす
			this->m_pPrev->m_pNext = NULL;
		}
	}

	// thisがそれ以外(今回の場合(真ん中))だったら
	else if (this != m_pTop&&this != m_pCur)
	{
		// pSceneに真ん中の情報を入れる
		CScene * pScene = this;		//pSceneは真ん中の代わりになる

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
		m_pTop = NULL;
		m_pCur = NULL;

	}
}

//=============================================================================
// すべてのオブジェクトの開放処理
//=============================================================================
void CScene::ReleaseAll(void)
{
	// pSceneにm_pTopの情報を入れる
	CScene * pScene = m_pTop;		//pSceneはm_Topの代わりになる

	//　次がNULLじゃないなら続く
	while (pScene != NULL)
	{
		// 現在の次の情報をpSceneNextの変数に入れる
		CScene * pSceneNext = pScene->m_pNext;

		if (pScene->m_bDeath == true)
		{
			// 現在の情報を開放する
			delete pScene;
			//pScene = NULL;
		}

		// 現在の情報を次の情報に更新する
		pScene = pSceneNext;
	}
}



//=============================================================================
// すべてのオブジェクトの更新処理
//=============================================================================
void CScene::UpdateAll(void)
{
	// pSceneにm_pTopの情報を入れる
	CScene * pScene = m_pTop;		//pSceneはm_Topの代わりになる

									// 次がNULLじゃない状態なら続く
	while (pScene != NULL)
	{
		// 現在の次の情報をpSceneNextの変数に入れる
		CScene * pSceneNext = pScene->m_pNext;

		// 現在の情報を更新する
		pScene->Update();

		if (pScene->m_bDeath == true)
		{
			delete pScene;
			pScene = NULL;
		}

		// 現在の情報を次の情報に更新する
		pScene = pSceneNext;
	}
}

//=============================================================================
// すべてのオブジェクトの描画処理
//=============================================================================
void CScene::DrawAll(void)
{
	// pSceneにm_pTopの情報を入れる
	CScene * pScene = m_pTop;		//pSceneはm_Topの代わりになる

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


//=============================================================================
// 一つのオブジェクトの開放処理
//=============================================================================
void  CScene::Release(void)
{
	// 現在のオブジェクトに死亡フラグが立つ
	m_bDeath = true;
}