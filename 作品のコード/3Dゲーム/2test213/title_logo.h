//=============================================================================
//
// �^�C�g�����S�̏��� [title_logo.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _TITLE_LOGO_H_
#define _TITLE_LOGO_H_

#include"scene.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CPolygon; //�O���錾

//*****************************************************************************
// �^�C�g�����S�̃N���X
//*****************************************************************************
class CTitle_Logo : public CScene
{
public:																				// �N�ł��A�N�Z�X�\
	CTitle_Logo(PRIORITY nPriority = PRIORITY_UI);																// �R���X�g���N�^
	~CTitle_Logo();																			// �f�X�g���N�^
																							// �����o�֐�
	static CTitle_Logo *Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size);							// �^�C�g�����S�̐���
	HRESULT Init(D3DXVECTOR3 pos);								// �^�C�g�����S�̏������֐�
	void Uninit(void);																// �^�C�g�����S�̏I���֐�
	void Update(void);																// �^�C�g�����S�̍X�V�֐�
	void Draw(void);																// �^�C�g�����S�̕`��֐�

private:																			// �����������A�N�Z�X�\	
	static CPolygon * m_Polygon;											// �|���S���N���X�̃|�C���^
	D3DXVECTOR3 m_pos;																// �|���S���̈ʒu
	D3DXVECTOR3 m_move;																// �|���S���̈ړ���
	D3DXVECTOR2 m_Size;																// �|���S���̑傫��
};
#endif