//=============================================================================
//
// �Q�[���̑I���̏��� [choose_game.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include"choose_game.h"
#include"renderer.h"
#include"manager.h"
#include"input.h"
#include"polygon.h"
#include"fade.h"
#include"effect.h"
#include"explanation.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
bool CChoose_Game::m_bNewGame = false;
CPolygon * CChoose_Game::m_pPolygon[CHOOSE_MAX] = {};
CExplanation * CChoose_Game::m_pExplanation = {};
CEffect * CChoose_Game::m_pEffect = NULL;
const char * CChoose_Game::m_pChooseUiFile = "data/TEXT/ChooseUi.txt";
bool CChoose_Game::m_bGame = false;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CChoose_Game::CChoose_Game(PRIORITY Priority) :CScene(PRIORITY_UI), ResetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f))
{
	m_bFade = true;
	m_nSituation = CHOOSE_NEWGAME;
	m_Size = D3DXVECTOR2(100, 50);
	m_bEffectUse = true;
	m_nRamNum = 0;
}


//=============================================================================
// �f�X�g���N�^
//=============================================================================
CChoose_Game::~CChoose_Game()
{

}

//=============================================================================
// �Q�[���̑I���̐�������
//=============================================================================
CChoose_Game *CChoose_Game::Create(D3DXVECTOR3 pos)
{
	// �Q�[���̑I���̃|�C���^�[����
	CChoose_Game* pChoose_Game = NULL;

	// ���I�������̊m��
	pChoose_Game = new CChoose_Game;

	// NULL�`�F�b�N
	if (pChoose_Game != NULL)
	{
		// �Q�[���̑I���̏������̌Ăяo��
		pChoose_Game->Init(pos);
	}
	return pChoose_Game;
}

//=============================================================================
// �Q�[���̑I���̏���������
//=============================================================================
HRESULT CChoose_Game::Init(D3DXVECTOR3 pos)
{
	// �Q�[���̑I����UI�̓ǂݍ��݂̌Ăяo��
	LodeChooseUI();

	// �G�t�F�N�g�̐��������̌Ăяo��
	m_pEffect = CEffect::Create(m_LodePos[m_nSituation]);

	// CHOOSE_MAX����
	for (int nCnt = 0; nCnt < CHOOSE_MAX; nCnt++)
	{	
		// �G�t�F�N�g�̐��������̌Ăяo��
		m_pPolygon[nCnt] = CPolygon::Create(m_LodePos[nCnt], m_LodeSize[nCnt], nCnt + 6);

		// �G�t�F�N�g�̐��������̌Ăяo��
		m_pExplanation = CExplanation::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), 18);		
	}

	// �����_���Ŕԍ������߂�
	m_nRamNum = rand() % 4;

	// �G�t�F�N�g�|���S���̐F�ݒ菈��
	SetPolygonColor();

	return S_OK;
}	// �Q�[���̑I���̏����������̏I��



//=============================================================================
// �Q�[���̑I���̏I������
//=============================================================================
void CChoose_Game::Uninit(void)
{
	// CHOOSE_MAX����
	for (int nCnt = 0; nCnt < CHOOSE_MAX; nCnt++)
	{
		if (m_pPolygon[nCnt] != NULL)
		{
			m_pPolygon[nCnt]->SetUse(false);
			m_pPolygon[nCnt] = NULL;
		}
	}
	
	// �Q�[���̑I���̉��
	Release();

}// �Q�[���̑I���̏I�������̏I��


