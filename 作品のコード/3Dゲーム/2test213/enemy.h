//=============================================================================
//
// 敵の処理 [enemy.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "scene.h"

#define ENEMY_TEXT "data/TEXT/Player.txt" //最大キーセット数


//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CModel;
class CShadow;

//*****************************************************************************
// 敵のクラス
//*****************************************************************************
class CEnemy : public CScene
{
public:
	CEnemy(PRIORITY nPriority = CScene::PRIORITY_ENEMY);			// コンストラクタ
	~CEnemy();														// デストラクタ

	//静的メンバ関数
	static CEnemy *Create(D3DXVECTOR3 pos, const char *pFileName);	// 生成関数
	// メンバ関数
	HRESULT Init(D3DXVECTOR3 pos);									// デフォルト初期化関数
	HRESULT Init(D3DXVECTOR3 pos, const char *pFileName);			// 初期化関数
	void Uninit(void);												// 終了関数
	void Update(void);												// 更新関数
	void Draw(void);												// 描画関数
	static CModel *GetModel(int nParts) { return m_pModel[nParts]; }		// モデルのポインターを取得
	static CShadow*GetShadow(void) { return m_pShadow; }			// 影のポインターを取得
	D3DXVECTOR3 GetPos(void) { return m_pos; }						// プレイヤの位置を取得
	D3DXVECTOR3 GetRot(void) { return m_rot; }						// プレイヤの向きを取得
	D3DXVECTOR3 GetSize(void);										// プレイヤの向きを取得
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }						// プレイヤの位置を取得
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }						// プレイヤの向きを取得
	void SetSize(D3DXVECTOR3 Size) { m_Size = Size; }						// プレイヤの向きを取得

private:	
	inline void LoadEnemy(const char *pFileName);			// 読み込み処理	
	D3DXVECTOR3 m_pos;									// 位置	
	D3DXVECTOR3 m_rot;									// 向き	
	D3DXVECTOR3 m_Size;									// 大きさ	
	D3DXMATRIX m_mtxWorld;								// ワールドマトリックス
	static CModel *m_pModel[20];						// モデルのポインターの生成
	static CShadow* m_pShadow;							// 影のポインターの生成
	int m_nModel;										// モデル数
	int m_nNumKey;										// 現在のキーNo.
};



#endif // !_PLAYER_H_