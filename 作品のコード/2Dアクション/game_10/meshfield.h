//=============================================================================
//
// ���b�V���t�B�[���h�̏��� [meshfield.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _MESHFIELD_H_//endif�ƃZ�b�g�i�K����ԏ�
#define _MESHFIELD_H_

#include"scene.h"

//*****************************************************************************
// ���b�V���t�B�[���h�N���X
//*****************************************************************************
class CMeshField : public CScene
{
public:																// �N�ł��A�N�Z�X�\

	CMeshField(PRIORITY Priority = PRIORITY_NOMAL);					// �R���X�g���N�^
	~CMeshField();													// �f�X�g���N�^
	// �����o�֐�
	static CMeshField *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// ���b�V���t�B�[���h�̐���	
	HRESULT Init(D3DXVECTOR3 pos);									// ���b�V���t�B�[���h�̃f�t�H���g�������֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);				// ���b�V���t�B�[���h�̏������֐�
	void Uninit(void);												// ���b�V���t�B�[���h�̏I���֐�
	void Update(void);												// ���b�V���t�B�[���h�̍X�V�֐�
	void Draw(void);												// ���b�V���t�B�[���h�̕`��֐�
	void BindTextuer(int nTextuer);

private:															// �����������A�N�Z�X�\

	static LPDIRECT3DTEXTURE9 m_pTexTure;									// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;								// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;								// �C���f�b�N�X�ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;											// ���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;												// ���b�V���t�B�[���h�̈ʒu
	D3DXVECTOR3 m_Size;												// ���b�V���t�B�[���h�̑傫��
	D3DXVECTOR3 m_rot;												// ���b�V���t�B�[���h�̌���

};
#endif