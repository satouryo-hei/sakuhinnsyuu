#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_
#include "main.h"
#include "scene.h"
#include "texture.h"

class CBillboard : public CScene
{
public:
	CBillboard(OBJTYPE nPriority = OBJTYPE_ITEM);
	~CBillboard();
	HRESULT Init(CTexture::Type type = CTexture::Text);
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	void BindTexture(CTexture::Type type);			//�摜�̐ݒ�
	void Setpos(D3DXVECTOR3 pos, D3DXVECTOR3 scale);//���_���ݒ�
	void SetColor(D3DXCOLOR col);
	static CBillboard *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CTexture::Type type);

private:
	LPDIRECT3DTEXTURE9		m_pTexture = NULL;				//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;				//���_�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;									//���[���h�}�g���b�N�X	
	D3DXMATRIX m_mtxView;									//�r���[�}�g���b�N�X
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_size;										//�|���S���T�C�Y
	D3DXCOLOR m_col;

};


#endif // !_BILLBOARD_H_

