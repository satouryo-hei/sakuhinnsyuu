//=============================================================================
//
// �I�u�W�F�N�g�̏��� [scene.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

#include"main.h"

//==============================
// �}�N����`
//==============================
#define MAX_DATA (1000)

//*****************************************************************************
// �I�u�W�F�N�g�N���X
//*****************************************************************************
class CScene
{
public:																										// �N�ł��A�N�Z�X�\

	// �`��̗D�揇��
	typedef enum
	{
		PRIORITY_NOMAL = 0,																					// �m�[�}��
		PRIORITY_BG,																						// �w�i
		PRIORITY_EFFECT,																					// �G�t�F�N�g
		PRIORITY_BULLET,																					// �e
		PRIORITY_PLAYER,																					// �v���C���[
		PRIORITY_EXPLOSION,																					// ����
		PRIORITY_UI,																						// UI(�X�R�A�Ȃ�
		PRIORITY_FADE,																						// �t�F�[�h
		PRIORITY_MAX																						// ���ׂĂ̐�
	} PRIORITY;

	// �I�u�W�F�N�g�̎��
	typedef enum 
	{
		OBJTYPE_NOMAL=0,																					// �m�[�}��
		OBJTYPE_PLAYER,																						// �v���C���[
		OBJTYPE_ENEMY,																						// �G
		OBJTYPE_PLAYERBULLET,																						// �e
		OBJTYPE_ENEMYBULLET,																						// �e
		OBJTYPE_MAX																							// ���ׂĂ̐�
	} OBJTYPE;

	CScene(int nPriority = 3);																				// �R���X�g���N�^
	virtual~CScene();																						// �f�X�g���N�^
	// �����o�֐�
	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size) = 0;											// �I�u�W�F�N�g�̏������֐�
	virtual void Uninit(void) = 0;																			// �I�u�W�F�N�g�̏I���֐��@
	virtual void Update(void) = 0;																			// �I�u�W�F�N�g�̍X�V�֐�
	virtual void Draw(void) = 0;																			// �I�u�W�F�N�g�̕`��֐�
	static void ReleseAll(void);																			// ���ׂẴI�u�W�F�N�g�̊J���֐�
	static void UpdateAll(void);																			// ���ׂẴI�u�W�F�N�g�̍X�V�֐�
	static void DrawAll(void);																				// ���ׂẴI�u�W�F�N�g�̕`��֐�
	void SetType(OBJTYPE objType) { m_ObjType = objType; }													// �I�u�W�F�N�g�̎�ނ̔z�u
	OBJTYPE GetOnjType(void) { return m_ObjType; }															// �I�u�W�F�N�g�̎�ނ̎擾����
	static CScene * GetScene(int nPriority,int nCountScene) { return m_apScene[nPriority][nCountScene]; }	// ���Ԗڂ̃I�u�W�F�N�g���̎擾����

protected:																									// �����Ɣh���n�̂݃A�N�Z�X�\
	void  Relese(void);																						// 1�̃I�u�W�F�N�g�̊J���֐�

private:																									// �����������A�N�Z�X�\
	// �����o�ϐ�
	static CScene *m_apScene[PRIORITY_MAX][MAX_DATA];														// ���ꂼ��̃I�u�W�F�N�g
	static int m_nNumAll;																					// �|���S���̑S�̂̐�
	int m_nID;																								// �i�[��̔ԍ�
	OBJTYPE m_ObjType;																						// �I�u�W�F�N�g�̎��
	int m_nPriority;																						// �D�揇�ʂ̔ԍ�
};
#endif
