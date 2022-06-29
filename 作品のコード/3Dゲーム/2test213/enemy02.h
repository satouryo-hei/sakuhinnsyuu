//=============================================================================
//
// 敵の処理 [player.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _ENEMY2_H_
#define _ENEMY2_H_
#include "enemy.h"
//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CModel;
class CShadow;

//*****************************************************************************
// 敵クラス
//*****************************************************************************
class CEnemy2 : public CEnemy
{
public:
	CEnemy2(PRIORITY nPriority = CScene::PRIORITY_ENEMY);
	~CEnemy2();

	//静的メンバ関数
	static CEnemy2 *Create(D3DXVECTOR3 pos, const char *pFileName);		// 生成
	// メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, const char *pFileName);				// 初期化
	void Uninit(void);													// 終了
	void Update(void);													// 更新
	void Draw(void);													// 描画
	static CModel *GetModel(int nParts) { return m_pModel[nParts]; }	// モデルのポインターを取得
	static CShadow*GetShadow(void) { return m_pShadow; }				// 影のポインターを取得
	D3DXVECTOR3 GetPos(void) { return m_pos; }							// プレイヤの位置を取得
	D3DXVECTOR3 GetRot(void) { return m_rot; }							// プレイヤの向きを取得
	static bool GetUse(void) { return m_bUse; }							// プレイヤの向きを取得

private:
	D3DXVECTOR3 m_pos;													// 位置	
	D3DXVECTOR3 m_rot;													// 向き	
	D3DXVECTOR3 m_Move;													// 移動量
	float m_fRadius;													// 半径
	float m_fRange;														// 角度
	float m_fFlame;														// フレーム数
	D3DXMATRIX m_mtxWorld;												// ワールドマトリックス
	static CModel *m_pModel[20];										// モデルのポインターの生成
	static CShadow* m_pShadow;											// 影のポインターの生成
	int m_nModel;														// モデル数
	int m_nNumKey;														// 現在のキーNo.
	static bool m_bUse;
};

#endif // !_PLAYER_H_