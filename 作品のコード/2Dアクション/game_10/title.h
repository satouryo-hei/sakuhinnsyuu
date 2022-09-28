//=============================================================================
//
// �^�C�g���̏��� [title.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

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
class CTitle : public CScene
{
public:
	CTitle(int nPriority = PRIORITY_NOMAL);										// �R���X�g���N�^
	~CTitle();																	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(D3DXVECTOR3 pos);												// �^�C�g���̏������֐�
	void Uninit(void);															// �^�C�g���̏I���֐��@
	void Update(void);															// �^�C�g���̍X�V�֐�
	void Draw(void);															// �^�C�g���̕`��֐�
	

private:																		// �����������A�N�Z�X�\	
	inline void UILode(void);													// UI�̓ǂݍ��ݏ���
	static CBg * m_pBg;
	static CLogo * m_pLogo;														// ���S�̃|�C���^�[����
	static CNextBotton * m_pNextBotton;											// ���̃{�^����UI�̃|�C���^�[����
	bool m_bFade;																// �J�ڂ������ǂ���
	D3DXVECTOR3 m_LodePos[2];
	D3DXVECTOR2 m_LodeSize[2];
	const char * m_pTitleUiFile;
};

#endif