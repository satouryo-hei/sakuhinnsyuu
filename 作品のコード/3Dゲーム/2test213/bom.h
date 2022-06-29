//=============================================================================
//
// �A�C�e������ [item.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _BOM_H_
#define _BOM_H_

#include "model_single.h"
#include"texture.h"

//*****************************************************************************
// �A�C�e���N���X
//*****************************************************************************
class CBom : public CModel_Single
{
public:
	CBom(PRIORITY nPriority = PRIORITY_ITEM);					// �R���X�g���N�^
	~CBom();														// �f�X�g���N�^
	static CBom *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char*Filedata);	// �|���S���̐���		
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char * Filedata);			// �������֐�
	void Uninit();																	// �I���֐�
	void Update();																	// �X�V�֐�
	void Draw();																	// �`��֐�

private:
	LPDIRECT3DTEXTURE9	m_pTexture = NULL;					// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;				// ���_�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;									// ���[���h�}�g���b�N�X	
	D3DXMATRIX m_mtxView;									// �r���[�}�g���b�N�X
	D3DXVECTOR3 m_pos;										// �ʒu
	D3DXVECTOR3 m_rot;										// ����
	D3DXVECTOR3 m_size;										// �傫��
	int m_nLife;											// �̗�
	float m_fRadius;
	bool m_bUse;
};
#endif // !_BILLBOARD_H_