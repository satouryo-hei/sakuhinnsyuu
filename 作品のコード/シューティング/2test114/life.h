//=============================================================================
//
// 命の処理 [life.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _LIFE_H_
#define _LIFE_H_

#include"scene.h"

class CNumber; // 前方宣言
class CUi;

//*****************************************************************************
// 命のクラス
//*****************************************************************************
class CLife : public CScene
{
public:																// 誰でもアクセス可能
	CLife(int nPriority = PRIORITY_UI);														// コンストラクタ
	~CLife();														// デストラクタ
																	// メンバ関数
	static CLife *Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size);		// 命の生成
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);				// 命の初期化関数
	void Uninit(void);												// 命の終了関数
	void Update(void);												// 命の更新関数
	void Draw(void);												// 命の描画関数
	void SetLife(int nLife);										// 命の配置関数
	void AddLife(int nValue);										// 命の計算関数
	int GetLife(void) { return m_nLife; }							// 命の取得処理

private:															// 自分だけがアクセス可能
	CNumber* m_apNumber[2];											// ナンバーのポインター
	CUi*  m_apUi;										// ポリゴンのポインター
	int m_nLife;													// 体力
	
};
#endif
