//=============================================================================
//
// �v���C���[�̏��� [player2.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include"player.h"
#include"renderer.h"
#include"manager.h"
#include"input.h"
#include"model.h"
#include"shadow.h"
#include"choose_game.h"
#include"bullet.h"
#include"camera.h"
#include"status_ui.h"
#include"bom.h"

//=============================================================================
// �ÓI�����o�ϐ��̐錾
//=============================================================================
CShadow* CPlayer::m_pShadow = NULL;
const char* CPlayer::m_pModelBom = "data/MODEL/bom.x";

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPlayer::CPlayer(PRIORITY Priority) :CScene(Priority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	memset(&m_pModel,NULL,sizeof(m_pModel));
	m_nNumKey = 0;
	m_nAttack = 0;
	m_nItem = 0;
}


//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPlayer::~CPlayer()
{

}

//=============================================================================
// �v���C���[�̐�������
//=============================================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	// �v���C���[�̃|�C���^�[����
	CPlayer* pPlayer = NULL;

	// ���I�������̊m��
	pPlayer = new CPlayer;

	// NULL�`�F�b�N
	if (pPlayer != NULL)
	{
		// ����������
		pPlayer->Init(pos);
		// �ړ��ʂ̐ݒ�
		pPlayer->m_move = move;
	}
	return pPlayer;
}

//=============================================================================
// �v���C���[�̏���������
//=============================================================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos)
{
	m_pos = pos;

	// �v���C���[�̓ǂݍ��ݏ���
	LoadPlayer(PLAYER_TEXT);

	// �V�����Q�[�����n�߂����ǂ����̎擾����
	bool bNewGame = CChoose_Game::GetNewGame();

	// �V�����Q�[�����n�߂Ė���������
	if (!bNewGame)
	{
		LoadStatas(STATUS_TEXT);
	}
	// �V�����n�߂Ă�����
	else
	{
		m_nAttack = 1;
	}
	// �e�̐�������
	m_pShadow = CShadow::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(20.0f, 0.0f, 20.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	return S_OK;
}	// �|���S���̏����������I��



//=============================================================================
// �v���C���[�̏I������
//=============================================================================
void CPlayer::Uninit(void)
{
	// �X�e�[�^�X�̏�������
	SaveStatas(STATUS_TEXT);

	// m_nModel����
	for (int nCntParts = 0; nCntParts < m_nModel; nCntParts++)
	{
		// NULL�`�F�b�N
		if (m_pModel[nCntParts] != NULL)
		{
			// �I�������̌Ăяo��
			m_pModel[nCntParts]->Uninit();
			m_pModel[nCntParts] = NULL;
		}
	}

	// NULL�`�F�b�N
	if (m_pShadow != NULL)
	{
		// �I�������̌Ăяo��
		m_pShadow->Uninit();
		m_pShadow = NULL;
	}

	// �������
	Release();

}// �|���S���̏I�������I��


//=============================================================================
// �v���C���[�̍X�V����
//=============================================================================
void CPlayer::Update(void)
{
	// �L�[�{�[�h�̃|�C���^�[�𐶐�
	CInputKeyboard *pInputKeyboard = NULL;

	// �}�l�[�W���[����L�[�{�[�h�̏����擾
	pInputKeyboard = CManager::GetInputKeyboard();

	// �X�e�[�^�XUI�̃|�C���^�[�𐶐��A�擾
	CStatus_UI * pStatus_UI = new CStatus_UI;

	// �J�����̌������擾
	D3DXVECTOR3 CameraRot = CManager::GetCamera()->GetRot();

	//�C�ӂŉ����ꂽ���ǂ���
	if (pInputKeyboard->GetPress(DIK_A) == true)//����������
	{
		//�C�ӂŉ����ꂽ���ǂ���
		if (pInputKeyboard->GetPress(DIK_W) == true)//����������
		{
			m_pos.z += m_move.z;
			m_pos.x -= m_move.x;
			m_rot.y = (D3DX_PI / 2) + (D3DX_PI / 4);

			//m_rot.y = CameraRot.y;
			//m_pos.x += sinf(m_rot.y)*m_move.x;
			//m_pos.z += cosf(m_rot.y)*m_move.z;
			//m_pos.x -= cosf(m_rot.y)*m_move.x;
			//m_pos.z += sinf(m_rot.y)*m_move.z;
		}
		//�C�ӂŉ����ꂽ���ǂ���
		else if (pInputKeyboard->GetPress(DIK_S) == true)//����������
		{
			m_pos.z -= m_move.z;
			m_pos.x -= m_move.x;
			m_rot.y = (D3DX_PI / 4);
		}
		// �v���X�ŉ���������Ȃ�������
		else
		{
			m_pos.x -= m_move.x;
			m_rot.y = (D3DX_PI / 2);
		}
	}
	else if (pInputKeyboard->GetPress(DIK_D) == true)//����������
	{
		//�C�ӂŉ����ꂽ���ǂ���
		if (pInputKeyboard->GetPress(DIK_W) == true)//����������
		{
			m_pos.z += m_move.z;
			m_pos.x += m_move.x;
			m_rot.y = -((D3DX_PI / 2) + (D3DX_PI / 4));
		}
		//�C�ӂŉ����ꂽ���ǂ���
		else if (pInputKeyboard->GetPress(DIK_S) == true)//����������
		{
			m_pos.z -= m_move.z;
			m_pos.x += m_move.x;
			m_rot.y = -(D3DX_PI / 4);
		}
		// �v���X�ŉ���������Ȃ�������
		else
		{
			m_pos.x += m_move.x;
			m_rot.y = -(D3DX_PI / 2);
		}
	}
	//�C�ӂŉ����ꂽ���ǂ���
	else if (pInputKeyboard->GetPress(DIK_W) == true)//����������
	{
		m_pos.z += m_move.z;
		m_rot.y = D3DX_PI;
	}
	else if (pInputKeyboard->GetPress(DIK_S) == true)//����������
	{
		m_pos.z -= m_move.z;
		m_rot.y = 0;
	}

	//�C�ӂŉ����ꂽ���ǂ���
	if (pInputKeyboard->GetTrigger(DIK_SPACE) == true)//����������
	{
		CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 30.0f, m_pos.z), D3DXVECTOR2(20, 20), 60);
	}

	// �A�C�e������3�ȏゾ������
	if (m_nItem >= 3)
	{
		if (pInputKeyboard->GetTrigger(DIK_B) == true)//����������
		{
			// �{���̐���
			CBom::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_pModelBom);

			// 3�����
			m_nItem -= 3;

			// ������0�����������Ȃ��Ă��܂�����
			if (m_nItem < 0)
			{
				m_nItem = 0;
			}
		}
	}
	// �e�̌��݂̈ʒu�̍X�V
	m_pShadow->SetPosition(m_pos);

	// ���̍U���͂̍X�V
	pStatus_UI->SetStatusNumber(m_nAttack);

}// �|���S���̍X�V�����I��



