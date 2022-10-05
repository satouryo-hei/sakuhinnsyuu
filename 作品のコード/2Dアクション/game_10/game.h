//=============================================================================
//
// �Q�[���̏��� [game.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "scene.h"
//*****************************************************************************
// �O���錾
//*****************************************************************************
class CBg;
class CTimer;
class CPlayer;
class CItem;
class CMeshField;
class CMeshSky;
class CWall;
class CStage_Top;
class CEnemy02;
class CGoal;
class CScore;
class CKeyui;

//*****************************************************************************
// �Q�[���̃N���X
//*****************************************************************************
class CGame : public CScene
{
public:
	CGame(int nPriority = PRIORITY_NOMAL);																	// �R���X�g���N�^
	~CGame();																	// �f�X�g���N�^

																				// �����o�֐�
	HRESULT Init(D3DXVECTOR3 pos);												// �Q�[���̏������֐�
	void Uninit(void);															// �Q�[���̏I���֐��@
	void Update(void);															// �Q�[���̍X�V�֐�
	void Draw(void);															// �Q�[���̕`��֐�

	static CBg*GetBg(void) { return m_pBg; }									// �w�i�̎擾����
	static CTimer*GetTimer(void) { return m_pTimer; }							// �^�C�}�[�̎擾����
	static CPlayer * GetPlayer(void) { return m_pPlayer; }
	static CMeshField*GetMeshField(void) { return m_pMeshField; }				// ���b�V���t�B�[���h�̃|�C���^�[���擾
	static CMeshSky*GetMeshSky(void) { return m_pMeshSky; }						// ��̃|�C���^�[���擾
	static CEnemy02*GetEnemy(void) { return m_pEnemy; }						// ��̃|�C���^�[���擾
	static CScore*GetScore(void) { return m_pScore; }						// ��̃|�C���^�[���擾


private:																		// �����������A�N�Z�X�\		
	static CBg *m_pBg;															// �w�i�̃|�C���^�[
	static CTimer* m_pTimer;													// �^�C�}�[�̃|�C���^�[
	static CPlayer* m_pPlayer;													// �v���C���[�̃|�C���^�[
	static CItem* m_pItem;											// �U���̓A�b�v�̃|�C���^�[
	static CMeshField * m_pMeshField;											// ���b�V���t�B�[���h�̃|�C���^�[
	static CMeshSky * m_pMeshSky;												// ��̃|�C���^�[
	static CWall * m_pWall;											// �ǂ̃|�C���^�[
	static CStage_Top * m_pStage;											// �X�e�[�W�̃|�C���^�[
	static CEnemy02* m_pEnemy;													// �G�̃|�C���^�[
	static CGoal * m_pGoal;														// �S�[���̃|�C���^�[
	static CScore * m_pScore;														// �S�[���̃|�C���^�[	
	static CKeyui* m_pKeyui;														// �S�[���̃|�C���^�[	
	static bool m_bRanking;														// �����L���O�������邩�ǂ���
	bool m_bUse;																// �g���Ă��邩�ǂ���
	bool m_bFade;																// �J�ڂ������ǂ���
};
#endif