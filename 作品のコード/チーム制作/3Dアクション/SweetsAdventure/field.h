#ifndef _FIELD_H_
#define _FIELD_H_
#include "scene3D.h"
#include "texture.h"
#define MAX_FIELD_VTX (4)
class CField : public CScene3D
{
public:
	typedef struct
	{
		D3DXVECTOR3 vtx, rot;
		D3DXMATRIX mtxWorld;							//���[���h�}�g���b�N�X
	}FieldVtx;//���f���̊e���_�̕ۑ��p�\����

	CField(OBJTYPE nPriority = OBJTYPE_FIELD);
	~CField();
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	static CField *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot,int nNum_X,int nNum_Z, CTexture::Type Tex);
	FieldVtx GetVtx(int nCnt) { return m_vtx[nCnt]; }
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	void SetMoveTex(float fSpeedX, float fSpeedY); 
	void SetCol(float fAlpha);

private:

	D3DXVECTOR3 m_size;										//�|���S���T�C�Y
	D3DXCOLOR m_col;
	LPDIRECT3DINDEXBUFFER9  m_pIdxBuffWall;	//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	FieldVtx				m_vtx[MAX_FIELD_VTX];			//�e���_�̏��i�[�\����
	D3DXVECTOR3				m_vtxMin, m_vtxMax;				//���f���̍ŏ��l�A�ő�l
	float m_MoveTexX, m_MoveTexZ;
	int m_nMax_Vtx_X;		//���u���b�N�̐�
	int m_nMax_Vtx_Z;		//�c�u���b�N�̐�
	int m_nVtx_Num_Max;		//�S�̒��_�̐�
	int m_nIdx_Num_Max;		//�C���f�b�N�X�̐�
	int m_nPoly_Num_Max;		//�O�p�`�̃|���S���̐�
	float m_fHalfWidth;		//�����̃T�C�Y
	float m_fHalfDepth;		//�����̃T�C�Y
};


#endif // !_FIELD_H_

