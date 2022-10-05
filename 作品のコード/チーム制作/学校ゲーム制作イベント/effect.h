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
public:																				// 誰でもアクセス可能
	CEffect(int nPriority = PRIORITY_EFFECT);										// コンストラクタ
	~CEffect();																		// デストラクタ
																// メンバ関数
	static CEffect *Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size,D3DXVECTOR2 AddSize, D3DXCOLOR m_AddCol,int nTex);	// エフェクトの生成
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);								// エフェクトの初期化関数
	void Uninit(void);																// エフェクトの終了関数
	void Update(void);																// エフェクトの更新関数
	void Draw(void);																// エフェクトの描画関数
	void AddColor(int nRed, int nGreen, int nBlue, int nAlpha);

private:																			// 自分だけがアクセス可能	
	D3DXVECTOR2 m_Size;	
	D3DXVECTOR2 m_AddSize;
	int m_nRed;																		// 赤
	int m_nGreen;																	// 緑
	int m_nBlue;																		// 青
	int m_nAlpha;																	// アルファ
	D3DXCOLOR m_AddCol;
	bool m_bUse;
};
#endif
