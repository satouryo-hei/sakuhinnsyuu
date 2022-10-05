//=============================================================================
//
// ���̏��� [sound.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// ���̃N���X
//*****************************************************************************
class CSound
{
public:
	CSound();
	~CSound();	
	// �T�E���h�t�@�C��	
	typedef enum
	{
		SOUND_LABEL_BGM = 0,			// �퓬bgm0
		SOUND_LABEL_BGM00,				// �q�[�����O
		SOUND_LABEL_BGM000,				// ���邳��BGM
		SOUND_LABEL_SUMMER_FOG,			// ���R�̉��ɋ߂����BGM
		SOUND_LABEL_SUMMER_EXPEDITION,	// �t�@���^�W�[��BGM
		SOUND_LABEL_BGM004,				// BGM4
		SOUND_LABEL_SHOT000,			// �V���b�g��
		SOUND_LABEL_bom000,				// ������
		SOUND_LABEL_MAX,
	} SOUND_LABEL;	
	// �����o�֐�	
	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT Play(SOUND_LABEL label);
	void Stop(SOUND_LABEL label);
	void Stop(void);

private:	
	// �p�����[�^�\���̒�`	
	typedef struct
	{
		char *filename;		// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g
	} PARAM;

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2 *m_pXAudio2;									// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice;				// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// �\�[�X�{�C�X
	BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];
	static PARAM m_aParam[SOUND_LABEL_MAX];
};

#endif
