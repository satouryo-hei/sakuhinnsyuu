//=============================================================================
//
// タイトルロゴの処理 [title_logo.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _TITLE_LOGO_H_
#define _TITLE_LOGO_H_

#include"scene.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CPolygon; //前方宣言

//*****************************************************************************
// タイトルロゴのクラス
//*****************************************************************************
class CTitle_Logo : public CScene
{
public:																				// 誰でもアクセス可能
	CTitle_Logo(PRIORITY nPriority = PRIORITY_UI);																// コンストラクタ
	~CTitle_Logo();																			// デストラクタ
																							// メンバ関数
	static CTitle_Logo *Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size);							// タイトルロゴの生成
	HRESULT Init(D3DXVECTOR3 pos);								// タイトルロゴの初期化関数
	void Uninit(void);																// タイトルロゴの終了関数
	void Update(void);																// タイトルロゴの更新関数
	void Draw(void);																// タイトルロゴの描画関数

private:																			// 自分だけがアクセス可能	
	static CPolygon * m_Polygon;											// ポリゴンクラスのポインタ
	D3DXVECTOR3 m_pos;																// ポリゴンの位置
	D3DXVECTOR3 m_move;																// ポリゴンの移動量
	D3DXVECTOR2 m_Size;																// ポリゴンの大きさ
};
#endif