//=============================================================================
//
// 点数の処理 [score.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include"scene2D.h"

#define SCORE_TEXT "data/TEXT/score.txt"
#define NUMSCORE (8)

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CNumber;

//*****************************************************************************
// 点数クラス
//*****************************************************************************
class CScore : public CScene2D
{
public:																// 誰でもアクセス可能
	CScore(PRIORITY nPriority = PRIORITY_UI);							// コンストラクタ
	~CScore();														// デストラクタ
																	// メンバ関数
	static CScore *Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size);		// 点数の生成
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);				// 点数の初期化関数
	void Uninit(void);												// 点数の終了関数
	void Update(void);												// 点数の更新関数
	void Draw(void);												// 点数の描画関数
	void SetScore(int nScore);										// 点数の配置関数
	void AddScore(int nValue);										// 点数の計算関数
	int GetScore(void) { return m_nScore; }							// 点数の取得関数
	static int LodeScore(void);

private:															// 自分だけがアクセス可能
	inline void SaveScore(void);									// 点数の書き込み関数
	CNumber* m_apNumber[NUMSCORE];											// ナンバーのポインター
	int m_nScore;													// 点数

};
#endif