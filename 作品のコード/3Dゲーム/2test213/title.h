//=============================================================================
//
// タイトルの処理 [title.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "scene.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CBg;
class CTitle_Logo;
class CPress_Next;

//*****************************************************************************
// タイトルのクラス
//*****************************************************************************
class CTitle : public CScene
{
public:
	CTitle(int nPriority = PRIORITY_NOMAL);										// コンストラクタ
	~CTitle();																	// デストラクタ

	// メンバ関数
	HRESULT Init(D3DXVECTOR3 pos);												// タイトルの初期化関数
	void Uninit(void);															// タイトルの終了関数　
	void Update(void);															// タイトルの更新関数
	void Draw(void);															// タイトルの描画関数

private:																		// 自分だけがアクセス可能
	static LPDIRECT3DTEXTURE9 m_pTexture;										// 共有するテスクチャのポインタ
	static CBg * m_pBg;															// 背景のポインターの生成
	static CTitle_Logo * m_pTitle_Logo;											// タイトルロゴのポインターの生成
	static CPress_Next * m_pPress_Next;											// タイトルロゴのポインターの生成
	bool m_bFade;																// フェードさせたかどうか
};

#endif