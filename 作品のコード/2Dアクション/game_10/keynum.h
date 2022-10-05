//=============================================================================
//
// 鍵のUIの処理 [keyui.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _KEYNUM_H_
#define _KEYNUM_H_

#include"scene2D.h"

#define MAX_KEYNUMBER (3)

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CNumber;

//*****************************************************************************
// ロゴのクラス
//*****************************************************************************
class CKeynum : public CScene2D
{
public:																		// 誰でもアクセス可能
	CKeynum(PRIORITY Priority = PRIORITY_UI);							// コンストラクタ
	~CKeynum();																// デストラクタ
																			// メンバ関数
	static CKeynum *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size);				// ロゴの生成
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 size);						// ロゴの初期化関数
	void Uninit(void);														// ロゴの終了関数
	void Update(void);														// ロゴの更新関数
	void Draw(void);														// ロゴの描画関数

private:																	// 自分だけがアクセス可能
	void SetNumKey(const int nNumKey);										// 鍵の数の設定処理
	CNumber * m_apNumber[MAX_KEYNUMBER];								// 番号の配列のポインターを生成
	D3DXVECTOR3 m_Pos;														// 現在の位置		

};
#endif // !_EFFECT_H_