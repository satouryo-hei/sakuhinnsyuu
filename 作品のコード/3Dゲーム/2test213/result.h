//=============================================================================
//
// ���U���g�̏��� [result.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "scene.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CBg;
class CRanking;

//*****************************************************************************
// ���U���g�̃N���X
//*****************************************************************************
class CResult : public CScene
{
public:
	CResult(int nPriority = PRIORITY_NOMAL);									// �R���X�g���N�^
	~CResult();																	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(D3DXVECTOR3 pos);												// ���U���g�̏������֐�
	void Uninit(void);															// ���U���g�̏I���֐��@
	void Update(void);															// ���U���g�̍X�V�֐�
	void Draw(void);															// ���U���g�̕`��֐�


private:																		// �����������A�N�Z�X�\
	static LPDIRECT3DTEXTURE9 m_pTexture;										// ���L����e�X�N�`���̃|�C���^
	static CBg * m_pBg;															// �w�i�N���X�̃|�C���^
	static CRanking * m_pRanking;												// �����L���O�N���X�̃|�C���^
	bool m_bFade;																// �t�F�[�h�����������ǂ���
};

#endif