//=============================================================================
//
// �I�u�W�F�N�g���� [scene.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include"scene.h"

// �ÓI�����o�ϐ��̐錾
CScene *CScene::m_apScene[PRIORITY_MAX][MAX_DATA] = {};
int CScene::m_nNumAll = 0;

//=============================================================================
// �I�u�W�F�N�g�̃R���X�g���N�^
//=============================================================================
CScene::CScene(int nPriority)
{
	m_nID = 0;

	m_nPriority = 0;

	for (int nCntScene = 0; nCntScene < MAX_DATA; nCntScene++)
	{
		if (m_apScene[nPriority][nCntScene] == NULL)
		{
			m_apScene[nPriority][nCntScene] = this;

			//�����̔ԍ���ݒ�
			m_nID = nCntScene;
			m_nPriority = nPriority;
			m_nNumAll++;
			break;
		}
	}
}

//=============================================================================
//�@�I�u�W�F�N�g�̃f�X�g���N�^
//=============================================================================
CScene::~CScene()
{

}

//=============================================================================
// ���ׂẴI�u�W�F�N�g�̊J������
//=============================================================================
void CScene::ReleseAll(void)
{
	for (int nCnt = 0; nCnt < PRIORITY_MAX; nCnt++)
	{
		for (int nCntScene = 0; nCntScene < MAX_DATA; nCntScene++)
		{
			if (m_apScene[nCnt][nCntScene] != NULL)
			{
				if (nCnt != PRIORITY_FADE)
				{
					m_apScene[nCnt][nCntScene]->Uninit();
				}
			}
		}
	}
}

//=============================================================================
// ���ׂẴI�u�W�F�N�g�̍X�V����
//=============================================================================
void CScene::UpdateAll(void)
{
	for (int nCnt = 0; nCnt < PRIORITY_MAX; nCnt++)
	{
		for (int nCntScene = 0; nCntScene < MAX_DATA; nCntScene++)
		{
			if (m_apScene[nCnt][nCntScene] != NULL)
			{
				m_apScene[nCnt][nCntScene]->Update();
			}
		}
	}
}

//=============================================================================
// ���ׂẴI�u�W�F�N�g�̕`�揈��
//=============================================================================
void CScene::DrawAll(void)
{
	for (int nCnt = 0; nCnt < PRIORITY_MAX; nCnt++)
	{
		for (int nCntScene = 0; nCntScene < MAX_DATA; nCntScene++)
		{
			if (m_apScene[nCnt][nCntScene] != NULL)
			{
				m_apScene[nCnt][nCntScene]->Draw();
			}
		}
	}
}


//=============================================================================
// ��̃I�u�W�F�N�g�̊J������
//=============================================================================
void  CScene::Relese(void)
{
		if (m_apScene[m_nPriority][m_nID] != NULL)
		{
			int nID = m_nID;
			int nPriority = m_nPriority;
			m_apScene[nPriority][nID] = this;
			delete m_apScene[nPriority][nID];
			m_apScene[nPriority][nID] = NULL;
			m_nNumAll--;
		}
}