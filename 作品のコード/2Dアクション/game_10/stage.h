//=============================================================================
//
// ステージ処理 [stage.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _STAGE_H_
#define _STAGE_H_

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
class CStage : public CScene
{
public:																		// 誰でもアクセス可能
	// ステージの種類
	typedef enum
	{
		STAGE_INVALID = -1,															// 無し
		STAGE_TUTORIAL = 0,															// チュートリアル
		STAGE_TOP,																	// 最初
		STAGE_MAX																	// ステージの種類の最後
	} STAGE;
	CStage(int Priority = PRIORITY_NOMAL);											// コンストラクタ
	virtual ~CStage();																		// デストラクタ
	// メンバ関数
	static CStage *Create(STAGE stage,D3DXVECTOR3 pos, const char * pStageFileName);// ステージの生成
	virtual HRESULT Init(D3DXVECTOR3 pos);											// ステージの初期化関数
	virtual void Uninit(void);														// ステージの終了関数
	virtual void Update(void) = 0;													// ステージの更新関数
	virtual void Draw(void) = 0;													// ステージの描画関数	


private:																			// 自分だけがアクセス可能
	inline void LodeStage(const char * pStageFileName);								// ステージの読み込み処理
	int m_aMap[128][256];															// ステージの読み込みんだ物を保存用変数
	int m_nLine;																	// 行
	int m_nColumn;																	// 列
	int m_nNum;																		// 数
	static CBlock* m_pBlock[256];													// ブロックのポインター	
};
#endif