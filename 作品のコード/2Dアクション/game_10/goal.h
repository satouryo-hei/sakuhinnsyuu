//=============================================================================
//
// ゴールの処理 [goal.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _GOAL_H_
#define _GOAL_H_

#include"scene2D.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CPushButton;

//*****************************************************************************
// ゴールのクラス
//*****************************************************************************
class CGoal : public CScene2D
{
public:																// 誰でもアクセス可能
	CGoal(int nPriority = PRIORITY_NOMAL);							// コンストラクタ
	~CGoal();														// デストラクタ
																	// メンバ関数
	static CGoal *Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size);		// ゴールの生成
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);				// ゴールの初期化関数
	void Uninit(void);												// ゴールの終了関数
	void Update(void);												// ゴールの更新関数
	void Draw(void);												// ゴールの描画関数

private:															// 自分だけがアクセス可能		
	static CPushButton * m_pPushButton;								// 押されるボタンのポインター生成
	D3DXVECTOR3 m_Pos;												// ゴールの現在地	
	D3DXVECTOR2 m_Size;												// ゴールの大きさ	
	bool m_bPush;													// 一度押されたかの判別用変数
};
#endif