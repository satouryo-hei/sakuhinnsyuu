//=============================================================================
//
// �G�̏��� [enemy.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include"scene2D.h"

//*****************************************************************************
// �G�̃N���X
//*****************************************************************************
class CEnemy : public CScene2D
{
public:																				// �N�ł��A�N�Z�X�\
	CEnemy(int nPriority = PRIORITY_PLAYER);										// �R���X�g���N�^
	virtual ~CEnemy();																		// �f�X�g���N�^
																					// �����o�֐�
	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size);		// �v���C���̐���
	static HRESULT Load(void);														// �e�N�X�`���̓ǂݍ���
	static void Unload(void);														// �e�N�X�`���̔j��
	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size);				// �G�̏������֐�
	virtual void Uninit(void);																// �G�̏I���֐�
	void Update(void);																// �G�̍X�V�֐�
	virtual void Draw(void);																// �G�̕`��֐�

private:																			// �����������A�N�Z�X�\				
	static LPDIRECT3DTEXTURE9 m_pTexture;											// �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 m_Move;																// �G�̈ړ���
	D3DXVECTOR2 m_Size;
};
#endif
