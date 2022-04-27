//=============================================================================
//
// UI�̏��� [ui.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include "ui.h"
#include"input.h"
#include"manager.h"

/*
�ł����imgui(���ނ���)��������
*/

//=============================================================================
// UI�̃R���X�g���N�^
//=============================================================================
CUi::CUi() : MaxSpeed(50.0f), MinSpeed(1.0f)
{
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Speed = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	m_col = D3DXCOLOR(255, 255, 255, 255);
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
	CUi *pUi = NULL;
	pUi = new CUi;

	// NULL�`�F�b�N
	if (pUi != NULL)
	{
		pUi->Init(pos, move, Size, nType);
	}
	return pUi;
}

//=============================================================================
// UI�̏���������
//=============================================================================
HRESULT CUi::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 Size, int nType)
{
	CScene2D::Init(pos, move, Size);
	CScene2D::BindTextuer(nType);
	m_Pos = pos;
	m_Move = move;
	m_Size = Size;
	m_pInputKeyboard = CManager::GetInputKeyboard();
	LodeAnim();
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

		// ������ύX�����邩�ǂ���
		ChangeSpeedUI();

		// ������ύX�����邩�ǂ���
		ChangeAnimeUI();

		// X����������
		if (m_pInputKeyboard->GetTrigger(DIK_X) == true)
		{
			m_Move = D3DXVECTOR3(10.0f, 10.0f, 0.0f);
		}

		// SPACE����������
		if (m_pInputKeyboard->GetTrigger(DIK_SPACE) == true)
		{
			m_Pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
			m_Size = D3DXVECTOR3(100.0f, 50.0f, 0.0f);
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
				m_Pos.x += sinf(D3DX_PI*-0.75f)*(m_Move.x*0.7f);
				m_Pos.y += cosf(D3DX_PI*-0.75f)*(m_Move.y*0.7f);
			}
			//A��S����������
			else if (m_pInputKeyboard->GetPress(DIK_S) == true)
			{
				//�����Ɉړ�
				m_Pos.x += sinf(D3DX_PI*-0.25f)*(m_Move.x*0.7f);
				m_Pos.y += cosf(D3DX_PI*-0.25f)*(m_Move.y*0.7f);
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
				m_Pos.x += sinf(D3DX_PI*0.75f)*(m_Move.x*0.7f);
				m_Pos.y += cosf(D3DX_PI*0.75f)*(m_Move.y*0.7f);
			}
			//D��W����������
			else if (m_pInputKeyboard->GetPress(DIK_S) == true)
			{
				//�E���Ɉړ�
				m_Pos.x += sinf(D3DX_PI*0.25f)*(m_Move.x*0.7f);
				m_Pos.y += cosf(D3DX_PI*0.25f)*(m_Move.y*0.7f);
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
// UI�̈ړ��ʂ̐��䏈��
//=============================================================================
void CUi::ChangeSpeedUI(void)
{
	// ������ύX�����邩�ǂ���
	if (m_bSpeed)
	{
		//===============================
		// �ړ��ʂ̕ύX
		//===============================
		// F����������
		if (m_pInputKeyboard->GetPress(DIK_F) == true)
		{
			m_Move.x += m_Speed.x;
		}
		// H����������
		else if (m_pInputKeyboard->GetPress(DIK_H) == true)
		{
			m_Move.x -= m_Speed.x;
		}
		// T����������
		if (m_pInputKeyboard->GetPress(DIK_T) == true)
		{
			m_Move.y += m_Speed.y;
		}
		// G����������
		else if (m_pInputKeyboard->GetPress(DIK_G) == true)
		{
			m_Move.y -= m_Speed.y;
		}

		//===============================
		// �ړ��ʂ̌v�Z�l�̕ύX
		//===============================
		// R����������
		if (m_pInputKeyboard->GetTrigger(DIK_R) == true)
		{
			m_Speed.x = 0.1f;
		}
		// Y����������
		else if (m_pInputKeyboard->GetTrigger(DIK_Y) == true)
		{
			m_Speed.y = 0.1f;
		}
		// V����������
		if (m_pInputKeyboard->GetTrigger(DIK_V) == true)
		{
			m_Speed.x = 1.0f;
		}
		// N����������
		else if (m_pInputKeyboard->GetTrigger(DIK_N) == true)
		{
			m_Speed.y = 1.0f;
		}

		//===============================
		// �����̍ŏ��l�̐ݒ�
		//===============================
		// ���̑������ŏ��l��菬�����ɂȂ�����
		if (m_Move.x < MinSpeed)
		{
			m_Move.x = MinSpeed;
		}
		// �c�̑������ŏ��l��菬�����ɂȂ�����
		else if (m_Move.y < MinSpeed)
		{
			m_Move.y = MinSpeed;
		}
		//===============================
		// �����̍ő�l�̐ݒ�
		//===============================
		// ���̑������ő�l���傫���ɂȂ�����
		if (m_Move.x > MaxSpeed)
		{
			m_Move.x = MaxSpeed;
		}
		// �c�̑������ő�l���傫���ɂȂ�����
		else if (m_Move.y > MaxSpeed)
		{
			m_Move.y = MaxSpeed;
		}
	}
}

//=============================================================================
// UI�̃e�N�X�`���A�j���[�V��������
//=============================================================================
void CUi::ChangeAnimeUI(void)
{
	if (m_bAnim)
	{
		m_nCounterAnim++;

		if (m_nCounterAnim % m_nAnimeSpeed == 0)
		{
			m_nPatternAnim++;

			CScene2D::SetTexAnime(m_nPatternAnim, m_fSizeAnimU, m_fMinSizeV, m_fMaxSizeV);

			if (m_nPatternAnim >= m_nMaxPatternAnim)
			{
				return;
			}
		}
	}
}

//=============================================================================
// UI�̃e�N�X�`���A�j���[�V�����ǂݍ��ݏ���
//=============================================================================
void CUi::LodeAnim(void)
{
	//--------------------------
	// �ǂݍ��ޗp�̕ϐ�
	//--------------------------
	char aFile[3][128] = {};
	char aName[128] = {};
	// �J���`�t�@�C���I
	FILE *pFile = fopen("data/TEXT/AnimUI.txt", "r");

	// �t�@�C������������
	if (pFile != NULL)
	{
		// �������[�v
		while (1)
		{
			fscanf(pFile, "%s", &aFile[0][0]);										// 1���ǂݍ���(2�s�ڈȍ~�͏㏑�������)

			while (strcmp(&aFile[0][0], "SETANIME") == 0)								// SETUI������������
			{
				fscanf(pFile, "%s", &aFile[1]);										// 1���ǂݍ���(2�s�ڈȍ~�͏㏑�������)
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
				else if (strcmp(&aFile[1][0], "ANIMEMINSIZEV") == 0)							// ANIMEMINSIZEV������������
				{
					fscanf(pFile, "%s%f", &aName[0], &m_fMinSizeV);
				}
				else if (strcmp(&aFile[1][0], "ANIMEMAXSIZEV") == 0)							// ANIMEMAXSIZEV������������
				{
					fscanf(pFile, "%s%f", &aName[0], &m_fMaxSizeV);
				}
				else if (strcmp(&aFile[1][0], "END_SETANIME") == 0)					// END_SETUI������������
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