//=============================================================================
//
// �����̃|���S���̏��� [polygon.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _POLYGON_H_
#define _POLYGON_H_

#include"scene.h"

class CScene2D; //�O���錾
class CManager;

//*****************************************************************************
// �����̃|���S���N���X
//*****************************************************************************
class CPolygon : public CScene
{
public:																			// �N�ł��A�N�Z�X�\
	typedef enum
	{
		SETTEX_PLAYER = 0,
		SETTEX_KAKERU,
		SETTEX_MAX
	} SETTEX;

	CPolygon(int nPriority = PRIORITY_UI);												// �R���X�g���N�^
	~CPolygon();																// �f�X�g���N�^
																				// �����o�֐�
	static CPolygon *Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size, int SetTex);		// �|���S���̐���
	static HRESULT Load(void);													// �e�N�X�`���̓ǂݍ���
	static void Unload(void);													// �e�N�X�`���̔j��
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);							// �|���S���̏������֐�
	void Uninit(void);															// �|���S���̏I���֐�
	void Update(void);															// �|���S���̍X�V�֐�
	void Draw(void);															// �|���S���̕`��֐�
	void SetTex(int SetTex);													// �e�N�X�`���̔z�u�֐�

private:																		// �����������A�N�Z�X�\
	static LPDIRECT3DTEXTURE9 m_pTexture[SETTEX_MAX];							// ���L����e�X�N�`���̃|�C���^
	static SETTEX m_SetTex;														// �ǂ̃e�N�X�`�����Ăяo����
	CScene2D * m_apScene2D[SETTEX_MAX];											// �I�u�W�F�N�g�N���X�̃|�C���^
	D3DXVECTOR2 m_Size;
};
#endif