//=============================================================================
//
// �G�t�F�N�g�̏��� [effect.cpp]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _SMOKE_EFFECT_H
#define _SMOKE_EFFECT_H

#include "billeffect.h"
#include "texture.h"
#define MAX_SMOKE_NUMALL (1)
#define MAX_SMOKE_CNT (8)//���̃J�E���^�[
#define MAX_SMOKE_SIZE (10)//���̑傫��
#define MAX_SMOKE_MOVE_X (0.5)//���̈ړ���
#define MAX_SMOKE_MOVE_Y (0.5)//���̈ړ���
#define MAX_SMOKE_MOVE_Z (0.5)//���̈ړ���

#define CIRCLE_HALF (float((rand() % 314) / 100.0f)/2 - float((rand() % 314) / 100.0f))/2 //�~�̔����̃}�N��

class CEffect;

class CSmoke_Effect : CBilleffect
{
public:

	CSmoke_Effect(CScene::OBJTYPE nPriority = CBilleffect::OBJTYPE_EFFECT);
	~CSmoke_Effect();
	static CSmoke_Effect *Create(D3DXVECTOR3 pos, float rotY, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, CTexture::Type type, D3DXVECTOR3 addmove, int nDensity, int nRadius, int nLife);
	HRESULT Init(D3DXVECTOR3 pos, float rotY, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, CTexture::Type type, D3DXVECTOR3 addmove, int nDensity, int nRadius, int nLife);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetSmoke(D3DXVECTOR3 pos, float rotY, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR3 addmove, int nDensity, int nRadius, int nLife);
	D3DXVECTOR3 Addmove(D3DXVECTOR3 move, D3DXVECTOR3 addmove);

	void SetUse(bool bUse) { m_bUse = bUse; }

private:
	CEffect *m_pEffect;		//�G�t�F�N�g�̃|�C���^�[
	D3DXVECTOR3 m_pos;		// ���݂̈ʒu
	D3DXVECTOR3 m_rot;		// ��]��
	D3DXVECTOR3 m_move;		// �ړ���
	D3DXVECTOR3 m_size;		// �傫��
	D3DXCOLOR m_col;		// �F
	int m_nLife;			// ����
	int m_nTimer;			//�J�E���^�[
	bool m_bUse;			// �g�p���Ă��邩�ǂ���
	float m_fRoll;
};

#endif