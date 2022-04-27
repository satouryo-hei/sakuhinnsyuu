//=============================================================================
//
// �G�t�F�N�g�p�̃r���{�[�h���� [billeffect.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _BILLEFFECT_H_
#define _BILLEFFECT_H_

#include "scene.h"
#include"texture.h"

//*****************************************************************************
// �G�t�F�N�g�p�̃r���{�[�h�N���X
//*****************************************************************************
class CBilleffect : public CScene
{
public:
	CBilleffect(PRIORITY nPriority = PRIORITY_NOMAL);					// �R���X�g���N�^
	~CBilleffect();														// �f�X�g���N�^
	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);			// �������֐�
	virtual void Uninit();												// �I���֐�
	virtual void Update();												// �X�V�֐�
	virtual void Draw();												// �`��֐�
	void BindTextuer(CTexture::Tex type);								// �e�N�X�`���̐ݒ�
	void Setposition(D3DXVECTOR3 pos, D3DXVECTOR3 Size);				// ���_���ݒ�
	void SetColor(D3DXCOLOR col);										// �F(1.0f)�̐ݒ菈��
	void SetColor(int nRad, int nGreen, int nBlue, int nAlpha);			// �F(255)�̐ݒ菈��

private:
	LPDIRECT3DTEXTURE9	m_pTexture = NULL;					// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;				// ���_�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;									// ���[���h�}�g���b�N�X	
	D3DXMATRIX m_mtxView;									// �r���[�}�g���b�N�X
	D3DXVECTOR3 m_pos;										// �ʒu
	D3DXVECTOR3 m_size;										// �傫��
	D3DXCOLOR m_col;										// �F
	int m_nRad;												// ��
	int m_nGreen;											// ��
	int m_nBlue;											// ��
	int m_nAlpha;											// �����x

};
#endif // !_BILLBOARD_H_