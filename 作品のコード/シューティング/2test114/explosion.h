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
	CExplosion(int nPriority = PRIORITY_EXPLOSION);																	// �R���X�g���N�^
	~CExplosion();																	// �f�X�g���N�^
																					// �����o�֐�
	static CExplosion *Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size);	// �����̐���
	static HRESULT Load(void);														// �e�N�X�`���̓ǂݍ���
	static void Unload(void);														// �e�N�X�`���̔j��
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
