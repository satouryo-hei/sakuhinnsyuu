//=============================================================================
//
// テクスチャの処理 [texture.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#define MAX_TEXTURE (32)

#include"main.h"

//*****************************************************************************
// オブジェクトクラス
//*****************************************************************************
class CTexture
{
public:																			// 誰でもアクセス可能

	CTexture();																	// コンストラクタ
	~CTexture();																// デストラクタ
																				// メンバ関数
	HRESULT Init(void);															// テクスチャの初期化関数
	void Uninit(void);															// テクスチャの終了関数
	static LPDIRECT3DTEXTURE9 GetTex(int nType) { return m_pTexture[nType]; }	// テクスチャのポインターを取得

private:																		// 自分だけがアクセス可能
	inline void Lode(void);
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE];							// テクスチャへのポインタ
	static int m_nMaxTex;														// テクスチャの最大数
	static const char * m_pTexFileName;											// テクスチャのファイル
};
#endif