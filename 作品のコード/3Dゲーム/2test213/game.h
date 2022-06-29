//=============================================================================
//
// ゲームの処理 [game.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "scene.h"
//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CBg;
class CPlayer;
class CScene3D;
class CModel;
class CModel_Single;
class CPlayer2;
class CMeshField;
class CMeshSky;
class CShadow;
class CBillboard;
class CWall_Manager;
class CWall;
class CTimer;
class CItem;
class CEnemy;
class CEnemy2;
class CScore;
class CStatus_UI;
class CGoal;
class CBom;

//*****************************************************************************
// ゲームのクラス
//*****************************************************************************
class CGame : public CScene
{
public:
	CGame();																	// コンストラクタ
	~CGame();																	// デストラクタ
																				// メンバ関数
	HRESULT Init(D3DXVECTOR3 pos);												// ゲームの初期化関数
	void Uninit(void);															// ゲームの終了関数　
	void Update(void);															// ゲームの更新関数
	void Draw(void);															// ゲームの描画関数

	static CBg*GetBg(void) { return m_pBg; }									// 背景の取得処理
	static CScene3D*GetScene3D(void) { return m_pScene3D; }						// シーン3Dの取得処理
	static CModel*GetModel(void) { return m_pModel; }							// モデルのポインターを取得
	static CModel_Single*GetModel_Single(void) { return m_pModel_Single; }		// 一つのモデルのポインターを取得
	static CPlayer*GetPlayer(void) { return m_pPlayer; }						// 3Dプレイヤーのポインターを取得
	static CMeshField*GetMeshField(void) { return m_pMeshField; }				// メッシュフィールドのポインターを取得
	static CMeshSky*GetMeshSky(void) { return m_pMeshSky; }						// 空のポインターを取得
	static CShadow*GetShadow(void) { return m_pShadow; }						// 影のポインターを取得
	static CBillboard*GetBillboard(void) { return m_pBillboard; }				// ビルボードのポインターを取得
	static CWall_Manager*GetWall_Manager(void) { return m_pWall_Manager; }		// 四角形の壁のポインターを取得
	static CWall*GetWall(void) { return m_pWall; }								// 壁のポインターを取得
	static CTimer*GetTimer(void) { return m_pTimer; }							// タイマーのポインターを取得
	static CItem*GetItem(void) { return *m_pItem; }								// アイテムのポインターを取得
	static CEnemy*GetEnemy(void) { return m_pEnemy; }							// 敵のポインターを取得
	static CEnemy2*GetEnemy2(void) { return m_pEnemy2; }						// 敵のポインターを取得
	static CScore*GetScore(void) { return m_pScore; }							// 点数のポインターを取得
	static CStatus_UI*GetStatus_UI(void) { return m_pStatus_UI; }				// ステータスUIのポインターを取得
	static CGoal*GetGoal(void) { return m_pGoal;}								// ゴールのポインターを取得
	static CBom*GetBom(void) { return m_pBom; }									// ボムのポインターを取得

private:																		// 自分だけがアクセス可能		
	static CBg *m_pBg;															// 背景のポインター
	static CScene3D * m_pScene3D;												// 3Dシーンのポインター
	static CModel * m_pModel;													// モデルのポインター
	static CModel_Single * m_pModel_Single;										// 一つのモデルのポインター
	static CPlayer * m_pPlayer;													// 3Dプレイヤーのポインター
	static CMeshField * m_pMeshField;											// メッシュフィールドのポインター
	static CMeshSky * m_pMeshSky;												// 空のポインター
	static CShadow* m_pShadow;													// 影のポインター
	static CBillboard* m_pBillboard;											// ビルボードのポインター
	static CWall_Manager* m_pWall_Manager;										// 四角形の壁のポインター
	static CWall* m_pWall;														// 壁のポインター
	static CTimer* m_pTimer;													// タイマーのポインター
	static CItem* m_pItem[3];													// アイテムのポインター
	static CEnemy*m_pEnemy;														// 敵のポインターを取得
	static CEnemy2*m_pEnemy2;													// 敵のポインターを取得
	static CScore*m_pScore;														// 点数のポインターを取得
	static CStatus_UI*m_pStatus_UI;												// ステータスUIのポインターを取得
	static CGoal*m_pGoal;														// ゴールのポインターを取得
	static CBom*m_pBom;															// ボムのポインターを取得
	static bool m_bRanking;														// ランキングをさせるか
	static const char*m_pModelData;												// 仮モデルのファイル名
	static const char*m_pModelAttack;											// アイテムのモデルのファイル名(攻撃力UP)
	static const char*m_pModelGoal; 											// ゴールのモデルのファイル名
	static const char * m_pModelBom; 											// ボムのモデルのファイル名
	bool m_bUse;																// 使っているかどうか

};
#endif