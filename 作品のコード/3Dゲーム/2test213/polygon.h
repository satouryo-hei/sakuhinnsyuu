//=============================================================================
//
// プレイヤーの処理 [player.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _POLYGON_H_
#define _POLYGON_H_

#include"scene2D.h"

//*****************************************************************************
// オブジェクトクラス
//*****************************************************************************
class CPolygon : public CScene2D
{
public:																			// 誰でもアクセス可能
	CPolygon(PRIORITY Priority = PRIORITY_NOMAL);								// コンストラクタ
	~CPolygon();																// デストラクタ
	// メンバ関数
	static CPolygon *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size,int nTex);		// ポリゴンの生成
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 size);							// ポリゴンの初期化関数
	void Uninit(void);															// ポリゴンの終了関数
	void Update(void);															// ポリゴンの更新関数
	void Draw(void);															// ポリゴンの描画関数
	void SetUse(bool bUse) { m_bUse = bUse; }									// 使用しているかどうかの設定関数
	void SetRoll(bool bRoll) { m_bRoll = bRoll; }								// 回転させるかどうかの設定関数
	void SetSize(D3DXVECTOR2 size); 											// 大きさの設定関数
	void SetCol(D3DCOLOR col); 											// 大きさの設定関数

private:																		// 自分だけがアクセス可能
	bool m_bUse;																// 使っているかどうか
	bool m_bRoll;																// 回転させるかどうか
};
#endif	// !_POLYGON_H_
