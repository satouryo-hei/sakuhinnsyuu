//=============================================================================
//
// ���b�V���̋�̏��� [meshsky.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _MESHSKY_H_//endif�ƃZ�b�g�i�K����ԏ�
#define _MESHSKY_H_

#include"scene.h"

//*****************************************************************************
// ���b�V���̋�N���X
//*****************************************************************************
class CMeshSky : public CScene
{
public:																									// �N�ł��A�N�Z�X�\

	CMeshSky(PRIORITY Priority = PRIORITY_NOMAL);														// �R���X�g���N�^
	~CMeshSky();																						// �f�X�g���N�^
																										// �����o�֐�
	static CMeshSky *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, int meshX, int meshY);	// ���b�V���̋�̐���	
	HRESULT Init(D3DXVECTOR3 pos);																		// ���b�V���̋�̃f�t�H���g�������֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, int meshX, int meshY);								// ���b�V���̋�̏������֐�
	void Uninit(void);																					// ���b�V���̋�̏I���֐�
	void Update(void);																					// ���b�V���̋�̍X�V�֐�
	void Draw(void);																					// ���b�V���̋�̕`��֐�
	void BindTextuer(int nTextuer);

private:																								// �����������A�N�Z�X�\

	static LPDIRECT3DTEXTURE9 m_pTexTure;																		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;																	// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;																	// �C���f�b�N�X�ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;																				// ���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;																					// ���b�V���̋�̈ʒu
	D3DXVECTOR3 m_Size;																					// ���b�V���̋�̑傫��
	D3DXVECTOR3 m_rot;																					// ���b�V���̋�̌���
	int m_nMeshX;																						// ���b�V����X
	int m_nMeshY;																						// ���b�V����Y
};																										
#endif