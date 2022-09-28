//=============================================================================
//
// �G�̏��� [enemy.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include"enemy02.h"
#include"renderer.h"
#include"manager.h"
#include"player.h"
#include"choose_game.h"
#include"game.h"
#include"noneblock.h"
#include"bullet.h"
#include"explosion.h"
#include"score.h"
#include"homing.h"
#include"tutorial.h"

//=============================================================================
// �G�̃R���X�g���N�^
//=============================================================================
CEnemy02::CEnemy02(int nPriority) : CEnemy(PRIORITY_ENEMY)
{
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_OldPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Size = D3DXVECTOR2(0.0f, 0.0f);
	m_Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_State = STATE_NOMAL;
	m_nStateTime = 5;
	m_nLife = 4;
	m_bAlive = true;
}


//=============================================================================
// �G�̃f�X�g���N�^
//=============================================================================
CEnemy02::~CEnemy02()
{

}

//=============================================================================
// �G�̐�������
//=============================================================================
CEnemy02 *CEnemy02::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size)
{
	CEnemy02 * pEnemy = NULL;
	pEnemy = new CEnemy02;

	if (pEnemy != NULL)
	{		
		pEnemy->Bindtexture(24);
		pEnemy->Init(pos, move, Size);
	}
	return pEnemy;	
}

//=============================================================================
// �G�̏���������
//=============================================================================
HRESULT CEnemy02::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size)
{	
	m_Pos = pos;
	m_OldPos = pos;
	m_Move = move;
	m_Size = Size;
	CEnemy::Init(pos, move, Size);

	return S_OK;
}	// �G�̏����������I��



	//=============================================================================
	// �G�̏I������
	//=============================================================================
void CEnemy02::Uninit(void)
{
	CEnemy::Uninit();

}// �G�̏I�������I��


 //=============================================================================
 // �G�̍X�V����
 //=============================================================================
void CEnemy02::Update(void)
{	

	D3DXVECTOR3 Playerpos = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR2 PlayerSize = D3DXVECTOR2(0, 0);
	if (!m_bAlive)
	{
		Uninit();
		return;
	}

	m_OldPos = m_Pos;
	
	bool bGame = CChoose_Game::GetGame();

	if (bGame)
	{
		Playerpos = CGame::GetPlayer()->GetPos();
		PlayerSize = CGame::GetPlayer()->GetSize();
	}
	else if (!bGame)
	{
		Playerpos = CTutorial::GetPlayer()->GetPos();
		PlayerSize = CTutorial::GetPlayer()->GetSize();
	}

	// �v���C���[�ƓG�̎Εӂ̋����𑪂�A����Βl(a-b)
	float fRange = fabs(Playerpos.x - m_Pos.x);		// fabs = ��Βl
	
	if (fRange != 0)
	{
		// ���݂̈ʒu+�~�̖ʐς��v���C���[�ƓG�̎Εӂ̋������~�̖ʐψȏ�(�E�̏ꍇ)or�ȉ��i���̏ꍇ�j�ɓ����Ă�����
		if (100.0f >= fRange)
		{
			m_Move.x = ((Playerpos.x - m_Pos.x) / (fRange/2));			
		}
	}
			
	// �d��
	m_Move.y++;
	m_Pos += m_Move;
	
	BlockCollision();
	BulletCollision();
	H_BulletCollision();

	switch (m_State)
	{
	case STATE_NOMAL:
		m_Col = D3DXCOLOR(255, 255, 255, 255);
		m_nStateTime = 5;
		break;

	case STATE_HIT:
		m_Col = D3DXCOLOR(255, 0, 0, 255);
		m_nStateTime--;
		if (m_nStateTime <= 0)
		{
			m_State = STATE_NOMAL;
			m_nStateTime = 0;
		}
		break;

	default:
		break;
	}
	SetPos(m_Pos);
	SetRgba(m_Col.r, m_Col.g, m_Col.b, m_Col.a);

	if (m_nLife <= 0)
	{
		m_nLife = 0;

		if (bGame)
		{
			CScore * pScore = CGame::GetScore();
			if (pScore != NULL)
			{
				pScore->AddScore(100);
			}
		}
		CExplosion::Create(m_Pos,m_Size,8);
		m_bAlive = false;
	}
	CEnemy::Update();

}// �G�̍X�V�����I��



 //=============================================================================
 // �G�̕`�揈��
 //=============================================================================
void CEnemy02::Draw(void)
{
	CEnemy::Draw();

}	// �G�̕`�揈���I��

