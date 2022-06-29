//=============================================================================
//
// �e�̏��� [bullet.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "billboard.h"

//*****************************************************************************
// �e�N���X
//*****************************************************************************
class CBullet : public CBillboard
{
public:
	CBullet(PRIORITY nPriority = PRIORITY_BULLET);					// �R���X�g���N�^
	~CBullet();														// �f�X�g���N�^
	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size,int nLife);		// �|���S���̐���	
	
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 size);			// �e�̏������֐�
	void Uninit();												// �e�̏I���֐�
	void Update();												// �e�̍X�V�֐�
	void Draw();												// �e�̕`��֐�
	D3DXVECTOR3 GetMove() { return m_move; }
	void SetMove(D3DXVECTOR3 move) { m_move = move; }
	void SetUse(bool buse) { m_bUse = buse; }
	
private:
	LPDIRECT3DTEXTURE9	m_pTexture = NULL;					// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;				// ���_�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;									// ���[���h�}�g���b�N�X	
	D3DXVECTOR3 m_pos;										// �ʒu
	D3DXVECTOR2 m_size;										// �傫��
	D3DXVECTOR3 m_move;										// �ړ���
	D3DXCOLOR m_col;										// �F
	int m_nLife;											// �e�̗̑�
	bool m_bUse;											// �e���g���Ă邩�ǂ���

};
#endif // !_BILLBOARD_H_