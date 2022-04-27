//=============================================================================
//
// �J�b�g�C���̏��� [cutin.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _CUTIN_H_//endif�ƃZ�b�g�i�K����ԏ�
#define _CUTIN_H_

#include "scene.h"
#include"manager.h"

class CScene2D;

//*****************************************************************************
// �J�b�g�C���̃N���X
//*****************************************************************************
class CCutin : public CScene
{
public:
	//�J�b�g�C���̏��
	typedef enum
	{
		CUTIN_NONE = 0,																//�������ĂȂ����
		CUTIN_IN,																	//�J�b�g�C��(����)
		CUTIN_OUT,																	//�J�b�g�A�E�g(�o��)
		CUTIN_MAX
	} CUTIN;

	//�J�b�g�C���̏��
	typedef enum
	{
		CUTTYP_BG = 0,
		CUTTYP_ANIME,	
		CUTTYP_MAX
	} CUTTYP;

	CCutin(int nPriority = PRIORITY_FADE);											// �R���X�g���N�^
	~CCutin();																		// �f�X�g���N�^

	// �����o�֐�
	static CCutin *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size, CUTTYP CutTyp);	// �e�̐���
	static HRESULT Load(void);														// �e�N�X�`���̓ǂݍ���
	static void Unload(void);														// �e�N�X�`���̔j��
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);								// �J�b�g�C���̏������֐�
	void Uninit(void);																// �J�b�g�C���̏I���֐��@
	void Update(void);																// �J�b�g�C���̍X�V�֐�
	void Draw(void);																// �J�b�g�C���̕`��֐�

private:																			// �����������A�N�Z�X�\
	static LPDIRECT3DTEXTURE9 m_pTexture[CUTTYP_MAX];										// ���L����e�X�N�`���̃|�C���^
	CScene2D * m_apScene2D[CUTTYP_MAX];
	static CUTIN m_Cutin;															// �J�b�g�C���̏��
	static CUTTYP m_Cuttyp;
	static D3DXCOLOR m_col;															// �J�b�g�C���̐F
	static D3DXVECTOR3 m_move;
	static bool m_bCutMood;															// �J�b�g�C�����Ă邩�ǂ���

};
#endif // _FADE_H_//ifndef�ƃZ�b�g�i�K����ԉ