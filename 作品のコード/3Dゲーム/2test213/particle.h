//=============================================================================
//
// �p�[�e�B�N���̏��� [effect.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _PARTICLE_H_//endif�ƃZ�b�g�i�K����ԏ�
#define _PARTICLE_H_

#include"billeffect.h"
#include "texture.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CIRCLE_HALF (float((rand() % 314) / 100.0f)/2 - float((rand() % 314) / 100.0f))/2 //�~�̔����̃}�N��
#define CIRCLE (float(rand() % 314) / 100.0f - float(rand() % 314) / 100.0f) //�~�̃}�N��

//*****************************************************************************
// �p�[�e�B�N���̃G�t�F�N�g�N���X
//*****************************************************************************
class CParticle : public CBilleffect
{
public:

	CParticle(PRIORITY nPriority = PRIORITY_NOMAL);
	~CParticle();

	//�v���g�^�C�v�錾
	static CParticle *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, int type,
		D3DXVECTOR3 addmove,D3DXVECTOR3 addsize, D3DXCOLOR addcol, int nLife);							// ��������
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, int type,
		D3DXVECTOR3 addmove,D3DXVECTOR3 addsize,D3DXCOLOR addcol, int nLife);							// ����������
	void Uninit(void);																					// �I������
	void Update(void);																					// �X�V����
	void Draw(void);																					// �`�揈��

private:
	D3DXVECTOR3 m_pos;						// ���݂̈ʒu
	D3DXVECTOR3 m_rot;						// ��]��
	D3DXVECTOR3 m_move;						// �ړ���
	D3DXVECTOR3 m_Addmove;					// �ړ��ʂ̌��Z�l
	D3DXVECTOR3 m_size;						// �傫��
	D3DXVECTOR3 m_AddSize;					// �傫���̌��Z�l
	D3DXCOLOR m_col;						// �F
	D3DXCOLOR m_addcol;						// �F�̌��Z�l
	int m_nLife;							// ����
	bool m_bUse;							// �g�p���Ă��邩�ǂ���

};
#endif // !_EFFECT_H_
