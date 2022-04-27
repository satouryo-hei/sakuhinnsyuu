//=============================================================================
//
// �v���C���[�̏��� [player.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _PRESS_NEXT_H_
#define _PRESS_NEXT_H_

#include"scene2D.h"

//*****************************************************************************
// �����̃|���S���N���X
//*****************************************************************************
class CPress_Next : public CScene2D
{
public:																								// �N�ł��A�N�Z�X�\
	CPress_Next(int nPriority = PRIORITY_UI);														// �R���X�g���N�^
	~CPress_Next();																					// �f�X�g���N�^
	// �����o�֐�
	static CPress_Next *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size, float fHeight);	// �|���S���̐���
	static HRESULT Load(void);																		// �e�N�X�`���̓ǂݍ���
	static void Unload(void);																		// �e�N�X�`���̔j��
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move,D3DXVECTOR2 Size);								// �|���S���̏������֐�
	void Uninit(void);																				// �|���S���̏I���֐�
	void Update(void);																				// �|���S���̍X�V�֐�
	void Draw(void);																				// �|���S���̕`��֐�

private:																							// �����������A�N�Z�X�\
	static LPDIRECT3DTEXTURE9 m_pTexture;															// ���L����e�X�N�`���̃|�C���^
	D3DXVECTOR3 m_pos;																				// �ʒu
	D3DXVECTOR3 m_move;																				// �ړ���
	D3DXVECTOR2 m_size;																				// �傫��
	float m_fHeight;																				// �傫��
};
#endif