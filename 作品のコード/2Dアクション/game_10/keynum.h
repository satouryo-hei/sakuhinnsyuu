//=============================================================================
//
// ����UI�̏��� [keyui.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _KEYNUM_H_
#define _KEYNUM_H_

#include"scene2D.h"

#define MAX_KEYNUMBER (3)

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CNumber;

//*****************************************************************************
// ���S�̃N���X
//*****************************************************************************
class CKeynum : public CScene2D
{
public:																		// �N�ł��A�N�Z�X�\
	CKeynum(PRIORITY Priority = PRIORITY_UI);							// �R���X�g���N�^
	~CKeynum();																// �f�X�g���N�^
																			// �����o�֐�
	static CKeynum *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size);				// ���S�̐���
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 size);						// ���S�̏������֐�
	void Uninit(void);														// ���S�̏I���֐�
	void Update(void);														// ���S�̍X�V�֐�
	void Draw(void);														// ���S�̕`��֐�

private:																	// �����������A�N�Z�X�\
	void SetNumKey(const int nNumKey);										// ���̐��̐ݒ菈��
	CNumber * m_apNumber[MAX_KEYNUMBER];								// �ԍ��̔z��̃|�C���^�[�𐶐�
	D3DXVECTOR3 m_Pos;														// ���݂̈ʒu		

};
#endif // !_EFFECT_H_