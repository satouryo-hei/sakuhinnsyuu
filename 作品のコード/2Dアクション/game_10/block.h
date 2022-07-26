//=============================================================================
//
// �u���b�N�̏��� [block.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include"scene.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CNoneBlock;
class CMoveBlock;
class CPushBlock;

//*****************************************************************************
// �u���b�N�̃N���X
//*****************************************************************************
class CBlock : public CScene
{
public:																					// �N�ł��A�N�Z�X�\
	typedef enum
	{
		BLOCKTYPE_NOME = 0,
		BLOCKTYPE_MOVEING,
		BLOCKTYPE_PUSH,
		BLOCKTYPE_MAX
	} BLOCKTYPE;

	CBlock(int nPriority = PRIORITY_BLOCK);													// �R���X�g���N�^
	~CBlock();																				// �f�X�g���N�^
																							// �����o�֐�
	static CBlock *Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size, D3DXVECTOR3 move, 
		int nBlockType, int nMovetype, float fMin, float fMax,bool bBreak ,int nTex);										// ���Ԃ̐���
	HRESULT Init(D3DXVECTOR3 pos);									// ���Ԃ̏������֐�
	void Uninit(void);																	// ���Ԃ̏I���֐�
	void Update(void);																	// ���Ԃ̍X�V�֐�
	void Draw(void);																	// ���Ԃ̕`��֐�
	void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR2 Size, D3DXVECTOR3 move,
		int nBlockType, int nMovetype, float fMin, float fMax, bool bBreak,int nTex);

private:																				// �����������A�N�Z�X�\
	static CNoneBlock * m_pNone;
	static CMoveBlock * m_pMove;
	static CPushBlock * m_pPush;
	D3DXVECTOR3 m_pos;
};
#endif