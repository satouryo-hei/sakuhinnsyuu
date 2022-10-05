//=============================================================================
//
// �X�e�[�W���� [stage.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _STAGE_SECOND_H_
#define _STAGE_SECOND_H_

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
class CStage_Top : public CScene
{
public:																// �N�ł��A�N�Z�X�\
	CStage_Top(int Priority = PRIORITY_NOMAL);						// �R���X�g���N�^
	~CStage_Top();													// �f�X�g���N�^
																	// �����o�֐�
	static CStage_Top *Create(D3DXVECTOR3 pos);						// �Q�[���̃X�e�[�W�̐���
	HRESULT Init(D3DXVECTOR3 pos);									// �Q�[���̃X�e�[�W�̏������֐�
	void Uninit(void);												// �Q�[���̃X�e�[�W�̏I���֐�
	void Update(void);												// �Q�[���̃X�e�[�W�̍X�V�֐�
	void Draw(void);												// �Q�[���̃X�e�[�W�̕`��֐�	


private:															// �����������A�N�Z�X�\
	inline void LodeStage(void);									// �X�e�[�W�̓ǂݍ��ݏ���
	int m_aMap[128][256];											// �X�e�[�W�̓ǂݍ��݂񂾕���ۑ��p�ϐ�
	int m_nLine;													// �s
	int m_nColumn;													// ��
	int m_nNum;														// ��
	static CBlock* m_pBlock[256];									// �u���b�N�̃|�C���^�[
	static const char * m_pTutorial_StageFileName;					// �X�e�[�W�̃t�@�C����
	static CGoal * m_pGoal;											// �S�[���̃|�C���^�[
	static CPlayer * m_pPlayer;											// �S�[���̃|�C���^�[
};
#endif