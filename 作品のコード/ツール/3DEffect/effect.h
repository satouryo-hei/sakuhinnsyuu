//=============================================================================
//
// �G�t�F�N�g�̏��� [effect.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _EFFECT_H_//endif�ƃZ�b�g�i�K����ԏ�
#define _EFFECT_H_

#include"billeffect.h"
#include "texture.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CIRCLE_HALF (float((rand() % 314) / 100.0f)/2 - float((rand() % 314) / 100.0f))/2 //�~�̔����̃}�N��
#define CIRCLE (float(rand() % 314) / 100.0f - float(rand() % 314) / 100.0f) //�~�̃}�N��
#define POSRAND (rand() % 10 + 10)

//*****************************************************************************
// �G�t�F�N�g�̃G�t�F�N�g�N���X
//*****************************************************************************
class CEffect : public CBilleffect
{
public:

	CEffect(PRIORITY nPriority = PRIORITY_NOMAL);
	~CEffect();

	//�v���g�^�C�v�錾
	static CEffect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, CTexture::Tex type,
		D3DXVECTOR3 addmove,D3DXVECTOR3 addsize, D3DXCOLOR addcol, int nLife);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, CTexture::Tex type, 
		D3DXVECTOR3 addmove,D3DXVECTOR3 addsize,D3DXCOLOR addcol, int nLife);
	void Uninit(void);
	void Update(void);
	void Draw(void);

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
