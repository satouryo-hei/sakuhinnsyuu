//=============================================================================
//
// 2Dエフェクトの処理 [effect.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include"scene.h"
#define COLRUM (float(rand() % 256) - float(rand() % 256)) //色のマクロ

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CPolygon;

//*****************************************************************************
// 2Dエフェクトのクラス
//*****************************************************************************
class CEffect : public CScene
{
public:																// 誰でもアクセス可能
	// ポリゴンの種類
	typedef enum
	{
		POLYGON_BACK = 0,
		POLYGON_BEFORE,
		POLYGON_MAX
	} POLYGON;

	CEffect(PRIORITY Priority = PRIORITY_EFFECT);					// コンストラクタ
	~CEffect();														// デストラクタ
																	// メンバ関数
	static CEffect *Create(D3DXVECTOR3 pos);						//  2Dエフェクトの生成
	HRESULT Init(D3DXVECTOR3 pos);									//  2Dエフェクトの初期化関数
	void Uninit(void);												//  2Dエフェクトの終了関数
	void Update(void);												//  2Dエフェクトの更新関数
	void Draw(void);												//  2Dエフェクトの描画関数
	void SetColor(D3DXCOLOR Col,int nNum);
	void SetVtxBuffColor(D3DXCOLOR Col, int nNum, int nVtxBuff);
	void Setpos(D3DXVECTOR3 pos);

private:															// 自分だけがアクセス可能
	static CPolygon * m_pPolygon[POLYGON_MAX];						// ポリゴンの配列ポインターを生成
	D3DXVECTOR2 m_Size;												// 大きさ
	D3DXCOLOR m_Col;												// 色
};
#endif // !_EFFECT_H_