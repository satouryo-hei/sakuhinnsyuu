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
	CItem(int nPriority = PRIORITY_ITEM);							// �R���X�g���N�^
	~CItem();														// �f�X�g���N�^
																	// �����o�֐�
	static CItem *Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size);		// ���Ԃ̐���
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);				// ���Ԃ̏������֐�
	void Uninit(void);												// ���Ԃ̏I���֐�
	void Update(void);												// ���Ԃ̍X�V�֐�
	void Draw(void);												// ���Ԃ̕`��֐�	

private:															// �����������A�N�Z�X�\
	void Colision(void);
	D3DXVECTOR3 m_pos;
	D3DXVECTOR2 m_size;
};
#endif
