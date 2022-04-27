//=============================================================================
//
// チュートリアルの処理 [tutorial.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "scene.h"

class CScene2D;
class CPress_Next;

//*****************************************************************************
// リザルトのクラス
//*****************************************************************************
class CTutorial : public CScene
{
public:
	CTutorial(int nPriority = PRIORITY_BG);																	// コンストラクタ
	~CTutorial();																	// デストラクタ

	// メンバ関数
	static HRESULT Load(void);													// テクスチャの読み込む
	static void Unload(void);													// テクスチャの破棄
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);							// タイトルの初期化関数
	void Uninit(void);															// タイトルの終了関数　
	void Update(void);															// タイトルの更新関数
	void Draw(void);															// タイトルの描画関数


private:																		// 自分だけがアクセス可能
	static LPDIRECT3DTEXTURE9 m_pTexture;										// 共有するテスクチャのポインタ
	static CPress_Next * m_Press_Next;
	CScene2D * m_apScene2D;														// オブジェクトクラスのポインタ
	bool m_bNextMode;
};
#endif