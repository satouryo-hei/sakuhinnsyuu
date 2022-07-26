//=============================================================================
//
// ブロックの処理 [block.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include"scene.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CNoneBlock;
class CMoveBlock;
class CPushBlock;

//*****************************************************************************
// ブロックのクラス
//*****************************************************************************
class CBlock : public CScene
{
public:																					// 誰でもアクセス可能
	typedef enum
	{
		BLOCKTYPE_NOME = 0,
		BLOCKTYPE_MOVEING,
		BLOCKTYPE_PUSH,
		BLOCKTYPE_MAX
	} BLOCKTYPE;

	CBlock(int nPriority = PRIORITY_BLOCK);													// コンストラクタ
	~CBlock();																				// デストラクタ
																							// メンバ関数
	static CBlock *Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size, D3DXVECTOR3 move, 
		int nBlockType, int nMovetype, float fMin, float fMax,bool bBreak ,int nTex);										// 時間の生成
	HRESULT Init(D3DXVECTOR3 pos);									// 時間の初期化関数
	void Uninit(void);																	// 時間の終了関数
	void Update(void);																	// 時間の更新関数
	void Draw(void);																	// 時間の描画関数
	void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR2 Size, D3DXVECTOR3 move,
		int nBlockType, int nMovetype, float fMin, float fMax, bool bBreak,int nTex);

private:																				// 自分だけがアクセス可能
	static CNoneBlock * m_pNone;
	static CMoveBlock * m_pMove;
	static CPushBlock * m_pPush;
	D3DXVECTOR3 m_pos;
};
#endif