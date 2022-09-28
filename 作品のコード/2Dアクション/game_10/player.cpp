//=============================================================================
//
// �v���C���[�̏��� [player.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include"player.h"
#include"renderer.h"
#include"manager.h"
#include"input.h"
#include"game.h"
#include"fade.h"
#include"bullet.h"
#include"homing.h"
#include"block.h"
#include"choose_game.h"
#include"noneblock.h"
#include"pushblock.h"
#include"moveblock.h"
#include"shotgun.h"
#include"enemy02.h"
/* �W�����v���̈ړ�����������
�Ȃ񂩋C���������@�����ۂ��Ȃ�
*/

//=============================================================================
// �ÓI�����o�֐��̐錾
//=============================================================================
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;
CBullet* CPlayer::m_pBullet = NULL;
CHoming* CPlayer::m_pHoming[MAX_BULLET] = {};
CShotgun* CPlayer::m_pShotgun = NULL;
int CPlayer::m_nItem = 0;
D3DXVECTOR3 CPlayer::m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
D3DXVECTOR2 CPlayer::m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
D3DXVECTOR3 CPlayer::m_posold = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
D3DXVECTOR3 CPlayer::m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
bool CPlayer::m_bJump = false;
bool CPlayer::m_bUse = true;
//=============================================================================
// �v���C���[�̃R���X�g���N�^
//=============================================================================
CPlayer::CPlayer(int nPriority) : CScene2D(PRIORITY_PLAYER), m_fSizeU(0.25f)
{
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
	m_nTimer = 0;
	m_nCoolTime = 50;
	m_Playertype = PLAYER_NOMAL;
	m_bDeath = false;
	m_bBullet = false;	
	m_bMovePush = true;
	m_nBulletType = 0;
	m_fSizeMaxV = 0.5f;
	m_fSizeMinV = 0.0f;
	m_nAttack = 2;
	m_fQuickening = 0.0f;
}


//=============================================================================
// �v���C���[�̃f�X�g���N�^
//=============================================================================
CPlayer::~CPlayer()
{

}

//=============================================================================
// �v���C���[�̐�������
//=============================================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size)
{
	CPlayer* pPlayer;

	pPlayer = new CPlayer;

	if (pPlayer != NULL)
	{
		pPlayer->Init(pos, Size);
		pPlayer->m_move = move;
		pPlayer->Bindtexture(16);
	}
	return pPlayer;
}

//=============================================================================
// �v���C���[�̏���������
//=============================================================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	int m_Life = 2;
	float m_fSpeed = 0;
	m_posold = pos;
	m_pos = pos;
	m_size = Size;
	m_bUse = true;
	CScene2D::Init(pos, Size);
	const bool bNewGame = CChoose_Game::GetNewGame();
	const bool bGame = CChoose_Game::GetGame();
	if (bNewGame)
	{
		m_nItem = 0;
#ifdef _DEBUG
		m_nItem = 100;
#endif // _DEBUG

	}
	else if (!bNewGame)
	{
		LoadItem();
	}

	if (!bGame)
	{
		m_nItem = 1;
	}

	CScene2D::SetTexAnime(m_nPatternAnim, m_fSizeU, m_fSizeMinV, m_fSizeMaxV);	

	return S_OK;
}	// �v���C���[�̏����������I��



	//=============================================================================
	// �v���C���[�̏I������
	//=============================================================================
void CPlayer::Uninit(void)
{
	SaveItem();
//	CScene2D::Uninit();
	Release();

}// �v���C���[�̏I�������I��


 //=============================================================================
 // �v���C���[�̍X�V����
 //=============================================================================
