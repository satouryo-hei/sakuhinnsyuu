//=============================================================================
//
// uiの処理 [player.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _UI_H_
#define _UI_H_

#include"scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SETUITEXT "data/TEXT/Setui.txt"

//*****************************************************************************
// プレイヤークラス
//*****************************************************************************
class CUi : public CScene
{
public:																// 誰でもアクセス可能

	CUi(int nPriority = PRIORITY_PLAYER);										// コンストラクタ
	~CUi();														// デストラクタ
				
	static CUi *Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size);							// タイトルロゴの生成
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);				// プレイヤの初期化関数
	void Uninit(void);												// プレイヤの終了関数
	void Update(void);												// プレイヤの更新関数
	void Draw(void);												// プレイヤの描画関数
	

private:															// 自分だけがアクセス可能
	inline void LodeUI(void);										// UIの読み込み処理
	int m_nNumUi;
	D3DXVECTOR3 m_LodePos[2];
	D3DXVECTOR2 m_LodeSize[2];
};
#endif
