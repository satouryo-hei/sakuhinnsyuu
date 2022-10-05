//=============================================================================
//
// UI�̓ǂݍ��ݏ��� [uilode.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include "uilode.h"
#include "renderer.h"
#include "manager.h"

//=============================================================================
// �ÓI�����o�ϐ��̐錾
//=============================================================================
int CUilode::m_nMaxUI = 0;

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CUilode::CUilode(const char * pFileNeme)
{
	memset(&m_LodePos[0], NULL, sizeof(m_LodePos));
	memset(&m_LodeSize[0], NULL, sizeof(m_LodeSize));
	Lode(pFileNeme);
}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CUilode::~CUilode()
{
	memset(&m_LodePos[0], NULL, sizeof(m_LodePos));
	memset(&m_LodeSize[0], NULL, sizeof(m_LodeSize));
}

//=============================================================================
// UI�̓ǂݍ��ݏ���
//=============================================================================
void CUilode::Lode(const char * pFileNeme)
{
	// �J���`�t�@�C���I
	FILE *pFile = fopen(pFileNeme, "r");
	//--------------------------
	// �ǂݍ��ޗp�̕ϐ�
	//--------------------------
	char aFile[3][128] = {};
	char aName[128] = {};
	int nSetCnt = 0;
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR2 size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �t�@�C������������
	if (pFile != NULL)
	{
		// �������[�v
		while (1)
		{
			fscanf(pFile, "%s", &aFile[0][0]);										// 1���ǂݍ���(2�s�ڈȍ~�͏㏑�������)

			if (strcmp(&aFile[0][0], "NUM_UI") == 0)								// NUM_UI������������
			{
				fscanf(pFile, "%s%d", &aName[0], &m_nMaxUI);						// UI�̐���ǂݍ���
			}

			while (strcmp(&aFile[0][0], "SETUI") == 0)								// SETUI������������
			{
				fscanf(pFile, "%s", &aFile[1]);										// 1���ǂݍ���(2�s�ڈȍ~�͏㏑�������)
				if (strcmp(&aFile[1][0], "POS") == 0)								// POS������������
				{
					fscanf(pFile, "%s%f%f%f", &aName[0], &pos.x, &pos.y, &pos.z);	// ���݂̈ʒu��ǂݍ���
				}
				else if (strcmp(&aFile[1][0], "SIZE") == 0)							// SIZE������������
				{
					fscanf(pFile, "%s%f%f", &aName[0], &size.x, &size.y);			// ���݂̑傫����ǂݍ���
				}
				else if (strcmp(&aFile[1][0], "END_SETUI") == 0)					// END_SETUI������������
				{
					m_LodePos[nSetCnt] = pos;										// �ǂݍ��񂾈ʒu���������o��SetPos�Ɉڂ�
					m_LodeSize[nSetCnt] = size;										// �ǂݍ��񂾑傫�����������o��SetSize�Ɉڂ�
					nSetCnt++;														// ���̕�
					break;															// �������[�v�𔲂���
				}
			}
			if (strcmp(&aFile[0][0], "END_SCRIPT") == 0)							// END_SCRIPT������������
			{
				break;																// �������[�v�𔲂���
			}
		}
	}
	else
	{
		printf("�t�@�C�����ǂݍ��܂�܂���ł����B");
	}

	// ����`�t�@�C���I
	fclose(pFile);
}