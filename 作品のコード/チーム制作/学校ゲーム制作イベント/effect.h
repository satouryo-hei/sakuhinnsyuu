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
public:																				// �N�ł��A�N�Z�X�\
	CEffect(int nPriority = PRIORITY_EFFECT);										// �R���X�g���N�^
	~CEffect();																		// �f�X�g���N�^
																// �����o�֐�
	static CEffect *Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size,D3DXVECTOR2 AddSize, D3DXCOLOR m_AddCol,int nTex);	// �G�t�F�N�g�̐���
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);								// �G�t�F�N�g�̏������֐�
	void Uninit(void);																// �G�t�F�N�g�̏I���֐�
	void Update(void);																// �G�t�F�N�g�̍X�V�֐�
	void Draw(void);																// �G�t�F�N�g�̕`��֐�
	void AddColor(int nRed, int nGreen, int nBlue, int nAlpha);

private:																			// �����������A�N�Z�X�\	
	D3DXVECTOR2 m_Size;	
	D3DXVECTOR2 m_AddSize;
	int m_nRed;																		// ��
	int m_nGreen;																	// ��
	int m_nBlue;																		// ��
	int m_nAlpha;																	// �A���t�@
	D3DXCOLOR m_AddCol;
	bool m_bUse;
};
#endif
