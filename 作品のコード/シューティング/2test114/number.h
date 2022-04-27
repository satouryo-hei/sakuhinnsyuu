//=============================================================================
//
// �����̏��� [number.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_

#include"main.h"

//*****************************************************************************
// �����N���X
//*****************************************************************************
class CNumber 
{
public:																// �N�ł��A�N�Z�X�\
	CNumber();														// �R���X�g���N�^
	~CNumber();														// �f�X�g���N�^
																	// �����o�֐�
	static CNumber *Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size);		// �����̐���
	static HRESULT Load(void);										// �e�N�X�`���̓ǂݍ���
	static void Unload(void);										// �e�N�X�`���̔j��
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);				// �����̏������֐�
	void Uninit(void);												// �����̏I���֐�
	void Update(void);												// �����̍X�V�֐�
	void Draw(void);												// �����̕`��֐�
	void SetNumber(int nNumber);									// �����̔z�u�֐�

private:															// �����������A�N�Z�X�\
	static LPDIRECT3DTEXTURE9 m_pTexture;							// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVlxBuff;								// ���_�o�b�t�@�ւ̃|�C���^

};
#endif

