//----------------------------------
//�|���S���̏���
//----------------------------------
#ifndef _SCENE2D_H
#define _SCENE2D_H
#include "main.h"
#include "scene.h"
#include "texture.h"

//�}�N����`
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)


//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;//���_���W
	float		rhw;//1.0f�ŌŒ�
	D3DCOLOR	col;//���_�J���[
	D3DXVECTOR2 tex;//�e�N�X�`�����W
} VERTEX_2D;
//------------------------------------------------------------------------------
//�N���X�̒�`
//------------------------------------------------------------------------------
class CScene2D : public CScene
{
public:
	CScene2D(OBJTYPE nPriority = OBJTYPE_NONE);
	~CScene2D();
	HRESULT Init(CTexture::Type type);
	HRESULT Init(void);

	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CScene2D *Create(D3DXVECTOR3 pos, float fSize, CTexture::Type texture=CTexture::Text);
	void SetScalePos(D3DXVECTOR3 pos, D3DXVECTOR3 scale);
	void SetPos(D3DXVECTOR3 vtx0, D3DXVECTOR3 vtx1, D3DXVECTOR3 vtx2, D3DXVECTOR3 vtx3);//���_���W�̐ݒ�
	void SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 scale);		//���_���W�̐ݒ�
	void BindTexture(CTexture::Type type);
	void SetTex(int nAnim,int nPartU);						//�e�N�X�`���̐ݒ�
	void SetTex(float fSpeedX, float fSpeedY);						//�e�N�X�`���̐ݒ�
	void SetTex(int nType, int nPattern, float fSize);
	void SetCol(D3DXCOLOR col);						//�e�N�X�`���̐ݒ�

private:

protected:

	LPDIRECT3DTEXTURE9		m_pTexture = NULL;				//�e�N�X�`���ւ̃|�C���^
	//VERTEX_2D				m_aVertex[4];					// ���_�����i�[����
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;				//���_�o�b�t�@�ւ̃|�C���^
	bool m_bUse;

};


#endif // !_SCENE2D_H
