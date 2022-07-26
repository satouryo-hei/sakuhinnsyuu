//=============================================================================
//
// �u���b�N�̏��� [block.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _NONEBLOCK_H_
#define _NONEBLOCK_H_

#include"scene2D.h"

//*****************************************************************************
// �u���b�N�̃N���X
//*****************************************************************************
class CNoneBlock : public CScene2D
{
public:																					// �N�ł��A�N�Z�X�\
	CNoneBlock(int nPriority = PRIORITY_BLOCK);													// �R���X�g���N�^
	~CNoneBlock();																				// �f�X�g���N�^
																							// �����o�֐�
	static CNoneBlock *Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size,bool bBreak, int nTex);										// ���Ԃ̐���
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);									// ���Ԃ̏������֐�
	void Uninit(void);																	// ���Ԃ̏I���֐�
	void Update(void);																	// ���Ԃ̍X�V�֐�
	void Draw(void);																	// ���Ԃ̕`��֐�
	void Colision();
	void Colision(int nPro, D3DXVECTOR3 pos, D3DXVECTOR3 posold,D3DXVECTOR2 Size);

private:																				// �����������A�N�Z�X�\
	D3DXVECTOR3 m_pos;	
	D3DXVECTOR2 m_size;			
	bool m_bBreak;																		// ���邩�ǂ���
	bool m_bUse;
};
#endif