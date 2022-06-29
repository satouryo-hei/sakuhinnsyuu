//=============================================================================
//
// �I�u�W�F�N�g�̏��� [scene.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

#include"main.h"

//*****************************************************************************
// �I�u�W�F�N�g�N���X
//*****************************************************************************
class CScene
{
public:													// �N�ł��A�N�Z�X�\

	// �I�u�W�F�N�g�̎��
	typedef enum
	{		 
		PRIORITY_NOMAL = 0,																					// �m�[�}��
		PRIORITY_FIRST,
		PRIORITY_SECOND,																					// 2��
		PRIORITY_THIRD,																						// 3��
		PRIORITY_PLAYER,
		PRIORITY_ENEMY,
		PRIORITY_MODEL,
		PRIORITY_ITEM,																						// 3��
		PRIORITY_BILLBOARD,
		PRIORITY_BULLET,
		PRIORITY_EFFECT,
		PRIORITY_UI,
		PRIORITY_FADE,
		PRIORITY_MAX																						// ���ׂĂ̐�
	} PRIORITY;

	CScene(PRIORITY Priority);															// �R���X�g���N�^
	virtual~CScene();																	// �f�X�g���N�^
	// �����o�֐�
	virtual HRESULT Init(D3DXVECTOR3 pos) = 0;											// �I�u�W�F�N�g�̏������֐�
	virtual void Uninit(void) = 0;														// �I�u�W�F�N�g�̏I���֐��@
	virtual void Update(void) = 0;														// �I�u�W�F�N�g�̍X�V�֐�
	virtual void Draw(void) = 0;														// �I�u�W�F�N�g�̕`��֐�
	static void ReleaseAll(void);														// ���ׂẴI�u�W�F�N�g�̊J���֐�
	static void UpdateAll(void);														// ���ׂẴI�u�W�F�N�g�̍X�V�֐�
	static void DrawAll(void);															// ���ׂẴI�u�W�F�N�g�̕`��֐�
	static CScene * GetScene(int nPriority) { return m_pTop[nPriority]; }				// ���Ԗڂ̃I�u�W�F�N�g���̎擾����
	static CScene * GetSceneNext(int nPriority) { return m_pTop[nPriority]->m_pNext; }	// ���Ԗڂ̎��̃I�u�W�F�N�g�̎擾����

protected:																				// �����Ɣh���n�̂݃A�N�Z�X�\
	void Release(void);																	// 1�̃I�u�W�F�N�g�̊J���֐�

private:																				// �����������A�N�Z�X�\
																						// �����o�ϐ�
	static CScene*m_pTop[PRIORITY_MAX];													// �擪�̃I�u�W�F�N�g�̃|�C���^
	static CScene*m_pCur[PRIORITY_MAX];													// ����(��Ԍ��)�̃I�u�W�F�N�g�̃|�C���^
	CScene*m_pPrev;																		// �O�̃I�u�W�F�N�g�ւ̃|�C���^
	CScene*m_pNext;																		// ���̃I�u�W�F�N�g�ւ̃|�C���^
	bool m_bDeath;																		// ���S�t���O
	int m_nPriority;																	// �D�揇��
};
#endif