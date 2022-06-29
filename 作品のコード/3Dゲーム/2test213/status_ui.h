//=============================================================================
//
// ステータスのUIの処理 [status_ui.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _STATUS_UI_H_
#define _STATUS_UI_H_

#include "scene.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CPolygon;
class CNumber;

//*****************************************************************************
// ステータスのUIのクラス
//*****************************************************************************
class CStatus_UI : public CScene
{
public:
	typedef enum
	{
		STAUI_BACK = 0,
		STAUI_STATUS,
		STAUI_ATTACK,
		STAUI_MAX
	} STAUI;

	CStatus_UI(int nPriority = PRIORITY_NOMAL);									// コンストラクタ
	~CStatus_UI();																// デストラクタ

																				// メンバ関数
	static CStatus_UI *Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size);		// ランキングの生成
	HRESULT Init(D3DXVECTOR3 pos);												// ステータスのUIの初期化関数
	void Uninit(void);															// ステータスのUIの終了関数　
	void Update(void);															// ステータスのUIの更新関数
	void Draw(void);															// ステータスのUIの描画関数
	void SetStatusNumber(const int nStatus);

private:																		// 自分だけがアクセス可能
	inline void LodeStatusUI();
	static const char *m_pStatusUIFlieName;												// 
	static const int m_nStatusNumber;												// 
	static CPolygon * m_pPolygon[STAUI_MAX];											// ポリゴンクラスのポインタ
	static CNumber * m_apNumber[2];												// 番号クラスのポインタ
	D3DXVECTOR2 m_Size;
	D3DXVECTOR3 m_LodePos[STAUI_MAX];
	D3DXVECTOR2 m_LodeSize[STAUI_MAX];
	int m_nStatus;
};

#endif