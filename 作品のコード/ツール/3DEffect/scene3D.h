//=============================================================================
//
// �|���S���̏��� [scene3D.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _SCENE3D_H_
#define _SCENE3D_H_

#include"scene.h"
#include"texture.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)		//���_�t�H�[�}�b�g3D

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		//���_���W
	D3DXVECTOR3 nor;		//�@���x�N�g��
	D3DCOLOR col;			//���_�J���[
	D3DXVECTOR2 tex;		//�e�N�X�`�����W
} VERTEX_3D;

//*****************************************************************************
// 3D�I�u�W�F�N�g�N���X
//*****************************************************************************
class CScene3D : public CScene
{
public:															// �N�ł��A�N�Z�X�\

	CScene3D(PRIORITY Priority = PRIORITY_NOMAL);				// �R���X�g���N�^
	~CScene3D();												// �f�X�g���N�^
																// �����o�֐�
	void BindTextuer(CTexture::Tex type);						// �e�N�X�`���̐ݒ�
	static CScene3D *Creste(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// �|���S���̐���
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);			// �|���S���̏������֐�
	void Uninit(void);											// �|���S���̏I���֐�
	void Update(void);											// �|���S���̍X�V�֐�
	void Draw(void);											// �|���S���̕`��֐�
	D3DXVECTOR3 GetPosition(void) { return m_pos; }				// pos�̎擾����
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }			// pos��Ԃ�����

private:														// �����������A�N�Z�X�\

	LPDIRECT3DTEXTURE9 m_pTexTure;								// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVlxBuff;							// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;							// �C���f�b�N�X�ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;										// ���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;											// �|���S���̈ʒu
	D3DXVECTOR3 m_Size;											// �|���S���̑傫��
	D3DXVECTOR3 m_rot;											// �|���S���̌���
};
#endif