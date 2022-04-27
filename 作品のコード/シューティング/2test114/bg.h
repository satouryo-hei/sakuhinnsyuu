//=============================================================================
//
// �w�i�̏��� [bg.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _BG_H_
#define _BG_H_

#include"scene.h"
class CScene2D; //�O���錾
class CManager;
//*****************************************************************************
// �w�i�̃N���X
//*****************************************************************************
class CBg : public CScene
{
public:																				// �N�ł��A�N�Z�X�\

	//�w�i�̎��
	typedef enum
	{
		TEX_TYP_TITLE = 0,
		TEX_TYP_GAME,
		TEX_TYP_RESULT,
		TEX_TYP_MAX
	} TEX_TYP;

	CBg(int nPriority);																// �R���X�g���N�^
	~CBg();																			// �f�X�g���N�^
																					// �����o�֐�
	static CBg *Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size);							// �w�i�̐���
	static HRESULT Load(void);														// �e�N�X�`���̓ǂݍ���
	static void Unload(void);														// �e�N�X�`���̔j��
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);								// �w�i�̏������֐�
	void Uninit(void);																// �w�i�̏I���֐�
	void Update(void);																// �w�i�̍X�V�֐�
	void Draw(void);																// �w�i�̕`��֐�
	float GetBgSpped(void) { return m_fPosTexU[0]; }

private:																			// �����������A�N�Z�X�\	
	static LPDIRECT3DTEXTURE9 m_pTexture[TEX_TYP_MAX];								// ���L����e�X�N�`���̃|�C���^
	CScene2D * m_apScene2D[TEX_TYP_MAX];											// �I�u�W�F�N�g�N���X�̃|�C���^
	float m_fPosTexU[TEX_TYP_MAX];													// �e�N�X�`����U�̍X�V
	float m_fPosTexV[TEX_TYP_MAX];													// �e�N�X�`����U�̍X�V

};
#endif