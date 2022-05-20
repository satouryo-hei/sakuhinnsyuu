//=============================================================================
//
// �Q�[���̑I������ [choose_game.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _CHOOSE_GAME_H_
#define _CHOOSE_GAME_H_

#include"scene.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CPolygon;
class CEffect;

//*****************************************************************************
// �Q�[���̑I���N���X
//*****************************************************************************
class CChoose_Game : public CScene
{
public:																// �N�ł��A�N�Z�X�\
	// �Q�[���̑I�����
	typedef enum 
	{
		CHOOSE_NEWGAME = 0,
		CHOOSE_CONTINUE,
		CHOOSE_TUTORIAL,
		CHOOSE_RESULT,
		CHOOSE_MAX
	} CHOOSE;

	CChoose_Game(PRIORITY Priority = PRIORITY_UI);				// �R���X�g���N�^
	~CChoose_Game();												// �f�X�g���N�^
	// �����o�֐�
	static CChoose_Game *Create(D3DXVECTOR3 pos);					// �Q�[���̑I���̐���
	HRESULT Init(D3DXVECTOR3 pos);									// �Q�[���̑I���̏������֐�
	void Uninit(void);												// �Q�[���̑I���̏I���֐�
	void Update(void);												// �Q�[���̑I���̍X�V�֐�
	void Draw(void);												// �Q�[���̑I���̕`��֐�
	static bool GetNewGame(void) { return m_bNewGame; }				// �V�����n�߂邩���擾
	void Resetcol(void);												// �F�����Z�b�g

private:															// �����������A�N�Z�X�\
	inline void LodeChooseUI(void);									// UI�̓ǂݍ��ݏ���
	static const char * m_pChooseUiFile;							// �I����ʂ�UI�t�@�C����
	static CPolygon * m_pPolygon[CHOOSE_MAX];						// �|���S���̔z��|�C���^�[�𐶐�
	static CEffect * m_pEffect;							// �G�t�F�N�g�̔z��|�C���^�[�𐶐�
	static bool m_bNewGame;											// �V�����n�߂邩�ǂ���
	const float m_fInterval;										// �|���S���̊Ԋu
	const D3DXCOLOR ResetCol;										// �����l�̐F
	D3DXVECTOR3 m_LodePos[CHOOSE_MAX];								// ui�̈ʒu�̓ǂݍ���
	D3DXVECTOR2 m_LodeSize[CHOOSE_MAX];								// ui�̑傫���̓ǂݍ���
	D3DXVECTOR2 m_Size;												// �傫��
	int m_nLodeUI;													// ui�̐��̓ǂݍ���
	int m_nSituation;												// �Q�[���̑I����ԑJ��
	bool m_bFade;													// �t�F�[�h���������ǂ���
	bool m_bEffectUse;												// �G�t�F�N�g�����悤�������ǂ���

};
#endif