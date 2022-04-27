//=============================================================================
//
// ポリゴンの処理 [polygon.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _POLYGON_H_
#define _POLYGON_H_

#include"scene2D.h"

//*****************************************************************************
// 複数のポリゴンクラス
//*****************************************************************************
class CPolygon : public CScene2D
{
public:																			// 誰でもアクセス可能
																				// ポリゴンの種類
	typedef enum
	{
		POLYGON_TYPE_FIRST = 0,
		POLYGON_TYPE_SECOND,
		POLYGON_TYPE_THIRD,
		POLYGON_TYPE_MAX
	} POLYGON_TYPE;

	CPolygon();													// コンストラクタ
	~CPolygon();												// デストラクタ
																// メンバ関数
	static CPolygon *Create(D3DXVECTOR3 pos, D3DXVECTOR3 Size);	// ポリゴンの生成
	static HRESULT Load(void);									// テクスチャの読み込む
	static void Unload(void);									// テクスチャの破棄
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 Size);			// ポリゴンの初期化関数
	void Uninit(void);											// ポリゴンの終了関数
	void Update(void);											// ポリゴンの更新関数
	void Draw(void);											// ポリゴンの描画関数

private:														// 自分だけがアクセス可能
	static LPDIRECT3DTEXTURE9 m_pTexture[POLYGON_TYPE_MAX];		// 共有するテスクチャのポインタ
	D3DXVECTOR3 m_Size;
	D3DXCOLOR m_col;
	POLYGON_TYPE m_Porigon_Type;								// ポリゴンの種類
	CPolygon*m_pPorigon;
	int m_nNumPorigon;											// ポリゴンの番号
};
#endif