//=============================================================================
//
// ランキングの処理 [ranking.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _RANKING_H_
#define _RANKING_H_

#include"scene2D.h"

#define PORT_NUMBER (12345)	//ポート番号

#define RANKING_TEXT "data/TEXT/Ranking.txt"
#define ONLINE_TEXT "data/TEXT/Online.txt"
#define ID_TEXT "data/TEXT/id.txt"
#define MAX_RANKING (5)
#define MAX_DATA (32)
#define MAX_NUM (256)

class CScore; // 前方宣言

//*****************************************************************************
// ランキングのクラス
//*****************************************************************************
class CRanking : public CScene2D
{
public:																// 誰でもアクセス可能
	CRanking(int nPriority = PRIORITY_UI);							// コンストラクタ
	~CRanking();													// デストラクタ
	// メンバ関数
	static CRanking *Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size);		// ランキングの生成
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);				// ランキングの初期化関数
	void Uninit(void);												// ランキングの終了関数
	void Update(void);												// ランキングの更新関数
	void Draw(void);												// ランキングの描画関数
	inline void SetRanking(const int nRanking);						// ランキングの設定関数
	inline void GetOnlineRanking(void);								// オンラインのランキングの取得関数
	inline int SetOnlineRanking(const int nScore);					// オンラインのランキングの設定関数
	void NewScore(const int nScore);												// 時間とスコアの計算する関数
	bool GetClear(void) { return m_bGameClear; }					// ゲームをクリアしたかどうかの取得関数
	void SetClear(bool bClear) { m_bGameClear = bClear; }			// ゲームをクリアしたかどうかの設定関数 

private:															// 自分だけがアクセス可能
	int AddScoreTime(void);											// 時間とスコアの計算する関数
	inline void LodeScore(void);									// スコアの読み込み関数
	inline void LodeOfflineRnking(void);							// オフライン時のランキングの読み込み関数
	inline bool LodeOnline(void);									// オンラインにするのかを読み込み関数
	// メンバ変数
	static CScore* m_apScore[MAX_RANKING];							// スコアのポインター
	int m_aRankScore[MAX_RANKING];									// 現在のランキングデータの取得用変数
	int m_nNowScore;												// 現在のスコア取得用変数
	char m_aRnkingData[MAX_RANKING][MAX_DATA];						// 現在の順位
	bool m_bGameClear;												// ゲームクリアしたかどうか
};
#endif