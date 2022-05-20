//=============================================================================
//
// ���[�h�̑I������ [select_mode.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _SELECT_MODE_H_
#define _SELECT_MODE_H_

#include"scene.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CPolygon;

//*****************************************************************************
// ���[�h�̑I���N���X
//*****************************************************************************
class CSelect_Mode : public CScene
{
public:																// �N�ł��A�N�Z�X�\
		
	// ���[�h�̑I�����
	typedef enum
	{
		SELECT_TUTORIAL = 0,
		SELECT_GAME,
		SELECT_RESULT,
		SELECT_MAX
	} SELECT;

	CSelect_Mode(PRIORITY Priority = PRIORITY_NOMAL);				// �R���X�g���N�^
	~CSelect_Mode();												// �f�X�g���N�^
																	// �����o�֐�
	static CSelect_Mode *Create(D3DXVECTOR3 pos);					// ���[�h�̑I���̐���
	HRESULT Init(D3DXVECTOR3 pos);									// ���[�h�̑I���̏������֐�
	void Uninit(void);												// ���[�h�̑I���̏I���֐�
	void Update(void);												// ���[�h�̑I���̍X�V�֐�
	void Draw(void);												// ���[�h�̑I���̕`��֐�

	void SetUse(bool bUse) { m_bUse = bUse; }						// �g���Ă��邩�ǂ����̐ݒ菈��

private:															// �����������A�N�Z�X�\
	static LPDIRECT3DTEXTURE9 m_pTexture;							// �e�N�X�`���̃|�C���^�[�𐶐�
	CPolygon * m_pPolygon[SELECT_MAX];								// �|���S���̔z��|�C���^�[�𐶐�
	bool m_bUse;													// �g���Ă��邩�ǂ���
	int m_nt;
};
#endif