//=============================================================================
//
// ���̏��� [sound.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include "sound.h"

// �ÓI�����o�ϐ��̐錾
CSound::PARAM CSound::m_aParam[SOUND_LABEL_MAX] = {};

//=============================================================================
// ���̃R���X�g���N�^
//=============================================================================
CSound::CSound()
{
	m_pXAudio2 = NULL;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	m_pMasteringVoice = NULL;						// �}�X�^�[�{�C�X

	for (int nConut = 0; nConut < SOUND_LABEL_MAX; nConut++)
	{
		m_apSourceVoice[nConut] = NULL;			// �\�[�X�{�C�X
		m_apDataAudio[nConut] = NULL;			// �I�[�f�B�I�f�[�^	
	}
}

//=============================================================================
//�@���̃f�X�g���N�^
//=============================================================================
CSound::~CSound()
{
}

//=============================================================================
// ���̏�����
//=============================================================================
HRESULT CSound::Init(HWND hWnd)
{
	// �e���f�ނ̃p�����[�^
	PARAM g_aParam[SOUND_LABEL_MAX] =
	{
		{ "data/BGM/bgm.wav", -1 },						// �퓬�ۂ�BGM
		{ "data/BGM/bgm00.wav", -1 },					// �q�[�����OBGM
		{ "data/BGM/bgm000.wav", -1 },					// ���邳��BGM
		{ "data/BGM/Summer_fog.wav", -1 },				// ���R�̉��ɋ߂�BGM
		{ "data/BGM/Summer_expedition.wav", -1 },		// �t�@���^�W�[��BGM
		{ "data/BGM/bgm004.wav", -1 },					// �T���v��BGM
		{ "data/SE/shot000.wav", 0 },					// �V���b�g��
		{ "data/SE/bom000.wav", 0 }						//������
	};

	HRESULT hr;

	// COM���C�u�����̏�����
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// XAudio2�I�u�W�F�N�g�̍쐬
	hr = XAudio2Create(&m_pXAudio2, 0);
	if(FAILED(hr))
	{
		// COM���C�u�����̏I������
		CoUninitialize();
		return E_FAIL;
	}
	
	// �}�X�^�[�{�C�X�̐���
	hr = m_pXAudio2->CreateMasteringVoice(&m_pMasteringVoice);
	if(FAILED(hr))
	{
		if(m_pXAudio2)
		{
			// XAudio2�I�u�W�F�N�g�̊J��
			m_pXAudio2->Release();
		}

		// COM���C�u�����̏I������
		CoUninitialize();
		return E_FAIL;
	}

	// �T�E���h�f�[�^�̏�����
	for(int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		HANDLE hFile;
		DWORD dwChunkSize = 0;
		DWORD dwChunkPosition = 0;
		DWORD filetype;
		WAVEFORMATEXTENSIBLE wfx;
		XAUDIO2_BUFFER buffer;

		// �o�b�t�@�̃N���A
		memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

		// �T�E���h�f�[�^�t�@�C���̐���
		hFile = CreateFile(g_aParam[nCntSound].filename, GENERIC_READ,
							FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
		if(hFile == INVALID_HANDLE_VALUE)
		{
			return HRESULT_FROM_WIN32(GetLastError());
		}
		if(SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
		{
			return HRESULT_FROM_WIN32(GetLastError());
		}
	
		// WAVE�t�@�C���̃`�F�b�N
		hr = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);
		if(FAILED(hr))
		{
			return S_FALSE;
		}
		hr = ReadChunkData(hFile, &filetype, sizeof(DWORD), dwChunkPosition);
		if(FAILED(hr))
		{
			return S_FALSE;
		}
		if(filetype != 'EVAW')
		{
			return S_FALSE;
		}
	
		// �t�H�[�}�b�g�`�F�b�N
		hr = CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);
		if(FAILED(hr))
		{
			return S_FALSE;
		}
		hr = ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
		if(FAILED(hr))
		{
			return S_FALSE;
		}

		// �I�[�f�B�I�f�[�^�ǂݍ���
		hr = CheckChunk(hFile, 'atad', &m_aSizeAudio[nCntSound], &dwChunkPosition);
		if(FAILED(hr))
		{
			return S_FALSE;
		}
		m_apDataAudio[nCntSound] = (BYTE*)malloc(m_aSizeAudio[nCntSound]);
		hr = ReadChunkData(hFile, m_apDataAudio[nCntSound], m_aSizeAudio[nCntSound], dwChunkPosition);
		if(FAILED(hr))
		{
			return S_FALSE;
		}
	
		m_pXAudio2->CreateSourceVoice(&m_apSourceVoice[nCntSound], &(wfx.Format));

		// �o�b�t�@�̐ݒ�
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
		buffer.AudioBytes = m_aSizeAudio[nCntSound];
		buffer.pAudioData = m_apDataAudio[nCntSound];
		buffer.Flags      = XAUDIO2_END_OF_STREAM;
		buffer.LoopCount  = g_aParam[nCntSound].nCntLoop;

		m_apSourceVoice[nCntSound]->SubmitSourceBuffer(&buffer);

		// �t�@�C�����N���[�Y
		CloseHandle(hFile);
	}

	return S_OK;
}


