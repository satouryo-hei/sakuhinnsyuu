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
	D3DXVECTOR3 m_size;										//ポリゴンサイズ
	D3DXCOLOR m_col;
	LPDIRECT3DINDEXBUFFER9  m_pIdxBuff;	//インデックスバッファへのポインタ
	LPDIRECT3DTEXTURE9		m_pTexture = NULL;				//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;				//頂点バッファへのポインタ
	D3DXMATRIX m_mtxWorld;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;

	int m_nMax_Vtx_X;		//横ブロックの数
	int m_nMax_Vtx_Y;		//縦ブロックの数
	int m_nVtx_Num_Max;		//全体頂点の数
	int m_nIdx_Num_Max;		//インデックスの数
	int m_nPoly_Num_Max;		//三角形のポリゴンの数
	float m_fHalfWidth;		//半分のサイズ
	float m_fHalfDepth;		//半分のサイズ
	float m_radius;    //球の半径。0.0以上
	float m_fNor;
	bool m_bCulling;
};


#endif // !_MESHSPHERE_H_

