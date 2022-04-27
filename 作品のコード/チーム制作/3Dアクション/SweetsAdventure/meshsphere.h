#ifndef _MESHSPHERE_H_
#define _MESHSPHERE_H_
#include "scene3D.h"
#include "texture.h"

class CMeshSphere : public CScene
{
public:
	CMeshSphere(OBJTYPE nPriority = OBJTYPE_FIELD);
	~CMeshSphere();
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	static CMeshSphere *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNum_X, int nNum_Z,float fRadius,float fNor, CTexture::Type Tex);
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	void SetCol(D3DXCOLOR col) { m_col = col; }
	void SetMesh(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius, float tex_rotX);

private:
protected:
	D3DXVECTOR3 m_size;										//�|���S���T�C�Y
	D3DXCOLOR m_col;
	LPDIRECT3DINDEXBUFFER9  m_pIdxBuff;	//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9		m_pTexture = NULL;				//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;				//���_�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;

	int m_nMax_Vtx_X;		//���u���b�N�̐�
	int m_nMax_Vtx_Y;		//�c�u���b�N�̐�
	int m_nVtx_Num_Max;		//�S�̒��_�̐�
	int m_nIdx_Num_Max;		//�C���f�b�N�X�̐�
	int m_nPoly_Num_Max;		//�O�p�`�̃|���S���̐�
	float m_fHalfWidth;		//�����̃T�C�Y
	float m_fHalfDepth;		//�����̃T�C�Y
	float m_radius;    //���̔��a�B0.0�ȏ�
	float m_fNor;
	bool m_bCulling;
};


#endif // !_MESHSPHERE_H_

