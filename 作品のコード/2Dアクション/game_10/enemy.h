//=============================================================================
//
// 敵の処理 [enemy.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include"scene2D.h"

//*****************************************************************************
// 敵のクラス
//*****************************************************************************
class CEnemy : public CScene2D
{
public:																											// 誰でもアクセス可能
	CEnemy(int nPriority = PRIORITY_PLAYER);																	// コンストラクタ
	virtual ~CEnemy();																							// デストラクタ
																												// メンバ関数	
	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move,D3DXVECTOR2 Size);		// 敵の初期化関数
	virtual void Uninit(void);														// 敵の終了関数
	virtual void Update(void);														// 敵の更新関数
	virtual void Draw(void);														// 敵の描画関数
	virtual D3DXVECTOR3 GetPos() { return m_Pos; }									// 敵の現在の位置の取得処理	
	virtual D3DXVECTOR3 GetMove() { return m_Move; }								// 敵の移動量の取得処理
	virtual D3DXVECTOR2 GetSize() { return m_Size; }								// 敵の大きさの取得処理
	virtual void SetPos(D3DXVECTOR3 pos) { m_Pos = pos; }							// 敵の現在の位置の設定処理	
	virtual void SetMove(D3DXVECTOR3 move) { m_Move = move; }						// 敵の移動量の設定処理
	virtual void SetSize(D3DXVECTOR2 size) { m_Size = size; }						// 敵の大きさの設定処理
	virtual void SetUse(bool bUse) { m_bUse = bUse; }

private:																			// 自分だけがアクセス可能				
	D3DXVECTOR3 m_Pos;																// 敵の現在の位置
	D3DXVECTOR3 m_Move;																// 敵の移動量
	D3DXVECTOR2 m_Size;																// 敵の大きさ
	bool m_bUse;																	// 使われいるかどうか
};
#endif
