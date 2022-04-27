//=============================================================================
//
// �^�C�g���̏��� [title.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "scene.h"

class CScene2D;
class CTitle_Logo;
class CPress_Next;
//*****************************************************************************
// �^�C�g���̃N���X
//*****************************************************************************
class CTitle : public CScene
{
public:
	CTitle(int nPriority = PRIORITY_BG);										// �R���X�g���N�^
	~CTitle();																	// �f�X�g���N�^

	// �����o�֐�
	static HRESULT Load(void);													// �e�N�X�`���̓ǂݍ���
	static void Unload(void);													// �e�N�X�`���̔j��
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);							// �^�C�g���̏������֐�
	void Uninit(void);															// �^�C�g���̏I���֐��@
	void Update(void);															// �^�C�g���̍X�V�֐�
	void Draw(void);															// �^�C�g���̕`��֐�
	

private:																		// �����������A�N�Z�X�\
	static LPDIRECT3DTEXTURE9 m_pTexture;										// ���L����e�X�N�`���̃|�C���^
	CScene2D * m_apScene2D;														// �I�u�W�F�N�g�N���X�̃|�C���^
	static CTitle_Logo * m_pTitle_Logo;
	static CPress_Next * m_Press_Next;
	bool m_bNextMode;
};

#endif