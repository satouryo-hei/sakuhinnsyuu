//=============================================================================
//
// フェードの処理 [fade.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _FADE_H_//endifとセット（必ず一番上
#define _FADE_H_

#include "scene2D.h"
#include"manager.h"

//*****************************************************************************
// フェードのクラス
//*****************************************************************************
class CFade : public CScene2D
{
public:
	//フェードの状態
	typedef enum
	{
		FADE_NONE = 0,																//何もしてない状態
		FADE_IN,																	//フェードイン(明るく)
		FADE_OUT,																	//フェードアウト(暗く)
		FADE_MAX
	} FADE;

	CFade(int nPriority = PRIORITY_FADE);														// コンストラクタ
	~CFade();																		// デストラクタ

	// メンバ関数
	static CFade *Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size,CManager::MODE mode);	// 弾の生成
	static HRESULT Load(void);														// テクスチャの読み込む
	static void Unload(void);														// テクスチャの破棄
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);								// フェードの初期化関数
	void Uninit(void);																// フェードの終了関数　
	void Update(void);																// フェードの更新関数
	void Draw(void);																// フェードの描画関数
	static FADE GetFade(void) { return m_Fade; }									// フェードの取得処理
	static void SetFade(CManager::MODE modeNext);									// フェードの配置処理

private:																			// 自分だけがアクセス可能
	static LPDIRECT3DTEXTURE9 m_pTexture;											// 共有するテスクチャのポインタ
	static FADE m_Fade;																// フェードの状態
	static D3DXCOLOR m_col;																// フェードの色
	static CManager::MODE m_ModeNext;
	int m_nRed;																		// 赤
	int m_nGreen;																	// 緑
	int m_nBlue;																	// 青
	int m_nAlpha;																	// アルファ
	
};
#endif // _FADE_H_//ifndefとセット（必ず一番下
