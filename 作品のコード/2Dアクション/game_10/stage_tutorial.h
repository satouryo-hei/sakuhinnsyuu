//=============================================================================
//
// ステージ処理 [stage.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _STAGE_TUTORIAL_H_
#define _STAGE_TUTORIAL_H_

#include"scene.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CBlock;
class CGoal;
class CMoveBlock;
class CPushBlock;
//*****************************************************************************
// ステージクラス
//*****************************************************************************
class CStage_Tutorial : public CScene
{
public:																// 誰でもアクセス可能
	CStage_Tutorial(int Priority = PRIORITY_NOMAL);				// コンストラクタ
	~CStage_Tutorial();												// デストラクタ
																	// メンバ関数
	static CStage_Tutorial *Create(D3DXVECTOR3 pos);				// ステージの選択の生成
	HRESULT Init(D3DXVECTOR3 pos);									// ステージの選択の初期化関数
	void Uninit(void);												// ステージの選択の終了関数
	void Update(void);												// ステージの選択の更新関数
	void Draw(void);												// ステージの選択の描画関数	


private:															// 自分だけがアクセス可能
	inline void LodeStage(void);									// ステージの読み込み処理
	int m_aMap[128][256];											// ステージの読み込みんだ物を保存用変数
	int m_nLine;													// 行
	int m_nColumn;													// 列
	int m_nNum;														// 数
	static CBlock* m_pBlock[256];									// ブロックのポインター
	static const char * m_pTutorial_StageFileName;					// ステージのファイル名

	static CGoal * m_pGoal;											// ゴールのポインター
	static CMoveBlock * m_pMove[128];								// 移動ブロックのポインター
	static CPushBlock * m_pPush[128];								// 押すブロックのポインター
};
#endif