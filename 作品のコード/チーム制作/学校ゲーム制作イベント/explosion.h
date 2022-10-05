//=============================================================================
//
// 爆発の処理 [explosion.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include"scene2D.h"

//*****************************************************************************
// 爆発のクラス
//*****************************************************************************
class CExplosion : public CScene2D
{
public:																				// 誰でもアクセス可能
	CExplosion(int nPriority = PRIORITY_EFFECT);																	// コンストラクタ
	~CExplosion();																	// デストラクタ
																					// メンバ関数
	static CExplosion *Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size, int nTex);	// 爆発の生成
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);				// 爆発の初期化関数
	void Uninit(void);																// 爆発の終了関数
	void Update(void);																// 爆発の更新関数
	void Draw(void);																// 爆発の描画関数

private:																			// 自分だけがアクセス可能	
	int m_nCounterAnim;																// アニメーションカウンタ
	int m_nPatternAnim;																// アニメーションパターンNo
	bool m_bUse;

};
#endif
