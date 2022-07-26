//=============================================================================
//
// �G�̏��� [enemy.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include"scene2D.h"

//*****************************************************************************
// �G�̃N���X
//*****************************************************************************
class CEnemy : public CScene2D
{
public:																											// �N�ł��A�N�Z�X�\
	CEnemy(int nPriority = PRIORITY_PLAYER);																	// �R���X�g���N�^
	virtual ~CEnemy();																							// �f�X�g���N�^
																												// �����o�֐�	
	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move,D3DXVECTOR2 Size);		// �G�̏������֐�
	virtual void Uninit(void);														// �G�̏I���֐�
	virtual void Update(void);														// �G�̍X�V�֐�
	virtual void Draw(void);														// �G�̕`��֐�
	virtual D3DXVECTOR3 GetPos() { return m_Pos; }									// �G�̌��݂̈ʒu�̎擾����	
	virtual D3DXVECTOR3 GetMove() { return m_Move; }								// �G�̈ړ��ʂ̎擾����
	virtual D3DXVECTOR2 GetSize() { return m_Size; }								// �G�̑傫���̎擾����
	virtual void SetPos(D3DXVECTOR3 pos) { m_Pos = pos; }							// �G�̌��݂̈ʒu�̐ݒ菈��	
	virtual void SetMove(D3DXVECTOR3 move) { m_Move = move; }						// �G�̈ړ��ʂ̐ݒ菈��
	virtual void SetSize(D3DXVECTOR2 size) { m_Size = size; }						// �G�̑傫���̐ݒ菈��
	virtual void SetUse(bool bUse) { m_bUse = bUse; }

private:																			// �����������A�N�Z�X�\				
	D3DXVECTOR3 m_Pos;																// �G�̌��݂̈ʒu
	D3DXVECTOR3 m_Move;																// �G�̈ړ���
	D3DXVECTOR2 m_Size;																// �G�̑傫��
	bool m_bUse;																	// �g��ꂢ�邩�ǂ���
};
#endif
