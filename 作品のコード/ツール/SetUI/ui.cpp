//=============================================================================
//
// UI�̏��� [ui.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include "ui.h"
#include"input.h"
#include"manager.h"

//=============================================================================
// UI�̃R���X�g���N�^
//=============================================================================
CUi::CUi() : m_fMaxSpeed(50.0f), m_fMinSpeed(1.0f), m_fDiagonalSpeed(0.7f),m_fUpAngle(0.75f), m_fDownAngle(0.25f), m_ResetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f)), m_ResetSize(D3DXVECTOR3(100.0f, 50.0f, 0.0f)), m_ResetMove(D3DXVECTOR3(10.0f, 10.0f, 0.0f)), m_nMaxSetTexNum(LIMITUI -1)
{
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	
	m_col = D3DXCOLOR(255, 255, 255, 255);
	m_nTextureType = 0;
	m_pInputKeyboard = NULL;
	m_bUse = true;
	m_bMove = true;
	m_bSize = true;
	m_bSpeed = false;
}

//=============================================================================
// UI�̃f�X�g���N�^
//=============================================================================
CUi::~CUi()
{

}

//=============================================================================
// UI�̐�������
//=============================================================================
CUi *CUi::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 Size, int nType)
{
	// UI�̃|�C���^�[�𐶐�
	CUi *pUi = NULL;

	// ���I�������̊m��
	pUi = new CUi;

	// NULL�`�F�b�N
	if (pUi != NULL)
	{
		// UI�̏����������̌Ăяo��
		pUi->Init(pos, move, Size, nType);
	}
	return pUi;
}

//=============================================================================
// UI�̏���������
//=============================================================================
HRESULT CUi::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 Size, int nType)
{
	// �I�u�W�F�N�g2D�����������̌Ăяo��
	CScene2D::Init(pos, move, Size);
	SetTex(nType);
	m_Pos = pos;
	m_Move = move;
	m_Size = Size;
	LodeAnim();
	m_pInputKeyboard = CManager::GetInputKeyboard();
	return S_OK;
}

//=============================================================================
// UI�̏I������
//=============================================================================
void CUi::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// UI�̍X�V����
//=============================================================================
void CUi::Update(void)
{	
	if (m_bUse == true)
	{
		// �ړ����邩�ǂ���
		ChangeMoveUI();		

		// �傫���̕ύX�����邩�ǂ���
		ChangeSizeUI();

		//===============================
		// ��ʒ[�Ƃ̓����蔻��
		//===============================
		if (m_Pos.x + m_Size.x >= SCREEN_WIDTH)
		{
			m_Pos.x = SCREEN_WIDTH - m_Size.x;
		}
		else if (m_Pos.x - m_Size.x <= 0)
		{
			m_Pos.x = m_Size.x;
		}
		if (m_Pos.y + m_Size.y >= SCREEN_HEIGHT)
		{
			m_Pos.y = SCREEN_HEIGHT - m_Size.y;
		}
		else if (m_Pos.y - m_Size.y <= 0)
		{
			m_Pos.y = m_Size.y;
		}
		// �A�j���[�V�����ɂ����邩�ǂ���
		ChangeAnimeUI();

		// X����������
		if (m_pInputKeyboard->GetTrigger(DIK_X) == true)
		{
			m_Move = m_ResetMove;
		}

		// SPACE����������
		if (m_pInputKeyboard->GetTrigger(DIK_SPACE) == true)
		{
			m_Pos = m_ResetPos;
			m_Size = m_ResetSize;
		}

		CScene2D::SetPosition(m_Pos);
		CScene2D::SetSize(m_Size);
		CScene2D::SetColor(m_col);
		CScene2D::Update();
	}
}

