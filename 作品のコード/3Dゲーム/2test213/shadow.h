//=============================================================================
//
// �e�̏��� [shadow.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _SHADOW_H_//endif�ƃZ�b�g�i�K����ԏ�
#define _SHADOW_H_

#include"scene3D.h"
//*****************************************************************************
// �e�̃N���X
//*****************************************************************************
class CShadow : public CScene3D
{
public:																			// �N�ł��A�N�Z�X�\
	CShadow(PRIORITY Priority = PRIORITY_SECOND);								// �R���X�g���N�^
	~CShadow();																	// �f�X�g���N�^

	// �����o�֐�
	static CShadow *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 Rot);	// �e�̐���
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);							// �e�̏������֐�
	void Uninit(void);															// �e�̏I���֐�
	void Update(void);															// �e�̍X�V�֐�
	void Draw(void);															// �e�̕`��֐�
	void SetShodow(D3DXVECTOR3 pos, D3DXVECTOR3 size);							// �e�̊֐�
	void SetPositionShadow(const D3DXVECTOR3 pos) { m_pos = pos; }				// �e�̈ʒu�̐ݒ�֐�
	D3DXVECTOR3 GetPositionShadow(void) { return m_pos; }						// �e�̈ʒu�̎擾�֐�

private:																		// �����������A�N�Z�X�\
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;											// ���_�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;														// ���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;															// �|���S���ʒu
	D3DXVECTOR3 m_size;															// �|���S���ʒu
	D3DXVECTOR3 m_rot;															// �|���S���̌���
	bool m_bUse;																// �g�p���Ă��邩
};
#endif // _POLYGON_H_//ifndef�ƃZ�b�g�i�K����ԉ