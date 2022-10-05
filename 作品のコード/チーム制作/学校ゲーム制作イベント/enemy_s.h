//=============================================================================
//
// エネミーSの処理 [enemy_s.h]
// Author : 青木睦浩
//
//=============================================================================
#ifndef _ENEMY_S_H_
#define _ENEMY_S_H_

#include "scene2D.h"
#include "enemy.h"


//*****************************************************************************
// エネミー（小）クラス（CEnemyの派生）
//*****************************************************************************
class CEnemyS : public CEnemy
{
public:
	CEnemyS();
	~CEnemyS();

	//メンバ関数
	static CEnemyS *Create();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	bool BulletCollision();
};
#endif