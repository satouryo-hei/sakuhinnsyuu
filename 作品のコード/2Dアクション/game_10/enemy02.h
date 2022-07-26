//=============================================================================
//
// �G�̏��� [enemy.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _ENEMY02_H_
#define _ENEMY02_H_

#include"enemy.h"

//*****************************************************************************
// �G�̃N���X
//*****************************************************************************
class CEnemy02 : public CEnemy
{
public:																				// �N�ł��A�N�Z�X�\
	CEnemy02(int nPriority = PRIORITY_PLAYER);										// �R���X�g���N�^
	virtual ~CEnemy02();															// �f�X�g���N�^
																					// �����o�֐�
	static CEnemy02 *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size);	// �v���C���̐���
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size);				// �G�̏������֐�
	void Uninit(void);																// �G�̏I���֐�
	void Update(void);																// �G�̍X�V�֐�
	void Draw(void);																// �G�̕`��֐�	

private:																			// �����������A�N�Z�X�\				
	void BlockCollision();															// �u���b�N�ƓG�̓����蔻��
	D3DXVECTOR3 m_Pos;																// �G�̌��݂̈ʒu
	D3DXVECTOR3 m_OldPos;															// �G�̑O��̈ʒu
	D3DXVECTOR3 m_Move;																// �G�̈ړ���
	D3DXVECTOR2 m_Size;																// �G�̑傫��
};
#endif
