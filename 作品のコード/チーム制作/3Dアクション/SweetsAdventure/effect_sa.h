//=============================================================================
//
// �G�t�F�N�g�̏��� [effect.cpp]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _EFFECT_SA_H_//endif�ƃZ�b�g�i�K����ԏ�
#define _EFFECT_SA_H_

#include"billeffect.h"
#include "texture.h"

// �}�N����`
#define CIRCLE (float(rand() % 360) / 100.0f - float(rand() % 360) / 100.0f) //�~�̃}�N��
#define POSRAND (rand() % 10 + 10)

class CEffect_sa : public CBilleffect
{
public:

	CEffect_sa(OBJTYPE OBJTYPE_EFFECT);
	~CEffect_sa();

	//�v���g�^�C�v�錾
	static CEffect_sa *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, CTexture::Type type, int nLife);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, CTexture::Type type, int nLife);
	void Uninit(void);
	void Update(void);
	void Draw(void);

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
