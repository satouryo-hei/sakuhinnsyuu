//========================================
// ���[�V�����̎���
// Author:������
//========================================
#ifndef _MOTION_H_
#define _MOTION_H_
#include "main.h"
class CModel;

//----------------------------
// �}�N����`
//----------------------------
#define MAX_PARTS (20)			// ���f��(�p�[�c)�̍ő吔
#define MAX_KEY (2)				// �L�[�̍ő吔
#define MAX_MOTION (10)			// ���[�V�����̍ő吔
#define MAX_LIMIT (15)
//------------------------------------------
// ���[�V�����N���X
//------------------------------------------
class CMotion
{
public:

	//----------------------------
	// �\����
	//----------------------------
	// ���[�V�����̎��
	typedef enum
	{
		MOTIONTYPE_NEUTRAL = 0,	// �j���[�g�������[�V����
		MOTIONTYPE_MOVE,		// ���[�u���[�V����
		MOTIONTYPE_ATTACK_0,		// �A�^�b�N���[�V����
		MOTIONTYPE_ATTACK_1,		// �A�^�b�N���[�V����
		MOTIONTYPE_ATTACK_2,		// �A�^�b�N���[�V����
		MOTIONTYPE_JUMP,		// �W�����v���[�V����
		MOTIONTYPE_MAX

	}MOTIONTYPE;

	// �L�[�̍\����
	typedef struct
	{
		float fPosX;	//�ʒux
		float fPosY;	//�ʒuy
		float fPosZ;	//�ʒuz
		float fRotX;	//����x
		float fRotY;	//����y
		float fRotZ;	//����z

	}KEY;

	// �L�[���̍\����
	typedef struct
	{
		float nFrame;					// �Đ��t���[��
		KEY **aKey;		// �e�p�[�c�̃L�[�v�f(���f���ɂ���ăp�[�c�����ς��)(���p�[�c�ڂ̈ʒu�Ɖ�]�������Ă��邩�̏��)								
		//			���p�[�c�̍ő吔(����)

	}KEY_INFO;

	// ���[�V�������̍\����
	typedef struct
	{
		bool bLoop;					// ���[�v���邩�ǂ���
		int nMaxKey;				// �L�[�̑���
		KEY_INFO **aKeyInfo;	// �L�[���[�L�[�̍ő吔](���[�V�����̉��Ԗڂ̓����������Ă��邩�̏��)

	}MOTION_INFO;

	//------------------------------------
	// �R���X�g���N�^�A�f�X�g���N�^
	//------------------------------------
	CMotion();
	~CMotion();

	//------------------------------------
	// �v���g�^�C�v�錾
	//------------------------------------
	HRESULT Init(void);								// ������
	void PlayMotion(int nNumParts, CModel **apModel, int& motionType, int& motionTypeLast);							// ���[�V�����̍Đ�

	void PlayMotion(int nNumParts,CModel **apModel, int& motionType, int& motionTypeLast,bool& bJudg,bool& bAttack,bool& bNeutral);							// ���[�V�����̍Đ�
	void MotionLoad(const char *sMotionFileName);							// ���[�V�����e�L�X�g��ǂݍ��ފ֐�

private:
protected:
	MOTION_INFO m_aMotionInfo[MAX_MOTION];	// ���[�V�������[���[�V�����^�C�v��](���݉������Ă��邩�̃��[�V�����̏�񂪓����Ă���)
	MOTIONTYPE m_MotionType;					// ���݂̃��[�V�����^�C�v
	MOTIONTYPE m_MotionTypeLast;				// �O��̃��[�V�����^�C�v
	int m_NumKey;								// ���݂̃L�[�ԍ�
	float m_motionCounter;						// ���[�V�����J�E���^�[
	int m_Timer;

};
#endif _MOTION_H_