//=============================================================================
// UI�̕`�揈��
//=============================================================================
void CUi::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// UI�̈ړ�����
//=============================================================================
void CUi::ChangeMoveUI(void)
{
	// �ړ����邩�ǂ���
	if (m_bMove)// �ړ�����Ȃ�
	{
		//�C�ӂŉ����ꂽ���ǂ���
		if (m_pInputKeyboard->GetPress(DIK_A) == true)//A��������
		{
			//A��W����������
			if (m_pInputKeyboard->GetPress(DIK_W) == true)
			{
				//����Ɉړ�
				m_Pos.x += sinf(D3DX_PI*-m_fUpAngle)*(m_Move.x*m_fDiagonalSpeed);
				m_Pos.y += cosf(D3DX_PI*-m_fUpAngle)*(m_Move.y*m_fDiagonalSpeed);
			}
			//A��S����������
			else if (m_pInputKeyboard->GetPress(DIK_S) == true)
			{
				//�����Ɉړ�
				m_Pos.x += sinf(D3DX_PI*-0.25f)*(m_Move.x*m_fDiagonalSpeed);
				m_Pos.y += cosf(D3DX_PI*-0.25f)*(m_Move.y*m_fDiagonalSpeed);
			}
			else //A����������
			{
				//���Ɉړ�
				m_Pos.x -= m_Move.x;
			}						  
		}
		else if (m_pInputKeyboard->GetPress(DIK_D) == true)//D��������
		{
			//D��W����������
			if (m_pInputKeyboard->GetPress(DIK_W) == true)
			{
				//�E��Ɉړ�
				m_Pos.x += sinf(D3DX_PI*m_fUpAngle)*(m_Move.x*m_fDiagonalSpeed);
				m_Pos.y += cosf(D3DX_PI*m_fUpAngle)*(m_Move.y*m_fDiagonalSpeed);
			}
			//D��W����������
			else if (m_pInputKeyboard->GetPress(DIK_S) == true)
			{
				//�E���Ɉړ�
				m_Pos.x += sinf(D3DX_PI*m_fDownAngle)*(m_Move.x*m_fDiagonalSpeed);
				m_Pos.y += cosf(D3DX_PI*m_fDownAngle)*(m_Move.y*m_fDiagonalSpeed);
			}
			else //D����������
			{
				//�E�Ɉړ�
				m_Pos.x += m_Move.x;
			}
		}

		//W����������
		if (m_pInputKeyboard->GetPress(DIK_W) == true)
		{
			//��Ɉړ�
			m_Pos.y -= m_Move.y;
		}
		//S����������
		if (m_pInputKeyboard->GetPress(DIK_S) == true)
		{
			//���Ɉړ�
			m_Pos.y += m_Move.y;
		}
	}
	//===============================
	// �����̍ŏ��l�̐ݒ�
	//===============================
	// ���̑������ŏ��l��菬�����ɂȂ�����
	if (m_Move.x <= m_fMinSpeed)
	{
		m_Move.x = m_fMinSpeed;
	}
	// �c�̑������ŏ��l��菬�����ɂȂ�����
	else if (m_Move.y <= m_fMinSpeed)
	{
		m_Move.y = m_fMinSpeed;
	}
	//===============================
	// �����̍ő�l�̐ݒ�
	//===============================
	// ���̑������ő�l���傫���ɂȂ�����
	if (m_Move.x >= m_fMaxSpeed)
	{
		m_Move.x = m_fMaxSpeed;
	}
	// �c�̑������ő�l���傫���ɂȂ�����
	else if (m_Move.y >= m_fMaxSpeed)
	{
		m_Move.y = m_fMaxSpeed;
	}
}

//=============================================================================
// UI�̑傫���̕ύX����
//=============================================================================
void CUi::ChangeSizeUI(void)
{
	// �傫���̕ύX�����邩�ǂ���
	if (m_bSize)
	{
		// ���̑傫����ύX
		if (m_pInputKeyboard->GetPress(DIK_Q) == true)
		{
			// ���ɑ傫������
			m_Size.x++;
		}
		else if (m_pInputKeyboard->GetPress(DIK_E) == true)
		{
			// ���ɏ���������
			m_Size.x--;
		}
		// �c�̑傫����ύX			
		if (m_pInputKeyboard->GetPress(DIK_Z) == true)
		{
			// �c�ɑ傫������
			m_Size.y++;
		}
		else if (m_pInputKeyboard->GetPress(DIK_C) == true)
		{
			// �c�ɏ���������
			m_Size.y--;
		}

		//===============================
		// �傫���̍ŏ��l�̐ݒ�
		//===============================
		// ���̑傫����0�ȉ��ɂȂ�����
		if (m_Size.x <= 0)
		{
			m_Size.x = 0;
		}
		// �c�̑傫����0�ȉ��ɂȂ�����
		else if (m_Size.y <= 0)
		{
			m_Size.y = 0;
		}
		//===============================
		// �傫���̍ő�l�̐ݒ�
		//===============================
		// ���̑傫�����ő�l�ɂȂ�����
		if (m_Size.x > SCREEN_WIDTH / 2)
		{
			m_Size.x = (SCREEN_WIDTH / 2);
		}
		// �c�̑傫�����ő�l�ɂȂ�����
		else if (m_Size.y > SCREEN_HEIGHT / 2)
		{
			m_Size.y = (SCREEN_HEIGHT / 2);
		}
	}
}

