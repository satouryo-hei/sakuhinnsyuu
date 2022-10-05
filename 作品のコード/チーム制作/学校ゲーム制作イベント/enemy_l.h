//=============================================================================
//
// �G�l�~�[L�̏��� [enemy_l.h]
// Author : �ؖr�_
//
//=============================================================================
#ifndef _ENEMY_l_H_
#define _ENEMY_l_H_

#include "scene2D.h"
#include "enemy.h"


//*****************************************************************************
// �G�l�~�[�i��j�N���X�iCEnemy�̔h���j
//*****************************************************************************
class CEnemyL : public CEnemy
{
public:
	CEnemyL();
	~CEnemyL();

	//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	bool BulletCollision();															// �u���b�N�ƓG�̓����蔻��	
};
#endif