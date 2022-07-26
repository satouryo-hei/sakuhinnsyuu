//=============================================================================
//
// ブロックの処理 [block.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _NONEBLOCK_H_
#define _NONEBLOCK_H_

#include"scene2D.h"

//*****************************************************************************
// ブロックのクラス
//*****************************************************************************
class CNoneBlock : public CScene2D
{
public:																					// 誰でもアクセス可能
	CNoneBlock(int nPriority = PRIORITY_BLOCK);													// コンストラクタ
	~CNoneBlock();																				// デストラクタ
																							// メンバ関数
	static CNoneBlock *Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size,bool bBreak, int nTex);										// 時間の生成
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);									// 時間の初期化関数
	void Uninit(void);																	// 時間の終了関数
	void Update(void);																	// 時間の更新関数
	void Draw(void);																	// 時間の描画関数
	void Colision();
	void Colision(int nPro, D3DXVECTOR3 pos, D3DXVECTOR3 posold,D3DXVECTOR2 Size);

private:																				// 自分だけがアクセス可能
	D3DXVECTOR3 m_pos;	
	D3DXVECTOR2 m_size;			
	bool m_bBreak;																		// 壊れるかどうか
	bool m_bUse;
};
#endif