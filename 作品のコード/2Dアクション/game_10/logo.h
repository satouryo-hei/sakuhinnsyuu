//=============================================================================
//
// ���S�̏��� [logo.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _LOGO_H_
#define _LOGO_H_

#include"scene.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CPolygon;

//*****************************************************************************
// ���S�̃N���X
//*****************************************************************************
class CLogo : public CScene
{
public:																		// �N�ł��A�N�Z�X�\
	CLogo(PRIORITY Priority = PRIORITY_EFFECT);								// �R���X�g���N�^
	~CLogo();																// �f�X�g���N�^
																			// �����o�֐�
	static CLogo *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size);				// ���S�̐���
	HRESULT Init(D3DXVECTOR3 pos);											// ���S�̏������֐�
	void Uninit(void);														// ���S�̏I���֐�
	void Update(void);														// ���S�̍X�V�֐�
	void Draw(void);														// ���S�̕`��֐�

private:																	// �����������A�N�Z�X�\
	static CPolygon * m_pPolygon;											// �|���S���̔z��|�C���^�[�𐶐�
	D3DXVECTOR3 m_Pos;														// ���݂̈ʒu
	D3DXVECTOR3 m_Move;														// �ړ���
	D3DXVECTOR2 m_Size;														// �傫��
	const float m_fHeight;													// ����
};
#endif // !_EFFECT_H_