//=============================================================================
//
// �e�̏��� [bullet.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _SHOTGUN_H_
#define _SHOTGUN_H_

#include"scene2D.h"

#define CIRCLE_HALF (float((rand() % 314) / 100.0f)/3- float((rand() % 314) / 100.0f))/3 //�~��3����1�̃}�N��

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CBullet;
//*****************************************************************************
// �e�̃N���X
//*****************************************************************************
class CShotgun : public CScene2D
{
public:																			// �N�ł��A�N�Z�X�\
	CShotgun(int nPriority = PRIORITY_SECOND);									// �R���X�g���N�^
	~CShotgun();																	// �f�X�g���N�^
																				// �����o�֐�
	static CShotgun *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size, int nAttack);	// �e�̐���
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);							// �e�̏������֐�
	void Uninit(void);															// �e�̏I���֐�
	void Update(void);															// �e�̍X�V�֐�
	void Draw(void);															// �e�̕`��֐�
	static bool GetUse(void) { return m_bUse; }
	static void SetUse(bool bUse) { m_bUse = bUse; }

private:																		// �����������A�N�Z�X�\		
	static bool m_bUse;															// �g���Ă��邩�ǂ���
	static CBullet * m_pBullet[3];													// �e�̃|�C���^�[	
	D3DXVECTOR3 m_Pos;															// �e�̌��ݒn
	D3DXVECTOR3 m_Move;															// �e�̈ړ���
	D3DXVECTOR2 m_Size;															// �e�̑傫��	
	int m_nLife;																// �e�̗̑�
	int m_nAttack;																// �e�̍U����
};
#endif