//=============================================================================
//
// 背景の処理 [bg.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _BG_H_
#define _BG_H_

#include"scene.h"
class CScene2D; //前方宣言
//*****************************************************************************
// 背景のクラス
//*****************************************************************************
class CBg : public CScene
{
public:																				// 誰でもアクセス可能
	CBg(int nPriority);																// コンストラクタ
	~CBg();																			// デストラクタ
	// メンバ関数
	static CBg *Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size, int nTex);				// 背景の生成
	HRESULT Init(D3DXVECTOR3 pos);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size, int nTex);						// 背景の初期化関数
	void Uninit(void);																// 背景の終了関数
	void Update(void);																// 背景の更新関数
	void Draw(void);																// 背景の描画関数

private:																			// 自分だけがアクセス可能	
	CScene2D * m_apScene2D;															// オブジェクトクラスのポインタ
};
#endif