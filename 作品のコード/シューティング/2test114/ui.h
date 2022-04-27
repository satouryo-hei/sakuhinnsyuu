//=============================================================================
//
// ui�̏��� [player.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _UI_H_
#define _UI_H_

#include"scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SETUITEXT "data/TEXT/Setui.txt"

//*****************************************************************************
// �v���C���[�N���X
//*****************************************************************************
class CUi : public CScene
{
public:																// �N�ł��A�N�Z�X�\

	CUi(int nPriority = PRIORITY_PLAYER);										// �R���X�g���N�^
	~CUi();														// �f�X�g���N�^
				
	static CUi *Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size);							// �^�C�g�����S�̐���
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);				// �v���C���̏������֐�
	void Uninit(void);												// �v���C���̏I���֐�
	void Update(void);												// �v���C���̍X�V�֐�
	void Draw(void);												// �v���C���̕`��֐�
	

private:															// �����������A�N�Z�X�\
	inline void LodeUI(void);										// UI�̓ǂݍ��ݏ���
	int m_nNumUi;
	D3DXVECTOR3 m_LodePos[2];
	D3DXVECTOR2 m_LodeSize[2];
};
#endif
