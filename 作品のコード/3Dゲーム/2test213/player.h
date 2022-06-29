//=============================================================================
//
// 3D�v���C���[�̏��� [player.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "scene.h"

#define MAX_PARTS (10)	//�ő�p�[�c��
#define MAX_KEYSET (10) //�ő�L�[�Z�b�g��
#define PLAYER_TEXT "data/TEXT/Player.txt"	// �v���C���[�e�L�X�g�t�@�C��
#define STATUS_TEXT "data/TEXT/Status.txt"	// �X�e�[�^�X�e�L�X�g�t�@�C��


//*****************************************************************************
// �O���錾
//*****************************************************************************
class CModel;
class CShadow;
class CCamera;

//*****************************************************************************
// 3D�v���C���[�N���X
//*****************************************************************************
class CPlayer : public CScene
{
public:
	CPlayer(PRIORITY nPriority = CScene::PRIORITY_PLAYER);
	~CPlayer();

	//�ÓI�����o�֐�
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move);
	// �����o�֐�
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	CModel *GetModel(int nParts) { return m_pModel[nParts]; }		// ���f���̃|�C���^�[���擾
	static CShadow*GetShadow(void) { return m_pShadow; }			// �e�̃|�C���^�[���擾
	D3DXVECTOR3 GetPos(void) { return m_pos; }						// �v���C���̈ʒu���擾
	D3DXVECTOR3 GetPosOld(void) { return m_posold; }						// �v���C���̈ʒu���擾
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }						// �v���C���̈ʒu���擾
	void SetPosOld(D3DXVECTOR3 posOld) { m_posold = posOld; }						// �v���C���̈ʒu���擾
	D3DXVECTOR3 GetRot(void) { return m_rot; }						// �v���C���̌������擾
	int GetAttack(void) { return m_nAttack; }						// �U���͂̎擾�֐�
	void SetAttack(int nAttack) { m_nAttack = nAttack; }			// �U���͂̐ݒ�֐�
	int GetItem(void) { return m_nItem; }						// �U���͂̎擾�֐�
	void SetItem(int nItem) { m_nItem = nItem; }			// �U���͂̐ݒ�֐�

private:
	inline void SaveStatas(const char *pStatasFile);	// ��������
	inline void LoadPlayer(const char *pFile);			// �ǂݍ��ݏ���
	inline void LoadStatas(const char *pStatasFile);	// �ǂݍ��ݏ���
	D3DXVECTOR3 m_pos;									// �ʒu
	D3DXVECTOR3 m_posold;									// �ʒu
	D3DXVECTOR3 m_move;									// �ړ���	
	D3DXVECTOR3 m_rot;									// ����	
	D3DXMATRIX m_mtxWorld;								// ���[���h�}�g���b�N�X
	CModel *m_pModel[MAX_PARTS];						// ���f���̃|�C���^�[�̐���
	static CShadow* m_pShadow;							// �e�̃|�C���^�[�̐���
	static CCamera* m_pCamera;							// �J�����̃|�C���^�[�̐���
	int m_nModel;										// ���f����
	int m_nNumKey;										// ���݂̃L�[No.
	int m_nAttack;										// �U����
	int m_nItem;										// �U����
	static const char* m_pModelBom;
};


#endif // !_PLAYER_H_