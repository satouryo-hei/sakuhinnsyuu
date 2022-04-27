//=============================================================================
//
// �����̏��� [beam.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _BEAM_H_
#define _BEAM_H_

#include"bullet.h"

//*****************************************************************************
// �����̃N���X
//*****************************************************************************
class CBeam : public CBullet
{
public:																			// �N�ł��A�N�Z�X�\
	CBeam(int nPriority = PRIORITY_BULLET);																	// �R���X�g���N�^
	~CBeam();																	// �f�X�g���N�^
																				// �����o�֐�
	static CBeam *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size);	// �e�̐���
	static HRESULT Load(void);													// �e�N�X�`���̓ǂݍ���
	static void Unload(void);													// �e�N�X�`���̔j��
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size);			// �r�[���̏������֐�
	void Uninit(void);															// �r�[���̏I���֐�
	void Update(void);															// �r�[���̍X�V�֐�
	void Draw(void);															// �r�[���̕`��֐�

private:																		// �����������A�N�Z�X�\	
	static LPDIRECT3DTEXTURE9 m_pTexture;										// ���L����e�X�N�`���̃|�C���^
	D3DXVECTOR3 m_Pos;
	D3DXVECTOR3 m_Move;															// �e�̈ړ���
	D3DXVECTOR2 m_Size;
	int m_Timer;
};

#endif