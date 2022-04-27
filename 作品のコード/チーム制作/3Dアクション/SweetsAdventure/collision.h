#ifndef _COLLISION_H
#define _COLLISION_H
//----------------------------------------
//当たり判定の処理
//----------------------------------------
#include "scene.h"
class CModel_Spawner;
class CField;
class CEnemy;
class CEnemy_Baum;
class CPlayer;
class CBarrier_Block;
class CBarrier_wood;
class CCollision : public CScene
{
public:
	typedef enum
	{
		COLLISION_NONE = 0,
		COLLISION_UP,
		COLLISION_DOWN,
		COLLISION_MAX,
	}COLLISION_TYPE;
	CCollision(OBJTYPE nPriority=CScene::OBJTYPE_NONE);
	~CCollision();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static bool SetCollision(CScene *pHit_Side, CScene *pAttack_Side);
	bool CollisionField(CField *field, D3DXVECTOR3 *pPos, D3DXVECTOR3 *pLastpos, float fRadius, float& fModelPos_Y);//設置物との当たり判定
	bool CollisionWeapon(CEnemy *Model, D3DXVECTOR3 pos,float fRadius);//設置物との当たり判定
	bool CollisionWeapon(CEnemy_Baum *Model, D3DXVECTOR3 pos, float fRadius);//設置物との当たり判定
	void CollisionObjectEnemy(CEnemy *Model, D3DXVECTOR3 *pPos, D3DXVECTOR3 *pLastpos, float fRadius);//設置物との当たり判定
	void CollisionObjectEnemy(CEnemy_Baum *Model, D3DXVECTOR3 *pPos, D3DXVECTOR3 *pLastpos, float fRadius);//設置物との当たり判定
	void CollisionObjectPlayer(CPlayer *Model, D3DXVECTOR3 *pPos, D3DXVECTOR3 *pLastpos, float fRadius);//設置物との当たり判定
	COLLISION_TYPE CollisionObjectModelShadow(CModel_Spawner *Model, D3DXVECTOR3 *pPos, float fRadius, float& fModelPos_Y);//設置物との当たり判定
	bool CollisionFieldShadow(CField *field, D3DXVECTOR3 *pPos, float fRadius, float& fModelPos_Y);//設置物との当たり判定
	bool CollisionWeaponBarrier(CModel_Spawner *Model, D3DXVECTOR3 pos, float fRadius);//設置物との当たり判定

	COLLISION_TYPE CollisionObjectModel(CModel_Spawner *Model,D3DXVECTOR3 *pPos, D3DXVECTOR3 *pLastpos, float fRadius,float& fModelPos_Y);//設置物との当たり判定
private:
};


#endif // !_COLLISION_H

