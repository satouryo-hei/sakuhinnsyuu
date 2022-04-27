//=============================================================================
//
// �^�������̃G�t�F�N�g�̏��� [siraight_effect.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _STRAIGHT_EFFECT_H
#define _STRAIGHT_EFFECT_H

#include "billeffect.h"
#include "texture.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CEffect;

//*****************************************************************************
//  �^�������̃G�t�F�N�g�N���X
//*****************************************************************************
class CStraight_Effect : CBilleffect
{
public:

	CStraight_Effect(PRIORITY nPriority = CBilleffect::PRIORITY_NOMAL);														// �R���X�g���N�^
	~CStraight_Effect();																									// �f�X�g���N�^
	static CStraight_Effect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, CTexture::Tex type, 	// ����
		D3DXVECTOR3 addmove, D3DXVECTOR3 addsize, D3DXCOLOR addcol, int nDensity, int nLife);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, CTexture::Tex type,					// ������
		D3DXVECTOR3 addmove, D3DXVECTOR3 addsize, D3DXCOLOR addcol, int nDensity, int nLife);
	void Uninit(void);																										// �I��
	void Update(void);																										// �X�V
	void Draw(void);																										// �`��
	void SetStraight(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, CTexture::Tex type,				// �ݒ�
		D3DXVECTOR3 addmove, D3DXVECTOR3 addsize, D3DXCOLOR addcol, int nDensity, int nLife);
	D3DXVECTOR3 Addmove(D3DXVECTOR3 move, D3DXVECTOR3 addmove);																// �v�Z����ړ���
	D3DXCOLOR Addcol(D3DXCOLOR col, D3DXCOLOR addcol);																		// �v�Z����F
	void SetUse(bool bUse) { m_bUse = bUse; }																				// �g���Ă��邩�ǂ���

private:
	CEffect *m_pEffect;		//�G�t�F�N�g�̃|�C���^�[
	D3DXVECTOR3 m_pos;		// ���݂̈ʒu
	D3DXVECTOR3 m_rot;		// ��]��
	D3DXVECTOR3 m_move;		// �ړ���
	D3DXVECTOR3 m_size;		// �傫��
	D3DXCOLOR m_col;		// �F
	int m_nLife;			// ����
	bool m_bUse;			// �g�p���Ă��邩�ǂ���
};

#endif