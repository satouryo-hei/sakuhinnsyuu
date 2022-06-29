//=============================================================================
//
// �G�̏��� [player2.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include"enemy.h"
#include"renderer.h"
#include"manager.h"
#include"input.h"
#include"model.h"
#include"shadow.h"
#include"title.h"

//=============================================================================
// �ÓI�����o�ϐ��̐錾
//=============================================================================
CShadow* CEnemy::m_pShadow = NULL;
CModel *CEnemy::m_pModel[20] = {};						// ���f���̃|�C���^�[�̐���

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEnemy::CEnemy(PRIORITY Priority) :CScene(PRIORITY_ENEMY)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nNumKey = 0;
}


//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEnemy::~CEnemy()
{

}

//=============================================================================
// �G�̐�������
//=============================================================================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos,const char *pFileName)
{
	// �G�̃|�C���^�[����
	CEnemy* pEnemy = NULL;

	// ���I�������̊m��
	pEnemy = new CEnemy;

	//�@NULL�`�F�b�N
	if (pEnemy != NULL)
	{
		pEnemy->Init(pos, pFileName);
	}
	return pEnemy;
}

//=============================================================================
// �G�̃f�t�H���g����������
//=============================================================================
HRESULT CEnemy::Init(D3DXVECTOR3 pos)
{
	m_pos = pos;

	return S_OK;
}	// �|���S���̏����������I��

//=============================================================================
// �G�̃I�[�o�[���[�h��������������
//=============================================================================
HRESULT CEnemy::Init(D3DXVECTOR3 pos, const char *pFileName)
{
	// �G�̃f�t�H���g�����������̌Ăяo��
	Init(pos);

	// �G�̃��f���ǂݍ��ݏ����̌Ăяo��
	LoadEnemy(pFileName);
	return S_OK;
}

//=============================================================================
// �G�̏I������
//=============================================================================
void CEnemy::Uninit(void)
{
	// m_nModel����
	for (int nCntParts = 0; nCntParts < m_nModel; nCntParts++)
	{
		// NULL�`�F�b�N
		if (m_pModel[nCntParts] != NULL)
		{
			// �e�N�X�`���̈ȊO��j��������
			m_pModel[nCntParts]->ReleaseModel();
			m_pModel[nCntParts] = NULL;
		}
	}

	// NULL�`�F�b�N
	if (m_pShadow != NULL)
	{
		// �e�̏I�������̌Ăяo��
		m_pShadow->Uninit();
		m_pShadow = NULL;
	}

	// �������
	Release();

}// �G�̏I�������I��


 //=============================================================================
 // �G�̍X�V����
 //=============================================================================
void CEnemy::Update(void)
{
}// �G�̍X�V�����I��



 //=============================================================================
 // �G�̕`�揈��
 //=============================================================================
void CEnemy::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();//�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxRotModel, mtxTransModel;//�v�Z�p�}�g���b�N�X
										  //�e�p�[�c�̃��[���h�}�g���b�N�X�̏�����gtryg
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRotModel, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRotModel);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTransModel, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTransModel);

	//�e�p�[�c�̃��[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
		
	//���f������
	for (int nCntParts = 0; nCntParts < m_nModel; nCntParts++)
	{
		// NULL�`�F�b�N
		if (m_pModel[nCntParts] != NULL)
		{
			// �`�揈���̌Ăяo��
			m_pModel[nCntParts]->Draw();
		}
	}
	

}// �|���S���̕`�揈���I��

 //=============================================================================
 // �G�̃��f���ǂݍ��ݏ���
 //=============================================================================
