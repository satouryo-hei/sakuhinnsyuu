//========================================
// �X�e�[�W
// Author:��
//========================================
#ifndef _STAGE_H_
#define _STAGE_H_
#include "main.h"
class CModel_Spawner;
class CField;
class CEnemy;
class CEnemy_Baum;
//----------------------------
// �}�N����`
//----------------------------
#define MAX_STAGE_MODEL (300)			// ���f��(�p�[�c)�̍ő吔
#define MAX_STAGE_ENEMY (30)			// ���f��(�p�[�c)�̍ő吔

#define MAX_KEY (2)				// �L�[�̍ő吔
#define MAX_STAGE (3)			// ���[�V�����̍ő吔

//------------------------------------------
// ���[�V�����N���X
//------------------------------------------
class CStage
{
public:
	//------------------------------------
	// �R���X�g���N�^�A�f�X�g���N�^
	//------------------------------------
	CStage();
	~CStage();

	//------------------------------------
	// �v���g�^�C�v�錾
	//------------------------------------
	HRESULT Init(void);								// ������
	void Uninit(void);
	void Update(void);
	void StageSet(const char *sStageFileName);							// ���[�V�����e�L�X�g��ǂݍ��ފ֐�
	CModel_Spawner *GetModel(int nNumModel) { return m_pStageModel[nNumModel]; }
	int	GetMaxModel(void) { return m_NumMaxModel; }
	int	GetMaxField(void) { return m_NumMaxField; }
	int	GetMaxEnemy(void) { return m_NumMaxEnemy; }
	int	GetMaxEnemyBaum(void) { return m_NumMaxEnemyBaum; }
	CField *GetField(int nNumField) { return m_pField[nNumField]; }
	CEnemy *GetEnemy(int nNumEnemy) { 
		
			return m_pEnemy[nNumEnemy];
		}
	CEnemy_Baum *GetEnemyBaum(int nNumEnemy) {
		
			return m_pEnemy_baum[nNumEnemy];
		 }

private:
	CModel_Spawner *m_pStageModel[MAX_STAGE_MODEL];	// 
	CModel_Spawner **m_pStageModelTYPE;
	CField **m_pField;
	CEnemy *m_pEnemy[MAX_STAGE_ENEMY];
	CEnemy_Baum *m_pEnemy_baum[MAX_STAGE_ENEMY];
	int		m_NumModel;
	int		m_NumMaxModel;
	int		m_NumMaxField;
	int		m_NumMaxEnemy;
	int		m_NumMaxEnemyBaum;

	char	**m_sModelFileName;
};
#endif _STAGE_H_