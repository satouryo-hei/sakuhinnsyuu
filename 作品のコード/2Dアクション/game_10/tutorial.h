//=============================================================================
//
// �Q�[���̏��� [tutorial.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "scene.h"
//*****************************************************************************
// �O���錾
//*****************************************************************************
class CPlayer;
class CItem;
class CMeshSky;
class CStage_Tutorial;
class CEnemy02;

//*****************************************************************************
// �Q�[���̃N���X
//*****************************************************************************
class CTutorial : public CScene
{
public:
	CTutorial(int nPriority = PRIORITY_NOMAL);																	// �R���X�g���N�^
	~CTutorial();																	// �f�X�g���N�^

																				// �����o�֐�
	HRESULT Init(D3DXVECTOR3 pos);												// �Q�[���̏������֐�
	void Uninit(void);															// �Q�[���̏I���֐��@
	void Update(void);															// �Q�[���̍X�V�֐�
	void Draw(void);															// �Q�[���̕`��֐�

	static CPlayer * GetPlayer(void) { return m_pPlayer; }
	static CMeshSky*GetMeshSky(void) { return m_pMeshSky; }						// ��̃|�C���^�[���擾
	static CEnemy02*GetEnemy(void) { return m_pEnemy; }						// ��̃|�C���^�[���擾	


private:																		// �����������A�N�Z�X�\		
	static CPlayer* m_pPlayer;													// �v���C���[�̃|�C���^�[
	static CItem* m_pAttack_up;											// �U���̓A�b�v�̃|�C���^�[	
	static CMeshSky * m_pMeshSky;												// ��̃|�C���^�[	
	static CStage_Tutorial * m_pStage;											// �X�e�[�W�̃|�C���^�[
	static CEnemy02* m_pEnemy;													// �G�̃|�C���^�[
	bool m_bUse;																// �g���Ă��邩�ǂ���
	bool m_bFade;																// �J�ڂ������ǂ���
};
#endif