//=============================================================================
//
// ui�̊Ǘ��^���� [ui_manager.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include "ui_manager.h"
#include"input.h"
#include"manager.h"

/*
�C�ӂŎ�ޑI���������āA�g�������グ��

���̂�����[�h��������
���ׂă��[�h������̂����
*/
//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
CUi*CUI_Manager::m_pUi[LIMITUI] = {};
int CUI_Manager::m_nAllui = 0;

//=============================================================================
// UI�̃R���X�g���N�^
//=============================================================================
CUI_Manager::CUI_Manager() : CScene(), m_nMaxUI(10), m_MinUI(0)
{
	memset(&m_SavePos, 0, sizeof(m_SavePos));
	memset(&m_SaveSize, 0, sizeof(m_SaveSize));
	memset(&m_LodePos, 0, sizeof(m_LodePos));
	memset(&m_LodeSize, 0, sizeof(m_LodeSize));
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Color = D3DXCOLOR(255, 255, 255, 255);
	m_nTex = 0;
	m_nLodeUI = 0;
	m_bUse = true;
}

//=============================================================================
// UI�̃f�X�g���N�^
//=============================================================================
CUI_Manager::~CUI_Manager()
{

}

//=============================================================================
// UI�̐�������
//=============================================================================
CUI_Manager *CUI_Manager::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 Size)
{
	CUI_Manager *pUI_Manager = NULL;
	pUI_Manager = new CUI_Manager;

	// NULL�`�F�b�N
	if (pUI_Manager != NULL)
	{
		pUI_Manager->Init(pos, move, Size);
	}
	return pUI_Manager;
}


//=============================================================================
// UI�̏���������
//=============================================================================
HRESULT CUI_Manager::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	LodeUI();
	m_Pos = pos;
	m_Size = size;
	return S_OK;
}

//=============================================================================
// UI�̏���������
//=============================================================================
HRESULT CUI_Manager::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 Size)
{
	CUI_Manager::Init(pos,Size);
	m_Move = move;
	m_pUi[m_nAllui] = CUi::Create(pos, move, Size, m_nTex);
	return S_OK;
}

//=============================================================================
// UI�̏I������
//=============================================================================
void CUI_Manager::Uninit(void)
{
	for (int nCnt = 0; nCnt < m_nAllui; nCnt++)
	{
		if (m_pUi[nCnt] != NULL)
		{
			delete m_pUi[nCnt];
			m_pUi[nCnt] = NULL;
		}
	}

}

