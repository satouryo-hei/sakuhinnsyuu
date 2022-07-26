//=============================================================================
//
// 敵の処理 [enemy.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _ENEMY02_H_
#define _ENEMY02_H_

#include"enemy.h"

//*****************************************************************************
// 敵のクラス
//*****************************************************************************
class CEnemy02 : public CEnemy
{
public:																				// 誰でもアクセス可能
	CEnemy02(int nPriority = PRIORITY_PLAYER);										// コンストラクタ
	virtual ~CEnemy02();															// デストラクタ
																					// メンバ関数
	static CEnemy02 *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size);	// プレイヤの生成
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size);				// 敵の初期化関数
	void Uninit(void);																// 敵の終了関数
	void Update(void);																// 敵の更新関数
	void Draw(void);																// 敵の描画関数	

private:																			// 自分だけがアクセス可能				
	void BlockCollision();															// ブロックと敵の当たり判定
	D3DXVECTOR3 m_Pos;																// 敵の現在の位置
	D3DXVECTOR3 m_OldPos;															// 敵の前回の位置
	D3DXVECTOR3 m_Move;																// 敵の移動量
	D3DXVECTOR2 m_Size;																// 敵の大きさ
};
#endif
