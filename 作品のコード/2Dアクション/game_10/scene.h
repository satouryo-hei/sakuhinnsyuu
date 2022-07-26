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
		PRIORITY_NOMAL = 0,													// ノーマル
		PRIORITY_FIRST,														// 1個目
		PRIORITY_SECOND,													// 2個目
		PRIORITY_THIRD,														// 3個目
		PRIORITY_GOAL,														// ゴール
		PRIORITY_EFFECT,													// エフェクト
		PRIORITY_BULLET,													// 弾
		PRIORITY_SOHTGUN,													// 拡散弾
		PRIORITY_H_BULLET,													// ホーミング弾
		PRIORITY_PLAYER,													// プレイヤー
		PRIORITY_ENEMY,														// 敵
		PRIORITY_BLOCK,														// ブロック
		PRIORITY_MOVEBLOCK,													// 移動ブロック
		PRIORITY_PUSHBLOCK,													// 押すブロック
		PRIORITY_ITEM,														// アイテム
		PRIORITY_UI,														// UI
		PRIORITY_FADE,														// フェード
		PRIORITY_MAX														// すべての数
	} PRIORITY;

	CScene(PRIORITY Priority);												// コンストラクタ
	virtual~CScene();														// デストラクタ
	// メンバ関数
	virtual HRESULT Init(D3DXVECTOR3 pos) = 0;								// オブジェクトの初期化関数
	virtual void Uninit(void) = 0;											// オブジェクトの終了関数　
	virtual void Update(void) = 0;											// オブジェクトの更新関数
	virtual void Draw(void) = 0;											// オブジェクトの描画関数
	static void ReleaseAll(void);											// すべてのオブジェクトの開放関数
	static void UpdateAll(void);											// すべてのオブジェクトの更新関数
	static void DrawAll(void);												// すべてのオブジェクトの描画関数
	static CScene * GetScene(int nPriority) { return m_pTop[nPriority]; }	// トップのオブジェクトの取得処理
	CScene * GetNext(CScene * pScene) { return pScene->m_pNext; }			// 次のオブジェクトの取得処理

protected:																	// 自分と派生系のみアクセス可能
	void Release(void);														// 1つのオブジェクトの開放関数

private:																	// 自分だけがアクセス可能
																			// メンバ変数
	static CScene*m_pTop[PRIORITY_MAX];										// 先頭のオブジェクトのポインタ
	static CScene*m_pCur[PRIORITY_MAX];										// 現在(一番後ろ)のオブジェクトのポインタ
	CScene*m_pPrev;															// 前のオブジェクトへのポインタ
	CScene*m_pNext;															// 次のオブジェクトへのポインタ
	bool m_bDeath;															// 死亡フラグ
	int m_nPriority;														// 優先順位
};
#endif