void CPlayer::Update(void)
{
	m_nCounterAnim++;
	if (!m_bUse)
	{
		Uninit();
		return;
	}
	CInputKeyboard *pInputKeyboard = NULL;

	pInputKeyboard = CManager::GetInputKeyboard();		
	
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_F1) == true)
	{
		m_nBulletType++;
		if (m_nBulletType >= SHOTTYPE_MAX)
		{
			m_nBulletType = SHOTTYPE_NOMAL;
		}
	}

	m_nTimer++;

	switch (m_Playertype)
	{
	case PLAYER_NOMAL:
		m_posold = m_pos;		
		
		//�C�ӂŉ����ꂽ���ǂ���
		if (pInputKeyboard->GetPress(DIK_A) /*&& !m_bJump*/)//����������
		{				
				m_fSizeMaxV = 1.0f;
				m_fSizeMinV = m_fSizeMaxV/2;
				m_pos.x -= m_move.x;
				m_fQuickening -= (m_move.x / 10);
				if (m_fQuickening <= -1.0f)
				{
					m_fQuickening = -1.0f;
				}
				m_bMovePush = false;				
				CScene2D::SetTexAnime(m_nPatternAnim, m_fSizeU, m_fSizeMinV, m_fSizeMaxV);
				SetAnimesion(m_nPatternAnim, m_fSizeU, m_fSizeMinV, m_fSizeMaxV);
		}
		else if (pInputKeyboard->GetPress(DIK_D) /*&& !m_bJump*/)//�E��������
		{							
				m_fSizeMaxV = 0.5f;
				m_fSizeMinV = 0.0f;
				m_pos.x += m_move.x;
				m_fQuickening += (m_move.x / 10);
				if (m_fQuickening >= 1.0f)
				{
					m_fQuickening = 1.0f;
				}
				m_bMovePush = true;
				CScene2D::SetTexAnime(m_nPatternAnim, m_fSizeU, m_fSizeMinV, m_fSizeMaxV);
				SetAnimesion(m_nPatternAnim, m_fSizeU, m_fSizeMinV, m_fSizeMaxV);
		}

		if (pInputKeyboard->GetTrigger(DIK_W) && !m_bJump)//��Ɉړ�
		{				
			m_move.y = -20.0f;
			m_bJump = true;
		}		
		
		//// �W�����v���̈ړ�����
		//if (m_bJump)
		//{
		//	//�C�ӂŉ����ꂽ���ǂ���
		//	if (pInputKeyboard->GetPress(DIK_A))//����������
		//	{
		//		m_fSizeMaxV = 1.0f;
		//		m_fSizeMinV = m_fSizeMaxV / 2;
		//		m_pos.x -= sinf(D3DX_PI*0.25f)*(m_move.x*0.9f);				
		//		m_bMovePush = false;
		//		CScene2D::SetTexAnime(m_nPatternAnim, m_fSizeU, m_fSizeMinV, m_fSizeMaxV);
		//		SetAnimesion(m_nPatternAnim, m_fSizeU, m_fSizeMinV, m_fSizeMaxV);
		//	}
		//	else if (pInputKeyboard->GetPress(DIK_D))//�E��������
		//	{
		//		m_fSizeMaxV = 0.5f;
		//		m_fSizeMinV = 0.0f;
		//		m_pos.x += (m_move.x / 10);				
		//		m_bMovePush = true;
		//		CScene2D::SetTexAnime(m_nPatternAnim, m_fSizeU, m_fSizeMinV, m_fSizeMaxV);
		//		SetAnimesion(m_nPatternAnim, m_fSizeU, m_fSizeMinV, m_fSizeMaxV);
		//	}
		//}


		if (m_bBullet)
		{
			m_nCoolTime--;
			if (m_nCoolTime < 0)
			{
				m_bBullet = false;
				m_nCoolTime = 0;
			}
		}

		if (pInputKeyboard->GetPress(DIK_SPACE) == true && !m_bBullet)
		{		
			Shot(m_nBulletType,m_bMovePush);
			//pManager->GetSound()->Play(CSound::SOUND_LABEL_SHOT000);		
			m_bBullet = true;
		}

		// �d��
		m_move.y++;
		m_pos.y += m_move.y;	

		if (m_pos.x + m_size.x >= SCREEN_WIDTH)
		{
			m_pos.x = SCREEN_WIDTH - m_size.x;			
		}
		else if (m_pos.x <= m_size.x)
		{
			m_pos.x = m_size.x;						
		}

		if (m_pos.y + m_size.y >= SCREEN_HEIGHT)
		{
			m_pos.y = SCREEN_HEIGHT - m_size.y;			
			m_bJump = false;
		}
		else if (m_pos.y <= m_size.y)
		{
			m_pos.y = m_size.y;			
			m_bJump = true;
		}
		break;

	case PLAYER_DEATH:

		if (m_nTimer % 5 == 0)
		{
			m_pos = D3DXVECTOR3(10.0f + m_size.x, 320.0f, 0.0f);

			m_Playertype = PLAYER_RESTARE;
		}
		m_bDeath = true;
		break;

	case PLAYER_RESTARE:
		if (m_pos.x >= 150)
		{
			m_Playertype = PLAYER_NOMAL;
		}
		else
		{
			m_pos.x += 5;
		}
		break;

		m_nTimer = 0;

	default:
		break;
	}

	EnemyColision();
	BlockColision();
	PushColision();
	MoveColision();
	SetPosition(m_pos);
	SetSize(m_size);
	CScene2D::Update();


}// �v���C���[�̍X�V�����I��

