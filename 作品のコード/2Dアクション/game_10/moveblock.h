//=============================================================================
//
// ブロックの処理 [block.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _MOVEBLOCK_H_
#define _MOVEBLOCK_H_

#include"scene2D.h"

//*****************************************************************************
// 移動ブロックのクラス
//*****************************************************************************
class CMoveBlock : public CScene2D
{
public:																					// 誰でもアクセス可能
	typedef enum
	{	
		MOVE_NONE = 0,
		MOVE_UP,
		MOVE_DOWN,
		MOVE_LEFT,
		MOVE_RIGHT,
		MOVE_MAX
	} MOVE;

	CMoveBlock(int nPriority = PRIORITY_BLOCK);													// コンストラクタ
	~CMoveBlock();																				// デストラクタ
																							// メンバ関数
	static CMoveBlock *Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size, D3DXVECTOR3 move,
		int nCondition, float fMin, float fMax, int nTex);										// 時間の生成
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);									// 時間の初期化関数
	void Uninit(void);																	// 時間の終了関数
	void Update(void);																	// 時間の更新関数
	void Draw(void);																	// 時間の描画関数
	void SetBlock(void);
	int MoveColision(void);	
	static int GetMoveBlock(void) { return m_MoveBlock; }							// 動いているかの状態の取得	
	D3DXVECTOR3 GetPos() { return m_pos; }
	D3DXVECTOR3 GetPosold() { return m_posOld; }
	D3DXVECTOR3 GetMove() { return m_move; }
	D3DXVECTOR2 Getsize() { return m_size; }
	void SetMove(D3DXVECTOR3 move) { m_move = move; }

private:																				// 自分だけがアクセス可能
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_move;
	D3DXVECTOR2 m_size;
	D3DXVECTOR3 m_posOld;
	static MOVE m_MoveBlock;																// 動いているかの状態	
	int m_nBlockType;
	int m_nBlockCondition;
	float m_fMin;
	float m_fMax;
	bool m_bMove;
};
#endif