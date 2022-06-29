//=============================================================================
//
// 3Dプレイヤーの処理 [player.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "scene.h"

#define MAX_PARTS (10)	//最大パーツ数
#define MAX_KEYSET (10) //最大キーセット数
#define PLAYER_TEXT "data/TEXT/Player.txt"	// プレイヤーテキストファイル
#define STATUS_TEXT "data/TEXT/Status.txt"	// ステータステキストファイル


//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CModel;
class CShadow;
class CCamera;

//*****************************************************************************
// 3Dプレイヤークラス
//*****************************************************************************
class CPlayer : public CScene
{
public:
	CPlayer(PRIORITY nPriority = CScene::PRIORITY_PLAYER);
	~CPlayer();

	//静的メンバ関数
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move);
	// メンバ関数
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	CModel *GetModel(int nParts) { return m_pModel[nParts]; }		// モデルのポインターを取得
	static CShadow*GetShadow(void) { return m_pShadow; }			// 影のポインターを取得
	D3DXVECTOR3 GetPos(void) { return m_pos; }						// プレイヤの位置を取得
	D3DXVECTOR3 GetPosOld(void) { return m_posold; }						// プレイヤの位置を取得
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }						// プレイヤの位置を取得
	void SetPosOld(D3DXVECTOR3 posOld) { m_posold = posOld; }						// プレイヤの位置を取得
	D3DXVECTOR3 GetRot(void) { return m_rot; }						// プレイヤの向きを取得
	int GetAttack(void) { return m_nAttack; }						// 攻撃力の取得関数
	void SetAttack(int nAttack) { m_nAttack = nAttack; }			// 攻撃力の設定関数
	int GetItem(void) { return m_nItem; }						// 攻撃力の取得関数
	void SetItem(int nItem) { m_nItem = nItem; }			// 攻撃力の設定関数

private:
	inline void SaveStatas(const char *pStatasFile);	// 書き込み
	inline void LoadPlayer(const char *pFile);			// 読み込み処理
	inline void LoadStatas(const char *pStatasFile);	// 読み込み処理
	D3DXVECTOR3 m_pos;									// 位置
	D3DXVECTOR3 m_posold;									// 位置
	D3DXVECTOR3 m_move;									// 移動量	
	D3DXVECTOR3 m_rot;									// 向き	
	D3DXMATRIX m_mtxWorld;								// ワールドマトリックス
	CModel *m_pModel[MAX_PARTS];						// モデルのポインターの生成
	static CShadow* m_pShadow;							// 影のポインターの生成
	static CCamera* m_pCamera;							// カメラのポインターの生成
	int m_nModel;										// モデル数
	int m_nNumKey;										// 現在のキーNo.
	int m_nAttack;										// 攻撃力
	int m_nItem;										// 攻撃力
	static const char* m_pModelBom;
};


#endif // !_PLAYER_H_