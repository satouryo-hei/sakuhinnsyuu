//=============================================================================
//
// �S�[���̏��� [goal.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _GOAL_H_
#define _GOAL_H_

#include"scene2D.h"
#include"manager.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CPushButton;

//*****************************************************************************
// �S�[���̃N���X
//*****************************************************************************
class CGoal : public CScene2D
{
public:																// �N�ł��A�N�Z�X�\
	CGoal(int nPriority = PRIORITY_NOMAL);							// �R���X�g���N�^
	~CGoal();														// �f�X�g���N�^
																	// �����o�֐�
	static CGoal *Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size, CManager::MODE NextMode);		// �S�[���̐���
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);				// �S�[���̏������֐�
	void Uninit(void);												// �S�[���̏I���֐�
	void Update(void);												// �S�[���̍X�V�֐�
	void Draw(void);												// �S�[���̕`��֐�
	static bool GetClear() { return m_bGameClear; }

private:															// �����������A�N�Z�X�\		
	static CPushButton * m_pPushButton;								// �������{�^���̃|�C���^�[����
	D3DXVECTOR3 m_Pos;												// �S�[���̌��ݒn	
	D3DXVECTOR2 m_Size;												// �S�[���̑傫��	
	bool m_bPush;													// ��x�����ꂽ���̔��ʗp�ϐ�
	static bool m_bGameClear;										// �N���A�������̔��ʗp�ϐ�
	int m_nCounterAnim;
	int m_nPatternAnim;
	CManager::MODE m_NextMode;

};
#endif