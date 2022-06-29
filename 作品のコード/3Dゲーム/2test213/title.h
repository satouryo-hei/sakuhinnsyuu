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
class CTitle_Logo;
class CPress_Next;

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
	static LPDIRECT3DTEXTURE9 m_pTexture;										// ���L����e�X�N�`���̃|�C���^
	static CBg * m_pBg;															// �w�i�̃|�C���^�[�̐���
	static CTitle_Logo * m_pTitle_Logo;											// �^�C�g�����S�̃|�C���^�[�̐���
	static CPress_Next * m_pPress_Next;											// �^�C�g�����S�̃|�C���^�[�̐���
	bool m_bFade;																// �t�F�[�h���������ǂ���
};

#endif