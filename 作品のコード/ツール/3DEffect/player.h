//=============================================================================
//
// �v���C���[�̏��� [player.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _PLATER_H_
#define _PLATER_H_

#include"scene2D.h"

//*****************************************************************************
// �I�u�W�F�N�g�N���X
//*****************************************************************************
class CPlayer : public CScene2D
{
public:																// �N�ł��A�N�Z�X�\
	CPlayer(PRIORITY Priority = PRIORITY_NOMAL);														// �R���X�g���N�^
	~CPlayer();														// �f�X�g���N�^
	// �����o�֐�
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 Size);		// �|���S���̐���
	static HRESULT Load(void);										// �e�N�X�`���̓ǂݍ���
	static void Unload(void);										// �e�N�X�`���̔j��
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 Size);				// �|���S���̏������֐�
	void Uninit(void);												// �|���S���̏I���֐�
	void Update(void);												// �|���S���̍X�V�֐�
	void Draw(void);												// �|���S���̕`��֐�

	void SetUse(bool bUse) { m_bUse = bUse; }

private:															// �����������A�N�Z�X�\
	int m_Life;														//�̗�
	float m_fSpeed;													//���΂₳
	float m_fUpSpeed;												//�����x
	const float m_fSpeedMax;										//���΂₳�̍ő�l																	
	static LPDIRECT3DTEXTURE9 m_pTexture;

	bool m_bUse;

};
#endif
