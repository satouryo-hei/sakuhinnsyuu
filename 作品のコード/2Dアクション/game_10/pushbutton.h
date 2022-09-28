//=============================================================================
//
// �����{�^���̕\������ [block.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _PUSHBUTTON_H_
#define _PUSHBUTTON_H_

#include"scene2D.h"

//*****************************************************************************
// �����{�^���\���̃N���X
//*****************************************************************************
class CPushButton : public CScene2D
{
public:																					// �N�ł��A�N�Z�X�\
	CPushButton(int nPriority = PRIORITY_UI);													// �R���X�g���N�^
	~CPushButton();																				// �f�X�g���N�^
																								// �����o�֐�
	static CPushButton *Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size,int nTex);										// ���Ԃ̐���
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);									// ���Ԃ̏������֐�
	void Uninit(void);																	// ���Ԃ̏I���֐�
	void Update(void);																	// ���Ԃ̍X�V�֐�
	void Draw(void);																	// ���Ԃ̕`��֐�
	static bool GetUse() { return m_bUse; }
	static void SetUse(bool bUse) { m_bUse = bUse; }
private:																				// �����������A�N�Z�X�\
	D3DXVECTOR3 m_Pos;																	// ���݂̈ʒu
	static bool m_bUse;																	// �g���Ă��邩�ǂ���
	int m_nPatternAnim;																	// �p�^�[���A�j���[�V����
	int	m_nCounterAnim;																	// �J�E���^�[�A�j���[�V����
};
#endif