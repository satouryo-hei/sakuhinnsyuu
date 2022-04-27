//=============================================================================
//
// �G�t�F�N�g�̏��� [effect.cpp]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _FAIR_EFFECT_H
#define _FAIR_EFFECT_H

#include "billeffect.h"
#include "texture.h"

#define RANGE (float(rand() % 100) / 100.0f - float(rand() % 100) / 100.0f) //�~�̃}�N��

class CEffect;

class Cfair_Effect : CBilleffect
{
public:

	Cfair_Effect(CScene::OBJTYPE nPriority = CBilleffect::OBJTYPE_EFFECT);
	~Cfair_Effect();
	static Cfair_Effect *Create(D3DXVECTOR3 pos, CTexture::Type type);
	HRESULT Init(D3DXVECTOR3 pos, CTexture::Type type);
	void Uninit(void);
	void Update(void);
	void Draw(void);

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