//=============================================================================
// �Q�[���̑I���̍X�V����
//=============================================================================
void CChoose_Game::Update(void)
{
	// ���L�[��������Ď�
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_LEFT) == true)
	{
		m_nSituation--;
		if (m_nSituation < CHOOSE_NEWGAME)
		{
			m_nSituation = CHOOSE_MAX - 1;
		}		
	}
	// �E�L�[��������Ď�
	else if (CManager::GetInputKeyboard()->GetTrigger(DIK_RIGHT) == true)
	{
		m_nSituation++;
		if (m_nSituation > CHOOSE_MAX - 1)
		{
			m_nSituation = CHOOSE_NEWGAME;
		}		
	}
	// �F������������
	Resetcol();
	
	// �I������Ă�����̂̐F��N���ɂ���
	m_pPolygon[m_nSituation]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_pEffect->Setpos(m_LodePos[m_nSituation]);
	m_pExplanation->SetSize(D3DXVECTOR2(250, 200), 0);
	m_pExplanation->SetSize(D3DXVECTOR2(200, 50), m_nSituation + 1);
	m_pExplanation->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), m_nSituation+1);

	// �I�����ꂽ���̏���
	switch (m_nSituation)
	{
	// �V�����Q�[�����n�߂��Ƃ�
	case CHOOSE_NEWGAME:				
		m_pEffect->SetColor(D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), CEffect::POLYGON_BACK);
		if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN) == true && m_bFade)
		{
			// �V������ԂŃQ�[�����n�߂�����
			m_bNewGame = true;
			// �Q�[����ʂɑJ��
			CFade::SetFade(CManager::MODE_GAME);
			// �A���Ńt�F�[�h�J�ڂ������Ȃ��悤�ɂ���
			m_bFade = false;
			// �Q�[���ɑJ�ڂ�������ċ�����
			m_bGame = true;
		}
		break;

	// ��������Q�[�����n�߂��Ƃ�
	case CHOOSE_CONTINUE:
		//m_pExplanation[CHOOSE_CONTINUE]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pEffect->SetColor(D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), CEffect::POLYGON_BACK);
		if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN) == true && m_bFade)
		{
			// �Â������ԂŃQ�[�����n�߂�����
			m_bNewGame = false;
			// �Q�[����ʂɑJ��
			CFade::SetFade(CManager::MODE_GAME);
			// �A���Ńt�F�[�h�J�ڂ������Ȃ��悤�ɂ���
			m_bFade = false;
			// �Q�[���ɑJ�ڂ�������ċ�����
			m_bGame = true;
		}
		break;

	// �`���[�g���A���ɍs���Ƃ�
	case CHOOSE_TUTORIAL:	
		//m_pExplanation[CHOOSE_TUTORIAL]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pEffect->SetColor(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), CEffect::POLYGON_BACK);
		if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN) == true && m_bFade)
		{	
			// �`���[�g���A����ʂɑJ��
			CFade::SetFade(CManager::MODE_TUTORIAL);
			// �A���Ńt�F�[�h�J�ڂ������Ȃ��悤�ɂ���
			m_bFade = false;
			// �Q�[���ɑJ�ڂ��ĂȂ����ċ�����
			m_bGame = false;
		}
		break;

	// ���U���g�ɍs���Ƃ�
	case CHOOSE_RESULT:		
		//m_pExplanation[CHOOSE_RESULT]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pEffect->SetColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), CEffect::POLYGON_BACK);
		if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN) == true && m_bFade)
		{
			// ���U���g��ʂɑJ��
			CFade::SetFade(CManager::MODE_RESULT);
			// �A���Ńt�F�[�h�J�ڂ������Ȃ��悤�ɂ���
			m_bFade = false;
			// �Q�[���ɑJ�ڂ��ĂȂ����ċ�����
			m_bGame = false;
		}
		break;

	// ����ȊO�̂Ƃ�
	default:
		if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN) == true && m_bFade)
		{
			// �^�C�g����ʂɑJ��
			CFade::SetFade(CManager::MODE_TITLE);
			// �A���Ńt�F�[�h�J�ڂ������Ȃ��悤�ɂ���
			m_bFade = false;
		}
		break;
	}

}// �Q�[���̑I���̍X�V�����I��



//=============================================================================
// �Q�[���̑I���̕`�揈��
//=============================================================================
void CChoose_Game::Draw(void)
{	

}	// �Q�[���̑I���̕`�揈���I��

//=============================================================================
// �Q�[���̑I���̐F������������
//=============================================================================
void CChoose_Game::Resetcol(void)
{
	for (int nCnt = 0; nCnt < CHOOSE_MAX; nCnt++)
	{
		// �|���S���̐F��ݒ�
		m_pPolygon[nCnt]->SetColor(ResetCol);			

		// �G�t�F�N�g�̐��������̌Ăяo��
		m_pExplanation->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), nCnt+1);
	}
}

//=============================================================================
// �Q�[���̑I����UI�̓ǂݍ��ݏ���
//=============================================================================
void CChoose_Game::LodeChooseUI(void)
{
	// �J���`�t�@�C���I
	FILE *pFile = fopen(m_pChooseUiFile, "r");
	//--------------------------
	// �ǂݍ��ޗp�̕ϐ�
	//--------------------------
	char aFile[3][128] = {};
	char aName[128] = {};
	int nSetCnt = 0;
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
// �G�t�F�N�g�|���S���̐F�ݒ菈��
//=============================================================================
void CChoose_Game::SetPolygonColor(void)
{
	for (int nCnt = 0; nCnt < VTXBUFFER_MAX; nCnt++)
	{
		// �}�b�N�X�l�܂ōs������0�ɖ߂�
		if (m_nRamNum >= VTXBUFFER_MAX)
		{
			m_nRamNum = VTXBUFFER_ZERO;
		}
		// 0�܂ōs������}�b�N�X�l�ɖ߂�
		else if (m_nRamNum < VTXBUFFER_ZERO)
		{
			m_nRamNum = VTXBUFFER_THRD;
		}

		// �I�����ꂽ���̏���
		switch (m_nRamNum)
		{
		// ���_��0��������
		case VTXBUFFER_ZERO:
			m_pEffect->SetVtxBuffColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.5f), CEffect::POLYGON_BEFORE, m_nRamNum);
			break;

		// ���_��1��������
		case VTXBUFFER_FAST:
			m_pEffect->SetVtxBuffColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.5f), CEffect::POLYGON_BEFORE, m_nRamNum);
			break;

		// ���_��2��������
		case VTXBUFFER_SECOND:
			m_pEffect->SetVtxBuffColor(D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.5f), CEffect::POLYGON_BEFORE, m_nRamNum);
			break;

		// ���_��3��������
		case VTXBUFFER_THRD:
			m_pEffect->SetVtxBuffColor(D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.5f), CEffect::POLYGON_BEFORE, m_nRamNum);
			break;

		// ����ȊO�̂Ƃ�
		default:
			m_pEffect->SetVtxBuffColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f), CEffect::POLYGON_BEFORE, m_nRamNum);
			break;
		}
		m_nRamNum++;
	}
}