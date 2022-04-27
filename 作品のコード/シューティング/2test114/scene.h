//=============================================================================
//
// オブジェクトの処理 [scene.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

#include"main.h"

//==============================
// マクロ定義
//==============================
#define MAX_DATA (1000)

//*****************************************************************************
// オブジェクトクラス
//*****************************************************************************
class CScene
{
public:																										// 誰でもアクセス可能

	// 描画の優先順位
	typedef enum
	{
		PRIORITY_NOMAL = 0,																					// ノーマル
		PRIORITY_BG,																						// 背景
		PRIORITY_EFFECT,																					// エフェクト
		PRIORITY_BULLET,																					// 弾
		PRIORITY_PLAYER,																					// プレイヤー
		PRIORITY_EXPLOSION,																					// 爆発
		PRIORITY_UI,																						// UI(スコアなど
		PRIORITY_FADE,																						// フェード
		PRIORITY_MAX																						// すべての数
	} PRIORITY;

	// オブジェクトの種類
	typedef enum 
	{
		OBJTYPE_NOMAL=0,																					// ノーマル
		OBJTYPE_PLAYER,																						// プレイヤー
		OBJTYPE_ENEMY,																						// 敵
		OBJTYPE_PLAYERBULLET,																						// 弾
		OBJTYPE_ENEMYBULLET,																						// 弾
		OBJTYPE_MAX																							// すべての数
	} OBJTYPE;

	CScene(int nPriority = 3);																				// コンストラクタ
	virtual~CScene();																						// デストラクタ
	// メンバ関数
	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size) = 0;											// オブジェクトの初期化関数
	virtual void Uninit(void) = 0;																			// オブジェクトの終了関数　
	virtual void Update(void) = 0;																			// オブジェクトの更新関数
	virtual void Draw(void) = 0;																			// オブジェクトの描画関数
	static void ReleseAll(void);																			// すべてのオブジェクトの開放関数
	static void UpdateAll(void);																			// すべてのオブジェクトの更新関数
	static void DrawAll(void);																				// すべてのオブジェクトの描画関数
	void SetType(OBJTYPE objType) { m_ObjType = objType; }													// オブジェクトの種類の配置
	OBJTYPE GetOnjType(void) { return m_ObjType; }															// オブジェクトの種類の取得処理
	static CScene * GetScene(int nPriority,int nCountScene) { return m_apScene[nPriority][nCountScene]; }	// 何番目のオブジェクトかの取得処理

protected:																									// 自分と派生系のみアクセス可能
	void  Relese(void);																						// 1つのオブジェクトの開放関数

private:																									// 自分だけがアクセス可能
	// メンバ変数
	static CScene *m_apScene[PRIORITY_MAX][MAX_DATA];														// それぞれのオブジェクト
	static int m_nNumAll;																					// ポリゴンの全体の数
	int m_nID;																								// 格納先の番号
	OBJTYPE m_ObjType;																						// オブジェクトの種類
	int m_nPriority;																						// 優先順位の番号
};
#endif
