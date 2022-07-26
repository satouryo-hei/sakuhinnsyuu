//=============================================================================
//
// ブロックの処理 [block.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _PUSHBLOCK_H_
#define _PUSHBLOCK_H_

#include"scene2D.h"

//*****************************************************************************
// 押すブロックのクラス
//*****************************************************************************
class CPushBlock : public CScene2D
{
public:																					// 誰でもアクセス可能
	CPushBlock(int nPriority = PRIORITY_BLOCK);													// コンストラクタ
	~CPushBlock();																				// デストラクタ
																							// メンバ関数
	static CPushBlock *Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size, D3DXVECTOR3 move,int nTex);										// 時間の生成
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);									// 時間の初期化関数
	void Uninit(void);																	// 時間の終了関数
	void Update(void);																	// 時間の更新関数
	void Draw(void);																	// 時間の描画関数
	void NoneColision(void);
	D3DXVECTOR3 GetPos() { return m_pos; }
	D3DXVECTOR2 Getsize() { return m_size; }
	D3DXVECTOR3 GetPosold() { return m_posOld; }
	D3DXVECTOR3 GetMove() { return m_move; }
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetMove(D3DXVECTOR3 move) { m_move = move; }

private:																				// 自分だけがアクセス可能
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_move;
	D3DXVECTOR2 m_size;
	D3DXVECTOR3 m_posOld;
};
#endif