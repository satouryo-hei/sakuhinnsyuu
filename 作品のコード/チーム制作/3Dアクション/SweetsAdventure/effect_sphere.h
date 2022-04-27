#ifndef _EFFECTSPFERE_H_
#define _EFFECTSPFERE_H_
#include "scene3D.h"
#include "texture.h"

class CEffectSphere : public CScene3D
{
public:
	CEffectSphere(OBJTYPE nPriority = OBJTYPE_EFFECT);
	~CEffectSphere();
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	static CEffectSphere *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNum_X, int nNum_Z, float fRadius, float fNor, CTexture::Type Tex);
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	void SetCol(D3DXCOLOR col) { m_col = col; }
	void SetMesh(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius,float tex_rotX);
private:
	D3DXVECTOR3 m_size;										//�|���S���T�C�Y
	D3DXCOLOR m_col;
	LPDIRECT3DINDEXBUFFER9  m_pIdxBuffWall;	//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	int m_nMax_Vtx_X;		//���u���b�N�̐�
	int m_nMax_Vtx_Y;		//�c�u���b�N�̐�
	int m_nVtx_Num_Max;		//�S�̒��_�̐�
	int m_nIdx_Num_Max;		//�C���f�b�N�X�̐�
	int m_nPoly_Num_Max;		//�O�p�`�̃|���S���̐�
	float m_fHalfWidth;		//�����̃T�C�Y
	float m_fHalfDepth;		//�����̃T�C�Y
	float m_radius;    //���̔��a�B0.0�ȏ�
	float m_fNor;
	bool m_bUninit;
};


#endif // !_EFFECTSPFERE_H_

