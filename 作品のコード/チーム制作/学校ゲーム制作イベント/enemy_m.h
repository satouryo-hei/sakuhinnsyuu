//=============================================================================
//
// エネミーMの処理 [enemy_m.h]
// Author : 青木睦浩
//
//=============================================================================
#ifndef _ENEMY_M_H_
#define _ENEMY_M_H_

#include "scene2D.h"
#include "enemy.h"


//*****************************************************************************
// エネミー（小）クラス（CEnemyの派生）
//*****************************************************************************
class CEnemyM : public CEnemy
{
public:
	CEnemyM();
	~CEnemyM();

	//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	bool BulletCollision();
};
#endif