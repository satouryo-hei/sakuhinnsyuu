//= == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == ==
//
// 管理処理 [stage_manager.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _STAGE_MANAGER_H_
#define _STAGE_MANAGER_H_

#include"main.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CStage_Tutorial;
class CStage_Top;
//*****************************************************************************
// マネージャークラス
//*****************************************************************************
class CStage_Manager
{
public:
	// ステージの遷移処理
	typedef enum
	{
		STAGE_INVALID = -1,														// 無し
		STAGE_TUTORIAL = 0,														// チュートリアル
		STAGE_TOP,																// 最初
		STAGE_MAX																// ステージの種類の最後
	} STAGE;

	CStage_Manager();															// コンストラクタ
	~CStage_Manager();															// デストラクタ
																				// メンバ関数
	HRESULT Init(void);															// マネージャーの初期化関数	
	void Uninit(void);															// マネージャーの終了関数　
	void Update(void);															// マネージャーの更新関数
	void Draw(void);															// マネージャーの描画関数
	static void SetStage(STAGE Stage);											// ステージの設定処理
	static STAGE GetStage(void) { return m_Stage; }								// ステージの取得処理
	static void ChangeStage(void);												// チェンジステージの処理

private:																		// 自分だけがアクセス可能
	static STAGE m_Stage;														// ステージのポインター生成
	static STAGE m_NextStage;													// 次のステージのポインター生成	
};

#endif