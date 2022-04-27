//=============================================================================
//
// �|���S���̏��� [scene.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include"scene.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
CScene*CScene::m_pTop = NULL;
CScene*CScene::m_pCur = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScene::CScene()
{
	// 1�ڂ̃|���S��
	if (m_pTop == NULL)
	{
		m_pTop = this;			//�擪(1��)�Ƀ^�X�L��n��
		m_pCur = this;			//���(1��)�ɊŔ�n��
		m_pPrev = NULL;			//�O(�̐l�͂��Ȃ�)
		m_pNext = NULL;			//��(�̐l�͂��Ȃ�)
	}
	else
	{
		// 2�ڈȍ~
		m_pPrev = m_pCur;		//(���X���ɂ����l���O�̐l�ɂȂ�j
		m_pCur->m_pNext = this;	//(���X���ɂ����l�����̐l�ɊŔ�n���j
		m_pCur = this;			//(��Ԍ�낪�������ƋC�Â�)
		m_pNext = NULL;			//��(�̐l�͂��Ȃ�)
	}
	// ���S�t���O���Ȃ�
	m_bDeath = false;
}

//=============================================================================
//�@�f�X�g���N�^
//=============================================================================
CScene::~CScene()
{
	// this��m_Top��������
	if (this == m_pTop)
	{
		// �g�b�v(m_pTop)�̏��ɂ���ϐ�{this(���̃|���S��)�̎�(m_pNext)}�̏�������
		m_pTop = this->m_pNext;

		// {this(���̃|���S��)�̎�(m_pNext)}�̏��ɂȂɂ���񂪓����Ă�����
		if (this->m_pNext != NULL)
		{
			// {this(���̃|���S��)�̎�(m_pNext)}�̑O(m_pPrev)�̏���NULL�����ď��𖳂���
			this->m_pNext->m_pPrev = NULL;
		}

	}
	// this��m_pCur��������
	else if (this == m_pCur)
	{
		// ��ԍŌ�(m_pCur)�̏���{this(���̃|���S��)�̑O(m_pPrev)}�̏���ϐ��ɓ����
		m_pCur = this->m_pPrev;

		// {this(���̃|���S��)�̑O(m_pPrev)}�̏��ɂȂɂ���񂪓����Ă�����
		if (this->m_pPrev != NULL)
		{
			// {this(���̃|���S��)�̑O(m_pPrev)}�̎�(m_pNext)�̏���NULL�����ď��𖳂���
			this->m_pPrev->m_pNext = NULL;
		}
	}

	// this������ȊO(����̏ꍇ(�^��))��������
	else if (this != m_pTop&&this != m_pCur)
	{
		// pScene�ɐ^�񒆂̏�������
		CScene * pScene = this;		//pScene�͐^�񒆂̑���ɂȂ�

		if (pScene != NULL)
		{
			// ���݂̑O�̏���pScenePrev�̕ϐ��ɓ����
			pScene->m_pPrev->m_pNext = pScene->m_pNext;

			// ���݂̎��̏���pSceneNext�̕ϐ��ɓ����
			pScene->m_pNext->m_pPrev = pScene->m_pPrev;
		}
	}
	else
	{
		m_pTop = NULL;
		m_pCur = NULL;

	}
}

//=============================================================================
// ���ׂẴI�u�W�F�N�g�̊J������
//=============================================================================
void CScene::ReleaseAll(void)
{
	// pScene��m_pTop�̏�������
	CScene * pScene = m_pTop;		//pScene��m_Top�̑���ɂȂ�

	//�@����NULL����Ȃ��Ȃ瑱��
	while (pScene != NULL)
	{
		// ���݂̎��̏���pSceneNext�̕ϐ��ɓ����
		CScene * pSceneNext = pScene->m_pNext;

		if (pScene->m_bDeath == true)
		{
			// ���݂̏����J������
			delete pScene;
			//pScene = NULL;
		}

		// ���݂̏������̏��ɍX�V����
		pScene = pSceneNext;
	}
}



//=============================================================================
// ���ׂẴI�u�W�F�N�g�̍X�V����
//=============================================================================
void CScene::UpdateAll(void)
{
	// pScene��m_pTop�̏�������
	CScene * pScene = m_pTop;		//pScene��m_Top�̑���ɂȂ�

									// ����NULL����Ȃ���ԂȂ瑱��
	while (pScene != NULL)
	{
		// ���݂̎��̏���pSceneNext�̕ϐ��ɓ����
		CScene * pSceneNext = pScene->m_pNext;

		// ���݂̏����X�V����
		pScene->Update();

		if (pScene->m_bDeath == true)
		{
			delete pScene;
			pScene = NULL;
		}

		// ���݂̏������̏��ɍX�V����
		pScene = pSceneNext;
	}
}

//=============================================================================
// ���ׂẴI�u�W�F�N�g�̕`�揈��
//=============================================================================
void CScene::DrawAll(void)
{
	// pScene��m_pTop�̏�������
	CScene * pScene = m_pTop;		//pScene��m_Top�̑���ɂȂ�

									//�@����NULL����Ȃ��Ȃ瑱��
	while (pScene != NULL)
	{
		// ���݂̎��̏���pSceneNext�̕ϐ��ɓ����
		CScene * pSceneNext = pScene->m_pNext;

		// ���݂̏���`�悷��
		pScene->Draw();

		// ���݂̏������̏��ɍX�V����
		pScene = pSceneNext;
	}
}


//=============================================================================
// ��̃I�u�W�F�N�g�̊J������
//=============================================================================
void  CScene::Release(void)
{
	// ���݂̃I�u�W�F�N�g�Ɏ��S�t���O������
	m_bDeath = true;
}