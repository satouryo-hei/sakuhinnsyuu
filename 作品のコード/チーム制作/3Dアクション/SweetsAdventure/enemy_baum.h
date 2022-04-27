#ifndef _ENEMY_BAUM_H_
#define _ENEMY_BAUM_H_
#include "scene.h"
#include "model.h"
#include "motion.h"

#define MAX_ENEMY_BAUM_PARTS (3)	//最大パーツ数
#define MAX_BAUM_SPEED (2.3)
#define MAX_BAUM_DRAWRADIUS (800.0f)
#define BAUM_ADD_SPEED (0.1)//ゲージを増やす量
#define BAUM_LIFE (1)//体力

class CEnemy_Baum : public CScene
{
public:
	typedef enum
	{
		NEUTRAL = 0,
		ATTACK,
		MAX
	}MOTION;

	CEnemy_Baum(OBJTYPE nPriority = CScene::OBJTYPE_ENEMY);
	~CEnemy_Baum();
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	bool bColision();
	//静的メンバー関数
	static CEnemy_Baum *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	CModel *GetModel(int nParts) { return m_pModel[nParts]; }
	D3DXVECTOR3 GetEnemyPos(void) { return m_pos; }
	void SetUninit(bool Uninit) { m_bUninit = Uninit; }
	bool GetUninit(void) { return m_bUninit; }
	void AddLife(int nLife);//体力の増減
	int GetLife(void) { return m_nLife; }//体力の増減
	void SetbDamage(bool bDamage) { m_bDamage = bDamage; }//ダメージを受けた状態にする
	int GetbDamage(void) { return m_bDamage; }//ダメージを受けている状態か取得

private:
	D3DXVECTOR3 m_pos, m_MoveSpeed; //位置
	D3DXVECTOR3 m_lastPos;//前回の位置;
	D3DXVECTOR3 m_rot; //向き
	D3DXVECTOR3 m_Lotrot; //前回の向き
	D3DXMATRIX m_mtxWorld; //ワールドマトリックス
	CModel  *m_pModel[MAX_ENEMY_BAUM_PARTS];
	CMotion *m_pMotion;
	bool m_bDraw;
	bool m_bUninit;
	bool m_bOnMissile;
	float m_fAng;
	int  m_nLife;//ライフ
	int  m_nTimer;
	int	 m_MotionType, m_MotionLastType;
	float m_fSoundInterval;
	float m_fWalkSoundInterval;
	bool	m_bNeutral;
	bool	m_bAttack;//今攻撃してるかどうか
	bool	m_bMotionStop;//モーションが止まったかどうか
	bool	m_bDamage;//今攻撃を受けているか
	bool    m_bEffect;

};


#endif // !_PLAYER_H_

