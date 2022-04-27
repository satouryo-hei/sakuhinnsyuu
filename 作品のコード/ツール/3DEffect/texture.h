//=============================================================================
//
// �e�N�X�`���̏��� [texture.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#define TEXTURE_TEXT "data/TEXT/TextureFile.txt"

#include"main.h"

//*****************************************************************************
// �e�N�X�`���N���X
//*****************************************************************************
class CTexture
{
public:																	// �N�ł��A�N�Z�X�\
	// �e�N�X�`���̎��
	typedef enum 
	{		
		Tex_Fild = 0,		// �t�B�[���h
		Tex_Effect,		// �G�t�F�N�g
		Tex_MAX			// �ő吔
	} Tex;

	CTexture();															// �R���X�g���N�^
	~CTexture();														// �f�X�g���N�^
	// �����o�֐�
	HRESULT Init(void);													// �e�N�X�`���̏������֐�
	void Uninit(void);													// �e�N�X�`���̏I���֐�
	inline void Lode(void);
	LPDIRECT3DTEXTURE9 GetTex(Tex Type) { return m_pTexture[Type]; }

private:																// �����������A�N�Z�X�\
	LPDIRECT3DTEXTURE9 m_pTexture[Tex_MAX];								// �e�N�X�`���ւ̃|�C���^
	static int m_nMaxTex;												// �e�N�X�`���̍ő吔
};
#endif