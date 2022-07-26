//=============================================================================
//
// �u���b�N�̏��� [block.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _MOVEBLOCK_H_
#define _MOVEBLOCK_H_

#include"scene2D.h"

//*****************************************************************************
// �ړ��u���b�N�̃N���X
//*****************************************************************************
class CMoveBlock : public CScene2D
{
public:																					// �N�ł��A�N�Z�X�\
	typedef enum
	{	
		MOVE_NONE = 0,
		MOVE_UP,
		MOVE_DOWN,
		MOVE_LEFT,
		MOVE_RIGHT,
		MOVE_MAX
	} MOVE;

	CMoveBlock(int nPriority = PRIORITY_BLOCK);													// �R���X�g���N�^
	~CMoveBlock();																				// �f�X�g���N�^
																							// �����o�֐�
	static CMoveBlock *Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size, D3DXVECTOR3 move,
		int nCondition, float fMin, float fMax, int nTex);										// ���Ԃ̐���
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);									// ���Ԃ̏������֐�
	void Uninit(void);																	// ���Ԃ̏I���֐�
	void Update(void);																	// ���Ԃ̍X�V�֐�
	void Draw(void);																	// ���Ԃ̕`��֐�
	void SetBlock(void);
	int MoveColision(void);	
	static int GetMoveBlock(void) { return m_MoveBlock; }							// �����Ă��邩�̏�Ԃ̎擾	
	D3DXVECTOR3 GetPos() { return m_pos; }
	D3DXVECTOR3 GetPosold() { return m_posOld; }
	D3DXVECTOR3 GetMove() { return m_move; }
	D3DXVECTOR2 Getsize() { return m_size; }
	void SetMove(D3DXVECTOR3 move) { m_move = move; }

private:																				// �����������A�N�Z�X�\
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_move;
	D3DXVECTOR2 m_size;
	D3DXVECTOR3 m_posOld;
	static MOVE m_MoveBlock;																// �����Ă��邩�̏��	
	int m_nBlockType;
	int m_nBlockCondition;
	float m_fMin;
	float m_fMax;
	bool m_bMove;
};
#endif