//=============================================================================
//
// �v���C���[�̏��� [player.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _POLYGON_H_
#define _POLYGON_H_

#include"scene2D.h"

//*****************************************************************************
// �I�u�W�F�N�g�N���X
//*****************************************************************************
class CPolygon : public CScene2D
{
public:																			// �N�ł��A�N�Z�X�\
	CPolygon(PRIORITY Priority = PRIORITY_NOMAL);								// �R���X�g���N�^
	~CPolygon();																// �f�X�g���N�^
	// �����o�֐�
	static CPolygon *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size,int nTex);		// �|���S���̐���
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 size);							// �|���S���̏������֐�
	void Uninit(void);															// �|���S���̏I���֐�
	void Update(void);															// �|���S���̍X�V�֐�
	void Draw(void);															// �|���S���̕`��֐�
	void SetUse(bool bUse) { m_bUse = bUse; }									// �g�p���Ă��邩�ǂ����̐ݒ�֐�
	void SetRoll(bool bRoll) { m_bRoll = bRoll; }								// ��]�����邩�ǂ����̐ݒ�֐�
	void SetSize(D3DXVECTOR2 size); 											// �傫���̐ݒ�֐�
	void SetCol(D3DCOLOR col); 											// �傫���̐ݒ�֐�

private:																		// �����������A�N�Z�X�\
	bool m_bUse;																// �g���Ă��邩�ǂ���
	bool m_bRoll;																// ��]�����邩�ǂ���
};
#endif	// !_POLYGON_H_
