//=============================================================================
//
// 2D�|���S���̏��� [scene2D.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

#include"scene.h"

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
// �I�u�W�F�N�g�N���X
//*****************************************************************************
class CScene2D : public CScene
{
public:																			// �N�ł��A�N�Z�X�\

	CScene2D(PRIORITY Priority = PRIORITY_NOMAL);								// �R���X�g���N�^
	~CScene2D();																// �f�X�g���N�^
	// �����o�֐�
	static CScene2D *Creste(D3DXVECTOR3 pos, D3DXVECTOR2 size, int nTex);					// �|���S���̐���
	void BindTextuer(int nTextuer);												// �e�N�X�`���̐ݒ�
	HRESULT Init(D3DXVECTOR3 pos);												// �|���S���̏������֐�
	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 size);	// �|���S���̏������֐�
	virtual void Uninit(void);													// �|���S���̏I���֐�
	virtual void Update(void);													// �|���S���̍X�V�֐�
	virtual void Draw(void);													// �|���S���̕`��֐�
	void SetColor(D3DXCOLOR col);												// �e�N�X�`���̐F(1.0f)�̐ݒ菈��
	void SetColor(int nRad, int nGreen, int nBlue, int nAlpha);					// �e�N�X�`���̐F(255)�̐ݒ菈��
	void SetAngle(D3DXVECTOR2 Angle, D3DXVECTOR2 size);					// �e�N�X�`���̐F(255)�̐ݒ菈��
	void SetUpdateRollingSize(void);											// �|���S���̉�]�g��k������
	void SetUpdateSize(int MaxSize, int MinSize);								// �|���S���̊g��k���ݒ菈��
	void SetUpdateRoll(float fSpeed,bool bAdd);									// �|���S���̉�]�ݒ菈��
	void SetUpdatePosSize(D3DXVECTOR3 pos, D3DXVECTOR2 Size);					// �|���S���̈ʒu�Ƒ傫������
	D3DXVECTOR3 GetPosition(void) { return m_pos; }								// pos�̎擾����
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }							// pos��Ԃ�����

private:																		// �����������A�N�Z�X�\
	LPDIRECT3DTEXTURE9 m_pTexTure;												// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;											// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;															// �|���S���̈ʒu
	D3DXVECTOR3 m_Move;															// �|���S���̈ړ���
	D3DXVECTOR2 m_Size;															// �|���S���̑傫��
	static const int m_nNumVertex;													// �|���S���̒��_��
	int m_Tex_Typ;																// �e�N�X�`���̎��
	float m_fRoll;																// �~��
	float m_fHypot;																// (�㔼�a��2��{���a��2��)�̒l
	float m_fAngle;																// ������
	bool m_bAdd;																// ���Z�����Z��
};
#endif