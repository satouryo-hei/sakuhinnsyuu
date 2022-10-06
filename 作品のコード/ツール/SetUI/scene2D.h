//=============================================================================
//
// �I�u�W�F�N�g2D�̏��� [scene2D.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

#include"scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FVF_VERTEX_2D (D3DFVF_XYZRHW |D3DFVF_DIFFUSE | D3DFVF_TEX1)

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;	//���_���W
	float rhw;			//1.0f�ŌŒ�
	D3DCOLOR col;		//���_�J���[
	D3DXVECTOR2 tex;	//�e�N�X�`�����W
} VERTEX_2D;

//*****************************************************************************
// �I�u�W�F�N�g2D�N���X
//*****************************************************************************
class CScene2D : public CScene
{
public:																									// �N�ł��A�N�Z�X�\
	CScene2D();																							// �R���X�g���N�^
	~CScene2D();																						// �f�X�g���N�^
	// �����o�֐�
	void BindTextuer(int nTex); 																		// �e�N�X�`���̐ݒ菈��
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 Size);													// �f�t�H���g�|���S���̏������֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 Size);									// �����n�̃|���S���̏������֐�(�I�[�o�[���[�h)
	void Uninit(void);																					// �I�u�W�F�N�g2D�̏I���֐�
	void Update(void);																					// �I�u�W�F�N�g2D�̍X�V�֐�
	void Draw(void);																					// �I�u�W�F�N�g2D�̕`��֐�	
	virtual D3DXVECTOR3 GetPosition(void) { return m_pos; }												// pos�̎擾����
	virtual void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }											// pos��Ԃ�����
	virtual D3DXVECTOR3 GetSize(void) { return m_Size; }												// Size�̎擾����
	virtual void SetSize(D3DXVECTOR3 size) { m_Size = size; }											// Size��Ԃ�����
	void SetColor(D3DXCOLOR col);																		// �F��Ԃ��֐�
	void CScene2D::SetTexAnime(int nPatternAnim, float fSizeAnimU, float fSizeMinV, float fSizeMaxV);	// �e�N�X�`���̃A�j���[�V�����֐�
	void SetTex(float fSizeMin, float fSizeMax);														// �e�N�X�`���̐ݒ�֐�

private:																								// �����������A�N�Z�X�\
	// �����o�ϐ�
	LPDIRECT3DTEXTURE9 m_pTexTure;																		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVlxBuff;																	// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;																					// �I�u�W�F�N�g2D�̈ʒu
	D3DXVECTOR3 m_Move;																					// �I�u�W�F�N�g2D�̈ړ���
	D3DXVECTOR3 m_Size;																					// �I�u�W�F�N�g2D�̃T�C�Y
};
#endif