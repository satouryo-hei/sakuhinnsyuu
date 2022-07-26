//=============================================================================
//
// ���Ԃ̏��� [item.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

#include"scene2D.h"

//*****************************************************************************
// ���Ԃ̃N���X
//*****************************************************************************
class CItem : public CScene2D
{
public:																// �N�ł��A�N�Z�X�\
	typedef enum 
	{
		ITEM_NONE = 0,
		ITEM_ATTACK,
		ITEM_LIFE,
		ITEM_MAX
	} ITEM;

	CItem(int nPriority = PRIORITY_NOMAL);							// �R���X�g���N�^
	~CItem();														// �f�X�g���N�^
	// �����o�֐�
	static CItem *Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size);		// ���Ԃ̐���
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);				// ���Ԃ̏������֐�
	void Uninit(void);												// ���Ԃ̏I���֐�
	void Update(void);												// ���Ԃ̍X�V�֐�
	void Draw(void);												// ���Ԃ̕`��֐�

private:															// �����������A�N�Z�X�\	
	ITEM item;
	int m_nAttack;
	int m_Life;

};
#endif