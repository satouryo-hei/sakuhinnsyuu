//=============================================================================
//
// �G�̏��� [enemy_doragonfly.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _ENEMY_DORAGONFLY_H_
#define _ENEMY_DORAGONFLY_H_

#include"enemy.h"

//*****************************************************************************
// �G�̃N���X
//*****************************************************************************
class CEnemy_Doragonfly : public CEnemy
{
public:																						// �N�ł��A�N�Z�X�\
	CEnemy_Doragonfly(int nPriority = PRIORITY_PLAYER);										// �R���X�g���N�^
	~CEnemy_Doragonfly();																	// �f�X�g���N�^
																							// �����o�֐�
	static CEnemy_Doragonfly *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size);	// �v���C���̐���
	static HRESULT Load(void);																// �e�N�X�`���̓ǂݍ���
	static void Unload(void);																// �e�N�X�`���̔j��
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size);						// �G�̏������֐�
	void Uninit(void);																		// �G�̏I���֐�
	void Update(void);																		// �G�̍X�V�֐�
	void Draw(void);																		// �G�̕`��֐�
	void SetAnimesion(int nPatternAnim, float fSizeAnimU, float fSizeMinV, float fSizeMaxV);// �G�̃A�j���[�V�����ݒ�֐�

private:																					// �����������A�N�Z�X�\				
	static LPDIRECT3DTEXTURE9 m_pTexture;													// �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 m_pos;																		// �g���{�̌��݂̈ʒu
	D3DXVECTOR3 m_Move;																		// �G�̈ړ���
	D3DXVECTOR2 m_Size;																		// �G�̑傫��
	D3DXVECTOR3 m_Playerpos;																// �v���C���[�̌���
	float m_fRange;																			// �G�ƃv���C���[�̋���
	bool m_bUse;																			// �G����ʓ��ɂ��邩�ǂ���
	int m_nCounterAnim;																		// �A�j���[�V�����J�E���^
	int m_nPatternAnim;																		// �A�j���[�V�����p�^�[��No
	float m_fSizeAnimU;																		// �A�j���[�V�����e�N�X�`���̉��T�C�Y
	float m_fSizeMinV;																		// �A�j���[�V�����̏c�̍ŏ��T�C�Y
	float m_fSizeMaxV;																		// �A�j���[�V�����̏c�̍ő�T�C�Y
	bool m_bAimPlayer;																		// �G���v���C���[���˂���Ă��邩�ǂ���
};																							
#endif