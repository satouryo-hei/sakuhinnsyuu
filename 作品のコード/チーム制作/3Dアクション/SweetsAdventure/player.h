#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "scene.h"
#include "model.h"
#include "motion.h"
//�ő�̃W�����v��
#define MAX_PLAYER_JUMP (1)
#define MAX_PLAYER_PARTS (10)
#define PLAYER_SIZE (20.0)
#define PLAYER_POS_X (60.0)
#define PLAYER_POS_Y (50.0)
#define PLAYER_POS_Z (-800.0)
#define PLAYER_FALL (-100.0)//��������ɓ���܂ł̈ʒu

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
	//�ÓI�����o�[�֐�
	static CPlayer *Create();
	CModel *GetParts(int nNumParts) { return m_pModel[nNumParts]; }
	D3DXVECTOR3 GetLastPos(void) { return m_lastpos; }
	void Attack(void);												//�v���C���[�̍U��
	int GetWeaponType(void) { return m_nWeaponType; }
private:

	D3DXVECTOR3 m_pos,m_lastpos; //�ʒu
	float m_Vec_x, m_Vec_y, m_Vec_z;
	float m_fLength;
	float m_move = 2.0f;
	D3DXVECTOR3 m_rot;												//����
	D3DXMATRIX m_mtxWorld;											//���[���h�}�g���b�N�X
	CModel *m_pModel[MAX_PARTS];
	CModel *m_pWeapon[TYPE_MAX];
	CModel *m_pCollision[TYPE_MAX];									//�����蔻��p�̕���̌��_�����߂���
	CShadow *pShadow;
	CMotion*m_pMotion[TYPE_MAX];
	CLayer_Structure *m_pLayer;
	bool	m_bland;												//�n�ʂɂ��Ă邩����
	bool	m_bColloison;											//�����蔻��
	bool	m_bJumpLock;											//�W�����v�̐���
	bool	m_bNeutral;
	bool	m_bAttack;												//���U�����Ă邩�ǂ���
	bool	m_bMotionStop;											//���[�V�������~�܂������ǂ���
	bool	m_bFall;												//��������
	bool	m_bMove;												// �ړ�����
	int		m_nCntJump;												//�W�����v�̃J�E���g
	float	m_fGravity;												//�d��
	float	m_fGravitySpeed;										//�d��
	float	m_fSoundInterval;										//�T�E���h�C���^�[�o��
	int		m_nLife;												//���C�t
	int		m_nWeaponType;											//����̃^�C�v
	int		m_nMotionType[TYPE_MAX],m_nMotionLastType[TYPE_MAX];
	int		m_nAttackType[TYPE_MAX];								//���̍U���^�C�v
	int     m_nTimer;
	int		m_nEffectTimer;
};


#endif // !_PLAYER_H_
