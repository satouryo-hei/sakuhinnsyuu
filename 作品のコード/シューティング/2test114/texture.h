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
// �I�u�W�F�N�g�N���X
//*****************************************************************************
class CTexture
{
public:															// �N�ł��A�N�Z�X�\

	//// �e�N�X�`���̎��
	//typedef enum 
	//{
	//	TEXTYPE_NOME = 0,
	//	TEXTYPE_NOME,
	//	TEXTYPE_NOME,
	//	TEXTYPE_MAX
	//} TEXTYPE;

	CTexture();													// �R���X�g���N�^
	~CTexture();												// �f�X�g���N�^
	// �����o�֐�
	HRESULT Init(void);											// �e�N�X�`���̏������֐�
	void Uninit(void);											// �e�N�X�`���̏I���֐�
	inline void Lode(void);
	LPDIRECT3DTEXTURE9 GetTex(int nType) { return m_pTexture[nType]; }

private:														// �����������A�N�Z�X�\

	LPDIRECT3DTEXTURE9 m_pTexture[32];							// �e�N�X�`���ւ̃|�C���^
	static int m_nMaxTex;										// �e�N�X�`���̍ő吔
};
#endif