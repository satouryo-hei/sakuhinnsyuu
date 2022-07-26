//=============================================================================
//
// �X�e�[�W���� [stage.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _STAGE_TUTORIAL_H_
#define _STAGE_TUTORIAL_H_

#include"scene.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CNoneBlock;
class CMoveBlock;
class CPushBlock;
class CBlock;
//*****************************************************************************
// �X�e�[�W�N���X
//*****************************************************************************
class CStage_Tutorial : public CScene
{
public:																// �N�ł��A�N�Z�X�\
	CStage_Tutorial(int Priority = PRIORITY_NOMAL);				// �R���X�g���N�^
	~CStage_Tutorial();												// �f�X�g���N�^
																	// �����o�֐�
	static CStage_Tutorial *Create(D3DXVECTOR3 pos);					// �Q�[���̑I���̐���
	HRESULT Init(D3DXVECTOR3 pos);									// �Q�[���̑I���̏������֐�
	void Uninit(void);												// �Q�[���̑I���̏I���֐�
	void Update(void);												// �Q�[���̑I���̍X�V�֐�
	void Draw(void);												// �Q�[���̑I���̕`��֐�
	static CNoneBlock*GetEnemy(void) { return *m_pNone; }						// ��̃|�C���^�[���擾


private:															// �����������A�N�Z�X�\
	inline void LodeStage(void);									// �X�e�[�W�̓ǂݍ��ݏ���
	int m_aMap[128][256];											// �X�e�[�W�̓ǂݍ��݂񂾕���ۑ��p�ϐ�
	int m_nLine;													// �s
	int m_nColumn;													// ��
	int m_nNum;														// ��
	static CBlock* m_pBlock[256];									// �u���b�N�̃|�C���^�[
	static const char * m_pTutorial_StageFileName;					// �X�e�[�W�̃t�@�C����

	static CNoneBlock * m_pNone[128];								// none�u���b�N�̃|�C���^�[
	static CMoveBlock * m_pMove[128];								// �ړ��u���b�N�̃|�C���^�[
	static CPushBlock * m_pPush[128];								// �����u���b�N�̃|�C���^�[
};
#endif