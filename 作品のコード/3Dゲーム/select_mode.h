//=============================================================================
//
// モードの選択処理 [select_mode.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _SELECT_MODE_H_
#define _SELECT_MODE_H_

#include"scene.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CPolygon;

//*****************************************************************************
// モードの選択クラス
//*****************************************************************************
class CSelect_Mode : public CScene
{
public:																// 誰でもアクセス可能
		
	// モードの選択種類
	typedef enum
	{
		SELECT_TUTORIAL = 0,
		SELECT_GAME,
		SELECT_RESULT,
		SELECT_MAX
	} SELECT;

	CSelect_Mode(PRIORITY Priority = PRIORITY_NOMAL);				// コンストラクタ
	~CSelect_Mode();												// デストラクタ
																	// メンバ関数
	static CSelect_Mode *Create(D3DXVECTOR3 pos);					// モードの選択の生成
	HRESULT Init(D3DXVECTOR3 pos);									// モードの選択の初期化関数
	void Uninit(void);												// モードの選択の終了関数
	void Update(void);												// モードの選択の更新関数
	void Draw(void);												// モードの選択の描画関数

	void SetUse(bool bUse) { m_bUse = bUse; }						// 使っているかどうかの設定処理

private:															// 自分だけがアクセス可能
	static LPDIRECT3DTEXTURE9 m_pTexture;							// テクスチャのポインターを生成
	CPolygon * m_pPolygon[SELECT_MAX];								// ポリゴンの配列ポインターを生成
	bool m_bUse;													// 使っているかどうか
	int m_nt;
};
#endif