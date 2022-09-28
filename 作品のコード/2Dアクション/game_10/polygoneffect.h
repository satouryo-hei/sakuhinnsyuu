//=============================================================================
//
// ポリゴンによるエフェクトの処理 [polygoneffect.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _POLYGONEFFECT_H_
#define _POLYGONEFFECT_H_

#include"scene.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CPolygon;

//*****************************************************************************
// ポリゴンによるエフェクトのクラス
//*****************************************************************************
class CPolygonEffect : public CScene
{
public:																		// 誰でもアクセス可能
	// ポリゴンの種類
	typedef enum
	{
		POLYGON_BACK = 0,													// 後ろ
		POLYGON_BEFORE,														// 前
		POLYGON_MAX															// 最大数
	} POLYGON;

	CPolygonEffect(PRIORITY Priority = PRIORITY_EFFECT);					// コンストラクタ
	~CPolygonEffect();														// デストラクタ
	// メンバ関数
	static CPolygonEffect *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size);		// ポリゴンによるエフェクトの生成
	HRESULT Init(D3DXVECTOR3 pos);											// ポリゴンによるエフェクトの初期化関数
	void Uninit(void);														// ポリゴンによるエフェクトの終了関数
	void Update(void);														// ポリゴンによるエフェクトの更新関数
	void Draw(void);														// ポリゴンによるエフェクトの描画関数
	void SetColor(D3DXCOLOR Col, int nNum);									// ポリゴンによるエフェクトの色の設定関数
	void SetVtxBuffColor(D3DXCOLOR Col, int nNum, int nVtxBuff);			// ポリゴンによるエフェクトの頂点ごとの色の関数
	void SetPos(D3DXVECTOR3 pos);											// ポリゴンによるエフェクトの現在の設定関数

private:																	// 自分だけがアクセス可能
	static CPolygon * m_pPolygon[POLYGON_MAX];								// ポリゴンの配列ポインターを生成
	D3DXVECTOR2 m_Size;														// 大きさ
};
#endif // !_EFFECT_H_