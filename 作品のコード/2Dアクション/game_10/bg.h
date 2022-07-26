//=============================================================================
//
// �w�i�̏��� [bg.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _BG_H_
#define _BG_H_

#include"scene.h"
//*****************************************************************************
// �O���錾
//*****************************************************************************
class CScene2D; //�O���錾
//*****************************************************************************
// �w�i�̃N���X
//*****************************************************************************
class CBg : public CScene
{
public:																				// �N�ł��A�N�Z�X�\
	CBg(int nPriority);																// �R���X�g���N�^
	~CBg();																			// �f�X�g���N�^
	// �����o�֐�
	static CBg *Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size, int nTex);				// �w�i�̐���
	HRESULT Init(D3DXVECTOR3 pos);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size, int nTex);						// �w�i�̏������֐�
	void Uninit(void);																// �w�i�̏I���֐�
	void Update(void);																// �w�i�̍X�V�֐�
	void Draw(void);																// �w�i�̕`��֐�

private:																			// �����������A�N�Z�X�\		
	CScene2D * m_apScene2D;															// �I�u�W�F�N�g�N���X�̃|�C���^
};
#endif