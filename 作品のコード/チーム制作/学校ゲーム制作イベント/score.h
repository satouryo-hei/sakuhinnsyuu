//=============================================================================
//
// �_���̏��� [score.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include"scene2D.h"

#define SCORE_TEXT "data/TEXT/score.txt"
#define NUMSCORE (8)

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CNumber;

//*****************************************************************************
// �_���N���X
//*****************************************************************************
class CScore : public CScene2D
{
public:																// �N�ł��A�N�Z�X�\
	CScore(PRIORITY nPriority = PRIORITY_UI);							// �R���X�g���N�^
	~CScore();														// �f�X�g���N�^
																	// �����o�֐�
	static CScore *Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size);		// �_���̐���
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);				// �_���̏������֐�
	void Uninit(void);												// �_���̏I���֐�
	void Update(void);												// �_���̍X�V�֐�
	void Draw(void);												// �_���̕`��֐�
	void SetScore(int nScore);										// �_���̔z�u�֐�
	void AddScore(int nValue);										// �_���̌v�Z�֐�
	static int GetScore(void) { return m_nScore; }							// �_���̎擾�֐�
	static int LodeScore(void);

private:															// �����������A�N�Z�X�\
	inline void SaveScore(void);									// �_���̏������݊֐�
	CNumber* m_apNumber[NUMSCORE];											// �i���o�[�̃|�C���^�[
	static int m_nScore;													// �_��

};
#endif