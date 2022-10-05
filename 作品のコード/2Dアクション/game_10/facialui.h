//=============================================================================
//
// ��̍����̕\������ [facialui.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _FACIALUI_H_
#define _FACIALUI_H_

#include"scene2D.h"

//*****************************************************************************
// ��̍����\���̃N���X
//*****************************************************************************
class CFacialui : public CScene2D
{
public:																					// �N�ł��A�N�Z�X�\
	/* ����(emotions)*/
	// ��̎��
	typedef enum
	{
		FACE_NOMAL = 0,																	// �m�[�}��
		FACE_JOY,																		// ���
		FACE_ANGER,																		// �{��
		FACE_SAD,																		// �߂���
		FACE_MAX																		// ��̑S���
	} FACE;
	CFacialui(int nPriority = PRIORITY_UI);												// �R���X�g���N�^
	~CFacialui();																		// �f�X�g���N�^
																						// �����o�֐�
	static CFacialui *Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size, int nTex);				// ��̍����̐���
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);									// ��̍����̏������֐�
	void Uninit(void);																	// ��̍����̏I���֐�
	void Update(void);																	// ��̍����̍X�V�֐�
	void Draw(void);																	// ��̍����̕`��֐�
private:																				// �����������A�N�Z�X�\
	D3DXVECTOR3 m_Pos;																	// ���݂̈ʒu	
	int m_nPatternAnim;																	// �p�^�[���A�j���[�V����
	int	m_nCounterAnim;																	// �J�E���^�[�A�j���[�V����
};
#endif