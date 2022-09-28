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
class CLogo;
class CNextBotton;

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
	inline void UILode(void);													// UIの読み込み処理
	static CBg * m_pBg;
	static CLogo * m_pLogo;														// ロゴのポインター生成
	static CNextBotton * m_pNextBotton;											// 次のボタンのUIのポインター生成
	bool m_bFade;																// 遷移したかどうか
	D3DXVECTOR3 m_LodePos[2];
	D3DXVECTOR2 m_LodeSize[2];
	const char * m_pTitleUiFile;
};

#endif