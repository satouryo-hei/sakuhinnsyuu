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
// �O���錾
//*****************************************************************************
class CBullet;
//*****************************************************************************
// �v���C���[�N���X
//*****************************************************************************
class CPlayer : public CScene2D
{
public:																				// �N�ł��A�N�Z�X�\
	CPlayer(int nPriority = PRIORITY_PLAYER);										// �R���X�g���N�^
	~CPlayer();																		// �f�X�g���N�^
																					// �����o�֐�
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size);	// �v���C���̐���
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);								// �v���C���̏������֐�
	void Uninit(void);																// �v���C���̏I���֐�
	void Update(void);																// �v���C���̍X�V�֐�
	void Draw(void);																// �v���C���̕`��֐�
	static D3DXVECTOR3 GetPos(void) { return m_pos; }								// ���݂̈ʒu�̎擾����
	static void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }							// ���݂̈ʒu�̐ݒ菈��
	static D3DXVECTOR2 GetSize(void) { return m_size; }								// �傫���̎擾����
	static D3DXVECTOR3 GetPosold(void) { return m_posold; }							// �O��̈ʒu�̎擾����
	static void SetUse(bool bUse) { m_bUse = bUse; }								// �e�̃|�C���^�[�̎擾����
	
private:																			// �����������A�N�Z�X�\		
	static D3DXVECTOR3 m_pos;														// ���݂̈ʒu
	static D3DXVECTOR2 m_size;														// �傫��
	static D3DXVECTOR3 m_posold;													// �O��̈ʒu
	static D3DXVECTOR3 m_move;														// �ړ���	
	static LPDIRECT3DTEXTURE9 m_pTexture;											// �e�N�X�`���ւ̃|�C���^
	int m_nTimer;																	// ����
	int m_nCoolTime;																// �N�[������
	bool m_bBullet;																	// �e��ł������ǂ���			
	static bool m_bUse;																// �g���Ă��邩�ǂ���	
	static CBullet * m_pBullet;														// �e�̃|�C���^�[�̐���
};
#endif