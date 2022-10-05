//=============================================================================
//
// 鍵のUIの処理 [keyui.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _KEYUI_H_
#define _KEYUI_H_

#include"scene2D.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CKeynum;

//*****************************************************************************
// ロゴのクラス
//*****************************************************************************
class CKeyui : public CScene2D
{
public:																		// 誰でもアクセス可能
	CKeyui(PRIORITY Priority = PRIORITY_UI);							// コンストラクタ
	~CKeyui();																// デストラクタ
																			// メンバ関数
	static CKeyui *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size);				// ロゴの生成
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 size);						// ロゴの初期化関数
	void Uninit(void);														// ロゴの終了関数
	void Update(void);														// ロゴの更新関数
	void Draw(void);														// ロゴの描画関数

private:																	// 自分だけがアクセス可能		
	D3DXVECTOR3 m_Pos;														// 現在の位置	
	D3DXVECTOR2 m_Size;														// 大きさ
	static CKeynum * m_pKeynum;

};
#endif // !_EFFECT_H_