//=============================================================================
// �v���C���[�̕`�揈��
//=============================================================================
void CPlayer::Draw(void)
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
	//CModel::SetMtx(m_mtxWorld);
	//���f������
	for (int nCntParts = 0; nCntParts < m_nModel; nCntParts++)
	{
		m_pModel[nCntParts]->Draw();
	}

}// �|���S���̕`�揈���I��

//=============================================================================
// �v���C���[�̓ǂݍ��ݏ���
//=============================================================================
void CPlayer::LoadPlayer(const char *pFileName)
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
// �v���C���[�̃X�e�[�^�X���������ݏ���
//=============================================================================
void CPlayer::SaveStatas(const char *pStatasFile)
{
	// �J���`�t�@�C���I
	FILE *pFile = fopen(pStatasFile, "w");

	// �t�@�C������������
	if (pFile != NULL)
	{
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "# �v���C���[�̃X�e�[�^�X�ݒ�t�@�C��[Setui.txt]\n");
		fprintf(pFile, "# Author : �����ĕ�\n");
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "SCRIPT\t\t# ���̍s�͐�Ώ����Ȃ����ƁI\n");
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "# �v���C���[�̃X�e�[�^�X���\n");
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "SETSTATUS\n");
		fprintf(pFile, "\tATTACK = %d\n", m_nAttack);
		fprintf(pFile, "END_SETSTATUS\n\n");

		fprintf(pFile, "END_SCRIPT\t\t# ���̍s�͐�Ώ����Ȃ����ƁI\n");
	}
	else
	{
		printf("�t�@�C�����ǂݍ��܂�܂���ł����B");
	}
	// ����`�t�@�C���I
	fclose(pFile);
}

//=============================================================================
// �v���C���[�̃X�e�[�^�X��ǂݍ��ݏ���
//=============================================================================
void CPlayer::LoadStatas(const char *pStatasFile)
{
	// �J���`�t�@�C���I
	FILE *pFile = fopen(pStatasFile, "r");
	//--------------------------
	// �ǂݍ��ޗp�̕ϐ�
	//--------------------------
	char aFile[3][128] = {};
	char aName[128] = {};

	// �t�@�C������������
	if (pFile != NULL)
	{
		// �������[�v
		while (1)
		{
			fscanf(pFile, "%s", &aFile[0][0]);										// 1���ǂݍ���(2�s�ڈȍ~�͏㏑�������)

			while (strcmp(&aFile[0][0], "SETSTATUS") == 0)							// SETSTATUS������������
			{
				fscanf(pFile, "%s", &aFile[1]);										// 1���ǂݍ���(2�s�ڈȍ~�͏㏑�������)
				if (strcmp(&aFile[1][0], "ATTACK") == 0)							// ATTACK������������
				{
					fscanf(pFile, "%s%d", &aName[0], &m_nAttack);	// ���݂̈ʒu��ǂݍ���
				}
				else if (strcmp(&aFile[1][0], "END_SETSTATUS") == 0)					// END_SETUI������������
				{
					break;															// �������[�v�𔲂���
				}
			}
			if (strcmp(&aFile[0][0], "END_SCRIPT") == 0)							// END_SCRIPT������������
			{
				break;																// �������[�v�𔲂���
			}
		}
	}
	else
	{
		printf("�t�@�C�����ǂݍ��܂�܂���ł����B");
	}

	// ����`�t�@�C���I
	fclose(pFile);
}