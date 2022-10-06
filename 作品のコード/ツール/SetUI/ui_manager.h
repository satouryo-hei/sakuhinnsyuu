//=============================================================================
//
// ui�̊Ǘ��^���� [ui_manager.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _UI_MANAGER_H_
#define _UI_MANAGER_H_

#include"scene2D.h"
#include"ui.h"

#define SETUITEXT "data/TEXT/Setui.txt"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CUi;

//*****************************************************************************
// ui�̊Ǘ��^�N���X
//*****************************************************************************
class CUI_Manager : public CScene
{
public:
	CUI_Manager();																	// �R���X�g���N�^
	~CUI_Manager();																	// �f�X�g���N�^

	// �ÓI�����o�֐�
	static CUI_Manager *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 Size);// UI�̊Ǘ��^�̐���
	static CUi*GetUi(int uitype) { return m_pUi[uitype]; }							// ���[�U�[�C���^�[�t�F�[�X�N���X�̃|�C���^
	static int GetNumUI(void) { return m_nAllui; }									// ���݂̌��擾�֐�

																					// �����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);								// UI�̊Ǘ��^�̏������֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 Size);				// UI�̊Ǘ��^�̏������֐�
	void Uninit(void);																// UI�̊Ǘ��^�̏I���֐��@
	void Update(void);																// UI�̊Ǘ��^�̍X�V�֐�
	void Draw(void);																// UI�̊Ǘ��^�̕`��֐�	
	void SetUI(D3DXVECTOR3 pos, D3DXVECTOR3 size);									// UI�̔z�u�֐�

	bool GetUse(void) { return m_bUse; }											// �g�p�󋵂̎擾�֐�
	int GetMax(void) { return m_nMaxUI; }											// �ő吔�擾�֐�
	void SetMax(int nMax) { (int)m_nMaxUI = nMax; }											// �ő吔�擾�֐�

private:																			// �����������A�N�Z�X�\
	inline void SaveUI(void);														// UI�̏������ݏ���
	inline void LodeUI(void);														// UI�̓ǂݍ��ݏ���
	void LodeSetAll(void);															// ���ׂĂ�UI��ݒu����
	void LodeSetNow(void);															// ����UI��ݒu����

	// �ÓI�����o�ϐ�
	static CUi*m_pUi[LIMITUI];														// ���[�U�[�C���^�[�t�F�[�X�̃C���X�^���X����
	static int m_nAllui;															// UI�͑S���ŉ���

	// �����o�ϐ�
	const int m_MinUI;																// UI�̍ŏ��l
	const int m_nMaxUI;																// UI�̍ő�l
	D3DXVECTOR3 m_Pos;																// �ʒu
	D3DXVECTOR3 m_Size;																// �傫��
	D3DXVECTOR3 m_Move;																// �ړ���
	D3DXCOLOR m_Color;																// �F
	D3DXVECTOR3 m_SavePos[LIMITUI];													// �ۑ��p�̈ʒu�̕ϐ�
	D3DXVECTOR3 m_SaveSize[LIMITUI];												// �ۑ��p�̑傫���̕ϐ�
	D3DXVECTOR3 m_LodePos[LIMITUI];													// �ǂݍ��ݗp�̈ʒu�̕ϐ�
	D3DXVECTOR3 m_LodeSize[LIMITUI];												// �ǂݍ��ݗp�̑傫���̕ϐ�
	int m_nTex;																		// ���Ԗڂ̃e�N�X�`����
	int m_nLodeUI;																	// �ǂݍ��ݗp��UI�̐�
	bool m_bUse;																	// �g�p���Ă邩
};
#endif