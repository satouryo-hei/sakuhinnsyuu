//=============================================================================
//
// �G�t�F�N�g�̏��� [effect.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include"scene2D.h"

//*****************************************************************************
// �G�t�F�N�g�̃N���X
//*****************************************************************************
class CEffect : public CScene2D
{
public:															// �N�ł��A�N�Z�X�\
	CEffect(int nPriority = PRIORITY_EFFECT);									// �R���X�g���N�^
	~CEffect();													// �f�X�g���N�^
																// �����o�֐�
	static CEffect *Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size);	// �G�t�F�N�g�̐���
	static HRESULT Load(void);									// �e�N�X�`���̓ǂݍ���
	static void Unload(void);									// �e�N�X�`���̔j��
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);			// �G�t�F�N�g�̏������֐�
	void Uninit(void);											// �G�t�F�N�g�̏I���֐�
	void Update(void);											// �G�t�F�N�g�̍X�V�֐�
	void Draw(void);											// �G�t�F�N�g�̕`��֐�


private:														// �����������A�N�Z�X�\	
	static LPDIRECT3DTEXTURE9 m_pTexture;						// ���L����e�X�N�`���̃|�C���^
	D3DXVECTOR2 m_Size;
	int m_nRed;													// ��
	int m_nGreen;												// ��
	int m_nBlue;												// ��
	int m_nAlpha;												// �A���t�@

};
#endif