//=============================================================================
// UI�̍X�V����
//=============================================================================
void CUI_Manager::Update(void)
{
	CManager * pManager = NULL;

	CInputKeyboard *pInputKeyboard = NULL;
	pInputKeyboard = CManager::GetInputKeyboard();

	if (m_bUse)
	{
		D3DXVECTOR3 pos = m_pUi[m_nAllui]->GetPos();
		D3DXVECTOR3 move = m_pUi[m_nAllui]->GetMove();
		D3DXVECTOR3 size = m_pUi[m_nAllui]->GetSize();
		m_Color = m_pUi[m_nAllui]->GetColor();


		m_pUi[m_nAllui]->SetPos(pos);
		m_pUi[m_nAllui]->SetSize(size);
		m_pUi[m_nAllui]->SetCol(m_Color);		
		m_pUi[m_nAllui]->Update();

		bool bMove= m_pUi[m_nAllui]->GetBoolMove();	
		bool bSize = m_pUi[m_nAllui]->GetBoolSize();
		bool bSpeed = m_pUi[m_nAllui]->GetBoolSpeed();
		bool bAnim = m_pUi[m_nAllui]->GetBoolAnim();

		// �ő�l�𑝂₷
		if (pInputKeyboard->GetTrigger(DIK_LEFT) == true)
		{
			int nMax = m_nMaxUI;
			nMax++;
			(int)m_nMaxUI = nMax;

			if (LIMITUI <=m_nMaxUI)
			{
				(int)m_nMaxUI = LIMITUI;
			}
		}

		// �ő�l�����炷
		if (pInputKeyboard->GetTrigger(DIK_RIGHT) == true)
		{
			int nMin = m_nMaxUI;
			nMin--;
			(int)m_nMaxUI = nMin;

			if (m_MinUI>=m_nMaxUI)
			{
				(int)m_nMaxUI = m_MinUI;
			}
		}

		// �ړ������邩�ǂ���
		if (pInputKeyboard->GetTrigger(DIK_F1) == true)
		{
			if (bMove)
			{
				bMove = false;
			}
			else if (!bMove)
			{
				bMove = true;
			}
			m_pUi[m_nAllui]->SetBoolMove(bMove);
		}

		// �傫���ύX�����邩�ǂ���
		if (pInputKeyboard->GetTrigger(DIK_F2) == true)
		{
			if (bSize)
			{
				bSize = false;
			}
			else if (!bSize)
			{
				bSize = true;
			}
			m_pUi[m_nAllui]->SetBoolSize(bSize);
		}

		// �����ύX�����邩�ǂ���
		if (pInputKeyboard->GetTrigger(DIK_F3) == true)
		{
			if (bSpeed)
			{
				bSpeed = false;
			}
			else if (!bSpeed)
			{
				bSpeed = true;
			}
			m_pUi[m_nAllui]->SetBoolSpeed(bSpeed);
		}

		// �A�j���[�V���������邩�ǂ���
		if (pInputKeyboard->GetTrigger(DIK_F4) == true)
		{
			if (bAnim)
			{
				bAnim = false;
			}
			else if (!bAnim)
			{
				bAnim = true;
			}
			m_pUi[m_nAllui]->SetBoolAnim(bAnim);
		}

		// ENTER����������
		if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
		{
			SetUI(pos, size);
		}		
	}

	// F9����������
	if (pInputKeyboard->GetTrigger(DIK_F9) == true)
	{
		SaveUI();
	}

	// F8����������
	if (pInputKeyboard->GetTrigger(DIK_F8) == true)
	{
		LodeUI();
	}

	// F7����������
	if (pInputKeyboard->GetTrigger(DIK_F7) == true)
	{
		LodeSetNow();
	}

	// F6����������
	if (pInputKeyboard->GetTrigger(DIK_F6) == true)
	{
		LodeSetAll();
	}
}

//=============================================================================
// UI�̕`�揈��
//=============================================================================
void CUI_Manager::Draw(void)
{
}

//=============================================================================
// UI�̔z�u�֐�
//=============================================================================
void CUI_Manager::SetUI(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	if (m_bUse)
	{
		m_SavePos[m_nAllui] = pos;							// pos��ۑ�����
		m_SaveSize[m_nAllui] = size;						// size��ۑ�����
		m_pUi[m_nAllui]->SetPos(pos);						// pos��ݒ肷��
		m_pUi[m_nAllui]->SetSize(size);						// size��ݒ肷��
		m_Color.a = 0.5f;									// �������ɂ���
		m_pUi[m_nAllui]->SetCol(m_Color);					// �F��ۑ�
		m_pUi[m_nAllui]->Update();							// �X�V����
		m_pUi[m_nAllui]->SetBoolUse(false);					// �g���I�������`���ĕԂ�
		m_nAllui++;											// ����UI���Ăяo��
		m_nTex++;											// ���̃e�N�X�`����ݒ�

		if (m_nAllui < m_nMaxUI)								// �}�b�N�X�l�܂ł����ĂȂ�������
		{
			// UI����
			m_pUi[m_nAllui] = CUi::Create(m_Pos, m_Move, m_Size, m_nTex);
		}
		else
		{
			// UI_manager���g��Ȃ�����
			m_bUse = false;
		}
	}
}

