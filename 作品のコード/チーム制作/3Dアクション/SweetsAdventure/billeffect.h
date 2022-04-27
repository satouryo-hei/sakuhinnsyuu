#ifndef _BILLEFFECT_H_
#define _BILLEFFECT_H_
#include "main.h"
#include "scene.h"
#include "texture.h"

class CBilleffect : public CScene
{
public:
	CBilleffect(OBJTYPE nPriority = OBJTYPE_NONE);
	~CBilleffect();
	static CBilleffect *Create(D3DXVECTOR3 size);
	HRESULT Init(CTexture::Type type = CTexture::Effect);
	HRESULT Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();
	void BindTexture(CTexture::Type type);			//�摜�̐ݒ�
	void Setposition(D3DXVECTOR3 pos, D3DXVECTOR3 scale);//���_���ݒ�
	void SetColor(D3DXCOLOR col);

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