//=============================================================================
//
// UIの処理 [keyui.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _BULLETUI_H_
#define _BULLETUI_H_

#include"scene2D.h"

#define MAX_KEYNUMBER (3)

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CPolygon;
class CNumber;

//*****************************************************************************
// ロゴのクラス
//*****************************************************************************
class CBulletui : public CScene
{
public:																		// 誰でもアクセス可能
	CBulletui(PRIORITY Priority = PRIORITY_EFFECT);							// コンストラクタ
	~CBulletui();																// デストラクタ
																			// メンバ関数
	static CBulletui *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size);				// ロゴの生成
	HRESULT Init(D3DXVECTOR3 pos);											// ロゴの初期化関数
	void Uninit(void);														// ロゴの終了関数
	void Update(void);														// ロゴの更新関数
	void Draw(void);														// ロゴの描画関数

private:																	// 自分だけがアクセス可能
	void SetNumbullet(const int nNumbullet);										// 鍵の数の設定処理
	static CPolygon * m_pPolygon;											// ポリゴンのポインターを生成
	CNumber * m_apNumber[MAX_KEYNUMBER];								// 番号の配列のポインターを生成
	D3DXVECTOR3 m_Pos;														// 現在の位置	
	D3DXVECTOR2 m_Size;														// 大きさ

};
#endif // !_EFFECT_H_