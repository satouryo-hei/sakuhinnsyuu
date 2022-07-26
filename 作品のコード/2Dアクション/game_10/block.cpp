//=============================================================================
//
// �u���b�N�̏��� [score.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include "block.h"

#include"noneblock.h"
#include"moveblock.h"
#include"pushblock.h"

//=============================================================================
// �ÓI�����o�ϐ��̐錾
//=============================================================================
CNoneBlock * CBlock::m_pNone = NULL;
CMoveBlock * CBlock::m_pMove = NULL;
CPushBlock * CBlock::m_pPush = NULL;

//=============================================================================
// �u���b�N�̃R���X�g���N�^
//=============================================================================
CBlock::CBlock(int nPriority) : CScene(PRIORITY_NOMAL)
{
	m_pos = D3DXVECTOR3(0, 0, 0);
}

//=============================================================================
// �u���b�N�̃f�X�g���N�^
//=============================================================================
CBlock::~CBlock()
{

}

//=============================================================================
// �u���b�N�̐�������
//=============================================================================
CBlock *CBlock::Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size, D3DXVECTOR3 move,
	int nBlockType, int nMovetype, float fMin, float fMax,bool bBreak ,int nTex)
{
	CBlock *pBlock = NULL;
	pBlock = new CBlock;

	if (pBlock != NULL)
	{
		pBlock->Init(pos);
		pBlock->SetBlock(pos, Size, move,nBlockType, nMovetype, 
			fMin, fMax, bBreak, nTex);
	}
	return pBlock;
}

//=============================================================================
// �u���b�N�̏���������
//=============================================================================
HRESULT CBlock::Init(D3DXVECTOR3 pos)
{
	m_pos = pos;	

	return S_OK;
}

//=============================================================================
// �u���b�N�̏I������
//=============================================================================
void CBlock::Uninit(void)
{
	Release();
}

//=============================================================================
// �u���b�N�̍X�V����
//=============================================================================
void CBlock::Update(void)
{

}

//=============================================================================
// �u���b�N�̕`�揈��
//=============================================================================
void CBlock::Draw(void)
{

}

//=============================================================================
// �u���b�N�̐ݒ菈��
//=============================================================================
void CBlock::SetBlock(D3DXVECTOR3 pos, D3DXVECTOR2 Size, D3DXVECTOR3 move,
	int nBlockType, int nMovetype, float fMin, float fMax, bool bBreak,int nTex)
{
	// �u���b�N�̏�Ԃ̑J��
	switch (nBlockType)
	{
		// �u���b�N���ړ������Ȃ��Ƃ�
	case BLOCKTYPE_NOME:
		m_pNone = CNoneBlock::Create(pos, Size, bBreak, nTex);
		break;

		// �u���b�N���̈ړ������Ă���Ƃ�
	case BLOCKTYPE_MOVEING:		
		m_pMove = CMoveBlock::Create(pos, Size, move,
			nMovetype, fMin, fMax, nTex);
		break;

		// �u���b�N���������Ƃ�
	case BLOCKTYPE_PUSH:
		m_pPush = CPushBlock::Create(pos, Size, move, nTex);
		break;

	default:
		break;
	}	
}
