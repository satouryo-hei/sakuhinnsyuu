//=============================================================================
//
// �Q�[���̏��� [game.h]
// Author : �����ĕ�
// Author : �ؖr�_
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
class CEnemy;
class CScore;
class CTimer;
class CBulletui;

//*****************************************************************************
// �Q�[���̃N���X
//*****************************************************************************
class CGame : public CScene
{
public:
	CGame(int nPriority = PRIORITY_NOMAL);										// �R���X�g���N�^
	~CGame();																	// �f�X�g���N�^

																				// �����o�֐�
	HRESULT Init(D3DXVECTOR3 pos);												// �Q�[���̏������֐�
	void Uninit(void);															// �Q�[���̏I���֐��@
	void Update(void);															// �Q�[���̍X�V�֐�
	void Draw(void);															// �Q�[���̕`��֐�
	static CBg*GetBg(void) { return m_pBg; }									// �w�i�̎擾����
	static CEnemy*GetEnemy(int nNum) { return m_pEnemy[nNum]; }									// �w�i�̎擾����
	static CScore*GetScore(void) { return m_pScore; }

private:																		// �����������A�N�Z�X�\		
	static CBg *m_pBg;															// �w�i�̃|�C���^�[
	static CPlayer * m_pPlayer;													// �v���C���[�̃|�C���^�[
	static CEnemy *m_pEnemy[10];													// �G�l�~�[�̃|�C���^�[
	static CScore * m_pScore;													// �_���̃|�C���^�[	
	static CTimer* m_pTimer;													// �^�C�}�[�̃|�C���^�[
	static CBulletui* m_pBulletui;													// �^�C�}�[�̃|�C���^�[
	bool m_bFade;																// �J�ڂ������ǂ���
	int m_nSpawn;
};
#endif
