//=============================================================================
//
// 敵の処理 [enemy.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _BOSS_H_
#define _BOSS_H_

#include"scene2D.h"

//*****************************************************************************
// 敵のクラス
//*****************************************************************************
class CBoss : public CScene2D
{
public:																											// 誰でもアクセス可能
	typedef enum
	{
		ACTION_NOMAL = 0,
		ACTION_BULLET,
		ACTION_ATTACK,
		ACTION_HIT,
		ACTION_MAX
	} ACTION;
	

	CBoss(int nPriority = PRIORITY_ENEMY);																	// コンストラクタ
	~CBoss();																							// デストラクタ
																										// メンバ関数	
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size);		// 敵の初期化関数
	void Uninit(void);														// 敵の終了関数
	void Update(void);														// 敵の更新関数
	void Draw(void);														// 敵の描画関数
	D3DXVECTOR3 GetPos() { return m_Pos; }									// 敵の現在の位置の取得処理	
	D3DXVECTOR3 GetMove() { return m_Move; }								// 敵の移動量の取得処理
	D3DXVECTOR2 GetSize() { return m_Size; }								// 敵の大きさの取得処理
	void SetPos(D3DXVECTOR3 pos) { m_Pos = pos; }							// 敵の現在の位置の設定処理	
	void SetMove(D3DXVECTOR3 move) { m_Move = move; }						// 敵の移動量の設定処理
	void SetSize(D3DXVECTOR2 size) { m_Size = size; }						// 敵の大きさの設定処理
	void SetUse(bool bUse) { m_bUse = bUse; }

private:																			// 自分だけがアクセス可能				
	D3DXVECTOR3 m_Pos;																// 敵の現在の位置
	D3DXVECTOR3 m_Move;																// 敵の移動量
	D3DXVECTOR2 m_Size;																// 敵の大きさ
	bool m_bUse;																	// 使われいるかどうか
};
#endif