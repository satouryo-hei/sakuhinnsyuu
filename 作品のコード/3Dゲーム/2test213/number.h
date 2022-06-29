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
public:																		// �N�ł��A�N�Z�X�\
	CNumber();																// �R���X�g���N�^
	~CNumber();																// �f�X�g���N�^
																			// �����o�֐�
	static CNumber *Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size,int nNum);		// �����̐���
	void BindTextuer(int nTextuer);											// �e�N�X�`���̐ݒ�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);						// �����̏������֐�
	void Uninit(void);														// �����̏I���֐�
	void Update(void);														// �����̍X�V�֐�
	void Draw(void);														// �����̕`��֐�
	void SetNumber(int nNumber);											// �����̔z�u�֐�
	void SetColor(D3DXCOLOR col);

private:																	// �����������A�N�Z�X�\

	static LPDIRECT3DTEXTURE9 m_pTexture;									// ���L����e�X�N�`���̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;										// ���_�o�b�t�@�ւ̃|�C���^

};

//�ݏ揈��(�����^���m)��9��ȉ��̂ݎg�p�\��
template<class T> T Exponentiation(T data0, T data1)
{
	T Answer = pow(data0, data1);
	return Answer;
}

#if 0
//�ݏ揈��(�����^���m)
template<class T> T Exponentiation(T data0, T data1, T data2)
{
	for (int i = 0; i < data2; i++)
	{
		data1 *= data0;
	}
	return data1;
}
#endif

#endif

