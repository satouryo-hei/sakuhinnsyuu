//=============================================================================
//
// �e�N�X�`���̏��� [texture.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#define MAX_TEXTURE (32)

#include"main.h"

//*****************************************************************************
//�e�N�X�`���̃N���X
//*****************************************************************************
class CTexture
{
public:																	// �N�ł��A�N�Z�X�\

	CTexture();															// �R���X�g���N�^
	~CTexture();														// �f�X�g���N�^
	// �����o�֐�
	HRESULT Init(void);													// �e�N�X�`���̏������֐�
	void Uninit(void);													// �e�N�X�`���̏I���֐�
	inline void Lode(void);
	static LPDIRECT3DTEXTURE9 GetTex(int nType) { return m_pTexture[nType]; }	// �e�N�X�`���̃|�C���^�[���擾

private:																// �����������A�N�Z�X�\

	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE];					// �e�N�X�`���ւ̃|�C���^
	static int m_nMaxTex;												// �e�N�X�`���̍ő吔
	static const char * m_pTexFileName;												// �e�N�X�`���̃t�@�C��
};
#endif