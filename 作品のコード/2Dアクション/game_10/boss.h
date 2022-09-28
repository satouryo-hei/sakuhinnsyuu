//=============================================================================
//
// �G�̏��� [enemy.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _BOSS_H_
#define _BOSS_H_

#include"scene2D.h"

//*****************************************************************************
// �G�̃N���X
//*****************************************************************************
class CBoss : public CScene2D
{
public:																											// �N�ł��A�N�Z�X�\
	typedef enum
	{
		ACTION_NOMAL = 0,
		ACTION_BULLET,
		ACTION_ATTACK,
		ACTION_HIT,
		ACTION_MAX
	} ACTION;
	

	CBoss(int nPriority = PRIORITY_ENEMY);																	// �R���X�g���N�^
	~CBoss();																							// �f�X�g���N�^
																										// �����o�֐�	
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size);		// �G�̏������֐�
	void Uninit(void);														// �G�̏I���֐�
	void Update(void);														// �G�̍X�V�֐�
	void Draw(void);														// �G�̕`��֐�
	D3DXVECTOR3 GetPos() { return m_Pos; }									// �G�̌��݂̈ʒu�̎擾����	
	D3DXVECTOR3 GetMove() { return m_Move; }								// �G�̈ړ��ʂ̎擾����
	D3DXVECTOR2 GetSize() { return m_Size; }								// �G�̑傫���̎擾����
	void SetPos(D3DXVECTOR3 pos) { m_Pos = pos; }							// �G�̌��݂̈ʒu�̐ݒ菈��	
	void SetMove(D3DXVECTOR3 move) { m_Move = move; }						// �G�̈ړ��ʂ̐ݒ菈��
	void SetSize(D3DXVECTOR2 size) { m_Size = size; }						// �G�̑傫���̐ݒ菈��
	void SetUse(bool bUse) { m_bUse = bUse; }

private:																			// �����������A�N�Z�X�\				
	D3DXVECTOR3 m_Pos;																// �G�̌��݂̈ʒu
	D3DXVECTOR3 m_Move;																// �G�̈ړ���
	D3DXVECTOR2 m_Size;																// �G�̑傫��
	bool m_bUse;																	// �g��ꂢ�邩�ǂ���
};
#endif