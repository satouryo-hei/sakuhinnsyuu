//=============================================================================
//
// �|���S���ɂ��G�t�F�N�g�̏��� [polygoneffect.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _POLYGONEFFECT_H_
#define _POLYGONEFFECT_H_

#include"scene.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CPolygon;

//*****************************************************************************
// 2D�G�t�F�N�g�̃N���X
//*****************************************************************************
class CPolygonEffect : public CScene
{
public:																// �N�ł��A�N�Z�X�\
																	// �|���S���̎��
	typedef enum
	{
		POLYGON_BACK = 0,
		POLYGON_BEFORE,
		POLYGON_MAX
	} POLYGON;

	CPolygonEffect(PRIORITY Priority = PRIORITY_EFFECT);					// �R���X�g���N�^
	~CPolygonEffect();														// �f�X�g���N�^
	// �����o�֐�
	static CPolygonEffect *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size);		//  2D�G�t�F�N�g�̐���
	HRESULT Init(D3DXVECTOR3 pos);											//  2D�G�t�F�N�g�̏������֐�
	void Uninit(void);														//  2D�G�t�F�N�g�̏I���֐�
	void Update(void);														//  2D�G�t�F�N�g�̍X�V�֐�
	void Draw(void);														//  2D�G�t�F�N�g�̕`��֐�
	void SetColor(D3DXCOLOR Col, int nNum);									//
	void SetVtxBuffColor(D3DXCOLOR Col, int nNum, int nVtxBuff);			//
	void Setpos(D3DXVECTOR3 pos);											//

private:																	// �����������A�N�Z�X�\
	static CPolygon * m_pPolygon[POLYGON_MAX];								// �|���S���̔z��|�C���^�[�𐶐�
	D3DXVECTOR2 m_Size;														// �傫��	
};
#endif // !_EFFECT_H_