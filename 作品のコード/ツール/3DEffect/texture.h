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
// テクスチャクラス
//*****************************************************************************
class CTexture
{
public:																	// 誰でもアクセス可能
	// テクスチャの種類
	typedef enum 
	{		
		Tex_Fild = 0,		// フィールド
		Tex_Effect,		// エフェクト
		Tex_MAX			// 最大数
	} Tex;

	CTexture();															// コンストラクタ
	~CTexture();														// デストラクタ
	// メンバ関数
	HRESULT Init(void);													// テクスチャの初期化関数
	void Uninit(void);													// テクスチャの終了関数
	inline void Lode(void);
	LPDIRECT3DTEXTURE9 GetTex(Tex Type) { return m_pTexture[Type]; }

private:																// 自分だけがアクセス可能
	LPDIRECT3DTEXTURE9 m_pTexture[Tex_MAX];								// テクスチャへのポインタ
	static int m_nMaxTex;												// テクスチャの最大数
};
#endif