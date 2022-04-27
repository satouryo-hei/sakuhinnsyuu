//=============================================================================
//
// �|���S���̏��� [polygon.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _POLYGON_H_
#define _POLYGON_H_

#include"scene2D.h"

//*****************************************************************************
// �����̃|���S���N���X
//*****************************************************************************
class CPolygon : public CScene2D
{
public:																			// �N�ł��A�N�Z�X�\
																				// �|���S���̎��
	typedef enum
	{
		POLYGON_TYPE_FIRST = 0,
		POLYGON_TYPE_SECOND,
		POLYGON_TYPE_THIRD,
		POLYGON_TYPE_MAX
	} POLYGON_TYPE;

	CPolygon();													// �R���X�g���N�^
	~CPolygon();												// �f�X�g���N�^
																// �����o�֐�
	static CPolygon *Create(D3DXVECTOR3 pos, D3DXVECTOR3 Size);	// �|���S���̐���
	static HRESULT Load(void);									// �e�N�X�`���̓ǂݍ���
	static void Unload(void);									// �e�N�X�`���̔j��
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 Size);			// �|���S���̏������֐�
	void Uninit(void);											// �|���S���̏I���֐�
	void Update(void);											// �|���S���̍X�V�֐�
	void Draw(void);											// �|���S���̕`��֐�

private:														// �����������A�N�Z�X�\
	static LPDIRECT3DTEXTURE9 m_pTexture[POLYGON_TYPE_MAX];		// ���L����e�X�N�`���̃|�C���^
	D3DXVECTOR3 m_Size;
	D3DXCOLOR m_col;
	POLYGON_TYPE m_Porigon_Type;								// �|���S���̎��
	CPolygon*m_pPorigon;
	int m_nNumPorigon;											// �|���S���̔ԍ�
};
#endif