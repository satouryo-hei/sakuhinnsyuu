//=============================================================================
//
// 複数のポリゴンの処理 [polygon.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _POLYGON_H_
#define _POLYGON_H_

#include"scene.h"

class CScene2D; //前方宣言
class CManager;

//*****************************************************************************
// 複数のポリゴンクラス
//*****************************************************************************
class CPolygon : public CScene
{
public:																			// 誰でもアクセス可能
	typedef enum
	{
		SETTEX_PLAYER = 0,
		SETTEX_KAKERU,
		SETTEX_MAX
	} SETTEX;

	CPolygon(int nPriority = PRIORITY_UI);												// コンストラクタ
	~CPolygon();																// デストラクタ
																				// メンバ関数
	static CPolygon *Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size, int SetTex);		// ポリゴンの生成
	static HRESULT Load(void);													// テクスチャの読み込む
	static void Unload(void);													// テクスチャの破棄
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);							// ポリゴンの初期化関数
	void Uninit(void);															// ポリゴンの終了関数
	void Update(void);															// ポリゴンの更新関数
	void Draw(void);															// ポリゴンの描画関数
	void SetTex(int SetTex);													// テクスチャの配置関数

private:																		// 自分だけがアクセス可能
	static LPDIRECT3DTEXTURE9 m_pTexture[SETTEX_MAX];							// 共有するテスクチャのポインタ
	static SETTEX m_SetTex;														// どのテクスチャを呼び出すか
	CScene2D * m_apScene2D[SETTEX_MAX];											// オブジェクトクラスのポインタ
	D3DXVECTOR2 m_Size;
};
#endif