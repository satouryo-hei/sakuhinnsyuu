#ifndef _ENEMY_BAUM_H_
#define _ENEMY_BAUM_H_
#include "scene.h"
#include "model.h"
#include "motion.h"

#define MAX_ENEMY_BAUM_PARTS (3)	//�ő�p�[�c��
#define MAX_BAUM_SPEED (2.3)
#define MAX_BAUM_DRAWRADIUS (800.0f)
#define BAUM_ADD_SPEED (0.1)//�Q�[�W�𑝂₷��
#define BAUM_LIFE (1)//�̗�

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
	//�ÓI�����o�[�֐�
	static CEnemy_Baum *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	CModel *GetModel(int nParts) { return m_pModel[nParts]; }
	D3DXVECTOR3 GetEnemyPos(void) { return m_pos; }
	void SetUninit(bool Uninit) { m_bUninit = Uninit; }
	bool GetUninit(void) { return m_bUninit; }
	void AddLife(int nLife);//�̗͂̑���
	int GetLife(void) { return m_nLife; }//�̗͂̑���
	void SetbDamage(bool bDamage) { m_bDamage = bDamage; }//�_���[�W���󂯂���Ԃɂ���
	int GetbDamage(void) { return m_bDamage; }//�_���[�W���󂯂Ă����Ԃ��擾

private:
	D3DXVECTOR3 m_pos, m_MoveSpeed; //�ʒu
	D3DXVECTOR3 m_lastPos;//�O��̈ʒu;
	D3DXVECTOR3 m_rot; //����
	D3DXVECTOR3 m_Lotrot; //�O��̌���
	D3DXMATRIX m_mtxWorld; //���[���h�}�g���b�N�X
	CModel  *m_pModel[MAX_ENEMY_BAUM_PARTS];
	CMotion *m_pMotion;
	bool m_bDraw;
	bool m_bUninit;
	bool m_bOnMissile;
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

