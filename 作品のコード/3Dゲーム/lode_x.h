//=============================================================================
//
// X���f���ǂݍ��ݏ��� [lode_x.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _LODE_X_H_
#define _LODE_X_H_

#define PLAYER_TEXT "data/TEXT/Player.txt"

#include"main.h"

//*****************************************************************************
// �I�u�W�F�N�g�N���X
//*****************************************************************************
class CLode_X
{
public:															// �N�ł��A�N�Z�X�\

	//// x�t�@�C���̎��
	//typedef enum 
	//{
	//	XTYPE_NOME = 0,
	//	XTYPE_NOME,
	//	XTYPE_NOME,
	//	XTYPE_MAX
	//} XTYPE;

	CLode_X();													// �R���X�g���N�^
	~CLode_X();												// �f�X�g���N�^
																// �����o�֐�
	HRESULT Init(void);											// �e�N�X�`���̏������֐�
	void Uninit(void);											// �e�N�X�`���̏I���֐�

private:														// �����������A�N�Z�X�\
	inline void Lode(void);										// 
	static int m_nMaxTex;										// �e�N�X�`���̍ő吔
	LPD3DXBUFFER m_pBuffMat;																// �}�e���A���i�ގ����j�ւ̃|�C���^
	DWORD m_nNumMat;																		// �}�e���A���̐�
	LPD3DXMESH m_pMesh;																		// ���b�V���i���_���j�ւ̃|�C���^
};
#endif