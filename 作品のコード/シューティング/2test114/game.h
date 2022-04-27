//=============================================================================
//
// �Q�[���̏��� [game.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "scene.h"
//=============================================================================
// �O���錾
//=============================================================================
class CBg;
class CPlayer;
class CEnemy;
class CScore;
class CLife;
class CTimer;
class CEnemy_Doragonfly;
class CEnemy_manager;
class CRanking;
class CUi;

//*****************************************************************************
// �Q�[���̃N���X
//*****************************************************************************
class CGame : public CScene
{
public:
	CGame();																	// �R���X�g���N�^
	~CGame();																	// �f�X�g���N�^

																				// �����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);							// �^�C�g���̏������֐�
	void Uninit(void);															// �^�C�g���̏I���֐��@
	void Update(void);															// �^�C�g���̍X�V�֐�
	void Draw(void);															// �^�C�g���̕`��֐�

	static CBg*GetBg(void) { return m_pBg; }									// �w�i�̎擾����
	static CPlayer*GetPlayer(void) { return m_pPlayer; }						// �v���C���[�̎擾����
	static CEnemy*GetEnemy(void) { return m_pEnemy; }							// �G�̎擾����
	static CScore*GetScore(void) { return m_pScore; }							// �X�R�A�̎擾����
	static CLife*GetLife(void) { return m_pLife; }								// �̗͂̎擾����
	static CTimer*GetTimer(void) { return m_pTimer; }
	static CEnemy_Doragonfly*GetEnemy_Doragonfly(void) { return m_pEmemy_Doragonfly; }
	static CUi*GetUI(void) { return m_pUi; }
	CEnemy_manager*GetEnemy_Manager(void) { return m_pEmemy_Manager; }
	static bool GetRanking(void) { return m_bRanking; }


private:																		// �����������A�N�Z�X�\
	static CBg *m_pBg;															// �w�i�̃|�C���^�[
	static CPlayer *m_pPlayer;													// �v���C���[�̃|�C���^�[
	static CEnemy*m_pEnemy;														// �G�̃|�C���^�[
	static CScore*m_pScore;														// �X�R�A�̃|�C���^�[
	static CLife*m_pLife;														// �̗͂̃|�C���^�[
	static CTimer*m_pTimer;
	static CEnemy_Doragonfly*m_pEmemy_Doragonfly;
	static CUi * m_pUi;
	CEnemy_manager*m_pEmemy_Manager;
	static bool m_bRanking;
	bool m_bNextMode;
};
#endif