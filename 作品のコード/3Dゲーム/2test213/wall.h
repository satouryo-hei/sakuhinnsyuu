//=============================================================================
//
// �ǂ̏��� [wall.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _WALL_H_//endif�ƃZ�b�g�i�K����ԏ�
#define _WALL_H_

#include"scene3D.h"
//*****************************************************************************
// �ǂ̃N���X
//*****************************************************************************
class CWall : public CScene3D
{
public:																			// �N�ł��A�N�Z�X�\
	CWall(PRIORITY Priority = PRIORITY_NOMAL);									// �R���X�g���N�^
	~CWall();																	// �f�X�g���N�^
																				// �����o�֐�
	static CWall *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 Rot);	// �ǂ̐���
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);							// �ǂ̏������֐�
	void Uninit(void);															// �ǂ̏I���֐�
	void Update(void);															// �ǂ̍X�V�֐�
	void Draw(void);															// �ǂ̕`��֐�
	void SetPositionWall(const D3DXVECTOR3 pos) { m_pos = pos; }				// �ǂ̈ʒu�̐ݒ�֐�
	D3DXVECTOR3 GetPositionShadow(void) { return m_pos; }						// �ǂ̈ʒu�̎擾�֐�

private:																		// �����������A�N�Z�X�\
	D3DXVECTOR3 m_pos;															// �|���S���ʒu
	D3DXVECTOR3 m_size;															// �|���S���ʒu
	D3DXVECTOR3 m_rot;															// �|���S���̌���
};
#endif // _POLYGON_H_//ifndef�ƃZ�b�g�i�K����ԉ