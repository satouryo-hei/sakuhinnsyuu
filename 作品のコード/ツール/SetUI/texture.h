//=============================================================================
//
// テクスチャの処理 [texture.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#define TEXTURE_TEXT "data/TEXT/TextureFile.txt"

#include"main.h"
#include"ui.h"

//*****************************************************************************
// オブジェクトクラス
//*****************************************************************************
class CTexture
{
public:																	// 誰でもアクセス可能
	CTexture();															// コンストラクタ
	~CTexture();														// デストラクタ

	// メンバ関数
	HRESULT Init(void);													// テクスチャの初期化関数
	void Uninit(void);													// テクスチャの終了関数
	LPDIRECT3DTEXTURE9 GetTex(int nType) { return m_pTexture[nType]; }	// テクスチャの取得関数

private:																// 自分だけがアクセス可能
	inline void Lode(void);												// テクスチャの読み込み関数

	// 静的メンバ変数
	static int m_nMaxTex;												// テクスチャの最大数

	// メンバ変数
	LPDIRECT3DTEXTURE9 m_pTexture[LIMITUI];								// テクスチャへのポインタ

};
#endif