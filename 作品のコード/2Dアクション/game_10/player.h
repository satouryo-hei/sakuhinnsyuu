//=============================================================================
//
// �v���C���[�̏��� [player.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _PLATER_H_
#define _PLATER_H_

#include"scene2D.h"

#define ITEM_TEXT "data/TEXT/Item.txt"
#define MAX_BULLET (30)
//*****************************************************************************
// �O���錾
//*****************************************************************************
class CBullet;
class CHoming;
class CShotgun;
//*****************************************************************************
// �v���C���[�N���X
//*****************************************************************************
class CPlayer : public CScene2D
{
public:																				// �N�ł��A�N�Z�X�\
	//�v���C���[�̏��
	typedef enum
	{
		PLAYER_NOMAL = 0,															// ���ʂ̏��
		PLAYER_DEATH,																// ���ꂽ���
		PLAYER_RESTARE,																// �ăX�^�[�g���
		PLAYER_MAX																	// ��Ԃ̍ő吔
	} PLAYER;

	CPlayer(int nPriority = PRIORITY_PLAYER);										// �R���X�g���N�^
	~CPlayer();																		// �f�X�g���N�^
																					// �����o�֐�
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size);	// �v���C���̐���
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);								// �v���C���̏������֐�
	void Uninit(void);																// �v���C���̏I���֐�
	void Update(void);																// �v���C���̍X�V�֐�
	void Draw(void);																// �v���C���̕`��֐�
	void BlockColision(void);														// �u���b�N�̓����蔻��
	void PushColision(void);														// �����u���b�N�̓����蔻��
	void MoveColision(void);														// �ړ��u���b�N�̓����蔻��
	PLAYER GetPlayerType(void) { return m_Playertype; }								// �v���C���[�̏�ԑJ��
	static CBullet *GetBullet(void) { return m_pBullet; }							// �e�̃|�C���^�[�̎擾����
	static int GetItem(void) { return m_nItem; }									// �A�C�e���̃|�C���^�[�̎擾����
	static void SetItem(int nItem) { m_nItem = nItem; }								// �A�C�e���̃|�C���^�[�̐ݒ菈��
	static D3DXVECTOR3 GetPos(void) { return m_pos; }								// ���݂̈ʒu�̎擾����
	static void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }							// ���݂̈ʒu�̐ݒ菈��
	static D3DXVECTOR2 GetSize(void) { return m_size; }								// �傫���̎擾����
	static D3DXVECTOR3 GetPosold(void) { return m_posold; }							// �O��̈ʒu�̎擾����
	static D3DXVECTOR3 GetMove(void) { return m_move; }								// �ړ��ʂ̎擾����
	static void SetMove(D3DXVECTOR3 move) { m_move = move; }						// �ړ��ʂ̐ݒ菈��
	static bool GetJump(void) { return m_bJump; }									// �W�����v�������ǂ����̎擾����
	static void SetJump(bool bJump) { m_bJump = bJump; }							// �W�����v�������ǂ����̐ݒ菈��
	static void SetUse(bool bUse) { m_bUse = bUse; }								// �e�̃|�C���^�[�̎擾����
	
private:																			// �����������A�N�Z�X�\
	void Shot(int nType, bool bMovetype);											// �e�̎�ނ̊֐�
	void EnemyColision(void);														// �G�Ƃ̓����蔻��
	inline void SaveItem(void);													// �X�e�[�^�X�̏������ݏ���
	inline void LoadItem(void);													// �X�e�[�^�X�̓ǂݍ��ݏ���
	void SetAnimesion(int nPattern, float fSizeU, float fSizeMinV, float fSizeMaxV);// �A�j���[�V���������֐�

	// �e�̎��
	typedef enum
	{
		SHOTTYPE_NOMAL = 0,															// ���ʂ̒e
		SHOTTYPE_HOMING,															// �z�[�~���O�e
		SHOTTYPE_SHOTGUN,															// �U�e
		SHOTTYPE_MAX																// �S�Ă̒e�̎��
	} SHOTTYPE;
	static D3DXVECTOR3 m_pos;														// ���݂̈ʒu
	static D3DXVECTOR2 m_size;														// �傫��
	static D3DXVECTOR3 m_posold;													// �O��̈ʒu
	static D3DXVECTOR3 m_move;														// �ړ���
	float m_fQuickening;															// ������
	static float m_fGravity;														// �d��
	static LPDIRECT3DTEXTURE9 m_pTexture;											// �e�N�X�`���ւ̃|�C���^
	int m_nCounterAnim;																// �A�j���[�V�����J�E���^
	int m_nPatternAnim;																// �A�j���[�V�����p�^�[��No
	const float m_fSizeU;
	float m_fSizeMinV;
	float m_fSizeMaxV;
	int m_nTimer;																	// ����
	int m_nCoolTime;																// �N�[������
	bool m_bBullet;																	// �e��ł������ǂ���
	bool m_bDeath;																	// �O��|�ꂽ���̔���
	PLAYER m_Playertype;															// �v���C���[�̏��
	static CBullet * m_pBullet;														// �e�̃|�C���^�[�̐���
	static CHoming * m_pHoming[MAX_BULLET];											// �z�[�~���O�e�̃|�C���^�[�̐���
	static CShotgun * m_pShotgun;													// �U�e�̃|�C���^�[����
	static int m_nItem;																// �A�C�e���̃|�C���^�[����
	static bool m_bJump;															// �W�����v�������ǂ���
	static bool m_bUse;																// �g���Ă��邩�ǂ���
	bool m_bMovePush;																// �ړ���������
	int m_nBulletType;																// �e�̎��
	int m_nAttack;
};
#endif