#ifndef _DELETEITEM_H
#define _DELETEITEM_H
#include "scene.h"
#include "texture.h"
#define DELETEITEM_CNT_LIMIT (20)
#define DELETEITEM_POINT (20)

class CDeleteItem
{
public:
	CDeleteItem();
	~CDeleteItem();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void ItemSuction(void);								//�A�C�e���������񂹂���֐�
	void SetTex(D3DXVECTOR2 tex, D3DXVECTOR2 tex1, D3DXVECTOR2 tex2, D3DXVECTOR2 tex3);
	void SetCol(D3DXCOLOR col);							//�J���[��ς���
	void SetScale(D3DXVECTOR3 scale) { m_Scale = scale; }
	void SetPos(D3DXVECTOR3 pos);						//�J���[��ς���
	D3DXVECTOR3 GetPos(void) { return m_pos; }			//�ʒu�̎擾
	D3DXVECTOR3 GetScale(void) { return m_Scale; }		//�傫���̎擾
	static CDeleteItem *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, CTexture::Type type = CTexture::Text, float fAngle = 0.0f);//�C���X�^���X��������
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;			//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3					m_Scale;				//�傫��
	D3DXVECTOR3					m_pos;					//��̈ʒu
	CTexture::Type				m_Type;					//�\������e�N�X�`���̃^�C�v
	int							m_nTimer;				//�^�C�}�[
	float						m_fAngle;				//�p�x
	float						m_fSpeed;				//�����񂹂��鑬�x
	float						m_fSucRadius;			//�����񂹂͈̔�
	bool						m_bDoSuction;			//�����񂹏�Ԃ�
	bool						m_bUninit;				//��������
};


#endif // !_DELETEITEM_H

