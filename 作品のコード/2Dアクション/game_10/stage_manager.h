//= == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == ==
//
// �Ǘ����� [stage_manager.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _STAGE_MANAGER_H_
#define _STAGE_MANAGER_H_

#include"main.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CStage_Tutorial;
class CStage_Top;
//*****************************************************************************
// �}�l�[�W���[�N���X
//*****************************************************************************
class CStage_Manager
{
public:
	// �X�e�[�W�̑J�ڏ���
	typedef enum
	{
		STAGE_INVALID = -1,														// ����
		STAGE_TUTORIAL = 0,														// �`���[�g���A��
		STAGE_TOP,																// �ŏ�
		STAGE_MAX																// �X�e�[�W�̎�ނ̍Ō�
	} STAGE;

	CStage_Manager();															// �R���X�g���N�^
	~CStage_Manager();															// �f�X�g���N�^
																				// �����o�֐�
	HRESULT Init(void);															// �}�l�[�W���[�̏������֐�	
	void Uninit(void);															// �}�l�[�W���[�̏I���֐��@
	void Update(void);															// �}�l�[�W���[�̍X�V�֐�
	void Draw(void);															// �}�l�[�W���[�̕`��֐�
	static void SetStage(STAGE Stage);											// �X�e�[�W�̐ݒ菈��
	static STAGE GetStage(void) { return m_Stage; }								// �X�e�[�W�̎擾����
	static void ChangeStage(void);												// �`�F���W�X�e�[�W�̏���

private:																		// �����������A�N�Z�X�\
	static STAGE m_Stage;														// �X�e�[�W�̃|�C���^�[����
	static STAGE m_NextStage;													// ���̃X�e�[�W�̃|�C���^�[����	
};

#endif