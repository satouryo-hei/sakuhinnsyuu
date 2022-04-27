#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "scene.h"
#include "model.h"
#include "motion.h"
//最大のジャンプ数
#define MAX_PLAYER_JUMP (1)
#define MAX_PLAYER_PARTS (10)
#define PLAYER_SIZE (20.0)
#define PLAYER_POS_X (60.0)
#define PLAYER_POS_Y (50.0)
#define PLAYER_POS_Z (-800.0)
#define PLAYER_FALL (-100.0)//落下判定に入るまでの位置

class CLayer_Structure;
class CShadow;
class CPlayer : public CScene
{
public:
	typedef enum
	{
		NOWN=0,
		COMBO_1,
		COMBO_2,
		COMBO_3,
		COMBO_MAX
	}COMBO;

	typedef enum
	{
		TYPE_SWORD=0,
		TYPE_HAMMER,
		TYPE_MAX
	}WEAPON_TYPE;

	typedef enum
	{
		S_NEUTRAL=0,
		S_MOVE,
		S_ATTACK_1,
		S_ATTACK_2,
		S_ATTACK_3,
		S_JUMP,
		S_PLACE,
		S_MAX
	}S_MOTION;

	typedef enum
	{
		H_NEUTRAL = 0,
		H_MOVE,
		H_ATTACK_1,
		H_ATTACK_2,
		H_JUMP,
		H_PLACE,
		H_MAX
	}H_MOTION;

	CPlayer(OBJTYPE nPriority = CScene::OBJTYPE_PLAYER);
	~CPlayer();
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	bool bColision();
	void Move(float fMoveSpeed);
	//静的メンバー関数
	static CPlayer *Create();
	CModel *GetParts(int nNumParts) { return m_pModel[nNumParts]; }
	D3DXVECTOR3 GetLastPos(void) { return m_lastpos; }
	void Attack(void);												//プレイヤーの攻撃
	int GetWeaponType(void) { return m_nWeaponType; }
private:

	D3DXVECTOR3 m_pos,m_lastpos; //位置
	float m_Vec_x, m_Vec_y, m_Vec_z;
	float m_fLength;
	float m_move = 2.0f;
	D3DXVECTOR3 m_rot;												//向き
	D3DXMATRIX m_mtxWorld;											//ワールドマトリックス
	CModel *m_pModel[MAX_PARTS];
	CModel *m_pWeapon[TYPE_MAX];
	CModel *m_pCollision[TYPE_MAX];									//当たり判定用の武器の原点を決めるやつ
	CShadow *pShadow;
	CMotion*m_pMotion[TYPE_MAX];
	CLayer_Structure *m_pLayer;
	bool	m_bland;												//地面についてるか判定
	bool	m_bColloison;											//当たり判定
	bool	m_bJumpLock;											//ジャンプの制限
	bool	m_bNeutral;
	bool	m_bAttack;												//今攻撃してるかどうか
	bool	m_bMotionStop;											//モーションが止まったかどうか
	bool	m_bFall;												//落下判定
	bool	m_bMove;												// 移動判定
	int		m_nCntJump;												//ジャンプのカウント
	float	m_fGravity;												//重力
	float	m_fGravitySpeed;										//重力
	float	m_fSoundInterval;										//サウンドインターバル
	int		m_nLife;												//ライフ
	int		m_nWeaponType;											//武器のタイプ
	int		m_nMotionType[TYPE_MAX],m_nMotionLastType[TYPE_MAX];
	int		m_nAttackType[TYPE_MAX];								//今の攻撃タイプ
	int     m_nTimer;
	int		m_nEffectTimer;
};


#endif // !_PLAYER_H_
