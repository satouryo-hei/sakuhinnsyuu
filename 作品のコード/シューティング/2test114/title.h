//=============================================================================
//
// タイトルの処理 [title.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "scene.h"

class CScene2D;
class CTitle_Logo;
class CPress_Next;
//*****************************************************************************
// タイトルのクラス
//*****************************************************************************
class CTitle : public CScene
{
public:
	CTitle(int nPriority = PRIORITY_BG);										// コンストラクタ
	~CTitle();																	// デストラクタ

	// メンバ関数
	static HRESULT Load(void);													// テクスチャの読み込む
	static void Unload(void);													// テクスチャの破棄
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);							// タイトルの初期化関数
	void Uninit(void);															// タイトルの終了関数　
	void Update(void);															// タイトルの更新関数
	void Draw(void);															// タイトルの描画関数
	

private:																		// 自分だけがアクセス可能
	static LPDIRECT3DTEXTURE9 m_pTexture;										// 共有するテスクチャのポインタ
	CScene2D * m_apScene2D;														// オブジェクトクラスのポインタ
	static CTitle_Logo * m_pTitle_Logo;
	static CPress_Next * m_Press_Next;
	bool m_bNextMode;
};

#endif