//=============================================================================
//
// 数字の処理 [number.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_

#include"main.h"

//*****************************************************************************
// 数字クラス
//*****************************************************************************
class CNumber 
{
public:																// 誰でもアクセス可能
	CNumber();														// コンストラクタ
	~CNumber();														// デストラクタ
																	// メンバ関数
	static CNumber *Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size);		// 数字の生成
	static HRESULT Load(void);										// テクスチャの読み込む
	static void Unload(void);										// テクスチャの破棄
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);				// 数字の初期化関数
	void Uninit(void);												// 数字の終了関数
	void Update(void);												// 数字の更新関数
	void Draw(void);												// 数字の描画関数
	void SetNumber(int nNumber);									// 数字の配置関数

private:															// 自分だけがアクセス可能
	static LPDIRECT3DTEXTURE9 m_pTexture;							// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVlxBuff;								// 頂点バッファへのポインタ

};
#endif

