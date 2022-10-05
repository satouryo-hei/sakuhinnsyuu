//=============================================================================
//
// �G�l�~�[�̏��� [enemy.h]
// Author : �ؖr�_
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include"scene2D.h"

//*****************************************************************************
// �G�l�~�[�N���X
//*****************************************************************************
class CEnemy : public CScene2D
{
public:																				// �N�ł��A�N�Z�X�\

	typedef enum
	{
		TYPE_S = 0,
		TYPE_M,
		TYPE_L,
		TYPE_MAX
	} TYPE;

	CEnemy(int nPriority = PRIORITY_ENEMY);										// �R���X�g���N�^
	~CEnemy();																		// �f�X�g���N�^

	// �����o�֐�
	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size, TYPE type);	// �G�l�~�[�̐���
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);								// �G�l�~�[�̏������֐�
	void Uninit(void);																// �G�l�~�[�̏I���֐�
	void Update(void);																// �G�l�~�[�̍X�V�֐�
	void Draw(void);																// �G�l�~�[�̕`��֐�
	void BulletCollision();
	CEnemy * GetEnemy(int nNum) { return m_pEnemy[nNum]; }														// ���݂̈ʒu



private:																			// �����������A�N�Z�X�\		
	D3DXVECTOR3 m_posold;													// �O��̈ʒu
	D3DXVECTOR3 m_move;														// �ړ���
	static LPDIRECT3DTEXTURE9 m_pTexture;											// �e�N�X�`���ւ̃|�C���^
	const float m_fSizeU;
	float m_fSizeMinV;
	float m_fSizeMaxV;
	int m_nTimer;																	// ����
	int m_nCoolTime;																// �N�[������
	bool m_bBullet;																	// �e��ł������ǂ���
	bool m_bDeath;																	// �O��|�ꂽ���̔���	
	static int m_nItem;																// �A�C�e���̃|�C���^�[����
	static bool m_bUse;																// �g���Ă��邩�ǂ���
	static CEnemy *m_pEnemy[100];// �|�C���^
	static int m_EnemyAll;
	bool m_bMovePush;																// �ړ���������
	int m_nBulletType;																// �e�̎��
	TYPE m_Type;
	
protected:
	D3DXVECTOR3 m_pos;														// ���݂̈ʒu
	int m_nLife;
	int m_nSpeed;
	D3DXVECTOR2 m_size;														// �傫��
};
#endif