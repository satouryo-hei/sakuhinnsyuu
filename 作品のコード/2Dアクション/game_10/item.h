//=============================================================================
//
// 時間の処理 [item.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

#include"scene2D.h"

//*****************************************************************************
// 時間のクラス
//*****************************************************************************
class CItem : public CScene2D
{
public:																// 誰でもアクセス可能
	CItem(int nPriority = PRIORITY_ITEM);							// コンストラクタ
	~CItem();														// デストラクタ
																	// メンバ関数
	static CItem *Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size);		// 時間の生成
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);				// 時間の初期化関数
	void Uninit(void);												// 時間の終了関数
	void Update(void);												// 時間の更新関数
	void Draw(void);												// 時間の描画関数	

private:															// 自分だけがアクセス可能
	void Colision(void);
	D3DXVECTOR3 m_pos;
	D3DXVECTOR2 m_size;
};
#endif
