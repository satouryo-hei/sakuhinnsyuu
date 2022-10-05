//=============================================================================
//
// UI�̏��� [keyui.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _BULLETUI_H_
#define _BULLETUI_H_

#include"scene2D.h"

#define MAX_KEYNUMBER (3)

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CPolygon;
class CNumber;

//*****************************************************************************
// ���S�̃N���X
//*****************************************************************************
class CBulletui : public CScene
{
public:																		// �N�ł��A�N�Z�X�\
	CBulletui(PRIORITY Priority = PRIORITY_EFFECT);							// �R���X�g���N�^
	~CBulletui();																// �f�X�g���N�^
																			// �����o�֐�
	static CBulletui *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size);				// ���S�̐���
	HRESULT Init(D3DXVECTOR3 pos);											// ���S�̏������֐�
	void Uninit(void);														// ���S�̏I���֐�
	void Update(void);														// ���S�̍X�V�֐�
	void Draw(void);														// ���S�̕`��֐�

private:																	// �����������A�N�Z�X�\
	void SetNumbullet(const int nNumbullet);										// ���̐��̐ݒ菈��
	static CPolygon * m_pPolygon;											// �|���S���̃|�C���^�[�𐶐�
	CNumber * m_apNumber[MAX_KEYNUMBER];								// �ԍ��̔z��̃|�C���^�[�𐶐�
	D3DXVECTOR3 m_Pos;														// ���݂̈ʒu	
	D3DXVECTOR2 m_Size;														// �傫��

};
#endif // !_EFFECT_H_