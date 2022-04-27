//=============================================================================
//
// ���n�G�t�F�N�g�̏��� [landing_effect.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _LANDING_EFFECT_H_//endif�ƃZ�b�g�i�K����ԏ�
#define _LANDING_EFFECT_H_

#include"billeffect.h"
#include "texture.h"

//*****************************************************************************
// ���n�G�t�F�N�g�N���X
//*****************************************************************************
class CLanding_Effect : public CBilleffect
{
public:

	CLanding_Effect(PRIORITY nPriority = CBilleffect::PRIORITY_NOMAL);															// �R���X�g���N�^
	~CLanding_Effect();																											// �f�X�g���N�^
																																//�v���g�^�C�v�錾
	static CLanding_Effect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, CTexture::Tex type,		// ����
		D3DXVECTOR3 addmove, D3DXVECTOR3 addsize, D3DXCOLOR addcol, int nRadius, int nDensity, int nLife);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, CTexture::Tex type,						// ������
		D3DXVECTOR3 addmove, D3DXVECTOR3 addsize, D3DXCOLOR addcol, int nRadius, int nDensity, int nLife);						
	void Uninit(void);																											// �I��
	void Update(void);																											// �X�V
	void Draw(void);																											// �`��
	void SetLanding(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, CTexture::Tex type,						// �ݒ�
		D3DXVECTOR3 addmove, D3DXVECTOR3 addsize, D3DXCOLOR addcol, int nRadius, int nDensity, int nLife);						
	D3DXVECTOR3 Addmove(D3DXVECTOR3 move, D3DXVECTOR3 addmove);																	// �v�Z����ړ���

private:
	D3DXVECTOR3 m_pos;						// ���݂̈ʒu
	D3DXVECTOR3 m_rot;						// ��]��
	D3DXVECTOR3 m_move;						// �ړ���
	D3DXVECTOR3 m_size;						// �傫��
	D3DXCOLOR m_col;						// �F
	int m_nLife;							// ����
	bool m_bUse;							// �g�p���Ă��邩�ǂ���

};
#endif // !_EFFECT_H_