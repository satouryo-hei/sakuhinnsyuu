//=============================================================================
//
// UI�̓ǂݍ��݂̏��� [uilode.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _UILODE_H_
#define _UILODE_H_

#define MAX_UI (12)
#include"main.h"

//*****************************************************************************
// UI�̓ǂݍ��݃N���X
//*****************************************************************************
class CUilode
{
public:																			// �N�ł��A�N�Z�X�\
	CUilode(const char * pFileNeme);											// �R���X�g���N�^
	~CUilode();																	// �f�X�g���N�^

	D3DXVECTOR3 GetUIPos(int nNum) { return m_LodePos[nNum]; }					// �ǂݍ��񂾈ʒu��Ԃ�
	D3DXVECTOR2 GetUISize(int nNum) { return m_LodeSize[nNum]; }				// �ǂݍ��񂾑傫����Ԃ�

private:																		// �����������A�N�Z�X�\
	inline void Lode(const char * pFileNeme);	
	static int m_nMaxUI;														// �e�N�X�`���̍ő吔	
	D3DXVECTOR3 m_LodePos[MAX_UI];												// ui�̈ʒu�̓ǂݍ���
	D3DXVECTOR2 m_LodeSize[MAX_UI];												// ui�̑傫���̓ǂݍ���
};
#endif