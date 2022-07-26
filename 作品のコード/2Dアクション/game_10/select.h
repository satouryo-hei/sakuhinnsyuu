//=============================================================================
//
// �I����ʂ̏��� [select.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _SELECT_H_
#define _SELECT_H_

#include "scene.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CBg;
class CChoose_Game;

//*****************************************************************************
// �I����ʂ̃N���X
//*****************************************************************************
class CSelect : public CScene
{
public:
	CSelect(int nPriority = PRIORITY_NOMAL);									// �R���X�g���N�^
	~CSelect();																	// �f�X�g���N�^

																				// �����o�֐�
	HRESULT Init(D3DXVECTOR3 pos);												// �I����ʂ̏������֐�
	void Uninit(void);															// �I����ʂ̏I���֐��@
	void Update(void);															// �I����ʂ̍X�V�֐�
	void Draw(void);															// �I����ʂ̕`��֐�
	static CChoose_Game * GetChoose_Game(void) { return m_pChoose_Game; }		// �Q�[���̑I���̎擾����

private:																		// �����������A�N�Z�X�\
	static CBg * m_pBg;															// �w�i�̃|�C���^�[�̐���
	static CChoose_Game * m_pChoose_Game;										// �Q�[���̑I���̃|�C���^�[�̐���
};
#endif