//=============================================================================
// ���̏I������
//=============================================================================
void CSound::Uninit(void)
{
	// �ꎞ��~
	for(int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		if(m_apSourceVoice[nCntSound] != NULL)
		{
			// �ꎞ��~
			m_apSourceVoice[nCntSound]->Stop(0);
	
			// �\�[�X�{�C�X�̔j��
			m_apSourceVoice[nCntSound]->DestroyVoice();
	
			// �I�[�f�B�I�f�[�^�̊J��
			free(m_apDataAudio[nCntSound]);
		}
	}
	
	// �}�X�^�[�{�C�X�̔j��
	m_pMasteringVoice->DestroyVoice();
	
	if(m_pXAudio2)
	{
		// XAudio2�I�u�W�F�N�g�̊J��
		m_pXAudio2->Release();
	}
	
	// COM���C�u�����̏I������
	CoUninitialize();
}

//=============================================================================
// �Z�O�����g�Đ�(��~)
//=============================================================================
HRESULT CSound::Play(SOUND_LABEL label)
{
	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER       buffer;

	// �o�b�t�@�̐ݒ�
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = m_aSizeAudio[label];
	buffer.pAudioData = m_apDataAudio[label];
	buffer.Flags      = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount  = m_aParam[label].nCntLoop;

	// ��Ԏ擾
	m_apSourceVoice[label]->GetState(&xa2state);
	if(xa2state.BuffersQueued != 0)
	{// �Đ���
		// �ꎞ��~
		m_apSourceVoice[label]->Stop(0);

		// �N���A
		m_apSourceVoice[label]->FlushSourceBuffers();
	}

	// �o�^
	m_apSourceVoice[label]->SubmitSourceBuffer(&buffer);

	// �Đ�
	m_apSourceVoice[label]->Start( 0 );

	return S_OK;
}

//=============================================================================
// �Z�O�����g��~
//=============================================================================
void CSound::Stop(SOUND_LABEL label)
{
	XAUDIO2_VOICE_STATE xa2state;

	// ��Ԏ擾
	m_apSourceVoice[label]->GetState(&xa2state);
	if(xa2state.BuffersQueued != 0)
	{// �Đ���
		// �ꎞ��~
		m_apSourceVoice[label]->Stop(0);

		// �N���A
		m_apSourceVoice[label]->FlushSourceBuffers();
	}
}

//=============================================================================
// �Z�O�����g��~
//=============================================================================
void CSound::Stop(void)
{
	for(int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		if(m_apSourceVoice[nCntSound] != NULL)
		{
			// �ꎞ��~
			m_apSourceVoice[nCntSound]->Stop(0);

			// �N���A
			m_apSourceVoice[nCntSound]->FlushSourceBuffers();
		}
	}
}

//=============================================================================
// �`�����N�̃`�F�b�N
//=============================================================================
HRESULT CSound::CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition)
{
	HRESULT hr = S_OK;
	DWORD dwRead;
	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD dwBytesRead = 0;
	DWORD dwOffset = 0;
	
	if(SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// �t�@�C���|�C���^��擪�Ɉړ�
		return HRESULT_FROM_WIN32(GetLastError());
	}
	
	while(hr == S_OK)
	{
		if(ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
		{// �`�����N�̓ǂݍ���
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if(ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
		{// �`�����N�f�[�^�̓ǂݍ���
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch(dwChunkType)
		{
		case 'FFIR':

			dwRIFFDataSize  = dwChunkDataSize;

			dwChunkDataSize = 4;

			if(ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
			{// �t�@�C���^�C�v�̓ǂݍ���
				hr = HRESULT_FROM_WIN32(GetLastError());
			}
			break;

		default:

			if(SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{// �t�@�C���|�C���^���`�����N�f�[�^���ړ�
				return HRESULT_FROM_WIN32(GetLastError());
			}
		}

		dwOffset += sizeof(DWORD) * 2;

		if(dwChunkType == format)
		{
			*pChunkSize         = dwChunkDataSize;
			*pChunkDataPosition = dwOffset;

			return S_OK;
		}

		dwOffset += dwChunkDataSize;

		if(dwBytesRead >= dwRIFFDataSize)
		{
			return S_FALSE;
		}
	}
	
	return S_OK;
}

//=============================================================================
// �`�����N�f�[�^�̓ǂݍ���
//=============================================================================
HRESULT CSound::ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
{
	DWORD dwRead;
	
	if(SetFilePointer(hFile, dwBufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// �t�@�C���|�C���^���w��ʒu�܂ňړ�
		return HRESULT_FROM_WIN32(GetLastError());
	}

	if(ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL) == 0)
	{// �f�[�^�̓ǂݍ���
		return HRESULT_FROM_WIN32(GetLastError());
	}
	
	return S_OK;
}