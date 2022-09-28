//=============================================================================
//
// 押すボタンの表示処理 [block.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _PUSHBUTTON_H_
#define _PUSHBUTTON_H_

#include"scene2D.h"

//*****************************************************************************
// 押すボタン表示のクラス
//*****************************************************************************
class CPushButton : public CScene2D
{
public:																					// 誰でもアクセス可能
	CPushButton(int nPriority = PRIORITY_UI);													// コンストラクタ
	~CPushButton();																				// デストラクタ
																								// メンバ関数
	static CPushButton *Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size,int nTex);										// 時間の生成
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);									// 時間の初期化関数
	void Uninit(void);																	// 時間の終了関数
	void Update(void);																	// 時間の更新関数
	void Draw(void);																	// 時間の描画関数
	static bool GetUse() { return m_bUse; }
	static void SetUse(bool bUse) { m_bUse = bUse; }
private:																				// 自分だけがアクセス可能
	D3DXVECTOR3 m_Pos;																	// 現在の位置
	static bool m_bUse;																	// 使っているかどうか
	int m_nPatternAnim;																	// パターンアニメーション
	int	m_nCounterAnim;																	// カウンターアニメーション
};
#endif