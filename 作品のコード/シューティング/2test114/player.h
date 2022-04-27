//=============================================================================
//
// �v���C���[�̏��� [player.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _PLATER_H_
#define _PLATER_H_

#include"scene2D.h"

//*****************************************************************************
// �v���C���[�N���X
//*****************************************************************************
class CPlayer : public CScene2D
{
public:																// �N�ł��A�N�Z�X�\

	//�v���C���[�̏��
	typedef enum 
	{
		PLAYER_NOMAL = 0,
		PLAYER_DEATH,
		PLAYER_RESTARE,
		PLAYER_MAX
	} PLAYER;

	CPlayer(int nPriority = PRIORITY_PLAYER);										// �R���X�g���N�^
	~CPlayer();														// �f�X�g���N�^
	// �����o�֐�
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size);		// �v���C���̐���
	static HRESULT Load(void);										// �e�N�X�`���̓ǂݍ���
	static void Unload(void);										// �e�N�X�`���̔j��
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size);				// �v���C���̏������֐�
	void Uninit(void);												// �v���C���̏I���֐�
	void Update(void);												// �v���C���̍X�V�֐�
	void Draw(void);												// �v���C���̕`��֐�
	PLAYER GetPlayerType(void) { return m_Playertype; }

private:															// �����������A�N�Z�X�\
	D3DXVECTOR3 m_move;												// �ړ���
	const float m_fSpeedMax;										// ���΂₳�̍ő�l																	
	static LPDIRECT3DTEXTURE9 m_pTexture;							// �e�N�X�`���ւ̃|�C���^
	int m_nCounterAnim;												// �A�j���[�V�����J�E���^
	int m_nPatternAnim;												// �A�j���[�V�����p�^�[��No
	int m_nTimer;													// �e���΂�����
	bool m_bDeath;													// �O��|�ꂽ���̔���
	PLAYER m_Playertype;											// �v���C���[�̏��
};
#endif
