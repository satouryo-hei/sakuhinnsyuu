//=============================================================================
//
// �e�̏��� [bullet.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _HOMING_H_
#define _HOMING_H_

#include"scene2D.h"

//*****************************************************************************
// �e�̃N���X
//*****************************************************************************
class CHoming : public CScene2D
{
public:																															// �N�ł��A�N�Z�X�\
	CHoming(int nPriority = PRIORITY_SECOND);																					// �R���X�g���N�^
	~CHoming();																													// �f�X�g���N�^
																																// �����o�֐�
	static CHoming *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size, D3DXVECTOR2 lastPoint,int nAttack);				// �e�̐���
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);																			// �e�̏������֐�
	void Uninit(void);																											// �e�̏I���֐�
	void Update(void);																											// �e�̍X�V�֐�
	void Draw(void);																											// �e�̕`��֐�
	bool GetUse(void) { return m_bUse; }
	void SetUse(bool bUse) { m_bUse = bUse; }
	D3DXVECTOR3 SetCurve();//(BezierCurve)�x�W�F�Ȑ�																			// �e�̃x�W�F�Ȑ��̌v�Z�֐�
private:																														// �����������A�N�Z�X�\	

	typedef struct
	{		
		int nCounter;//�x�W�F�Ȑ��p	
		int nDivNum;//�x�W�F�Ȑ��p
		double dPoint0[2];// �n�_
		double dPoint1[2];// ����_
		double dPoint2[2];// ����_		
		double dPoint3[2];// �I�_				
	}homing;

	homing m_Homing;

	static LPDIRECT3DTEXTURE9 m_pTexture;										// ���L����e�X�N�`���̃|�C���^
	bool m_bUse;															// �g���Ă��邩�ǂ���
	D3DXVECTOR3 m_Pos;															// �e�̌��ݒn
	D3DXVECTOR3 m_Move;															// �e�̈ړ���
	D3DXVECTOR2 m_Size;															// �e�̑傫��
	int m_nPriority;															// �`�揇
	int m_nLife;																// �e�̗̑�
	int m_nAttack;																// �e�̍U��
};
#endif