void CEnemy::LoadEnemy(const char *pFileName)
{
	//�f�o�C�X���擾����
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	FILE *pFile = fopen(pFileName, "r");
	//--------------------------
	// �ǂݍ��ޗp�̕ϐ�
	//--------------------------
	char aFile[128] = {};								// �ǂݍ��񂾃t�@�C���̃f�[�^�ϐ�
	char aFileName[10][128] = {};						// �ǂݍ��񂾃t�@�C���̃f�[�^���ꎞ�I�ɕۑ��p�ϐ�
	int nCntModelFile = 0;								// �ǂݍ��񂾃��f���̃t�@�C���𐔂���ϐ�
	int nIndex = 0;										// �ǂݍ��񂾃��f�������Ԗڂ���������ϐ�
	int nParent = 0;									// �e�̃��f�������Ԗڂ���������ϐ�
	bool bChara = false;								// �L�����N�^�[�̓ǂݍ��݂������邩�ǂ����ϐ�
	bool bPatu = false;									// �p�[�c�̓ǂݍ��݂������邩�ǂ����̕ϐ�
	int nCntModel = 0;									// ���f���̐������ɓǂݍ��񂾃t�@�C�������Ԃɐ��������Ă����ϐ�
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �t�@�C������������
	if (pFile != NULL)
	{
		// �������[�v
		while (1)
		{
			fscanf(pFile, "%s", &aFile[0]);													// 1���ǂݍ���(2�s�ڈȍ~�͏㏑�������)

			if (strcmp(&aFile[0], "NUM_MODEL") == 0)										// NUM_MODEL������������
			{
				fscanf(pFile, "%s%d", &aFile[0], &m_nModel);								// ���f���̐���ǂݍ���
			}

			if (strcmp(&aFile[0], "MODEL_FILENAME") == 0)									// MODEL_FILENAME������������
			{
				fscanf(pFile, "%s%s", &aFile[0], &aFileName[nCntModelFile]);				// ���f���t�@�C������ǂݍ���
				nCntModelFile++;
			}

			if (strcmp(&aFile[0], "CHARACTERSET") == 0)										// CHARACTERSET������������
			{
				bChara = true;
			}
			else if (strcmp(&aFile[0], "END_CHARACTERSET") == 0)							// END_CHARACTERSET������������
			{
				bChara = false;
			}

			if (bChara)
			{
				if (strcmp(&aFile[0], "PARTSSET") == 0)										// PARTSSET������������
				{
					bPatu = true;
				}
				else if (strcmp(&aFile[0], "END_PARTSSET") == 0)							// END_PARTSSET������������
				{
					m_pModel[nIndex] = CModel::Create(pos, rot, &aFileName[nCntModel][0]);	// ���f���̐���

					if (nParent != -1)														// �e�̃��f������������
					{
						m_pModel[nIndex]->SetParent(m_pModel[nParent]);
					}
					else
					{
						m_pModel[nIndex]->SetParent(NULL);
					}
					nCntModel++;
					bPatu = false;
				}

				if (bPatu)
				{
					if (strcmp(&aFile[0], "INDEX") == 0)								//���f���t�@�C���ǂݍ��݂̎��́A���Ԗڂ̃��f�����Ăяo����
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &nIndex);
					}
					else if (strcmp(&aFile[0], "PARENT") == 0)							//�e���f��
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &nParent);
					}
					else if (strcmp(&aFile[0], "POS") == 0)								// POS������������
					{
						fscanf(pFile, "%s%f%f%f", &aFile[0], &pos.x, &pos.y, &pos.z);	// ���݂̈ʒu��ǂݍ���
					}
					else if (strcmp(&aFile[0], "ROT") == 0)								// ROT������������
					{
						fscanf(pFile, "%s%f%f%f", &aFile[0], &rot.x, &rot.y, &rot.z);	// ���݂̉�]�ʂ�ǂݍ���
					}
				}
			}

			if (strcmp(&aFile[0], "END_SCRIPT") == 0)									// END_SCRIPT������������
			{
				break;																	// �������[�v�𔲂���
			}
		}
	}
	else
	{
		printf("�t�@�C�����ǂݍ��܂�܂���ł����B");
	}

	fclose(pFile);
}

//=============================================================================
// �G�̃��f���ǂݍ��ݏ���
//=============================================================================
D3DXVECTOR3 CEnemy::GetSize(void)
{
	m_Size = m_pModel[0]->GetSize();

	return m_Size;
}
