//�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{
// �T�E���h���� [sound.h]
// Author : �ъC�l
//�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//===========================================================
// �T�E���h�N���X
//===========================================================
class CSound
{
public:
	CSound();
	~CSound();

	//=================================
	// �T�E���h�t�@�C��
	//=================================
	typedef enum
	{
		//--------------------------
		// �a�f�l
		//--------------------------
		SOUND_LABEL_BGM_TITLE = 0,			// �^�C�g����BGM
		SOUND_LABEL_BGM_GAME,				// �Q�[����BGM
		SOUND_LABEL_BGM_RESULT,				// ���U���g��BGM

		//--------------------------
		// �r�d
		//--------------------------
		SOUND_LABEL_SE_ENEMY_DEATH,			// �G�̏���
		SOUND_LABEL_SE_ENEMY_DEATH2,		// �G�̏���2
		SOUND_LABEL_SE_ENEMY_DEATH3,		// �G�̏���3
		SOUND_LABEL_SE_ENEMY_DEATH4,		// �G�̏���4
		SOUND_LABEL_SE_AXE_ATTACK,			// ���U��
		SOUND_LABEL_SE_AXE_HIT,				// ���q�b�g(�G)
		SOUND_LABEL_SE_AXE_HIT_WALL,		// ���q�b�g(��)
		SOUND_LABEL_SE_AXE_HIT_TREE,		// ���q�b�g(��)
		SOUND_LABEL_SE_SWORD_ATTACK,		// ���U��
		SOUND_LABEL_SE_SWORD_HIT,			// ���q�b�g(�G)
		SOUND_LABEL_SE_SWORD_HIT_WALL,		// ���q�b�g(��)
		SOUND_LABEL_SE_SWORD_HIT_TREE,		// ���q�b�g(��)
		SOUND_LABEL_SE_BREAK_TREE,			// �؂̔j��
		SOUND_LABEL_SE_BREAK_WALL,			// �ǂ̔j��
		SOUND_LABEL_SE_GOAL,				// �S�[��(�N���b�J�[��)
		SOUND_LABEL_SE_GOAL2,				// �S�[��2(���艹)
		SOUND_LABEL_SE_WARNING,				// �x����
		SOUND_LABEL_SE_WATER_FALL,			// ��������
		SOUND_LABEL_SE_DAMAGE,				// �_���[�W��
		SOUND_LABEL_SE_WALK,				// ������
		SOUND_LABEL_SE_WALK2,				// ������2
		SOUND_LABEL_SE_JUMP,				// �W�����v
		SOUND_LABEL_SE_CHANGE_WEAPON,		// ���펝���ւ�
		SOUND_LABEL_SE_SELECT,				// �J�[�\����
		SOUND_LABEL_SE_ENTER,				// ���艹
		SOUND_LABEL_MAX

	} SOUND_LABEL;

	//=============================================================================
	// �v���g�^�C�v�錾
	//=============================================================================
	HRESULT InitSound(void);
	void UninitSound(void);
	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);
	void ControllVoice(SOUND_LABEL label, float fVolume) { m_apSourceVoice[label]->SetVolume(fVolume); }

private:
	//=============================================================================
	// �p�����[�^�\���̒�`
	//=============================================================================
	typedef struct
	{
		char *filename;		// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g
	} PARAM;

	// �e���f�ނ̃p�����[�^
	static PARAM m_aParam[SOUND_LABEL_MAX];

	//=============================================================================
	// �v���g�^�C�v�錾
	//=============================================================================
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	//=============================================================================
	// �O���[�o���ϐ�
	//=============================================================================
	IXAudio2 *m_pXAudio2 = NULL;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;			// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX] = {};	// �\�[�X�{�C�X
	BYTE *m_apDataAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^�T�C�Y

};
#endif
