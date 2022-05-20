//=============================================================================
//
// �G�t�F�N�g�̏��� [effect.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include"scene.h"
#define COLRUM (float(rand() % 256) - float(rand() % 256)) //�~�̃}�N��

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CPolygon;

//*****************************************************************************
// �Q�[���̑I���N���X
//*****************************************************************************
class CEffect : public CScene
{
public:																// �N�ł��A�N�Z�X�\
	// �|���S���̎��
	typedef enum
	{
		POLYGON_BACK = 0,
		POLYGON_BEFORE,
		POLYGON_MAX
	} POLYGON;

	// �|���S���̎��
	typedef enum
	{
		COLOR_R = 0,
		COLOR_G,
		COLOR_B,
		COLOR_A,
		COLOR_MAX
	} COLOR;

	CEffect(PRIORITY Priority = PRIORITY_EFFECT);					// �R���X�g���N�^
	~CEffect();														// �f�X�g���N�^
																	// �����o�֐�
	static CEffect *Create(D3DXVECTOR3 pos);						// �Q�[���̑I���̐���
	HRESULT Init(D3DXVECTOR3 pos);									// �Q�[���̑I���̏������֐�
	void Uninit(void);												// �Q�[���̑I���̏I���֐�
	void Update(void);												// �Q�[���̑I���̍X�V�֐�
	void Draw(void);												// �Q�[���̑I���̕`��֐�
	void SetColor(D3DXCOLOR Col,int nNum);
	void Setpos(D3DXVECTOR3 pos);

private:															// �����������A�N�Z�X�\
	static CPolygon * m_pPolygon[POLYGON_MAX];								// �|���S���̔z��|�C���^�[�𐶐�
	bool m_bUse;													// �g���Ă��邩�ǂ���
	D3DXVECTOR2 m_Size;												// �傫��
	D3DXCOLOR m_Col;												// �F
	int m_nCnt;
};
#endif // !_EFFECT_H_