//=============================================================================
//
// ����UI�̏��� [keyui.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _KEYUI_H_
#define _KEYUI_H_

#include"scene2D.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CKeynum;

//*****************************************************************************
// ���S�̃N���X
//*****************************************************************************
class CKeyui : public CScene2D
{
public:																		// �N�ł��A�N�Z�X�\
	CKeyui(PRIORITY Priority = PRIORITY_UI);							// �R���X�g���N�^
	~CKeyui();																// �f�X�g���N�^
																			// �����o�֐�
	static CKeyui *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size);				// ���S�̐���
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 size);						// ���S�̏������֐�
	void Uninit(void);														// ���S�̏I���֐�
	void Update(void);														// ���S�̍X�V�֐�
	void Draw(void);														// ���S�̕`��֐�

private:																	// �����������A�N�Z�X�\		
	D3DXVECTOR3 m_Pos;														// ���݂̈ʒu	
	D3DXVECTOR2 m_Size;														// �傫��
	static CKeynum * m_pKeynum;

};
#endif // !_EFFECT_H_