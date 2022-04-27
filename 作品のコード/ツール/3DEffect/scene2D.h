//=============================================================================
//
// �|���S���̏��� [scene.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

#include"scene.h"
#include"texture.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FVF_VERTEX_2D (D3DFVF_XYZRHW |D3DFVF_DIFFUSE | D3DFVF_TEX1)		//���_�t�H�[�}�b�g2D

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;					//���_���W
	float rhw;							//1.0f�ŌŒ�
	D3DCOLOR col;						//���_�J���[
	D3DXVECTOR2 tex;					//�e�N�X�`�����W
} VERTEX_2D;

//*****************************************************************************
// 2D�I�u�W�F�N�g�N���X
//*****************************************************************************
class CScene2D : public CScene
{
public:															// �N�ł��A�N�Z�X�\

	CScene2D(PRIORITY Priority = PRIORITY_NOMAL);				// �R���X�g���N�^
	~CScene2D();												// �f�X�g���N�^
	// �����o�֐�
	void BindTextuer(CTexture::Tex type);						// �e�N�X�`���̐ݒ�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);			// �|���S���̏������֐�
	void Uninit(void);											// �|���S���̏I���֐�
	void Update(void);											// �|���S���̍X�V�֐�
	void Draw(void);											// �|���S���̕`��֐�
	void SetColor(D3DXCOLOR col);								// �e�N�X�`���̐F(1.0f)�̐ݒ菈��
	void SetColor(int nRad, int nGreen, int nBlue, int nAlpha);	// �e�N�X�`���̐F(255)�̐ݒ菈��
	void SetUpdateRollingSize(void);
	void SetUpdateSize(void);
	void SetUpdateRoll(void);
	void SetUpdatePosSize(D3DXVECTOR3 pos, D3DXVECTOR3 Size);
	D3DXVECTOR3 GetPosition(void) { return m_pos; }				// pos�̎擾����
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }			// pos��Ԃ�����

private:														// �����������A�N�Z�X�\
																   
	LPDIRECT3DTEXTURE9 m_pTexTure;								// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVlxBuff;							// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;											// �|���S���̈ʒu
	D3DXVECTOR3 m_Size;											// �|���S���̑傫��
	int m_Tex_Typ;												// �e�N�X�`���̎��
	float m_fRoll;												// �~��
	float m_fHypot;												// (�㔼�a��2��{���a��2��)�̒l
	float m_fAngle;												// ������
	bool m_bAdd;												// ���Z�����Z��
};
#endif