//=============================================================================
// UI�̃e�N�X�`���A�j���[�V��������
//=============================================================================
void CUi::ChangeAnimeUI(void)
{
	// �A�j���[�V����������Ȃ�
	if (m_bAnim)
	{		
		// �A�j���[�V�����̃J�E���g��i�߂�
		m_nCounterAnim++;

		// �A�j���[�V�����̃J�E���g���A�j���[�V�����̑����Ŋ����ė]�����̂�0��������(����؂ꂽ��)
		if (m_nCounterAnim % m_nAnimeSpeed == 0)
		{
			// �A�j���[�V�����̃p�^�[������i�߂�
			m_nPatternAnim++;

			// �A�j���[�V�����̃e�N�X�`���ݒ�
			CScene2D::SetTexAnime(m_nPatternAnim, m_fSizeAnimU, m_fMinSizeV, m_fMaxSizeV);

			// �A�j���[�V�����̃p�^�[�������p�^�[���̍ő吔�𒴂�����
			if (m_nPatternAnim >= m_nMaxPatternAnim)
			{
				// �A�j���[�V�����̃p�^�[�����̏�����
				m_nPatternAnim = 0;
				return;
			}
		}
	}
	else
	{
		// �A�j���[�V������̃e�N�X�`���̊��蓖�Ă�����������
		CScene2D::SetTex(0,1);
		m_nCounterAnim = 0;
		m_nPatternAnim = 0;
	}
}

//=============================================================================
// UI�̃e�N�X�`���̐ݒ菈��
//=============================================================================
void CUi::SetTex(int nTex)
{
	// �e�N�X�`���^�C�v�̐����ő�l�𒴂�����
	if (nTex > m_nMaxSetTexNum)
	{
		// �e�N�X�`���^�C�v�̐��ɍŏ��l�ɑ��
		nTex = 0;
	}
	// �e�N�X�`���^�C�v�̐����ŏ��l��艺��������
	else if (nTex < 0)
	{
		// �e�N�X�`���^�C�v�̐��ɍő�l�ɑ��
		nTex = m_nMaxSetTexNum;
	}

	// �e�N�X�`���̐ݒ菈��
	BindTextuer(nTex);

	// �ݒ肳�ꂽ�����i�[
	m_nTextureType = nTex;
}

//=============================================================================
// UI�̃e�N�X�`���A�j���[�V�����ǂݍ��ݏ���
//=============================================================================
void CUi::LodeAnim(void)
{
	//--------------------------
	// �ǂݍ��ޗp�̕ϐ�
	//--------------------------
	char aFile[2][128] = {};
	char aName[128] = {};
	// �J���`�t�@�C���I
	FILE *pFile = fopen("data/TEXT/AnimUI.txt", "r");

	// �t�@�C������������
	if (pFile != NULL)
	{
		// �������[�v
		while (1)
		{
			fscanf(pFile, "%s", &aFile[0][0]);												// 1���ǂݍ���(2�s�ڈȍ~�͏㏑�������)

			while (strcmp(&aFile[0][0], "SETANIME") == 0)									// SETANIME������������
			{
				fscanf(pFile, "%s", &aFile[1]);												// 1���ǂݍ���(2�s�ڈȍ~�͏㏑�������)
				if (strcmp(&aFile[1][0], "ANIMESPEED") == 0)								// ANIMESPEED������������
				{
					fscanf(pFile, "%s%d", &aName[0], &m_nAnimeSpeed);
				}
				else if (strcmp(&aFile[1][0], "ANIMEPATTERN") == 0)							// ANIMEPATTERN������������
				{
					fscanf(pFile, "%s%d", &aName[0], &m_nMaxPatternAnim);
				}
				else if (strcmp(&aFile[1][0], "ANIMESIZEU") == 0)							// ANIMESIZEU������������
				{
					fscanf(pFile, "%s%f", &aName[0], &m_fSizeAnimU);
				}
				else if (strcmp(&aFile[1][0], "ANIMEMINSIZEV") == 0)						// ANIMEMINSIZEV������������
				{
					fscanf(pFile, "%s%f", &aName[0], &m_fMinSizeV);
				}
				else if (strcmp(&aFile[1][0], "ANIMEMAXSIZEV") == 0)						// ANIMEMAXSIZEV������������
				{
					fscanf(pFile, "%s%f", &aName[0], &m_fMaxSizeV);
				}
				else if (strcmp(&aFile[1][0], "END_SETANIME") == 0)							// END_SETUI������������
				{
					break;																	// �������[�v�𔲂���
				}
			}
			if (strcmp(&aFile[0][0], "END_SCRIPT") == 0)									// END_SCRIPT������������
			{
				break;																		// �������[�v�𔲂���
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

