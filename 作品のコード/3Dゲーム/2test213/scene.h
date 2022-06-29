//=============================================================================
//
// オブジェクトの処理 [scene.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

#include"main.h"

//*****************************************************************************
// オブジェクトクラス
//*****************************************************************************
class CScene
{
public:													// 誰でもアクセス可能

	// オブジェクトの種類
	typedef enum
	{		 
		PRIORITY_NOMAL = 0,																					// ノーマル
		PRIORITY_FIRST,
		PRIORITY_SECOND,																					// 2個目
		PRIORITY_THIRD,																						// 3個目
		PRIORITY_PLAYER,
		PRIORITY_ENEMY,
		PRIORITY_MODEL,
		PRIORITY_ITEM,																						// 3個目
		PRIORITY_BILLBOARD,
		PRIORITY_BULLET,
		PRIORITY_EFFECT,
		PRIORITY_UI,
		PRIORITY_FADE,
		PRIORITY_MAX																						// すべての数
	} PRIORITY;

	CScene(PRIORITY Priority);															// コンストラクタ
	virtual~CScene();																	// デストラクタ
	// メンバ関数
	virtual HRESULT Init(D3DXVECTOR3 pos) = 0;											// オブジェクトの初期化関数
	virtual void Uninit(void) = 0;														// オブジェクトの終了関数　
	virtual void Update(void) = 0;														// オブジェクトの更新関数
	virtual void Draw(void) = 0;														// オブジェクトの描画関数
	static void ReleaseAll(void);														// すべてのオブジェクトの開放関数
	static void UpdateAll(void);														// すべてのオブジェクトの更新関数
	static void DrawAll(void);															// すべてのオブジェクトの描画関数
	static CScene * GetScene(int nPriority) { return m_pTop[nPriority]; }				// 何番目のオブジェクトかの取得処理
	static CScene * GetSceneNext(int nPriority) { return m_pTop[nPriority]->m_pNext; }	// 何番目の次のオブジェクトの取得処理

protected:																				// 自分と派生系のみアクセス可能
	void Release(void);																	// 1つのオブジェクトの開放関数

private:																				// 自分だけがアクセス可能
																						// メンバ変数
	static CScene*m_pTop[PRIORITY_MAX];													// 先頭のオブジェクトのポインタ
	static CScene*m_pCur[PRIORITY_MAX];													// 現在(一番後ろ)のオブジェクトのポインタ
	CScene*m_pPrev;																		// 前のオブジェクトへのポインタ
	CScene*m_pNext;																		// 次のオブジェクトへのポインタ
	bool m_bDeath;																		// 死亡フラグ
	int m_nPriority;																	// 優先順位
};
#endif