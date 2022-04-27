#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "scene.h"
#include "model.h"
#include "motion.h"
class CSound;

#define MAX_ENEMY_PARTS (10)	//�ő�p�[�c��
#define MAX_KEYSET (10) //�ő�L�[�Z�b�g��
#define MAX_SPEED (1.8)
#define MAX_DRAWRADIUS (800.0f)
#define MAX_COLRADIUS (200.0f)
#define MAX_TEMPTATION_RADIUS (150.0f)//�U�f�˒��͈�
#define ENEMY_ADD_SPEED (0.2)//�Q�[�W�𑝂₷��
#define ENEMY_LIFE (2)//�̗�
#define INVINCIBLE_TIME (30)//���G����
class CEnemy : public CScene
{
public:
	typedef enum
	{
		NEUTRAL = 0,
		MOVE,
		ATTACK,
		MAX
	}MOTION;

	CEnemy(OBJTYPE nPriority = CScene::OBJTYPE_ENEMY);
	~CEnemy();
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	bool bColision();
	//�ÓI�����o�[�֐�
	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	CModel *GetModel(int nParts) { return m_pModel[nParts]; }
	D3DXVECTOR3 GetEnemyPos(void) { return m_pos; }
	void SetUninit(bool Uninit) { m_bUninit = Uninit; }
	bool GetUninit(void) { return m_bUninit; }
	void AddLife(int nLife);//�̗͂̑���
	int GetLife(void) { return m_nLife; }//�̗͂̑���
	void SetbDamage(bool bDamage) { m_bDamage = bDamage; }//�_���[�W���󂯂���Ԃɂ���
	int GetbDamage(void) { return m_bDamage; }//�_���[�W���󂯂Ă����Ԃ��擾

private:
	CMotion *m_pMotion;

	D3DXVECTOR3 m_pos, m_MoveSpeed; //�ʒu
	D3DXVECTOR3 m_lastPos;//�O��̈ʒu;
	D3DXVECTOR3 m_rot; //����
	D3DXVECTOR3 m_Lotrot; //�O��̌���
	D3DXMATRIX m_mtxWorld; //���[���h�}�g���b�N�X
	CModel *m_pModel[MAX_ENEMY_PARTS];
	bool m_bUninit;
	bool m_bOnMissile;
	bool m_bDraw;
	float m_fAng;
	int  m_nLife;//���C�t
	int  m_nTimer;
	int	 m_MotionType, m_MotionLastType;
	float m_fSoundInterval;
	float m_fWalkSoundInterval;
	bool	m_bNeutral;
	bool	m_bAttack;//���U�����Ă邩�ǂ���
	bool	m_bMotionStop;//���[�V�������~�܂������ǂ���
	bool	m_bDamage;//���U�����󂯂Ă��邩
	bool    m_bEffect;
};


#endif // !_PLAYER_H_

