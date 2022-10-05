//=============================================================================
//
// ���ɍs���{�^����UI�̏��� [nextbutton.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _NEXTBUTTON_H_
#define _NEXTBUTTON_H_

#include"scene.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CPolygon;

//*****************************************************************************
// ���S�̃N���X
//*****************************************************************************
class CNextBotton : public CScene
{
public:																		// �N�ł��A�N�Z�X�\
	CNextBotton(PRIORITY Priority = PRIORITY_EFFECT);								// �R���X�g���N�^
	~CNextBotton();																// �f�X�g���N�^
																			// �����o�֐�
	static CNextBotton *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size);				// ���S�̐���
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
	const int m_nColMax;													// �F�̍ő�l
	D3DXCOLOR m_Col;														// �F
	bool m_bAdditionCol;													// �F�����Z���邩�ǂ���
};
#endif // !_EFFECT_H_