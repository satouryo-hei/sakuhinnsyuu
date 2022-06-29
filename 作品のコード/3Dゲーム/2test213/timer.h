//=============================================================================
//
// ���Ԃ̏��� [timer.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _TIMERE_H_
#define _TIMERE_H_

#define TIMETEXT "data/TEXT/time.txt"
#define MAX_TIME (3)

#include"scene2D.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CNumber;
class CPolygon;

//*****************************************************************************
// ���Ԃ̃N���X
//*****************************************************************************
class CTimer : public CScene2D
{
public:																// �N�ł��A�N�Z�X�\
	CTimer(int nPriority = PRIORITY_UI);							// �R���X�g���N�^
	~CTimer();														// �f�X�g���N�^
																	// �����o�֐�
	static CTimer *Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size);		// ���Ԃ̐���
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);				// ���Ԃ̏������֐�
	void Uninit(void);												// ���Ԃ̏I���֐�
	void Update(void);												// ���Ԃ̍X�V�֐�
	void Draw(void);												// ���Ԃ̕`��֐�
	void SetTimer(int nTimer);										// ���Ԃ̔z�u�֐�
	static int GetTimer(void) { return m_nTimer; }					// ���Ԃ̎擾�֐�
	static void SeveTimer(int nTime);
	static int LodeTimer(void);

private:															// �����������A�N�Z�X�\
	CNumber* m_apNumber[MAX_TIME];									// �i���o�[�̃|�C���^�[
	static CPolygon * m_apPolygon;									// �|���S���̃|�C���^�[
	static int m_nTimer;											// ����
	int m_nCntTimer;												// ���Ԃ𐔂���

};
#endif
