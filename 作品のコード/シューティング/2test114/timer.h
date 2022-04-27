//=============================================================================
//
// 時間の処理 [timer.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _TIMERE_H_
#define _TIMERE_H_

#define TIMETEXT "data/TEXT/time.txt"

#include"scene2D.h"

class CNumber; // 前方宣言

//*****************************************************************************
// 時間のクラス
//*****************************************************************************
class CTimer : public CScene2D
{
public:																// 誰でもアクセス可能
	CTimer(int nPriority = PRIORITY_UI);							// コンストラクタ
	~CTimer();														// デストラクタ
																	// メンバ関数
	static CTimer *Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size);		// 時間の生成
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);				// 時間の初期化関数
	void Uninit(void);												// 時間の終了関数
	void Update(void);												// 時間の更新関数
	void Draw(void);												// 時間の描画関数
	void SetTimer(int nTimer);										// 時間の配置関数
	static int GetTimer(void) { return m_nTimer; }					// 時間の取得関数
	static void SeveTimer(int nTime);
	static int LodeTimer(void);

private:															// 自分だけがアクセス可能
	CNumber* m_apNumber[8];											// ナンバーのポインター
	static int m_nTimer;													// 時間
	int m_nCntTimer;												// 時間を数える

};
#endif
