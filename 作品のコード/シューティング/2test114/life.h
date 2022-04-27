//=============================================================================
//
// ���̏��� [life.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _LIFE_H_
#define _LIFE_H_

#include"scene.h"

class CNumber; // �O���錾
class CUi;

//*****************************************************************************
// ���̃N���X
//*****************************************************************************
class CLife : public CScene
{
public:																// �N�ł��A�N�Z�X�\
	CLife(int nPriority = PRIORITY_UI);														// �R���X�g���N�^
	~CLife();														// �f�X�g���N�^
																	// �����o�֐�
	static CLife *Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size);		// ���̐���
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);				// ���̏������֐�
	void Uninit(void);												// ���̏I���֐�
	void Update(void);												// ���̍X�V�֐�
	void Draw(void);												// ���̕`��֐�
	void SetLife(int nLife);										// ���̔z�u�֐�
	void AddLife(int nValue);										// ���̌v�Z�֐�
	int GetLife(void) { return m_nLife; }							// ���̎擾����

private:															// �����������A�N�Z�X�\
	CNumber* m_apNumber[2];											// �i���o�[�̃|�C���^�[
	CUi*  m_apUi;										// �|���S���̃|�C���^�[
	int m_nLife;													// �̗�
	
};
#endif
