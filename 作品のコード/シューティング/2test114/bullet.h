//=============================================================================
//
// �e�̏��� [bullet.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include"scene2D.h"

//*****************************************************************************
// �e�̃N���X
//*****************************************************************************
class CBullet : public CScene2D
{
public:																									// �N�ł��A�N�Z�X�\
	CBullet(int nPriority = PRIORITY_BULLET);															// �R���X�g���N�^
	~CBullet();																							// �f�X�g���N�^
	// �����o�֐�
	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move,D3DXVECTOR2 Size,CScene::OBJTYPE ObjType);	// �e�̐���
	static HRESULT Load(void);																			// �e�N�X�`���̓ǂݍ���
	static void Unload(void);																			// �e�N�X�`���̔j��
	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size);									// �e�̏������֐�
	virtual void Uninit(void);																					// �e�̏I���֐�
	void Update(void);																					// �e�̍X�V�֐�
	virtual void Draw(void);																					// �e�̕`��֐�


private:																								// �����������A�N�Z�X�\	
	static LPDIRECT3DTEXTURE9 m_pTexture;																// ���L����e�X�N�`���̃|�C���^
	D3DXVECTOR3 m_Move;																					// �e�̈ړ���
	D3DXVECTOR2 m_Size;																					// �e�̑傫��
	const float m_fSpeedMax;																			// ���΂₳�̍ő�l
	int m_nLife;																						// �e�̎���
	int m_nPriority;
	static CScene::OBJTYPE m_ObjType;
};
#endif
