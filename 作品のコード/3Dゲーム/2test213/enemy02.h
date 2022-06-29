//=============================================================================
//
// �G�̏��� [player.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _ENEMY2_H_
#define _ENEMY2_H_
#include "enemy.h"
//*****************************************************************************
// �O���錾
//*****************************************************************************
class CModel;
class CShadow;

//*****************************************************************************
// �G�N���X
//*****************************************************************************
class CEnemy2 : public CEnemy
{
public:
	CEnemy2(PRIORITY nPriority = CScene::PRIORITY_ENEMY);
	~CEnemy2();

	//�ÓI�����o�֐�
	static CEnemy2 *Create(D3DXVECTOR3 pos, const char *pFileName);		// ����
	// �����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, const char *pFileName);				// ������
	void Uninit(void);													// �I��
	void Update(void);													// �X�V
	void Draw(void);													// �`��
	static CModel *GetModel(int nParts) { return m_pModel[nParts]; }	// ���f���̃|�C���^�[���擾
	static CShadow*GetShadow(void) { return m_pShadow; }				// �e�̃|�C���^�[���擾
	D3DXVECTOR3 GetPos(void) { return m_pos; }							// �v���C���̈ʒu���擾
	D3DXVECTOR3 GetRot(void) { return m_rot; }							// �v���C���̌������擾
	static bool GetUse(void) { return m_bUse; }							// �v���C���̌������擾

private:
	D3DXVECTOR3 m_pos;													// �ʒu	
	D3DXVECTOR3 m_rot;													// ����	
	D3DXVECTOR3 m_Move;													// �ړ���
	float m_fRadius;													// ���a
	float m_fRange;														// �p�x
	float m_fFlame;														// �t���[����
	D3DXMATRIX m_mtxWorld;												// ���[���h�}�g���b�N�X
	static CModel *m_pModel[20];										// ���f���̃|�C���^�[�̐���
	static CShadow* m_pShadow;											// �e�̃|�C���^�[�̐���
	int m_nModel;														// ���f����
	int m_nNumKey;														// ���݂̃L�[No.
	static bool m_bUse;
};

#endif // !_PLAYER_H_