//=============================================================================
//
// �|���S���̏��� [scene2D.h]
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
// �|���S���N���X
//*****************************************************************************
class CScene2D : public CScene
{
public:																						// �N�ł��A�N�Z�X�\
	CScene2D(int nPriority = 3);															// �R���X�g���N�^
	~CScene2D();																			// �f�X�g���N�^
	// �����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);										// �f�t�H���g�|���S���̏������֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move,D3DXVECTOR2 Size);						// �����n�̃|���S���̏������֐�(�I�[�o�[���[�h)
	void Uninit(void);																		// �|���S���̏I���֐�
	void Update(void);																		// �|���S���̍X�V�֐�
	void Draw(void);																		// �|���S���̕`��֐�	
	virtual D3DXVECTOR3 GetPosition(void) { return m_pos; }									// pos�̎擾����
	virtual void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }								// pos��Ԃ�����
	virtual D3DXVECTOR2 GetSize(void) { return m_Size; }									// pos�̎擾����
	virtual void SetSize(D3DXVECTOR2 size) { m_Size = size; }								// pos��Ԃ�����
	void BindTextuer(LPDIRECT3DTEXTURE9 pTexTure) { m_pTexTure = pTexTure;}					// �e�N�X�`���̃|�C���^��Ԃ�����
	void SetUpdatePos(void);																// �g��k���Ɖ�]�̍X�V����
	void SetUpdateMovePos(D3DXVECTOR3 pos,D3DXVECTOR3 move, D3DXVECTOR2 Size);				// �����|���S���̍X�V����
	void SetUpdateRoll(void);																// �|���S���̉�]����
	void SetUpdateScale(int nMAXSize, int nMINSize);										// �|���S���̃T�C�Y�ύX����
	void SetTexAnime(int nPatternAnim,float fSizeAnim);										// �A�j���[�V�����̃e�N�X�`���z�u����
	void SetTexAnime(int nPatternAnim, float fSizeAnimU, float fSizeMinV,float fSizeMaxV);	// �A�j���[�V�����̃e�N�X�`���z�u����
	void SetTex(float fPosTexU ,float fPosTexV);											// �����e�N�X�`���̔z�u����
	void SetColor(D3DXCOLOR col);															// �e�N�X�`���̐F(1.0f)�̐ݒ菈��
	void SetColor(int nRad, int nGreen, int nBlue, int nAlpha);								// �e�N�X�`���̐F(255)�̐ݒ菈��

private:																	// �����������A�N�Z�X�\																			   
	LPDIRECT3DTEXTURE9 m_pTexTure;											// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVlxBuff;										// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;														// �|���S���̈ʒu
	D3DXVECTOR3 m_Move;														// �|���S���̈ړ���
	D3DXVECTOR2 m_Size;														// �|���S���̃T�C�Y
	int m_Typ;																// ���
	float m_fRoll;															// �~��
	float m_fHypot;															// �Ε�((�㔼�a��2��{���a��2��)�̒l)
	float m_fAngle;															// ������
	bool m_bAdd;															// ���Z�����Z��

};
#endif