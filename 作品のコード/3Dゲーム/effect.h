//=============================================================================
//
// エフェクトの処理 [effect.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include"scene.h"
#define COLRUM (float(rand() % 256) - float(rand() % 256)) //円のマクロ

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CPolygon;

//*****************************************************************************
// ゲームの選択クラス
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

	// ポリゴンの種類
	typedef enum
	{
		COLOR_R = 0,
		COLOR_G,
		COLOR_B,
		COLOR_A,
		COLOR_MAX
	} COLOR;

	CEffect(PRIORITY Priority = PRIORITY_EFFECT);					// コンストラクタ
	~CEffect();														// デストラクタ
																	// メンバ関数
	static CEffect *Create(D3DXVECTOR3 pos);						// ゲームの選択の生成
	HRESULT Init(D3DXVECTOR3 pos);									// ゲームの選択の初期化関数
	void Uninit(void);												// ゲームの選択の終了関数
	void Update(void);												// ゲームの選択の更新関数
	void Draw(void);												// ゲームの選択の描画関数
	void SetColor(D3DXCOLOR Col,int nNum);
	void Setpos(D3DXVECTOR3 pos);

private:															// 自分だけがアクセス可能
	static CPolygon * m_pPolygon[POLYGON_MAX];								// ポリゴンの配列ポインターを生成
	bool m_bUse;													// 使っているかどうか
	D3DXVECTOR2 m_Size;												// 大きさ
	D3DXCOLOR m_Col;												// 色
	int m_nCnt;
};
#endif // !_EFFECT_H_