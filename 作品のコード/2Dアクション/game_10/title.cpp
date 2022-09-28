//=============================================================================
//
// �^�C�g���̏��� [title.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include "title.h"
#include "scene2D.h"
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"bg.h"
#include"fade.h"
#include"game.h"
#include"nextbutton.h"
#include"logo.h"

//=============================================================================
// �ÓI�����o�ϐ��̐錾
//=============================================================================
CBg* CTitle::m_pBg = NULL;
CLogo* CTitle::m_pLogo = NULL;
CNextBotton* CTitle::m_pNextBotton = NULL;

//=============================================================================
// �^�C�g���̃R���X�g���N�^
//=============================================================================
CTitle::CTitle(int nPriority) : CScene(PRIORITY_NOMAL), m_pTitleUiFile("data/TEXT/TitleUI.txt")
{
	m_bFade = false;
}

//=============================================================================
// �^�C�g���̃f�X�g���N�^
//=============================================================================
CTitle::~CTitle()
{

}

//=============================================================================
// �^�C�g���̏���������
//=============================================================================
HRESULT CTitle::Init(D3DXVECTOR3 pos)
{
	UILode();
	m_pBg = CBg::Create(pos, D3DXVECTOR2(SCREEN_WIDTH/2, SCREEN_HEIGHT/2), 14);
	m_pLogo = CLogo::Create(m_LodePos[0], m_LodeSize[0]);
	m_pNextBotton = CNextBotton::Create(m_LodePos[1], m_LodeSize[1]);
	return S_OK;
}

//=============================================================================
// �^�C�g���̏I������
//=============================================================================
void CTitle::Uninit(void)
{
	CScene::Release();

	if (m_pBg != NULL)
	{
		m_pBg->Uninit();
		m_pBg = NULL;
	}
}

//=============================================================================
// �^�C�g���̍X�V����
//=============================================================================
void CTitle::Update(void)
{
	CInputKeyboard *pInputKeyboard = NULL;
	pInputKeyboard = CManager::GetInputKeyboard();


	//�C�ӂŉ����ꂽ���ǂ���
	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true && !m_bFade)//ENTER��������
	{				
		CFade::SetFade(CManager::MODE_SELECT);
		m_bFade = true;
	}
}

//=============================================================================
// �^�C�g���̕`�揈��
//=============================================================================
void CTitle::Draw(void)
{

}

//=============================================================================
// �^�C�g����UI���[�h����
//=============================================================================
void CTitle::UILode(void)
{
	// �J���`�t�@�C���I
	FILE *pFile = fopen(m_pTitleUiFile, "r");
	//--------------------------
	// �ǂݍ��ޗp�̕ϐ�
	//--------------------------
	char aFile[3][128] = {};
	char aName[128] = {};
	int nSetCnt = 0;
	int nLodeUI = 0;
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR2 size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �t�@�C������������
	if (pFile != NULL)
	{
		// �������[�v
		while (1)
		{
			fscanf(pFile, "%s", &aFile[0][0]);										// 1���ǂݍ���(2�s�ڈȍ~�͏㏑�������)

			if (strcmp(&aFile[0][0], "NUM_UI") == 0)								// NUM_UI������������
			{
				fscanf(pFile, "%s%d", &aName[0], &nLodeUI);						// UI�̐���ǂݍ���
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