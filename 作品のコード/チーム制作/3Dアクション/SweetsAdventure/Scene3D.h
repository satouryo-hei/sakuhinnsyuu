//----------------------------------
//�|���S���̏���
//----------------------------------
#ifndef _SCENE3D_H
#define _SCENE3D_H
#include "main.h"
#include "scene.h"
#include "texture.h"

//�}�N����`
#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)


//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;//���_���W
	D3DXVECTOR3 nor;//�@���x�N�g��
	D3DCOLOR	col;//���_�J���[
	D3DXVECTOR2 tex;//�e�N�X�`�����W
} VERTEX_3D;
//------------------------------------------------------------------------------
//�N���X�̒�`
//------------------------------------------------------------------------------
class CScene3D : public CScene
{
public:
	CScene3D(OBJTYPE nPriority = OBJTYPE_NONE);
	~CScene3D();
	HRESULT Init(CTexture::Type type= CTexture::Text);
	HRESULT Init(void);

	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 scale);		//���_���W�̐ݒ�
	void BindTexture(CTexture::Type type);
	void SetTex(int nAnim, int nPartU);						//�e�N�X�`���̐ݒ�
	void SetTex(float fSpeedX, float fSpeedY);				//�e�N�X�`���̐ݒ�
	void SetCol(D3DXCOLOR col);								//�e�N�X�`���̐ݒ�
	static CScene3D *Create(D3DXVECTOR3 size);

private:

protected:

	LPDIRECT3DTEXTURE9		m_pTexture = NULL;				//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;				//���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DDEVICE9 m_pDevice = NULL;//�f�o�C�X�̃|�C���^

	D3DXMATRIX m_mtxWorld;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_size;

};


#endif // !_SCENE3D_H
