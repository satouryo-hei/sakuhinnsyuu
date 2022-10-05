//=============================================================================
//
// 音の処理 [sound.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// 音のクラス
//*****************************************************************************
class CSound
{
public:
	CSound();
	~CSound();	
	// サウンドファイル	
	typedef enum
	{
		SOUND_LABEL_BGM = 0,			// 戦闘bgm0
		SOUND_LABEL_BGM00,				// ヒーリング
		SOUND_LABEL_BGM000,				// うるさいBGM
		SOUND_LABEL_SUMMER_FOG,			// 自然の音に近いやつBGM
		SOUND_LABEL_SUMMER_EXPEDITION,	// ファンタジーなBGM
		SOUND_LABEL_BGM004,				// BGM4
		SOUND_LABEL_SHOT000,			// ショット音
		SOUND_LABEL_bom000,				// 爆発音
		SOUND_LABEL_MAX,
	} SOUND_LABEL;	
	// メンバ関数	
	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT Play(SOUND_LABEL label);
	void Stop(SOUND_LABEL label);
	void Stop(void);

private:	
	// パラメータ構造体定義	
	typedef struct
	{
		char *filename;		// ファイル名
		int nCntLoop;		// ループカウント
	} PARAM;

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2 *m_pXAudio2;									// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice *m_pMasteringVoice;				// マスターボイス
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// ソースボイス
	BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// オーディオデータ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];
	static PARAM m_aParam[SOUND_LABEL_MAX];
};

#endif
