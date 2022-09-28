//=============================================================================
//
// �e�̏��� [bullet.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include"scene2D.h"

//*****************************************************************************
// �e�̃N���X
//*****************************************************************************
class CBullet : public CScene2D
{
public:																			// �N�ł��A�N�Z�X�\
	CBullet(int nPriority = PRIORITY_SECOND);									// �R���X�g���N�^
	~CBullet();																	// �f�X�g���N�^
	// �����o�֐�
	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move,D3DXVECTOR2 Size, int nLife, bool bEffect);	// �e�̐���
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);							// �e�̏������֐�
	void Uninit(void);															// �e�̏I���֐�
	void Update(void);															// �e�̍X�V�֐�
	void Draw(void);															// �e�̕`��֐�
	bool GetUse(void) { return m_bUse; }
	void SetUse(bool bUse) { m_bUse = bUse; }
	void EnemyColision();
	D3DXVECTOR3 GetPosOld() { return m_PosOld; }
	int GetAttack() { return m_nAttack; }

private:																		// �����������A�N�Z�X�\		
	bool m_bUse;															// �g���Ă��邩�ǂ���
	bool m_bEffect;																// �G�t�F�N�g���g�����ǂ���
	D3DXVECTOR3 m_Pos;															// �e�̌��ݒn
	D3DXVECTOR3 m_PosOld;															// �e�̌��ݒn
	D3DXVECTOR3 m_Move;															// �e�̈ړ���
	D3DXVECTOR2 m_Size;															// �e�̑傫��	
	int m_nLife;																// �e�̗̑�
	int m_nAttack;																// �e�̍U����

};
#endif
