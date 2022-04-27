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

//*****************************************************************************
// オブジェクトクラス
//*****************************************************************************
class CTexture
{
public:															// 誰でもアクセス可能

	//// テクスチャの種類
	//typedef enum 
	//{
	//	TEXTYPE_NOME = 0,
	//	TEXTYPE_NOME,
	//	TEXTYPE_NOME,
	//	TEXTYPE_MAX
	//} TEXTYPE;

	CTexture();													// コンストラクタ
	~CTexture();												// デストラクタ
	// メンバ関数
	HRESULT Init(void);											// テクスチャの初期化関数
	void Uninit(void);											// テクスチャの終了関数
	inline void Lode(void);
	LPDIRECT3DTEXTURE9 GetTex(int nType) { return m_pTexture[nType]; }

private:														// 自分だけがアクセス可能

	LPDIRECT3DTEXTURE9 m_pTexture[32];							// テクスチャへのポインタ
	static int m_nMaxTex;										// テクスチャの最大数
};
#endif