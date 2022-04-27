//=============================================================================
//
// エフェクトの処理 [effect.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include"scene2D.h"

//*****************************************************************************
// エフェクトのクラス
//*****************************************************************************
class CEffect : public CScene2D
{
public:															// 誰でもアクセス可能
	CEffect(int nPriority = PRIORITY_EFFECT);									// コンストラクタ
	~CEffect();													// デストラクタ
																// メンバ関数
	static CEffect *Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size);	// エフェクトの生成
	static HRESULT Load(void);									// テクスチャの読み込み
	static void Unload(void);									// テクスチャの破棄
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);			// エフェクトの初期化関数
	void Uninit(void);											// エフェクトの終了関数
	void Update(void);											// エフェクトの更新関数
	void Draw(void);											// エフェクトの描画関数


private:														// 自分だけがアクセス可能	
	static LPDIRECT3DTEXTURE9 m_pTexture;						// 共有するテスクチャのポインタ
	D3DXVECTOR2 m_Size;
	int m_nRed;													// 赤
	int m_nGreen;												// 緑
	int m_nBlue;												// 青
	int m_nAlpha;												// アルファ

};
#endif
