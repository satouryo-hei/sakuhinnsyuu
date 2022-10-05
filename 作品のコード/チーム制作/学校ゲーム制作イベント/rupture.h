//=============================================================================
//
// �e�̔j��̏��� [rupture.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _RUPTURE_H_
#define _RUPTURE_H_

#include"Scene.h"

#define MAX_BULLET (8)

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CBullet;
//*****************************************************************************
// �e�̔j��̃N���X
//*****************************************************************************
class CRupture : public CScene
{
public:																		// �N�ł��A�N�Z�X�\
	typedef enum
	{
		RUPTURE_TYPE_SCOND = 0,
		RUPTURE_TYPE_FOURTH,
		RUPTURE_TYPE_SIXTH,
		RUPTURE_TYPE_EIGHTH,
		RUPTURE_TYPE_LIMIT			//��ނ̍ő吔
	} RUPTURE_TYPE;

	CRupture(int Priority = PRIORITY_NOMAL);																// �R���X�g���N�^
	~CRupture();																// �f�X�g���N�^
																			// �����o�֐�
	static CRupture *Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size, int nNum);	// �e�̔j��̐���	
	HRESULT Init(D3DXVECTOR3 pos);											// �e�̔j��̏������֐�
	void Uninit(void);														// �e�̔j��̏I���֐�
	void Update(void);														// �e�̔j��̍X�V�֐�
	void Draw(void);														// �e�̔j��̕`��֐�	
	void SetRupture(int Type);												// �e�̔j��̐ݒ�֐�

private:																	// �����������A�N�Z�X�\
	typedef enum
	{
		BULLET_NUM_ZERO = 0,
		BULLET_NUM_FIRST,
		BULLET_NUM_SECOND,
		BULLET_NUM_THIRD,
		BULLET_NUM_FOURTH,
		BULLET_NUM_FIFTH,
		BULLET_NUM_SIXTH,
		BULLET_NUM_SEVEBNTH,
		BULLET_NUM_EIGHTH,
		BULLET_NUM_LIMIT			//��ނ̍ő吔
	} BULLET_NUM;


	static CBullet* m_pBullet[8];
	D3DXVECTOR3 m_Pos;
	D3DXVECTOR2 m_Size;
};
#endif