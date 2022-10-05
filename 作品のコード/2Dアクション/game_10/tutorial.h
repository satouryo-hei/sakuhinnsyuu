//=============================================================================
//
// ゲームの処理 [tutorial.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "scene.h"
//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CPlayer;
class CItem;
class CMeshSky;
class CStage_Tutorial;
class CEnemy02;

//*****************************************************************************
// ゲームのクラス
//*****************************************************************************
class CTutorial : public CScene
{
public:
	CTutorial(int nPriority = PRIORITY_NOMAL);																	// コンストラクタ
	~CTutorial();																	// デストラクタ

																				// メンバ関数
	HRESULT Init(D3DXVECTOR3 pos);												// ゲームの初期化関数
	void Uninit(void);															// ゲームの終了関数　
	void Update(void);															// ゲームの更新関数
	void Draw(void);															// ゲームの描画関数

	static CPlayer * GetPlayer(void) { return m_pPlayer; }
	static CMeshSky*GetMeshSky(void) { return m_pMeshSky; }						// 空のポインターを取得
	static CEnemy02*GetEnemy(void) { return m_pEnemy; }						// 空のポインターを取得	


private:																		// 自分だけがアクセス可能		
	static CPlayer* m_pPlayer;													// プレイヤーのポインター
	static CItem* m_pAttack_up;											// 攻撃力アップのポインター	
	static CMeshSky * m_pMeshSky;												// 空のポインター	
	static CStage_Tutorial * m_pStage;											// ステージのポインター
	static CEnemy02* m_pEnemy;													// 敵のポインター
	bool m_bUse;																// 使っているかどうか
	bool m_bFade;																// 遷移したかどうか
};
#endif