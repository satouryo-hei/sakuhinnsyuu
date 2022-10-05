//=============================================================================
//
// �G�l�~�[M�̏��� [enemy_m.h]
// Author : �ؖr�_
//
//=============================================================================
#ifndef _ENEMY_M_H_
#define _ENEMY_M_H_

#include "scene2D.h"
#include "enemy.h"


//*****************************************************************************
// �G�l�~�[�i���j�N���X�iCEnemy�̔h���j
//*****************************************************************************
class CEnemyM : public CEnemy
{
public:
	CEnemyM();
	~CEnemyM();

	//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	bool BulletCollision();
};
#endif