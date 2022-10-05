//=============================================================================
//
// ステージ処理 [stage.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _STAGE_SECOND_H_
#define _STAGE_SECOND_H_

#include"scene.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CBlock;
class CGoal;
class CPlayer;
//*****************************************************************************
// ステージクラス
//*****************************************************************************
class CStage_Top : public CScene
{
public:																// 誰でもアクセス可能
	CStage_Top(int Priority = PRIORITY_NOMAL);						// コンストラクタ
	~CStage_Top();													// デストラクタ
																	// メンバ関数
	static CStage_Top *Create(D3DXVECTOR3 pos);						// ゲームのステージの生成
	HRESULT Init(D3DXVECTOR3 pos);									// ゲームのステージの初期化関数
	void Uninit(void);												// ゲームのステージの終了関数
	void Update(void);												// ゲームのステージの更新関数
	void Draw(void);												// ゲームのステージの描画関数	


private:															// 自分だけがアクセス可能
	inline void LodeStage(void);									// ステージの読み込み処理
	int m_aMap[128][256];											// ステージの読み込みんだ物を保存用変数
	int m_nLine;													// 行
	int m_nColumn;													// 列
	int m_nNum;														// 数
	static CBlock* m_pBlock[256];									// ブロックのポインター
	static const char * m_pTutorial_StageFileName;					// ステージのファイル名
	static CGoal * m_pGoal;											// ゴールのポインター
	static CPlayer * m_pPlayer;											// ゴールのポインター
};
#endif