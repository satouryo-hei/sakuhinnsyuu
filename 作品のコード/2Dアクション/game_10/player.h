//=============================================================================
//
// �v���C���[�̏��� [player.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _PLATER_H_
#define _PLATER_H_

#include"scene2D.h"

#define STATUS_TEXT "data/TEXT/Status.txt"
#define MAX_BULLET (30)
//*****************************************************************************
// �O���錾
//*****************************************************************************
class CBullet;
class CHoming;
class CBullet03;
//*****************************************************************************
// �v���C���[�N���X
//*****************************************************************************
class CPlayer : public CScene2D
{
public:																// �N�ł��A�N�Z�X�\
																	//�v���C���[�̏��
	typedef enum
	{
		PLAYER_NOMAL = 0,
		PLAYER_DEATH,
		PLAYER_RESTARE,
		PLAYER_MAX
	} PLAYER;

	CPlayer(int nPriority = PRIORITY_PLAYER);										// �R���X�g���N�^
	~CPlayer();														// �f�X�g���N�^
																	// �����o�֐�
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size);		// �v���C���̐���
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);				// �v���C���̏������֐�
	void Uninit(void);												// �v���C���̏I���֐�
	void Update(void);												// �v���C���̍X�V�֐�
	void Draw(void);												// �v���C���̕`��֐�
	void BlockColision(void);										// �u���b�N�̓����蔻��
	void PushColision(void);										// �u���b�N�̓����蔻��
	void MoveColision(void);										// �u���b�N�̓����蔻��
	PLAYER GetPlayerType(void) { return m_Playertype; }
	static CBullet *GetBullet(void) { return m_pBullet; }												// �v���C���̕`��֐�
	static int GetItem(void) { return m_nItem; }
	static void SetItem(int nItem) { m_nItem = nItem; }
	static D3DXVECTOR3 GetPos(void) { return m_pos; }
	static void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	static D3DXVECTOR2 GetSize(void) { return m_size; }
	static D3DXVECTOR3 GetPosold(void) { return m_posold; }
	static D3DXVECTOR3 GetMove(void) { return m_move; }
	static void SetMove(D3DXVECTOR3 move) { m_move = move; }
	static bool GetJump(void) { return m_bJump; }
	static void SetJump(bool bJump) { m_bJump = bJump; }
	static void SetUse(bool bUse) { m_bUse = bUse; }
	
private:															// �����������A�N�Z�X�\
	void Shot(int nType, bool bMovetype);
	inline void SaveStatus(void);
	inline void LoadStatus(void);

	typedef enum
	{
		SHOTTYPE_NOMAL = 0,
		SHOTTYPE_HOMING,		
		SHOTTYPE_SHOYGUN,
		SHOTTYPE_MAX
	} SHOTTYPE;
	static D3DXVECTOR3 m_pos;												// �ړ���
	static D3DXVECTOR2 m_size;
	static D3DXVECTOR3 m_posold;												// �ړ���
	static D3DXVECTOR3 m_move;												// �ړ���
	static float m_fGravity;												// �ړ���
	static LPDIRECT3DTEXTURE9 m_pTexture;							// �e�N�X�`���ւ̃|�C���^
	int m_nCounterAnim;												// �A�j���[�V�����J�E���^
	int m_nPatternAnim;												// �A�j���[�V�����p�^�[��No
	int m_nTimer;													// ����
	int m_nCoolTime;												// �N�[������
	bool m_bBullet;													// �e��ł������ǂ���
	bool m_bDeath;													// �O��|�ꂽ���̔���
	PLAYER m_Playertype;											// �v���C���[�̏��
	static CBullet * m_pBullet;										// �e�̃|�C���^�[�̐���
	static CHoming * m_pHoming[MAX_BULLET];							// �g�U�e�̃|�C���^�[�̐���
	static CBullet03 * m_pBullet03;									// �z�[�~���O�e�̃|�C���^�[����
	static int m_nItem;												// �A�C�e���̃|�C���^�[����
	static bool m_bJump;											// �W�����v�������ǂ���
	static bool m_bUse;												// �g���Ă��邩�ǂ���
	bool m_bMovePush;												// �ړ���������
	int m_nBulletType;												// �e�̎��
};
#endif