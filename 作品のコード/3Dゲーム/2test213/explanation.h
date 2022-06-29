//=============================================================================
//
// 説明文の処理 [effect.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _EXPLANATION_H_
#define _EXPLANATION_H_

#include"scene.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CPolygon;

//*****************************************************************************
// 説明文のクラス
//*****************************************************************************
class CExplanation : public CScene
{
public:																// 誰でもアクセス可能
	// 説明文の種類
	typedef enum
	{
		EXPLANATION_SPEECH_BUBBLE = 0,
		EXPLANATION_LETTER_TITLE,
		EXPLANATION_LETTER_TUTORIAL,
		EXPLANATION_LETTER_GAME,
		EXPLANATION_LETTER_RESULT,
		EXPLANATION_MAX
	} EXPLANATION;

	CExplanation(PRIORITY Priority = PRIORITY_EFFECT);		// コンストラクタ
	~CExplanation();										// デストラクタ
															// メンバ関数
	static CExplanation *Create(D3DXVECTOR3 pos,int nTex);	//  説明文の生成
	HRESULT Init(D3DXVECTOR3 pos);							//  説明文の初期化関数
	void Uninit(void);										//  説明文の終了関数
	void Update(void);										//  説明文の更新関数
	void Draw(void);										//  説明文の描画関数
	void SetSize(D3DXVECTOR2 Size,int nNum);
	void SetColor(D3DXCOLOR Col, int nNum);

private:													// 自分だけがアクセス可能
	static CPolygon * m_pPolygon[EXPLANATION_MAX];			// ポリゴンの配列ポインターを生成
	D3DXVECTOR2 m_Size;										// 大きさ
	D3DXCOLOR m_Col;										// 色
	int m_nTex;
};
#endif // !_EFFECT_H_