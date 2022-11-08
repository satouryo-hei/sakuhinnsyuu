//=============================================================================
//
// �X�e�[�W���� [stage.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _STAGE_H_
#define _STAGE_H_

#include"scene.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CBlock;
class CGoal;
class CPlayer;
//*****************************************************************************
// �X�e�[�W�N���X
//*****************************************************************************
class CStage : public CScene
{
public:																		// �N�ł��A�N�Z�X�\
	// �X�e�[�W�̎��
	typedef enum
	{
		STAGE_INVALID = -1,															// ����
		STAGE_TUTORIAL = 0,															// �`���[�g���A��
		STAGE_TOP,																	// �ŏ�
		STAGE_MAX																	// �X�e�[�W�̎�ނ̍Ō�
	} STAGE;
	CStage(int Priority = PRIORITY_NOMAL);											// �R���X�g���N�^
	virtual ~CStage();																		// �f�X�g���N�^
	// �����o�֐�
	static CStage *Create(STAGE stage,D3DXVECTOR3 pos, const char * pStageFileName);// �X�e�[�W�̐���
	virtual HRESULT Init(D3DXVECTOR3 pos);											// �X�e�[�W�̏������֐�
	virtual void Uninit(void);														// �X�e�[�W�̏I���֐�
	virtual void Update(void) = 0;													// �X�e�[�W�̍X�V�֐�
	virtual void Draw(void) = 0;													// �X�e�[�W�̕`��֐�	


private:																			// �����������A�N�Z�X�\
	inline void LodeStage(const char * pStageFileName);								// �X�e�[�W�̓ǂݍ��ݏ���
	int m_aMap[128][256];															// �X�e�[�W�̓ǂݍ��݂񂾕���ۑ��p�ϐ�
	int m_nLine;																	// �s
	int m_nColumn;																	// ��
	int m_nNum;																		// ��
	static CBlock* m_pBlock[256];													// �u���b�N�̃|�C���^�[	
};
#endif