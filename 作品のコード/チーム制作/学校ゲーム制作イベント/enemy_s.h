//=============================================================================
//
// �G�l�~�[S�̏��� [enemy_s.h]
// Author : �ؖr�_
//
//=============================================================================
#ifndef _ENEMY_S_H_
#define _ENEMY_S_H_

#include "scene2D.h"
#include "enemy.h"


//*****************************************************************************
// �G�l�~�[�i���j�N���X�iCEnemy�̔h���j
//*****************************************************************************
class CEnemyS : public CEnemy
{
public:
	CEnemyS();
	~CEnemyS();

	//�����o�֐�
	static CEnemyS *Create();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	bool BulletCollision();
};
#endif