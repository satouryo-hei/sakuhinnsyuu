//=============================================================================
//
// 2D�I�u�W�F�N�g�̏��� [scene2D.h]
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
// 2D�I�u�W�F�N�g�N���X
//*****************************************************************************
class CScene2D : public CScene
{
public:																			// �N�ł��A�N�Z�X�\

	CScene2D(PRIORITY Priority = PRIORITY_NOMAL);											// �R���X�g���N�^
	~CScene2D();																			// �f�X�g���N�^
	// �����o�֐�
	static CScene2D *Creste(D3DXVECTOR3 pos, D3DXVECTOR2 size, int nTex);					// �|���S���̐���
	void BindTextuer(int nTextuer);															// �e�N�X�`���̐ݒ�
	HRESULT Init(D3DXVECTOR3 pos);															// 2D�I�u�W�F�N�g�̏������֐�
	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 size);								// �|���S���̏������֐�
	virtual void Uninit(void);																// 2D�I�u�W�F�N�g�̏I���֐�
	virtual void Update(void);																// 2D�I�u�W�F�N�g�̍X�V�֐�
	virtual void Draw(void);																// 2D�I�u�W�F�N�g�̕`��֐�
	void SetColor(D3DXCOLOR col);															// �e�N�X�`���̐F(1.0f)�̐ݒ菈��
	void SetVtxBuffColor(D3DXCOLOR col,int nVtxBuff);										// ���ꂼ��̒��_�̐F(1.0f)�̐ݒ菈��
	void SetColor(int nRad, int nGreen, int nBlue, int nAlpha);								// �e�N�X�`���̐F(255)�̐ݒ菈��
	void SetAngle(D3DXVECTOR2 Angle, D3DXVECTOR2 size);										// �e�N�X�`���̐F(255)�̐ݒ菈��
	void SetUpdateRollingSize(void);														// 2D�I�u�W�F�N�g�̉�]�g��k������
	void SetUpdateSize(int MaxSize, int MinSize);											// 2D�I�u�W�F�N�g�̊g��k���ݒ菈��
	void SetUpdateRoll(float fSpeed,bool bAdd);												// 2D�I�u�W�F�N�g�̉�]�ݒ菈��
	void SetUpdatePosSize(D3DXVECTOR3 pos, D3DXVECTOR2 Size);								// 2D�I�u�W�F�N�g�̈ʒu�Ƒ傫������
	void SetTexAnime(int nPatternAnim, float fSizeAnimU, float fSizeMinV, float fSizeMaxV);	// 2D�I�u�W�F�N�g�̃A�j���[�V��������
	D3DXVECTOR3 GetPosition(void) { return m_pos; }											// pos�̎擾����
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }										// pos��Ԃ�����
	D3DXVECTOR2 GetSize(void) { return m_Size; }											// Size�̎擾����
	void SetSize(D3DXVECTOR2 Size) { m_Size = Size; }										// Size��Ԃ�����

private:																					// �����������A�N�Z�X�\
	LPDIRECT3DTEXTURE9 m_pTexTure;															// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;														// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;																		// 2D�I�u�W�F�N�g�̈ʒu
	D3DXVECTOR3 m_Move;																		// 2D�I�u�W�F�N�g�̈ړ���
	D3DXVECTOR2 m_Size;																		// 2D�I�u�W�F�N�g�̑傫��
	static const int m_nNumVertex;															// 2D�I�u�W�F�N�g�̒��_��
	int m_Tex_Typ;																			// �e�N�X�`���̎��
	float m_fRoll;																			// �~��
	float m_fHypot;																			// (�㔼�a��2��{���a��2��)�̒l
	float m_fAngle;																			// ������
	bool m_bAdd;																			// ���Z�����Z��
};
#endif