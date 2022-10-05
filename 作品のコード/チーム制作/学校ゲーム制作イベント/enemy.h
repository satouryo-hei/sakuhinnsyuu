//=============================================================================
//
// エネミーの処理 [enemy.h]
// Author : 青木睦浩
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include"scene2D.h"

//*****************************************************************************
// エネミークラス
//*****************************************************************************
class CEnemy : public CScene2D
{
public:																				// 誰でもアクセス可能

	typedef enum
	{
		TYPE_S = 0,
		TYPE_M,
		TYPE_L,
		TYPE_MAX
	} TYPE;

	CEnemy(int nPriority = PRIORITY_ENEMY);										// コンストラクタ
	~CEnemy();																		// デストラクタ

	// メンバ関数
	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size, TYPE type);	// エネミーの生成
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);								// エネミーの初期化関数
	void Uninit(void);																// エネミーの終了関数
	void Update(void);																// エネミーの更新関数
	void Draw(void);																// エネミーの描画関数
	void BulletCollision();
	CEnemy * GetEnemy(int nNum) { return m_pEnemy[nNum]; }														// 現在の位置



private:																			// 自分だけがアクセス可能		
	D3DXVECTOR3 m_posold;													// 前回の位置
	D3DXVECTOR3 m_move;														// 移動量
	static LPDIRECT3DTEXTURE9 m_pTexture;											// テクスチャへのポインタ
	const float m_fSizeU;
	float m_fSizeMinV;
	float m_fSizeMaxV;
	int m_nTimer;																	// 時間
	int m_nCoolTime;																// クール時間
	bool m_bBullet;																	// 弾を打ったかどうか
	bool m_bDeath;																	// 前回倒れたかの判定	
	static int m_nItem;																// アイテムのポインター生成
	static bool m_bUse;																// 使われているかどうか
	static CEnemy *m_pEnemy[100];// ポインタ
	static int m_EnemyAll;
	bool m_bMovePush;																// 移動した向き
	int m_nBulletType;																// 弾の種類
	TYPE m_Type;
	
protected:
	D3DXVECTOR3 m_pos;														// 現在の位置
	int m_nLife;
	int m_nSpeed;
	D3DXVECTOR2 m_size;														// 大きさ
};
#endif