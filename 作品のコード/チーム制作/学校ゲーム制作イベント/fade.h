//=============================================================================
//
// �t�F�[�h�̏��� [fade.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _FADE_H_//endif�ƃZ�b�g�i�K����ԏ�
#define _FADE_H_

#include "scene2D.h"
#include"manager.h"
//*****************************************************************************
// �O���錾
//*****************************************************************************
class CBg;

//*****************************************************************************
// �t�F�[�h�̃N���X
//*****************************************************************************
class CFade : public CScene2D
{
public:
	//�t�F�[�h�̏��
	typedef enum
	{
		FADE_NONE = 0,																//�������ĂȂ����
		FADE_IN,																	//�t�F�[�h�C��(���邭)
		FADE_OUT,																	//�t�F�[�h�A�E�g(�Â�)
		FADE_MAX
	} FADE;

	CFade(PRIORITY Priority = PRIORITY_FADE);														// �R���X�g���N�^
	~CFade();																		// �f�X�g���N�^
	void BindTextuer(int nTextuer);												// �e�N�X�`���̐ݒ�
																					// �����o�֐�
	static CFade *Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size, CManager::MODE mode);	// �e�̐���
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);								// �t�F�[�h�̏������֐�
	void Uninit(void);																// �t�F�[�h�̏I���֐��@
	void Update(void);																// �t�F�[�h�̍X�V�֐�
	void Draw(void);																// �t�F�[�h�̕`��֐�
	static FADE GetFade(void) { return m_Fade; }									// �t�F�[�h�̎擾����
	static void SetFade(CManager::MODE modeNext);									// �t�F�[�h�̔z�u����
	// �X�e�[�W�t�F�[�h�ǉ��H

private:																			// �����������A�N�Z�X�\
	static LPDIRECT3DTEXTURE9 m_pTexture;											// ���L����e�X�N�`���̃|�C���^
	static FADE m_Fade;																// �t�F�[�h�̏��
	static D3DXCOLOR m_col;															// �t�F�[�h�̐F
	static CManager::MODE m_ModeNext;												// ���̃��[�h
	static CBg *m_pBg;																// �w�i�̃|�C���^�[����
	int m_nRed;																		// ��
	int m_nGreen;																	// ��
	int m_nBlue;																	// ��
	int m_nAlpha;																	// �A���t�@

};
#endif // _FADE_H_//ifndef�ƃZ�b�g�i�K����ԉ�
