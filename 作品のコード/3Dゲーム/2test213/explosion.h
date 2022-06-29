//=============================================================================
//
// �����̏��� [explosion.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include"billboard.h"

//*****************************************************************************
// �����̃N���X
//*****************************************************************************
class CExplosion : public CBillboard
{
public:																				// �N�ł��A�N�Z�X�\
	CExplosion(PRIORITY nPriority = PRIORITY_EFFECT);								// �R���X�g���N�^
	~CExplosion();																	// �f�X�g���N�^
																					// �����o�֐�
	static CExplosion *Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size);	// �����̐���
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);				// �����̏������֐�
	void Uninit(void);																// �����̏I���֐�
	void Update(void);																// �����̍X�V�֐�
	void Draw(void);																// �����̕`��֐�

private:																			// �����������A�N�Z�X�\	
	static LPDIRECT3DTEXTURE9 m_pTexture;											// ���L����e�X�N�`���̃|�C���^
	int m_nCounterAnim;																// �A�j���[�V�����J�E���^
	int m_nPatternAnim;																// �A�j���[�V�����p�^�[��No

};
#endif