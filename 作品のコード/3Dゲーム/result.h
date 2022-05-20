//=============================================================================
//
// リザルトの処理 [result.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "scene.h"

class CBg;

//*****************************************************************************
// リザルトのクラス
//*****************************************************************************
class CResult : public CScene
{
public:
	CResult(int nPriority = PRIORITY_NOMAL);									// コンストラクタ
	~CResult();																	// デストラクタ

	// メンバ関数
	HRESULT Init(D3DXVECTOR3 pos);												// リザルトの初期化関数
	void Uninit(void);															// リザルトの終了関数　
	void Update(void);															// リザルトの更新関数
	void Draw(void);															// リザルトの描画関数


private:																		// 自分だけがアクセス可能
	static LPDIRECT3DTEXTURE9 m_pTexture;										// 共有するテスクチャのポインタ
	static CBg * m_pBg;															// 背景クラスのポインタ
	bool m_bFade;
};

#endif