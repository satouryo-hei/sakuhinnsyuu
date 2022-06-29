//=============================================================================
//
// �G�̏��� [enemy.h]
// Author : �����ĕ�
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "scene.h"

#define ENEMY_TEXT "data/TEXT/Player.txt" //�ő�L�[�Z�b�g��


//*****************************************************************************
// �O���錾
//*****************************************************************************
class CModel;
class CShadow;

//*****************************************************************************
// �G�̃N���X
//*****************************************************************************
class CEnemy : public CScene
{
public:
	CEnemy(PRIORITY nPriority = CScene::PRIORITY_ENEMY);			// �R���X�g���N�^
	~CEnemy();														// �f�X�g���N�^

	//�ÓI�����o�֐�
	static CEnemy *Create(D3DXVECTOR3 pos, const char *pFileName);	// �����֐�
	// �����o�֐�
	HRESULT Init(D3DXVECTOR3 pos);									// �f�t�H���g�������֐�
	HRESULT Init(D3DXVECTOR3 pos, const char *pFileName);			// �������֐�
	void Uninit(void);												// �I���֐�
	void Update(void);												// �X�V�֐�
	void Draw(void);												// �`��֐�
	static CModel *GetModel(int nParts) { return m_pModel[nParts]; }		// ���f���̃|�C���^�[���擾
	static CShadow*GetShadow(void) { return m_pShadow; }			// �e�̃|�C���^�[���擾
	D3DXVECTOR3 GetPos(void) { return m_pos; }						// �v���C���̈ʒu���擾
	D3DXVECTOR3 GetRot(void) { return m_rot; }						// �v���C���̌������擾
	D3DXVECTOR3 GetSize(void);										// �v���C���̌������擾
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }						// �v���C���̈ʒu���擾
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }						// �v���C���̌������擾
	void SetSize(D3DXVECTOR3 Size) { m_Size = Size; }						// �v���C���̌������擾

private:	
	inline void LoadEnemy(const char *pFileName);			// �ǂݍ��ݏ���	
	D3DXVECTOR3 m_pos;									// �ʒu	
	D3DXVECTOR3 m_rot;									// ����	
	D3DXVECTOR3 m_Size;									// �傫��	
	D3DXMATRIX m_mtxWorld;								// ���[���h�}�g���b�N�X
	static CModel *m_pModel[20];						// ���f���̃|�C���^�[�̐���
	static CShadow* m_pShadow;							// �e�̃|�C���^�[�̐���
	int m_nModel;										// ���f����
	int m_nNumKey;										// ���݂̃L�[No.
};



#endif // !_PLAYER_H_