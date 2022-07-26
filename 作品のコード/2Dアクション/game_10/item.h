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
	typedef enum 
	{
		ITEM_NONE = 0,
		ITEM_ATTACK,
		ITEM_LIFE,
		ITEM_MAX
	} ITEM;

	CItem(int nPriority = PRIORITY_NOMAL);							// コンストラクタ
	~CItem();														// デストラクタ
	// メンバ関数
	static CItem *Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size);		// 時間の生成
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);				// 時間の初期化関数
	void Uninit(void);												// 時間の終了関数
	void Update(void);												// 時間の更新関数
	void Draw(void);												// 時間の描画関数

private:															// 自分だけがアクセス可能	
	ITEM item;
	int m_nAttack;
	int m_Life;

};
#endif