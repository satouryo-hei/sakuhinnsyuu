//=============================================================================
//
// �`���[�g���A���̏��� [title.h]
// Author : �����ĕ�
// Author : �ؖr�_
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "scene.h"
//*****************************************************************************
// �O���錾
//*****************************************************************************
class CBg;
class CLogo;
class CNextBotton;
//*****************************************************************************
// �^�C�g���̃N���X
//*****************************************************************************
class CTutorial : public CScene
{
public:
	CTutorial(int nPriority = PRIORITY_NOMAL);										// �R���X�g���N�^
	~CTutorial();																	// �f�X�g���N�^

																				// �����o�֐�
	HRESULT Init(D3DXVECTOR3 pos);												// �^�C�g���̏������֐�
	void Uninit(void);															// �^�C�g���̏I���֐��@
	void Update(void);															// �^�C�g���̍X�V�֐�
	void Draw(void);															// �^�C�g���̕`��֐�


private:																		// �����������A�N�Z�X�\		
	static CBg * m_pBg;
	static CLogo * m_pLogo;														// ���S�̃|�C���^�[����
	static CNextBotton * m_pNextBotton;											// ���̃{�^����UI�̃|�C���^�[����
	bool m_bFade;																// �J�ڂ������ǂ���
};

#endif