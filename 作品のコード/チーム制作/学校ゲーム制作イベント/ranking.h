//=============================================================================
//
// ランキングの処理 [ranking.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _RANKING_H_
#define _RANKING_H_

#include"scene.h"

#define PORT_NUMBER (12345)	//ポート番号

#define RANKING_TEXT "data/TEXT/Ranking.txt"
#define ONLINE_TEXT "data/TEXT/Online.txt"
#define ID_TEXT "data/TEXT/id.txt"
#define MAX_RANKING (5)
#define MAX_DATA (32)
#define MAX_NUM (256)

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CScore;

//*****************************************************************************
// ランキングのクラス
//*****************************************************************************
class CRanking : public CScene
{
public:																// 誰でもアクセス可能
	CRanking(PRIORITY nPriority = PRIORITY_UI);							// コンストラクタ
	~CRanking();													// デストラクタ
																	// メンバ関数
	static CRanking *Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size);		// ランキングの生成
	HRESULT Init(D3DXVECTOR3 pos/*, D3DXVECTOR2 m_Size*/);				// ランキングの初期化関数
	void Uninit(void);												// ランキングの終了関数
	void Update(void);												// ランキングの更新関数
	void Draw(void);												// ランキングの描画関数
	inline void SetRanking(const int nRanking);						// ランキングの設定関数
	inline void GetOnlineRanking(void);								// オンラインのランキングの取得関数
	inline int SetOnlineRanking(const int nScore);					// オンラインのランキングの設定関数
	void NewScore(const int nScore);												// 時間とスコアの計算する関数	

private:															// 自分だけがアクセス可能
	inline void LodeRankingUI(void);
	int AddScoreTime(const int nScore);											// 時間とスコアの計算する関数	
	inline void LodeOfflineRnking(void);							// オフライン時のランキングの読み込み関数
	inline bool LodeOnline(void);									// オンラインにするのかを読み込み関数
																	// メンバ変数
	static const char * m_apUIFlieName;								// 現在の順位
	static CScore* m_apScore[MAX_RANKING];							// スコアのポインター
	D3DXVECTOR3 m_Pos;												// 現在位置
	D3DXVECTOR2 m_Size;												// 大きさ
	int m_aRankScore[MAX_RANKING];									// 現在のランキングデータの取得用変数	
	char m_aRnkingData[MAX_RANKING][MAX_DATA];						// 現在の順位
	bool m_bGameClear;												// ゲームクリアしたかどうか
	bool m_bGamePlay;												// ゲームクリアしたかどうか
	D3DXVECTOR3 m_LodePos[MAX_RANKING];
	D3DXVECTOR2 m_LodeSize[MAX_RANKING];
};

//入れ替え処理
template<class T> void swap(T &data0, T &data1)
{
	T dataWk;
	dataWk = data0;
	data0 = data1;
	data1 = dataWk;
}
#endif