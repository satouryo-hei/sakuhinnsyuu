//=============================================================================
//
// 次に行くボタンのUIの処理 [nextbutton.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _NEXTBUTTON_H_
#define _NEXTBUTTON_H_

#include"scene.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CPolygon;

//*****************************************************************************
// ロゴのクラス
//*****************************************************************************
class CNextBotton : public CScene
{
public:																		// 誰でもアクセス可能
	CNextBotton(PRIORITY Priority = PRIORITY_EFFECT);								// コンストラクタ
	~CNextBotton();																// デストラクタ
																			// メンバ関数
	static CNextBotton *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size);				// ロゴの生成
	HRESULT Init(D3DXVECTOR3 pos);											// ロゴの初期化関数
	void Uninit(void);														// ロゴの終了関数
	void Update(void);														// ロゴの更新関数
	void Draw(void);														// ロゴの描画関数

private:																	// 自分だけがアクセス可能
	static CPolygon * m_pPolygon;											// ポリゴンの配列ポインターを生成
	D3DXVECTOR3 m_Pos;														// 現在の位置
	D3DXVECTOR3 m_Move;														// 移動量
	D3DXVECTOR2 m_Size;														// 大きさ
	const float m_fHeight;													// 高さ
	const int m_nColMax;													// 色の最大値
	D3DXCOLOR m_Col;														// 色
	bool m_bAdditionCol;													// 色を加算するかどうか
};
#endif // !_EFFECT_H_