//=============================================================================
// �G�ƃu���b�N�̓����蔻�菈��
//=============================================================================
void CEnemy02::BlockCollision()
{
	CScene * pScene = CScene::GetScene(CScene::PRIORITY_BLOCK);

	while (pScene != NULL)
	{
		// �擾�����I�u�W�F�N�g�𕁒ʂ̃u���b�N�ɑ��
		CNoneBlock *pBlock = (CNoneBlock*)pScene;

		D3DXVECTOR3 Blockpos = pBlock->GetPosition();
		D3DXVECTOR2 Blocksize = pBlock->GetSize();

		if (m_Pos.x - m_Size.x < Blockpos.x + Blocksize.x &&				//�u���b�N�̉E�[
			m_Pos.x + m_Size.x > Blockpos.x - Blocksize.x &&				//�u���b�N�̍��[
			m_Pos.y - m_Size.y < Blockpos.y + Blocksize.y &&				//�u���b�N�̉���
			m_Pos.y + m_Size.y > Blockpos.y - Blocksize.y)					//�u���b�N�̏㕔
		{
			if (m_OldPos.y + m_Size.y <= Blockpos.y - Blocksize.y)			//�u���b�N�̏㕔			
			{
				m_Pos.y = Blockpos.y - m_Size.y - Blocksize.y;
				m_Move.y = 0.0f;
			}
			else if (m_OldPos.y - m_Size.y >= Blockpos.y + Blocksize.y)		//�u���b�N�̉���			
			{
				m_Pos.y = Blockpos.y + Blocksize.y + m_Size.y;
			}
			else if (m_OldPos.x - m_Size.x >= Blockpos.x + Blocksize.x)		//�u���b�N�̉E�[			
			{
				m_Pos.x = Blockpos.x + m_Size.x + Blocksize.x;
				m_Move.x = 1;
			}
			else if (m_OldPos.x + m_Size.x <= Blockpos.x - Blocksize.x)		//�u���b�N�̍��[			
			{
				m_Pos.x = Blockpos.x - m_Size.x - Blocksize.x;
				m_Move.x = -1;
			}
		}
		// �u���b�N�I�u�W�F�N�g�̎��̃I�u�W�F�N�g���擾
		CScene * pSceneNext = CScene::GetNext(pScene);
		pScene = pSceneNext;
	}
}

//=============================================================================
// �G�ƃu���b�N�̓����蔻�菈��
//=============================================================================
void CEnemy02::BulletCollision()
{
	CScene * pScene = CScene::GetScene(CScene::PRIORITY_BULLET);

	while (pScene != NULL)
	{
		// �擾�����I�u�W�F�N�g�𕁒ʂ̃u���b�N�ɑ��
		CBullet *pBullet = (CBullet*)pScene;

		D3DXVECTOR3 Bulletpos = pBullet->GetPosition();
		D3DXVECTOR2 Bulletsize = pBullet->GetSize();
		int nAttack = pBullet->GetAttack();

		if (m_Pos.x - m_Size.x <= Bulletpos.x + Bulletsize.x &&				//�u���b�N�̉E�[
			m_Pos.x + m_Size.x >= Bulletpos.x - Bulletsize.x &&				//�u���b�N�̍��[
			m_Pos.y - m_Size.y <= Bulletpos.y + Bulletsize.y &&				//�u���b�N�̉���
			m_Pos.y + m_Size.y >= Bulletpos.y - Bulletsize.y)					//�u���b�N�̏㕔
		{
			pBullet->SetUse(true);
			m_State = STATE_HIT;
			m_nLife -= nAttack;
		}
		// �u���b�N�I�u�W�F�N�g�̎��̃I�u�W�F�N�g���擾
		CScene * pSceneNext = CScene::GetNext(pScene);
		pScene = pSceneNext;
	}
}

//=============================================================================
// �G�ƃu���b�N�̓����蔻�菈��
//=============================================================================
void CEnemy02::H_BulletCollision()
{
	CScene * pScene = CScene::GetScene(CScene::PRIORITY_H_BULLET);

	while (pScene != NULL)
	{
		// �擾�����I�u�W�F�N�g�𕁒ʂ̃u���b�N�ɑ��
		CHoming *pHoming = (CHoming*)pScene;

		D3DXVECTOR3 Bulletpos = pHoming->GetPosition();
		D3DXVECTOR2 Bulletsize = pHoming->GetSize();
		//int nAttack = pBullet->GetAttack();

		if (m_Pos.x - m_Size.x <= Bulletpos.x + Bulletsize.x &&				//�u���b�N�̉E�[
			m_Pos.x + m_Size.x >= Bulletpos.x - Bulletsize.x &&				//�u���b�N�̍��[
			m_Pos.y - m_Size.y <= Bulletpos.y + Bulletsize.y &&				//�u���b�N�̉���
			m_Pos.y + m_Size.y >= Bulletpos.y - Bulletsize.y)					//�u���b�N�̏㕔
		{
			pHoming->SetUse(true);
			m_State = STATE_HIT;
			m_nLife -= 1;
		}
		// �u���b�N�I�u�W�F�N�g�̎��̃I�u�W�F�N�g���擾
		CScene * pSceneNext = CScene::GetNext(pScene);
		pScene = pSceneNext;
	}
}