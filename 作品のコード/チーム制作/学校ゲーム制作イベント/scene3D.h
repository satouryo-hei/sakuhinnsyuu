//=============================================================================
//
// 3D�|���S���̏��� [scene3D.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _SCENE3D_H_
#define _SCENE3D_H_

#include"scene.h"

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
public:																						// �N�ł��A�N�Z�X�\

	CScene3D(PRIORITY Priority = PRIORITY_NOMAL);											// �R���X�g���N�^
	~CScene3D();																			// �f�X�g���N�^
	// �����o�֐�
	static CScene3D *Creste(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot);			// 3D�I�u�W�F�N�g�̐���
	void BindTextuer(int nTex);																// �e�N�X�`���̐ݒ�
	HRESULT Init(D3DXVECTOR3 pos);															// 3D�I�u�W�F�N�g�̃f�t�H���g�������֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot);						// 3D�I�u�W�F�N�g�̏������֐�
	void Uninit(void);																		// 3D�I�u�W�F�N�g�̏I���֐�
	void Update(void);																		// 3D�I�u�W�F�N�g�̍X�V�֐�
	void Draw(void);																		// 3D�I�u�W�F�N�g�̕`��֐�
	void SetNorVector(D3DXVECTOR3 nor);														// �@���x�N�g����ݒ�֐�
	D3DXVECTOR3 GetPosition(void) { return m_pos; }											// pos�̎擾����
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }										// pos��Ԃ�����
	void SetTexAnime(int nPatternAnim, float fSizeAnimU, float fSizeMinV, float fSizeMaxV);	// �e�N�X�`���A�j���[�V�����̐ݒ�֐�

private:																					// �����������A�N�Z�X�\

	LPDIRECT3DTEXTURE9 m_pTexTure;															// ���L����e�X�N�`���̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;														// ���_�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;																	// ���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;																		// 3D�I�u�W�F�N�g�̈ʒu
	D3DXVECTOR3 m_Size;																		// 3D�I�u�W�F�N�g�̑傫��
	D3DXVECTOR3 m_rot;																		// 3D�I�u�W�F�N�g�̌���
};
#endif