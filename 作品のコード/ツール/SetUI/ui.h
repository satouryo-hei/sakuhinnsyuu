//=============================================================================
//
// UI�̏��� [ui.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _UI_H_
#define _UI_H_

#include"scene2D.h"
#define LIMITUI (20)

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ANIME_TEXT "data/TEXT/AnimUI.txt"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CInputKeyboard;

//*****************************************************************************
// UI�̃N���X
//*****************************************************************************
class CUi : public CScene2D
{
public:																					// �N�ł��A�N�Z�X�\
	CUi();																				// �R���X�g���N�^
	~CUi();																				// �f�X�g���N�^
	// �ÓI�����o�֐�
	static CUi *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 Size, int ntype);	// UI�̐���
																						// �����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 Size, int ntype);		// UI�̏������֐�
	void Uninit(void);																	// UI�̏I���֐�
	void Update(void);																	// UI�̍X�V�֐�
	void Draw(void);																	// UI�̕`��֐�
	void ChangeMoveUI(void);
	void ChangeSizeUI(void);	
	void ChangeAnimeUI(void);
	void SetTex(int nTex);																// �e�N�X�`���̐ݒ�֐�
	void SetPos(D3DXVECTOR3 pos) { m_Pos = pos; }										// �ʒu�̐ݒ�֐�
	void SetSize(D3DXVECTOR3 size) { m_Size = size; }									// �傫���̐ݒ�֐�
	void SetMove(D3DXVECTOR3 move) { m_Move = move; }									// �ړ��ʂ̐ݒ�֐�	
	void SetCol(D3DXCOLOR col) { m_col = col; }											// �����̐ݒ�֐�
	D3DXVECTOR3 GetPos(void) { return m_Pos; }											// �ʒu�̎擾�֐�
	D3DXVECTOR3 GetSize(void) { return m_Size; }										// �傫���̎擾�֐�
	D3DXVECTOR3 GetMove(void) { return m_Move; }										// �ړ��ʂ̎擾�֐�	
	D3DXCOLOR GetColor(void) { return m_col; }											// �F�̎擾�֐�
	
	void SetBoolUse(bool bUse) { m_bUse = bUse; }										// UI�̎g���Ă��邩�֐�
	void SetBoolMove(bool bMove) { m_bMove =bMove; }									// UI�̈ړ����邩�֐�
	void SetBoolSize(bool bSize) { m_bSize = bSize; }									// UI�̑傫���ύX���邩�擾�֐�
	void SetBoolSpeed(bool bSpeed) { m_bSpeed = bSpeed; }								// UI�̑����ύX�����邩�擾�֐�
	void SetBoolAnim(bool bAnime) { m_bAnim = bAnime; }									// UI�̑����ύX�����邩�擾�֐�
	int GetTex(void) { return m_nTextureType; }											// �e�N�X�`���̎擾�֐�
	bool GetBoolUse(void) { return m_bUse; }											// UI�̎g���Ă��邩�擾�֐�
	bool GetBoolMove(void) { return m_bMove; }											// UI�̈ړ����邩�擾�֐�
	bool GetBoolSize(void) { return m_bSize; }											// UI�̑傫���ύX���邩�擾�֐�
	bool GetBoolSpeed(void) { return m_bSpeed; }										// UI�̑����ύX�����邩�擾�֐�
	bool GetBoolAnim(void) { return m_bAnim; }											// UI�̑����ύX�����邩�擾�֐�

private:																				// �����������A�N�Z�X�\
	inline void LodeAnim(void);

	// �����o�ϕs�ϐ�
	const int m_nMaxSetTexNum;															// �ݒ肷��e�N�X�`���̍ő�l
	const float m_fMaxSpeed;															// �����̍ő�l
	const float m_fMinSpeed;															// �����̍ŏ��l
	const float m_fDiagonalSpeed;														// �΂߈ړ����Ɋ|���鑬���̒l
	const float m_fUpAngle;																// �p�x�̌v�Z�p�ϐ��i��n�j
	const float m_fDownAngle;															// �p�x�̌v�Z�p�ϐ��i���n�j
	const D3DXVECTOR3 m_ResetPos;														// ���݂̈ʒu�̏������ϐ�
	const D3DXVECTOR3 m_ResetSize;														// �傫���̏������ϐ�
	const D3DXVECTOR3 m_ResetMove;														// �ړ��ʂ̏������ϐ�

	// �����o�ϐ�
	D3DXVECTOR3 m_Pos;																	// �ʒu
	D3DXVECTOR3 m_Size;																	// �傫��
	D3DXVECTOR3 m_Move;																	// �ړ���	
	D3DXCOLOR m_col;																	// �F
	CInputKeyboard *m_pInputKeyboard;													// �L�[�{�[�h����
	int m_nCounterAnim;																	// �A�j���[�V�����̃J�E���^�[
	int m_nAnimeSpeed;																	// �A�j���[�V�����̑���
	int m_nMaxPatternAnim;																// �A�j���[�V�����̃p�^�[���̍ő吔
	int m_nPatternAnim;																	// �A�j���[�V�����̃p�^�[����
	int m_nTextureType;																	// ���݂̃e�N�X�`���̃^�C�v
	float m_fSizeAnimU;																	// �A�j���[�V������U���W
	float m_fMinSizeV;																	// �A�j���[�V������V���W�̍ŏ��T�C�Y
	float m_fMaxSizeV;																	// �A�j���[�V������V���W�̍ő�T�C�Y
	bool m_bUse;																		// �g�p���Ă邩
	bool m_bMove;																		// �ړ����邩�ǂ���
	bool m_bSize;																		// �傫����ύX���邩�ǂ���
	bool m_bSpeed;																		// ������ύX���邩�ǂ���
	bool m_bAnim;																		// �A�j���[�V�����ɂ��邩�ǂ���

};
#endif