//=============================================================================
//
// ���Ԃ̏��� [attack_up.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _ATTACK_UP_H_
#define _ATTACK_UP_H_

#include"scene2D.h"

//*****************************************************************************
// ���Ԃ̃N���X
//*****************************************************************************
class CAttack_up : public CScene2D
{
public:																// �N�ł��A�N�Z�X�\
	CAttack_up(int nPriority = PRIORITY_ITEM);							// �R���X�g���N�^
	~CAttack_up();														// �f�X�g���N�^
																	// �����o�֐�
	static CAttack_up *Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size);		// ���Ԃ̐���
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);				// ���Ԃ̏������֐�
	void Uninit(void);												// ���Ԃ̏I���֐�
	void Update(void);												// ���Ԃ̍X�V�֐�
	void Draw(void);												// ���Ԃ̕`��֐�

private:															// �����������A�N�Z�X�\
	D3DXVECTOR3 m_pos;
	D3DXVECTOR2 m_size;
};
#endif
