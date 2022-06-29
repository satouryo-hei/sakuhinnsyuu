//=============================================================================
//
// �P�̂̃��f������ [model_single.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _MODEL_SINGLE_H_//endif�ƃZ�b�g�i�K����ԏ�
#define _MODEL_SINGLE_H_

#include"scene.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CModel;

//*****************************************************************************
// �P�̂̃��f���N���X
//*****************************************************************************
class CModel_Single : public CScene
{
public:																							// �N�ł��A�N�Z�X�\
	CModel_Single(PRIORITY Priority = PRIORITY_MODEL);											// �R���X�g���N�^
	~CModel_Single();																			// �f�X�g���N�^
	// �����o�֐�
	static CModel_Single *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char*pFiledata);		// �P�̂̃��f���̐���
	HRESULT Init(D3DXVECTOR3 pos);																// �P�̂̃��f���̃f�t�H���g�������֐�
	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char*pFiledata);				// �P�̂̃��f���̏������֐�
	virtual void Uninit(void);																	// �P�̂̃��f���̏I���֐�
	virtual void Update(void);																	// �P�̂̃��f���̍X�V�֐�
	virtual void Draw(void);																	// �P�̂̃��f���̕`��֐�
	void ReleaseSingle(void);																	// �P�̂̃��f���̉������
	void SetPos(D3DXVECTOR3 pos);																// �P�̂̃��f���̈ʒu�̐ݒ菈��
	void SetRot(D3DXVECTOR3 rot);																// �P�̂̃��f���̌����̐ݒ菈��

private:																						// �����������A�N�Z�X�\
	D3DXMATRIX m_mtxWorld;																		// ���[���h�}�g���b�N�X
	D3DXVECTOR3 m_Pos;																			// �P�̂̃��f���̈ړ���
	D3DXVECTOR3 m_Size;																			// �P�̂̃��f���̈ړ���
	D3DXVECTOR3 m_rot;																			// ����
	CModel * m_pModel;																			// ���f���̃|�C���^�[����
};
#endif // _POLYGON_H_//ifndef�ƃZ�b�g�i�K����ԉ