//----------------------------------
//�I�u�W�F�N�g�̏���
//----------------------------------
#include "scene.h"
#include "scene2D.h"
#include "manager.h"
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��錾
//-----------------------------------------------------------------------------
int CScene::m_nNumAll[OBJTYPE_MAX] = {};
CScene *CScene::m_pCur[OBJTYPE_MAX] = {};
CScene *CScene::m_pTop[OBJTYPE_MAX] = {};



//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScene::CScene()
{
}
CScene::CScene(OBJTYPE nPriority)
{
	//�g�b�v��NULL��������擪�I�u�W�F�N�g
	if (m_pTop[nPriority] == NULL)
	{
		m_pTop[nPriority] = this;
		m_pCur[nPriority] = this;
		m_pPrev = NULL;
		m_pNext = NULL;
		m_bDamage = false;

	}
	//����
	//m_pCur��NULL�������猻�݂̃I�u�W�F�N�g
	else
	{
		m_pCur[nPriority]->m_pNext = this;//�O�̃I�u�W�F�N�g�̎��͎���
		m_pPrev = m_pCur[nPriority];	//�����̑O�̃I�u�W�F�N�g����
		m_pCur[nPriority] = this;		//���݂̃I�u�W�F�N�g�������ɂ���
		m_pNext = NULL;
		m_bDamage = false;

	}
	m_bDath = false;
	m_nPriority = nPriority;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================

CScene::~CScene()
{
	//�R�R�̃I�u�W�F�N�g����������Ă�����
	if (this == m_pTop[m_nPriority] && this == m_pCur[m_nPriority])
	{
		m_pTop[m_nPriority] = NULL;
		m_pCur[m_nPriority] = NULL;
		m_pNext = NULL;
		m_pPrev = NULL;
	}
	else if (this == m_pTop[m_nPriority])
	{
		m_pNext->m_pPrev = NULL;
		m_pTop[m_nPriority] = m_pNext;

	}
	else if (this == m_pCur[m_nPriority])
	{
		m_pPrev->m_pNext = NULL;
		m_pCur[m_nPriority] = m_pPrev;

	}
	else
	{
		m_pPrev->m_pNext = m_pNext;
		m_pNext->m_pPrev = m_pPrev;
	}


}
//�S�ẴI�u�W�F�̍X�V	
void CScene::UpdateAll(void)
{
	for (int nObj = 0; nObj < OBJTYPE_MAX; nObj++)
	{
		if (CManager::GetPause() == false)
		{
			if (m_pTop[nObj] != NULL)
			{
				CScene *m_pUpdate = m_pTop[nObj];				//���ɍX�V����I�u�W�F�N�g�̊i�[
																//m_pUpdate��NULL������܂�
				while (m_pUpdate != NULL)
				{
					m_pUpdate->Update();
					m_pUpdate = m_pUpdate->m_pNext;
				}
			}
		}
		else
		{
			if (nObj == OBJTYPE_PAUSE || nObj == OBJTYPE_UI || nObj == OBJTYPE_FADE)
			{
				if (m_pTop[nObj] != NULL)
				{
					CScene *m_pUpdate = m_pTop[nObj];				//���ɍX�V����I�u�W�F�N�g�̊i�[
																	//m_pUpdate��NULL������܂�
					while (m_pUpdate != NULL)
					{
						if (m_pUpdate->m_bDath == false)
						{
							m_pUpdate->Update();
						}
							m_pUpdate = m_pUpdate->m_pNext;

					}
				}
			}
		}
	}

	//���S�t���O����
	for (int nObj = 0; nObj < OBJTYPE_MAX; nObj++)
	{
		CScene *m_pUpdate = m_pTop[nObj];				//���ɍX�V����I�u�W�F�N�g�̊i�[
		CScene *m_pDeleteUpdate = NULL;				//���ɍX�V����I�u�W�F�N�g�̊i�[
		//�I�u�W�F�N�g��NULL�ɂȂ�܂�
		while (m_pUpdate)
		{
			//���̃f�[�^�������Ȃ��悤�ɕۑ�
			m_pDeleteUpdate = m_pUpdate->m_pNext;
			//���S�t���O�������Ă�����
			if (m_pUpdate->m_bDath == true)
			{
				//����
				delete m_pUpdate;
				m_pUpdate = NULL;
			}
			//���̃I�u�W�F�N�g�ɂ���
			m_pUpdate = m_pDeleteUpdate;

		}
	}

}
//�S�ẴI�u�W�F�̕`��
void CScene::DrawAll(void)
{
	for (int nObj = 0; nObj < OBJTYPE_MAX; nObj++)
	{
		if (m_pTop[nObj] != NULL)
		{
			CScene *m_pDraw = m_pTop[nObj];				//���ɍX�V����I�u�W�F�N�g�̊i�[
														//m_pUpdate��NULL������܂�
			while (m_pDraw)
			{
				if (m_pDraw->m_bDath == false)
				{
					m_pDraw->Draw();
				}
					m_pDraw = m_pDraw->m_pNext;

			}
		}
	}
	//���S�t���O����
	for (int nObj = 0; nObj < OBJTYPE_MAX; nObj++)
	{
		CScene *m_pDraw = m_pTop[nObj];				//���ɍX�V����I�u�W�F�N�g�̊i�[
		CScene *m_pDeleteDraw = NULL;				//���ɍX�V����I�u�W�F�N�g�̊i�[

		while (m_pDraw)
		{
			//���̃f�[�^�������Ȃ��悤�ɕۑ�

			m_pDeleteDraw = m_pDraw->m_pNext;
			//���S�t���O�������Ă�����
			if (m_pDraw->m_bDath == true)
			{
				//����
				delete m_pDraw;
				m_pDraw = NULL;
			}
			//���̃I�u�W�F�N�g�ɂ���
			m_pDraw = m_pDeleteDraw;

		}
	}

}
//�S�ẴC���X�^���X�̔j������
void CScene::Delete(void)
{
	for (int nObj = 0; nObj < OBJTYPE_MAX; nObj++)
	{
		CScene *pScene;
		pScene = m_pTop[nObj];
		//�Ō�̃I�u�W�F�N�g�̎���Next��NULL�łȂ�������
		//�������[�v
		if (nObj != OBJTYPE_FADE)
		{
			while (pScene != NULL)
			{
				//�g�b�v�̎��̃I�u�W�F�N�g���i�[
				CScene *pDeletePrev = pScene->m_pNext;
				//�g�b�v�̏�������
				delete pScene;
				pScene = NULL;
				//�g�b�v�̏������̃I�u�W�F�N�g�ɂ���
				pScene = pDeletePrev;
			}

		}
	}
}
//�I�u�W�F�N�g�P�̂̃C���X�^���X�j��
void CScene::Release(void)
{
	m_bDath = true;

}

void CScene::LifeSub(int nPow)
{
	m_nLife -= nPow; 
}