//=============================================================================
// �v���C���[�̕`�揈��
//=============================================================================
void CPlayer::Draw(void)
{
	CScene2D::Draw();

}	// �v���C���[�̕`�揈���I��


//=============================================================================
// �v���C���[�̒e�̏���
//=============================================================================
void CPlayer::Shot(int nType, bool bMovetype)
{
	int nHang = 0;	

	// �u���b�N�I�u�W�F�N�g���擾
	CScene * pScene = CScene::GetScene(CScene::PRIORITY_ENEMY);

	if (bMovetype)
	{
		nHang = 1;
	}
	else
	{
		nHang = -1;
	}
	
	switch (nType)
	{
	case SHOTTYPE_NOMAL:
		m_pBullet = CBullet::Create(m_pos, D3DXVECTOR3(nHang*30.0f, 0.0f, 0.0f), D3DXVECTOR2(20.0f, 20.0f), 30, true);
		m_nCoolTime = 40;
		break;

	case SHOTTYPE_HOMING:
		if (pScene != NULL)
		{
			CEnemy02 * pEnemy02 = (CEnemy02*)pScene;
			for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
			{
				m_pHoming[nCnt] = CHoming::Create(m_pos, D3DXVECTOR3(30.0f, 0.0f, 0.0f), D3DXVECTOR2(20.0f, 20.0f), D3DXVECTOR2(pEnemy02->GetPos().x, pEnemy02->GetPos().y), m_nAttack);
			}
		}
		else
		{
			for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
			{
				m_pHoming[nCnt] = CHoming::Create(m_pos, D3DXVECTOR3(30.0f, 0.0f, 0.0f), D3DXVECTOR2(20.0f, 20.0f), D3DXVECTOR2(rand() % 1280, 10), m_nAttack);
			}
		}
		
		m_nCoolTime = 100;
		break;

	case SHOTTYPE_SHOTGUN:
		m_pShotgun = CShotgun::Create(m_pos, D3DXVECTOR3(nHang*30.0f, nHang*20.0f, 0), D3DXVECTOR2(20.0f, 20.0f), 0);
		m_nCoolTime = 40;
		break;
	default:
		break;
	}
}

