//=============================================================================
//
// �������玟�֏��� [player.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _PRESS_NEXT_H_
#define _PRESS_NEXT_H_

#include"scene2D.h"
//*****************************************************************************
// �O���錾
//*****************************************************************************
class CPolygon;

//*****************************************************************************
// �������玟�փN���X
//*****************************************************************************
class CPress_Next : public CScene
{
public:																								// �N�ł��A�N�Z�X�\
	CPress_Next(PRIORITY nPriority = PRIORITY_UI);														// �R���X�g���N�^
	~CPress_Next();																					// �f�X�g���N�^
																									// �����o�֐�
	static CPress_Next *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size, float fHeight);	// �|���S���̐���
	HRESULT Init(D3DXVECTOR3 pos);																	// �|���S���̏������֐�
	void Uninit(void);																				// �|���S���̏I���֐�
	void Update(void);																				// �|���S���̍X�V�֐�
	void Draw(void);																				// �|���S���̕`��֐�

private:																							// �����������A�N�Z�X�\
	static LPDIRECT3DTEXTURE9 m_pTexture;															// ���L����e�X�N�`���̃|�C���^
	D3DXVECTOR3 m_pos;																				// �ʒu
	D3DXVECTOR3 m_move;																				// �ړ���
	D3DXVECTOR2 m_size;																				// �傫��
	float m_fHeight;																				// �傫��
	static CPolygon * m_pPolygon;											// �|���S���N���X�̃|�C���^
};
#endif