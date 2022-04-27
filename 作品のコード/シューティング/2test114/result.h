//=============================================================================
//
// リザルトの処理 [result.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "scene.h"

class CScene2D;

//*****************************************************************************
// リザルトのクラス
//*****************************************************************************
class CResult : public CScene
{
public:
	CResult(int nPriority = PRIORITY_BG);																	// コンストラクタ
	~CResult();																	// デストラクタ

	// メンバ関数
	static HRESULT Load(void);													// テクスチャの読み込む
	static void Unload(void);													// テクスチャの破棄
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);							// タイトルの初期化関数
	void Uninit(void);															// タイトルの終了関数　
	void Update(void);															// タイトルの更新関数
	void Draw(void);															// タイトルの描画関数


private:																		// 自分だけがアクセス可能
	static LPDIRECT3DTEXTURE9 m_pTexture;										// 共有するテスクチャのポインタ
	CScene2D * m_apScene2D;														// オブジェクトクラスのポインタ
	bool m_bNextMode;
};

#endif