//=============================================================================
//
// uiの管理型処理 [ui_manager.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _UI_MANAGER_H_
#define _UI_MANAGER_H_

#include"scene2D.h"
#include"ui.h"

#define SETUITEXT "data/TEXT/Setui.txt"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CUi;

//*****************************************************************************
// uiの管理型クラス
//*****************************************************************************
class CUI_Manager : public CScene
{
public:
	CUI_Manager();																	// コンストラクタ
	~CUI_Manager();																	// デストラクタ

	// 静的メンバ関数
	static CUI_Manager *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 Size);// UIの管理型の生成
	static CUi*GetUi(int uitype) { return m_pUi[uitype]; }							// ユーザーインターフェースクラスのポインタ
	static int GetNumUI(void) { return m_nAllui; }									// 現在の個数取得関数

																					// メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);								// UIの管理型の初期化関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 Size);				// UIの管理型の初期化関数
	void Uninit(void);																// UIの管理型の終了関数　
	void Update(void);																// UIの管理型の更新関数
	void Draw(void);																// UIの管理型の描画関数	
	void SetUI(D3DXVECTOR3 pos, D3DXVECTOR3 size);									// UIの配置関数

	bool GetUse(void) { return m_bUse; }											// 使用状況の取得関数
	int GetMax(void) { return m_nMaxUI; }											// 最大数取得関数
	void SetMax(int nMax) { (int)m_nMaxUI = nMax; }											// 最大数取得関数

private:																			// 自分だけがアクセス可能
	inline void SaveUI(void);														// UIの書き込み処理
	inline void LodeUI(void);														// UIの読み込み処理
	void LodeSetAll(void);															// すべてのUIを設置処理
	void LodeSetNow(void);															// 今のUIを設置処理

	// 静的メンバ変数
	static CUi*m_pUi[LIMITUI];														// ユーザーインターフェースのインスタンス生成
	static int m_nAllui;															// UIは全部で何個か

	// メンバ変数
	const int m_MinUI;																// UIの最小値
	const int m_nMaxUI;																// UIの最大値
	D3DXVECTOR3 m_Pos;																// 位置
	D3DXVECTOR3 m_Size;																// 大きさ
	D3DXVECTOR3 m_Move;																// 移動量
	D3DXCOLOR m_Color;																// 色
	D3DXVECTOR3 m_SavePos[LIMITUI];													// 保存用の位置の変数
	D3DXVECTOR3 m_SaveSize[LIMITUI];												// 保存用の大きさの変数
	D3DXVECTOR3 m_LodePos[LIMITUI];													// 読み込み用の位置の変数
	D3DXVECTOR3 m_LodeSize[LIMITUI];												// 読み込み用の大きさの変数
	int m_nTex;																		// 何番目のテクスチャか
	int m_nLodeUI;																	// 読み込み用のUIの数
	bool m_bUse;																	// 使用してるか
};
#endif