//=============================================================================
// �v���C���[�̃X�e�[�^�X�̏������ݏ���
//=============================================================================
void CPlayer::SaveItem(void)
{
	// �J���`�t�@�C���I
	FILE *pFile = fopen(ITEM_TEXT, "w");

	// �t�@�C������������
	if (pFile != NULL)
	{
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "# �v���C���[�̃A�C�e�����ݒ�t�@�C��[Setui.txt]\n");
		fprintf(pFile, "# Author : �����ĕ�\n");
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "SCRIPT\t\t# ���̍s�͐�Ώ����Ȃ����ƁI\n");		
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "# �v���C���[�̃A�C�e�������\n");
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "SETITEM\n");
		fprintf(pFile, "\tITEM = %d\n", m_nItem);
		fprintf(pFile, "END_SETITEM\n\n");
		
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
// �v���C���[�̃X�e�[�^�X�̓ǂݍ��ݏ���
//=============================================================================
void CPlayer::LoadItem(void)
{
	// �J���`�t�@�C���I
	FILE *pFile = fopen(ITEM_TEXT, "r");
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

			while (strcmp(&aFile[0][0], "SETITEM") == 0)							// SETSTATUS������������
			{
				fscanf(pFile, "%s", &aFile[1]);										// 1���ǂݍ���(2�s�ڈȍ~�͏㏑�������)
				if (strcmp(&aFile[1][0], "ITEM") == 0)							// ATTACK������������
				{
					fscanf(pFile, "%s%d", &aName[0], &m_nItem);	// ���݂̈ʒu��ǂݍ���
				}
				else if (strcmp(&aFile[1][0], "END_SETITEM") == 0)					// END_SETUI������������
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

//=============================================================================
// �����Ȃ��u���b�N�̓����蔻��
//=============================================================================
void CPlayer::BlockColision(void)
{
	/*�I�u�W�F�N�g���������ē����蔻����킯�邩
	�u���b�Ncpp�Ń^�C�v���������ē����蔻��𕪂��邩*/

	// �u���b�N�I�u�W�F�N�g���擾
	CScene * pScene = CScene::GetScene(CScene::PRIORITY_BLOCK);

	// pScene��NULL����Ȃ��ꍇ���[�v������
	while (pScene != NULL)
	{
		// �擾�����I�u�W�F�N�g�𕁒ʂ̃u���b�N�ɑ��
		CNoneBlock *pBlock = (CNoneBlock*)pScene;

		D3DXVECTOR3 Blockpos = pBlock->GetPosition();
		D3DXVECTOR2 Blocksize = pBlock->GetSize();

		if (m_pos.x - m_size.x < Blockpos.x + Blocksize.x &&				// �v���C���[�̍��[<�u���b�N�̉E�[
			m_pos.x + m_size.x > Blockpos.x - Blocksize.x &&				// �v���C���[�̉E�[>�u���b�N�̍��[
			m_pos.y - m_size.y < Blockpos.y + Blocksize.y &&				// �v���C���[�̏�[<�u���b�N�̉��[
			m_pos.y + m_size.y > Blockpos.y - Blocksize.y)					// �v���C���[�̉��[>�u���b�N�̏�[
		{																	   
			if (m_posold.y + m_size.y <= Blockpos.y - Blocksize.y)			// �O��̃v���C���[�̉��[<=�u���b�N�̏�[
			{																   
				m_pos.y = Blockpos.y - m_size.y - Blocksize.y;				   
				m_bJump = false;											   
				m_move.y = 0.0f;											   
			}																   
			else if (m_posold.y - m_size.y >= Blockpos.y + Blocksize.y)		// �O��̃v���C���[�̏�[>=�u���b�N�̉��[
			{																   
				m_pos.y = Blockpos.y + Blocksize.y + m_size.y;				   
				m_move.y = 0.0f;											   
			}																   
			else if (m_posold.x - m_size.x >= Blockpos.x + Blocksize.x)		// �O��̃v���C���[�̍��[>=�u���b�N�̉E�[			
			{																   
				m_pos.x = Blockpos.x + m_size.x + Blocksize.x;				   
				m_bJump = false;											   
			}																   
			else if (m_posold.x + m_size.x <= Blockpos.x - Blocksize.x)		// �O��̃v���C���[�̉E�[<=�u���b�N�̍��[
			{
				m_pos.x = Blockpos.x - m_size.x - Blocksize.x;
				m_bJump = false;
			}
		}
		// ���݂̃I�u�W�F�N�g�̎����擾
		CScene * pSceneNext = CScene::GetNext(pScene);
		pScene = pSceneNext;
	}
}

//=============================================================================
// �����u���b�N�̓����蔻��
//=============================================================================
void CPlayer::PushColision(void)
{
	// �����u���b�N�I�u�W�F�N�g���擾
	CScene * pScene = CScene::GetScene(CScene::PRIORITY_PUSHBLOCK);	

	// pScene��NULL����Ȃ��ꍇ���[�v������
	while (pScene != NULL)
	{		
		CPushBlock *pBlock = (CPushBlock*)pScene;
		D3DXVECTOR3 Blockpos = pBlock->GetPos();
		D3DXVECTOR3 Blockposold = pBlock->GetPosold();
		D3DXVECTOR3 Blockmove = pBlock->GetMove();
		D3DXVECTOR2 Blocksize = pBlock->Getsize();
		
		if (m_pos.x - m_size.x < Blockpos.x + Blocksize.x &&				// �v���C���[�̍��[<�u���b�N�̉E�[
			m_pos.x + m_size.x > Blockpos.x - Blocksize.x &&				// �v���C���[�̉E�[>�u���b�N�̍��[
			m_pos.y - m_size.y < Blockpos.y + Blocksize.y &&				// �v���C���[�̏�[<�u���b�N�̉��[
			m_pos.y + m_size.y > Blockpos.y - Blocksize.y)					// �v���C���[�̉��[>�u���b�N�̏�[
		{
			if (m_posold.y + m_size.y <= Blockpos.y - Blocksize.y)			// �O��̃v���C���[�̉��[<=�u���b�N�̏�[
			{
				m_pos.y = Blockpos.y - Blocksize.y - m_size.y;
				m_move.y = 0.0f;
				m_bJump = false;
			}
			else if (m_posold.y - m_size.y >= Blockpos.y + Blocksize.y)		// �O��̃v���C���[�̏�[>=�u���b�N�̉��[
			{
				m_pos.y = Blockpos.y + Blocksize.y + m_size.y;
			}
			if (m_posold.x + m_size.x <= Blockpos.x - Blocksize.x)			// �O��̃v���C���[�̍��[>=�u���b�N�̉E�[
			{																
				m_pos.x = Blockpos.x - m_size.x - Blocksize.x;
				m_move.x = 2;
				Blockmove.x = m_move.x;
				Blockpos.x += Blockmove.x;
				pBlock->SetPos(Blockpos);									
				pBlock->SetMove(Blockmove);
			}
			if (m_posold.x - m_size.x >= Blockpos.x + Blocksize.x)			// �O��̃v���C���[�̉E�[<=�u���b�N�̍��[
			{
				m_pos.x = Blockpos.x + m_size.x + Blocksize.x;
				m_move.x = 2;
				Blockmove.x = m_move.x;				
				Blockpos.x -= Blockmove.x;
				pBlock->SetPos(Blockpos);
				pBlock->SetMove(Blockmove);
			}
		}
		// �������I�u�W�F�N�g���v���C���[����Ȃ�
		else
		{
			m_move.x = 10;
		}
		// ���݂̃I�u�W�F�N�g�̎����擾
		CScene * pSceneNext = CScene::GetNext(pScene);
		pScene = pSceneNext;
	}
}

//=============================================================================
// �ړ��u���b�N�̓����蔻��
//=============================================================================
void CPlayer::MoveColision(void)
{
	// �ړ��u���b�N�̃I�u�W�F�N�g���擾
	CScene * pScene = CScene::GetScene(CScene::PRIORITY_MOVEBLOCK);	

	// pScene��NULL����Ȃ��ꍇ���[�v������
	while (pScene != NULL)
	{
		CMoveBlock *pBlock = (CMoveBlock*)pScene;
		D3DXVECTOR3 Blockpos = pBlock->GetPos();
		D3DXVECTOR3 Blockposold = pBlock->GetPosold();
		D3DXVECTOR3 Blockmove = pBlock->GetMove();
		D3DXVECTOR2 Blocksize = pBlock->Getsize();

		if (m_pos.x + m_size.x >= Blockpos.x - Blocksize.x &&			// �v���C���[�̍��[<=�u���b�N�̉E�[���[���[
			m_pos.x - m_size.x <= Blockpos.x + Blocksize.x &&			// �v���C���[�̉E�[>=�u���b�N�̍��[�E�[�E�[
			m_pos.y + m_size.y >= Blockpos.y - Blocksize.y &&			// �v���C���[�̏�[<=�u���b�N�̉��[��������
			m_pos.y - m_size.y <= Blockpos.y + Blocksize.y)				// �v���C���[�̉��[>=�u���b�N�̏�[
		{
			if (m_posold.x + m_size.x <= Blockpos.x - Blocksize.x)		// �O��̃v���C���[�̉E�[<=�u���b�N�̍��[
			{
				m_pos.x = Blockpos.x - m_size.x - Blocksize.x;

				// �u���b�N���E�Ɉړ������Ă���Ƃ�
				if (pBlock->GetMoveBlock() == CMoveBlock::MOVE_RIGHT)
				{
					// �u���b�N���ړ����Ă�Ƃ��̃v���C���[�̈ړ�����
					m_pos.x -= Blockmove.x;
				}
			}
			if (m_posold.x - m_size.x >= Blockpos.x + Blocksize.x)		// �O��̃v���C���[�̍��[>=�u���b�N�̉E�[
			{
				m_pos.x = Blockpos.x + m_size.x + Blocksize.x;

				// �u���b�N���E�Ɉړ������Ă���Ƃ�
				if (pBlock->GetMoveBlock() == CMoveBlock::MOVE_LEFT)
				{
					// �u���b�N���ړ����Ă�Ƃ��̃v���C���[�̈ړ�����
					m_pos.x += Blockmove.x;
				}
			}
		}
		// ���݂̃I�u�W�F�N�g�̎����擾
		CScene * pSceneNext = CScene::GetNext(pScene);
		pScene = pSceneNext;
	}
}

void CPlayer::EnemyColision(void)
{
	// �G�̃I�u�W�F�N�g���擾
	CScene * pScene = CScene::GetScene(CScene::PRIORITY_ENEMY);

	// pScene��NULL����Ȃ��ꍇ���[�v������
	while (pScene != NULL)
	{
		CEnemy02 *pEnemy = (CEnemy02*)pScene;
		D3DXVECTOR3 Enemypos = pEnemy->GetPos();
		D3DXVECTOR3 Enemyposold = pEnemy->GetPosold();
		D3DXVECTOR3 Enemymove = pEnemy->GetMove();
		D3DXVECTOR2 Enemysize = pEnemy->GetSize();

		if (m_pos.x - m_size.x < Enemypos.x + Enemysize.x &&				// �v���C���[�̍��[<�u���b�N�̉E�[
			m_pos.x + m_size.x > Enemypos.x - Enemysize.x &&				// �v���C���[�̉E�[>�u���b�N�̍��[
			m_pos.y - m_size.y < Enemypos.y + Enemysize.y &&				// �v���C���[�̏�[<�u���b�N�̉��[
			m_pos.y + m_size.y > Enemypos.y - Enemysize.y)					// �v���C���[�̉��[>�u���b�N�̏�[
		{
			pEnemy->SetAlive(false);
			m_nItem = 0;
			m_bUse = false;
			CFade::SetFade(CManager::MODE_RESULT);
		}		
		// ���݂̃I�u�W�F�N�g�̎����擾
		CScene * pSceneNext = CScene::GetNext(pScene);
		pScene = pSceneNext;
	}
}


//=============================================================================
// �v���C���[�̃A�j���[�V�����ݒ菈��
//=============================================================================
void CPlayer::SetAnimesion(int nPatternAnim, float fSizeAnimU, float fSizeMinV, float fSizeMaxV)
{
	if (m_nCounterAnim % 10 == 0)
	{
		m_nPatternAnim++;

		CScene2D::SetTexAnime(nPatternAnim, fSizeAnimU, fSizeMinV, fSizeMaxV);

		if (m_nPatternAnim >= 4)
		{
			m_nPatternAnim = 0;
			return;
		}
	}
}