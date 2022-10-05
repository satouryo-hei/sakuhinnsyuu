//=============================================================================
//
// エネミーLの処理 [enemy_l.h]
// Author : 青木睦浩
//
//=============================================================================
#ifndef _ENEMY_l_H_
#define _ENEMY_l_H_

#include "scene2D.h"
#include "enemy.h"


//*****************************************************************************
// エネミー（大）クラス（CEnemyの派生）
//*****************************************************************************
class CEnemyL : public CEnemy
{
public:
	CEnemyL();
	~CEnemyL();

	//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	bool BulletCollision();															// ブロックと敵の当たり判定	
};
#endif