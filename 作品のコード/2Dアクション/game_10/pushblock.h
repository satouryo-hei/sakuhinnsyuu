//=============================================================================
//
// �u���b�N�̏��� [block.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _PUSHBLOCK_H_
#define _PUSHBLOCK_H_

#include"scene2D.h"

//*****************************************************************************
// �����u���b�N�̃N���X
//*****************************************************************************
class CPushBlock : public CScene2D
{
public:																					// �N�ł��A�N�Z�X�\
	CPushBlock(int nPriority = PRIORITY_BLOCK);													// �R���X�g���N�^
	~CPushBlock();																				// �f�X�g���N�^
																							// �����o�֐�
	static CPushBlock *Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size, D3DXVECTOR3 move,int nTex);										// ���Ԃ̐���
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);									// ���Ԃ̏������֐�
	void Uninit(void);																	// ���Ԃ̏I���֐�
	void Update(void);																	// ���Ԃ̍X�V�֐�
	void Draw(void);																	// ���Ԃ̕`��֐�
	void NoneColision(void);
	D3DXVECTOR3 GetPos() { return m_pos; }
	D3DXVECTOR2 Getsize() { return m_size; }
	D3DXVECTOR3 GetPosold() { return m_posOld; }
	D3DXVECTOR3 GetMove() { return m_move; }
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetMove(D3DXVECTOR3 move) { m_move = move; }

private:																				// �����������A�N�Z�X�\
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_move;
	D3DXVECTOR2 m_size;
	D3DXVECTOR3 m_posOld;
};
#endif