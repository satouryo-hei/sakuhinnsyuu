//=============================================================================
//
// �������̏��� [effect.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _EXPLANATION_H_
#define _EXPLANATION_H_

#include"scene.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CPolygon;

//*****************************************************************************
// �������̃N���X
//*****************************************************************************
class CExplanation : public CScene
{
public:																// �N�ł��A�N�Z�X�\
	// �������̎��
	typedef enum
	{
		EXPLANATION_SPEECH_BUBBLE = 0,
		EXPLANATION_LETTER_TITLE,
		EXPLANATION_LETTER_TUTORIAL,
		EXPLANATION_LETTER_GAME,
		EXPLANATION_LETTER_RESULT,
		EXPLANATION_MAX
	} EXPLANATION;

	CExplanation(PRIORITY Priority = PRIORITY_EFFECT);		// �R���X�g���N�^
	~CExplanation();										// �f�X�g���N�^
															// �����o�֐�
	static CExplanation *Create(D3DXVECTOR3 pos,int nTex);	//  �������̐���
	HRESULT Init(D3DXVECTOR3 pos);							//  �������̏������֐�
	void Uninit(void);										//  �������̏I���֐�
	void Update(void);										//  �������̍X�V�֐�
	void Draw(void);										//  �������̕`��֐�
	void SetSize(D3DXVECTOR2 Size,int nNum);
	void SetColor(D3DXCOLOR Col, int nNum);

private:													// �����������A�N�Z�X�\
	static CPolygon * m_pPolygon[EXPLANATION_MAX];			// �|���S���̔z��|�C���^�[�𐶐�
	D3DXVECTOR2 m_Size;										// �傫��
	D3DXCOLOR m_Col;										// �F
	int m_nTex;
};
#endif // !_EFFECT_H_