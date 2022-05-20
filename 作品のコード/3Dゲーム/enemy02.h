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
// 3D�v���C���[�N���X
//*****************************************************************************
class CEnemy2 : public CEnemy
{
public:
	CEnemy2(PRIORITY nPriority = CScene::PRIORITY_PLAYER);
	~CEnemy2();

	//�ÓI�����o�֐�
	static CEnemy2 *Create(D3DXVECTOR3 pos, const char *pFileName);	// ����
	// �����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, const char *pFileName);			// ������
	void Uninit(void);												// �I��
	void Update(void);												// �X�V
	void Draw(void);												// �`��
	static CModel *GetModel(int nParts) { return m_pModel[nParts]; }		// ���f���̃|�C���^�[���擾
	static CShadow*GetShadow(void) { return m_pShadow; }			// �e�̃|�C���^�[���擾
	D3DXVECTOR3 GetPos(void) { return m_pos; }						// �v���C���̈ʒu���擾
	D3DXVECTOR3 GetRot(void) { return m_rot; }						// �v���C���̌������擾

private:
	D3DXVECTOR3 m_pos;									// �ʒu	
	D3DXVECTOR3 m_rot;									// ����	
	D3DXVECTOR3 m_Move;									// �ړ���
	float m_fRadius;									// ���a
	float m_fRange;										// �p�x
	D3DXMATRIX m_mtxWorld;								// ���[���h�}�g���b�N�X
	static CModel *m_pModel[20];						// ���f���̃|�C���^�[�̐���
	static CShadow* m_pShadow;							// �e�̃|�C���^�[�̐���
	int m_nModel;										// ���f����
	int m_nNumKey;										// ���݂̃L�[No.
};

#endif // !_PLAYER_H_