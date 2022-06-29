//=============================================================================
//
// �A�C�e������ [item.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

#include "model_single.h"
#include"texture.h"

//*****************************************************************************
// �A�C�e���N���X
//*****************************************************************************
class CItem : public CModel_Single
{
public:
	CItem(PRIORITY nPriority = PRIORITY_ITEM);					// �R���X�g���N�^
	~CItem();														// �f�X�g���N�^
	static CItem *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char*Filedata);	// �|���S���̐���		
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot,const char * Filedata);			// �������֐�
	void Uninit();																	// �I���֐�
	void Update();																	// �X�V�֐�
	void Draw();																	// �`��֐�
	bool GetUse() { return m_bUse; }

private:
	LPDIRECT3DTEXTURE9	m_pTexture = NULL;					// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;				// ���_�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;									// ���[���h�}�g���b�N�X	
	D3DXMATRIX m_mtxView;									// �r���[�}�g���b�N�X
	D3DXVECTOR3 m_pos;										// �ʒu
	D3DXVECTOR3 m_rot;										// ����
	D3DXVECTOR3 m_size;										// �傫��
	bool m_bUse;											// �傫��

};
#endif // !_BILLBOARD_H_