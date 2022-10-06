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
#include"ui.h"

//*****************************************************************************
// �I�u�W�F�N�g�N���X
//*****************************************************************************
class CTexture
{
public:																	// �N�ł��A�N�Z�X�\
	CTexture();															// �R���X�g���N�^
	~CTexture();														// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);													// �e�N�X�`���̏������֐�
	void Uninit(void);													// �e�N�X�`���̏I���֐�
	LPDIRECT3DTEXTURE9 GetTex(int nType) { return m_pTexture[nType]; }	// �e�N�X�`���̎擾�֐�

private:																// �����������A�N�Z�X�\
	inline void Lode(void);												// �e�N�X�`���̓ǂݍ��݊֐�

	// �ÓI�����o�ϐ�
	static int m_nMaxTex;												// �e�N�X�`���̍ő吔

	// �����o�ϐ�
	LPDIRECT3DTEXTURE9 m_pTexture[LIMITUI];								// �e�N�X�`���ւ̃|�C���^

};
#endif