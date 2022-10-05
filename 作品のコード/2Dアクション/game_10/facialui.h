//=============================================================================
//
// 顔の差分の表示処理 [facialui.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _FACIALUI_H_
#define _FACIALUI_H_

#include"scene2D.h"

//*****************************************************************************
// 顔の差分表示のクラス
//*****************************************************************************
class CFacialui : public CScene2D
{
public:																					// 誰でもアクセス可能
	/* 感情(emotions)*/
	// 顔の種類
	typedef enum
	{
		FACE_NOMAL = 0,																	// ノーマル
		FACE_JOY,																		// 喜び
		FACE_ANGER,																		// 怒り
		FACE_SAD,																		// 悲しみ
		FACE_MAX																		// 顔の全種類
	} FACE;
	CFacialui(int nPriority = PRIORITY_UI);												// コンストラクタ
	~CFacialui();																		// デストラクタ
																						// メンバ関数
	static CFacialui *Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size, int nTex);				// 顔の差分の生成
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);									// 顔の差分の初期化関数
	void Uninit(void);																	// 顔の差分の終了関数
	void Update(void);																	// 顔の差分の更新関数
	void Draw(void);																	// 顔の差分の描画関数
private:																				// 自分だけがアクセス可能
	D3DXVECTOR3 m_Pos;																	// 現在の位置	
	int m_nPatternAnim;																	// パターンアニメーション
	int	m_nCounterAnim;																	// カウンターアニメーション
};
#endif