//=============================================================================
// UI�̏����o������
//=============================================================================
void CUI_Manager::SaveUI(void)
{
	// �J���`�t�@�C���I
	FILE *pFile = fopen(SETUITEXT, "w");

	// �t�@�C������������
	if (pFile != NULL)
	{
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "# UI�ݒ�t�@�C��[Setui.txt]\n");
		fprintf(pFile, "# Author : �����ĕ�\n");
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "# �Z�b�g����UI�����̃e�L�X�g�t�@�C���ɏ����o���܂�\n");
		fprintf(pFile, "# UI���\n");
		fprintf(pFile, "#==============================================================================\n");		
		fprintf(pFile, "SCRIPT\t\t# ���̍s�͐�Ώ����Ȃ����ƁI\n");
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "# �ǂݍ���UI�̐�\n");
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "NUM_UI = %d\n", m_nAllui);
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "# �\������UI�̔z�u���\n");
		fprintf(pFile, "#==============================================================================\n");

		// UI�̐�����
		for (int nCnt = 0; nCnt < m_nAllui; nCnt++)
		{
			fprintf(pFile, "#%d��\n", nCnt + 1);
			fprintf(pFile, "SETUI\n");
			fprintf(pFile, "\tPOS = %.1f %.1f %.1f\n", m_SavePos[nCnt].x, m_SavePos[nCnt].y, m_SavePos[nCnt].z);	//���݂̈ʒu����������
			fprintf(pFile, "\tSIZE = %.1f %.1f\n", m_SaveSize[nCnt].x, m_SaveSize[nCnt].y);							//���݂̑傫������������
			fprintf(pFile, "END_SETUI\n\n");
		}
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
// UI�̓ǂݍ��ݏ���
//=============================================================================
void CUI_Manager::LodeUI(void)
{
	// �J���`�t�@�C���I
	FILE *pFile = fopen(SETUITEXT, "r");
	//--------------------------
	// �ǂݍ��ޗp�̕ϐ�
	//--------------------------
	char aFile[3][128] = {};
	char aName[128] = {};
	int nSetCnt = 0;
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �t�@�C������������
	if (pFile != NULL)
	{
		// �������[�v
		while (1)
		{
			fscanf(pFile, "%s", &aFile[0][0]);										// 1���ǂݍ���(2�s�ڈȍ~�͏㏑�������)

			if (strcmp(&aFile[0][0], "NUM_UI") == 0)								// NUM_UI������������
			{
				fscanf(pFile, "%s%d", &aName[0], &m_nLodeUI);						// UI�̐���ǂݍ���
			}

			while (strcmp(&aFile[0][0], "SETUI") == 0)								// SETUI������������
			{
				fscanf(pFile, "%s", &aFile[1]);										// 1���ǂݍ���(2�s�ڈȍ~�͏㏑�������)
				if (strcmp(&aFile[1][0], "POS") == 0)								// POS������������
				{
					fscanf(pFile, "%s%f%f%f", &aName[0], &pos.x, &pos.y, &pos.z);	// ���݂̈ʒu��ǂݍ���
				}
				else if (strcmp(&aFile[1][0], "SIZE") == 0)							// SIZE������������
				{
					fscanf(pFile, "%s%f%f", &aName[0], &size.x, &size.y);			// ���݂̑傫����ǂݍ���
				}
				else if (strcmp(&aFile[1][0], "END_SETUI") == 0)					// END_SETUI������������
				{
					m_LodePos[nSetCnt] = pos;										// �ǂݍ��񂾈ʒu���������o��SetPos�Ɉڂ�
					m_LodeSize[nSetCnt] = size;										// �ǂݍ��񂾑傫�����������o��SetSize�Ɉڂ�
					nSetCnt++;														// ���̕�
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

//=============================================================================
// �ǂݍ��݂񂾂��ׂĂ�UI��ݒu����
//=============================================================================
void CUI_Manager::LodeSetAll(void)
{
	// m_nLodeUI����
	for (int nCnt = 0; nCnt < m_nLodeUI; nCnt++)
	{
		SetUI(m_LodePos[nCnt], m_LodeSize[nCnt]);
	}
}

//=============================================================================
// �ǂݍ��݂񂾍���UI��ݒu����
//=============================================================================
void CUI_Manager::LodeSetNow(void)
{
	m_pUi[m_nAllui]->SetPos(m_LodePos[m_nAllui]);
	m_pUi[m_nAllui]->SetSize(m_LodeSize[m_nAllui]);
}
