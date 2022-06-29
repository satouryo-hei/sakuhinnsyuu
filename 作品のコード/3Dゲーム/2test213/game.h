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
class CPlayer;
class CScene3D;
class CModel;
class CModel_Single;
class CPlayer2;
class CMeshField;
class CMeshSky;
class CShadow;
class CBillboard;
class CWall_Manager;
class CWall;
class CTimer;
class CItem;
class CEnemy;
class CEnemy2;
class CScore;
class CStatus_UI;
class CGoal;
class CBom;

//*****************************************************************************
// �Q�[���̃N���X
//*****************************************************************************
class CGame : public CScene
{
public:
	CGame();																	// �R���X�g���N�^
	~CGame();																	// �f�X�g���N�^
																				// �����o�֐�
	HRESULT Init(D3DXVECTOR3 pos);												// �Q�[���̏������֐�
	void Uninit(void);															// �Q�[���̏I���֐��@
	void Update(void);															// �Q�[���̍X�V�֐�
	void Draw(void);															// �Q�[���̕`��֐�

	static CBg*GetBg(void) { return m_pBg; }									// �w�i�̎擾����
	static CScene3D*GetScene3D(void) { return m_pScene3D; }						// �V�[��3D�̎擾����
	static CModel*GetModel(void) { return m_pModel; }							// ���f���̃|�C���^�[���擾
	static CModel_Single*GetModel_Single(void) { return m_pModel_Single; }		// ��̃��f���̃|�C���^�[���擾
	static CPlayer*GetPlayer(void) { return m_pPlayer; }						// 3D�v���C���[�̃|�C���^�[���擾
	static CMeshField*GetMeshField(void) { return m_pMeshField; }				// ���b�V���t�B�[���h�̃|�C���^�[���擾
	static CMeshSky*GetMeshSky(void) { return m_pMeshSky; }						// ��̃|�C���^�[���擾
	static CShadow*GetShadow(void) { return m_pShadow; }						// �e�̃|�C���^�[���擾
	static CBillboard*GetBillboard(void) { return m_pBillboard; }				// �r���{�[�h�̃|�C���^�[���擾
	static CWall_Manager*GetWall_Manager(void) { return m_pWall_Manager; }		// �l�p�`�̕ǂ̃|�C���^�[���擾
	static CWall*GetWall(void) { return m_pWall; }								// �ǂ̃|�C���^�[���擾
	static CTimer*GetTimer(void) { return m_pTimer; }							// �^�C�}�[�̃|�C���^�[���擾
	static CItem*GetItem(void) { return *m_pItem; }								// �A�C�e���̃|�C���^�[���擾
	static CEnemy*GetEnemy(void) { return m_pEnemy; }							// �G�̃|�C���^�[���擾
	static CEnemy2*GetEnemy2(void) { return m_pEnemy2; }						// �G�̃|�C���^�[���擾
	static CScore*GetScore(void) { return m_pScore; }							// �_���̃|�C���^�[���擾
	static CStatus_UI*GetStatus_UI(void) { return m_pStatus_UI; }				// �X�e�[�^�XUI�̃|�C���^�[���擾
	static CGoal*GetGoal(void) { return m_pGoal;}								// �S�[���̃|�C���^�[���擾
	static CBom*GetBom(void) { return m_pBom; }									// �{���̃|�C���^�[���擾

private:																		// �����������A�N�Z�X�\		
	static CBg *m_pBg;															// �w�i�̃|�C���^�[
	static CScene3D * m_pScene3D;												// 3D�V�[���̃|�C���^�[
	static CModel * m_pModel;													// ���f���̃|�C���^�[
	static CModel_Single * m_pModel_Single;										// ��̃��f���̃|�C���^�[
	static CPlayer * m_pPlayer;													// 3D�v���C���[�̃|�C���^�[
	static CMeshField * m_pMeshField;											// ���b�V���t�B�[���h�̃|�C���^�[
	static CMeshSky * m_pMeshSky;												// ��̃|�C���^�[
	static CShadow* m_pShadow;													// �e�̃|�C���^�[
	static CBillboard* m_pBillboard;											// �r���{�[�h�̃|�C���^�[
	static CWall_Manager* m_pWall_Manager;										// �l�p�`�̕ǂ̃|�C���^�[
	static CWall* m_pWall;														// �ǂ̃|�C���^�[
	static CTimer* m_pTimer;													// �^�C�}�[�̃|�C���^�[
	static CItem* m_pItem[3];													// �A�C�e���̃|�C���^�[
	static CEnemy*m_pEnemy;														// �G�̃|�C���^�[���擾
	static CEnemy2*m_pEnemy2;													// �G�̃|�C���^�[���擾
	static CScore*m_pScore;														// �_���̃|�C���^�[���擾
	static CStatus_UI*m_pStatus_UI;												// �X�e�[�^�XUI�̃|�C���^�[���擾
	static CGoal*m_pGoal;														// �S�[���̃|�C���^�[���擾
	static CBom*m_pBom;															// �{���̃|�C���^�[���擾
	static bool m_bRanking;														// �����L���O�������邩
	static const char*m_pModelData;												// �����f���̃t�@�C����
	static const char*m_pModelAttack;											// �A�C�e���̃��f���̃t�@�C����(�U����UP)
	static const char*m_pModelGoal; 											// �S�[���̃��f���̃t�@�C����
	static const char * m_pModelBom; 											// �{���̃��f���̃t�@�C����
	bool m_bUse;																// �g���Ă��邩�ǂ���

};
#endif