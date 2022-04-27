//=============================================================================
//
// Polygon����
// Author : �V���K�G & ������
//
//=============================================================================
#ifndef _POLYGON_H_
#define _POLYGON_H_

#include "scene2D.h"
class CTexture;

class CPolygon : public CScene2D
{

public:

	CPolygon(OBJTYPE nPriority = OBJTYPE_POLYGON);		//�R���X�g���N�^
	~CPolygon();									//�f�X�g���N�^

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CPolygon *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, CTexture::Type texture);
	void SetPos(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPos(void) { return m_Pos; }
	D3DXVECTOR3 GetScale(void) { return m_Scale; }
private:
	D3DXVECTOR3 m_Pos;
	D3DXVECTOR3 m_Scale;
	CTexture::Type m_Tex;
};

#endif // _POLYGON_H_
