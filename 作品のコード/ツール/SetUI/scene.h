//=============================================================================
//
// �|���S���̏��� [scene.h]
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
public:																// �N�ł��A�N�Z�X�\
	CScene();														// �R���X�g���N�^
	virtual~CScene();												// �f�X�g���N�^
	// �����o�֐�
	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size) = 0;	// �|���S���̏������֐�
	virtual void Uninit(void) = 0;									// �|���S���̏I���֐��@
	virtual void Update(void) = 0;									// �|���S���̍X�V�֐�
	virtual void Draw(void) = 0;									// �|���S���̕`��֐�
	static void ReleaseAll(void);									// ���ׂẴI�u�W�F�N�g�̊J���֐�
	static void UpdateAll(void);									// ���ׂẴI�u�W�F�N�g�̍X�V�֐�
	static void DrawAll(void);										// ���ׂẴI�u�W�F�N�g�̕`��֐�

protected:															// �����Ɣh���n�̂݃A�N�Z�X�\
	void  Release(void);											// 1�̃I�u�W�F�N�g�̊J���֐�

private:															// �����������A�N�Z�X�\
	// �ÓI�����o�ϐ�
	static CScene*m_pTop;											// �擪�̃I�u�W�F�N�g�̃|�C���^
	static CScene*m_pCur;											// ����(��Ԍ��)�̃I�u�W�F�N�g�̃|�C���^

	// �����o�ϐ�
	CScene*m_pPrev;													// �O�̃I�u�W�F�N�g�ւ̃|�C���^
	CScene*m_pNext;													// ���̃I�u�W�F�N�g�ւ̃|�C���^
	bool m_bDeath;													// ���S�t���O
};
#endif
