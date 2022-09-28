//=============================================================================
//
// �����̏��� [explosion.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include"scene2D.h"

//*****************************************************************************
// �����̃N���X
//*****************************************************************************
class CExplosion : public CScene2D
{
public:																				// �N�ł��A�N�Z�X�\
	CExplosion(int nPriority = PRIORITY_EFFECT);																	// �R���X�g���N�^
	~CExplosion();																	// �f�X�g���N�^
																					// �����o�֐�
	static CExplosion *Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size, int nTex);	// �����̐���
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);				// �����̏������֐�
	void Uninit(void);																// �����̏I���֐�
	void Update(void);																// �����̍X�V�֐�
	void Draw(void);																// �����̕`��֐�

private:																			// �����������A�N�Z�X�\	
	int m_nCounterAnim;																// �A�j���[�V�����J�E���^
	int m_nPatternAnim;																// �A�j���[�V�����p�^�[��No
	bool m_bUse;

};
#endif
