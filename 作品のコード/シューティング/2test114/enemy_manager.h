//=============================================================================
//
// �G�̏��� [enemy_manager.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _ENEMY_MANAGER_H_
#define _ENEMY_MANAGER_H_

/*
�����L���O��������Ȃ�J�E���gup�ɂ��Ă鎞�ԁ[�X�R�A�Ń����L���O���v�Z����

���ʂ̓o�u���\�[�g�ȂǂŒT���ď��ʕt�������邩
�ォ��T���Ă����ē����X�R�A����Ȃ������珇�ʕt��������݂����ȏ���
�ʂ̃t�@�C���ŏ��ʕt�������Ă����ǂݍ��ނ̂�����
*/

#include"main.h"
//*****************************************************************************
// �O���錾
//*****************************************************************************
class CEnemy;
class CEnemy_Doragonfly;
class CTimer;
//*****************************************************************************
// �G�}�l�[�W���[�N���X�i�G�Ǘ��N���X
//*****************************************************************************
class CEnemy_manager
{
public:																				// �N�ł��A�N�Z�X�\
																					//�J�b�g�C���̏��
	typedef enum
	{
		ENEMY_NONE = 0,																//�ݒu�^�̓G(�w�)
		ENEMY_DORAGONFLY,															//�G(�g���{)
		ENEMY_MAX
	} ENEMY;

	CEnemy_manager();																// �R���X�g���N�^
	~CEnemy_manager();																	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);				// �G�̏������֐�
	void Uninit(void);																// �G�̏I���֐�
	void Update(void);																// �G�̍X�V�֐�
	void Draw(void);																// �G�̕`��֐�

private:																			// �����������A�N�Z�X�\
	CEnemy*m_pEnemy;
	CEnemy_Doragonfly*m_pEmemy_Doragonfly;
	static int m_nNowTimer;
	char m_Name[256];
	char m_Data[256];
	int m_GetTime[128];
	int m_GetEnemyType;
	int m_nCntTime;
	int m_nCoolTime;
};

#endif