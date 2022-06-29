//=============================================================================
//
// �r���{�[�h���� [billboard.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "scene.h"
#include"texture.h"

//*****************************************************************************
// �r���{�[�h�N���X
//*****************************************************************************
class CBillboard : public CScene
{
public:
	CBillboard(PRIORITY nPriority = PRIORITY_BILLBOARD);									// �R���X�g���N�^
	~CBillboard();																			// �f�X�g���N�^
	static CBillboard *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size);							// �|���S���̐���	
	HRESULT Init(D3DXVECTOR3 pos);															// �f�t�H���g�������֐�
	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 size);								// �������֐�
	virtual void Uninit();																	// �I���֐�
	virtual void Update();																	// �X�V�֐�
	virtual void Draw();																	// �`��֐�
	void BindTextuer(int type);																// �e�N�X�`���̐ݒ�
	void SetPosSize(D3DXVECTOR3 pos, D3DXVECTOR2 size);										// ���_���ݒ�
	void SetColor(D3DXCOLOR col);															// �F(1.0f)�̐ݒ菈��
	void SetColor(int nRad, int nGreen, int nBlue, int nAlpha);								// �F(255)�̐ݒ菈��
	void SetTexAnime(int nPatternAnim, float fSizeAnimU, float fSizeMinV, float fSizeMaxV);	// �e�N�X�`���̃A�j���[�V�����ݒ菈��
	D3DXVECTOR3 GetPos() { return m_pos; }
	D3DXVECTOR2 GetSize(){ return m_size; }
protected:																				// �����Ɣh���n�̂݃A�N�Z�X�\

private:
	LPDIRECT3DTEXTURE9	m_pTexture = NULL;					// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;				// ���_�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;									// ���[���h�}�g���b�N�X	
	D3DXVECTOR3 m_pos;										// �ʒu
	D3DXVECTOR2 m_size;										// �傫��
	D3DXCOLOR m_col;										// �F
	int m_nRad;												// ��
	int m_nGreen;											// ��
	int m_nBlue;											// ��
	int m_nAlpha;											// �����x

};
#endif // !_BILLBOARD_H_