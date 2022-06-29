//=============================================================================
//
// �S�[������ [goal.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _GOAL_H_
#define _GOAL_H_

#include "model_single.h"
#include"texture.h"

//*****************************************************************************
// �S�[���N���X
//*****************************************************************************
class CGoal : public CModel_Single
{
public:
	CGoal(PRIORITY nPriority = PRIORITY_ITEM);					// �R���X�g���N�^
	~CGoal();														// �f�X�g���N�^
	static CGoal *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char*pFiledata);	// �|���S���̐���		
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char * pFiledata);			// �������֐�
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
	float m_fRadius;										// ���a

};
#endif // !_BILLBOARD_H_