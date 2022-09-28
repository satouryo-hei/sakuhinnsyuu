//=============================================================================
//
// �u���b�N�̏��� [score.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include "moveblock.h"
#include"player.h"
#include"enemy.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
CMoveBlock::MOVE CMoveBlock::m_MoveBlock = CMoveBlock::MOVE_NONE;	// �u���b�N�̈ړ����

//=============================================================================
// �u���b�N�̃R���X�g���N�^
//=============================================================================
CMoveBlock::CMoveBlock(int nPriority) : CScene2D(PRIORITY_MOVEBLOCK)
{
	m_pos = D3DXVECTOR3(0, 0, 0);
	m_move = D3DXVECTOR3(0, 0, 0);
	m_size = D3DXVECTOR2(0, 0);	
	m_bMove = true;
}

//=============================================================================
// �u���b�N�̃f�X�g���N�^
//=============================================================================
CMoveBlock::~CMoveBlock()
{

}

//=============================================================================
// �u���b�N�̐�������
//=============================================================================
CMoveBlock *CMoveBlock::Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size, D3DXVECTOR3 move,
	int nCondition, float fMin, float fMax, int nTex)
{
	CMoveBlock *pMoveBlock = NULL;
	pMoveBlock = new CMoveBlock;

	if (pMoveBlock != NULL)
	{
		pMoveBlock->Init(pos, Size);
		pMoveBlock->m_nBlockCondition = nCondition;
		pMoveBlock->m_fMin = fMin;
		pMoveBlock->m_fMax = fMax;
		pMoveBlock->m_move = move;
		pMoveBlock->Bindtexture(0);
	}
	return pMoveBlock;
}

//=============================================================================
// �u���b�N�̏���������
//=============================================================================
HRESULT CMoveBlock::Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	m_pos = pos;
	m_size = Size;
	CScene2D::Init(pos, Size);
	return S_OK;
}

//=============================================================================
// �u���b�N�̏I������
//=============================================================================
void CMoveBlock::Uninit(void)
{
	//CScene2D::Uninit();
	Release();
}

//=============================================================================
// �u���b�N�̍X�V����
//=============================================================================
void CMoveBlock::Update(void)
{
	SetBlock();
	MoveColision();

	CScene2D::Update();
}

//=============================================================================
// �u���b�N�̕`�揈��
//=============================================================================
void CMoveBlock::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// �u���b�N�̐ݒ菈��
//=============================================================================
void CMoveBlock::SetBlock(void)
{
	// �u���b�N�̏�Ԃ̑J��
	switch (m_nBlockCondition)
	{
		// �u���b�N����Ɉړ������Ă���Ƃ�
	case MOVE_UP:
		if (m_pos.y > m_fMin)
		{
			m_pos.y -= m_move.y;
		}
		else
		{
			m_nBlockCondition = MOVE_DOWN;
		}
		break;

		// �u���b�N�����Ɉړ������Ă���Ƃ�
	case MOVE_DOWN:
		if (m_pos.y < m_fMax)
		{
			m_pos.y += m_move.y;
		}
		else
		{
			m_nBlockCondition = MOVE_UP;
		}
		break;

		// �u���b�N�����Ɉړ������Ă���Ƃ�
	case MOVE_LEFT:
		if (m_pos.x > m_fMin)
		{
			m_pos.x -= m_move.x;
		}
		else
		{
			m_nBlockCondition = MOVE_RIGHT;
		}
		break;

		// �u���b�N���E�Ɉړ������Ă���Ƃ�
	case MOVE_RIGHT:
		if (m_pos.x < m_fMax)
		{
			m_pos.x += m_move.x;
		}
		else
		{
			m_nBlockCondition = MOVE_LEFT;
		}
		break;

	default:
		break;
	}

	m_MoveBlock = (MOVE)m_nBlockCondition;
	CScene2D::SetPosition(m_pos);
}

//=============================================================================
// �ړ��u���b�N�̓����蔻��
//=============================================================================
int CMoveBlock::MoveColision(void)
{
	//=============================================================================
	// ���@�ƃu���b�N�̓����蔻��
	//=============================================================================
	for (int nPriority = 0; nPriority < PRIORITY_MAX; nPriority++)
	{
		// �I�u�W�F�N�g�̃|�C���^�[����
		CScene * pScene = NULL;

		// �I�u�W�F�N�g�̎擾
		pScene = CScene::GetScene(nPriority);

		if (pScene != NULL)
		{
			// �������I�u�W�F�N�g���v���C���[�Ȃ�
			if (nPriority == CScene::PRIORITY_PLAYER)
			{
				CPlayer *pPlayer = (CPlayer*)pScene;

				D3DXVECTOR3 Playerpos = pPlayer->GetPos();
				D3DXVECTOR3 posold = pPlayer->GetPosold();
				D3DXVECTOR3 move = pPlayer->GetMove();
				D3DXVECTOR2 playersize = pPlayer->GetSize();
				D3DXVECTOR3 Initmove = pPlayer->GetMove();
				bool bJump = pPlayer->GetJump();


				if (m_pos.x - m_size.x <= Playerpos.x + playersize.x &&				//�u���b�N�̍��[
					m_pos.x + m_size.x >= Playerpos.x - playersize.x &&				//�u���b�N�̉E�[
					m_pos.y - m_size.y <= Playerpos.y + playersize.y &&				//�u���b�N�̉���
					m_pos.y + m_size.y >= Playerpos.y - playersize.y)				//�u���b�N�̏㕔
				{
					if (m_pos.x - m_size.x >= posold.x + playersize.x)		//�u���b�N�̍��[
					{
						Playerpos.x = m_pos.x - m_size.x - playersize.x;

						// �u���b�N�����Ɉړ������Ă���Ƃ�
						if (m_nBlockCondition == MOVE_LEFT)
						{
							// �u���b�N���ړ����Ă�Ƃ��̃v���C���[�̈ړ�����
							Playerpos.x -= m_move.x;
						}

						//move.y = 0.2f;

						pPlayer->SetPos(Playerpos);
						
						pPlayer->SetJump(false);

						// �v���C���[���u���b�N�̍����ɂ���Ƃ�
						return MOVE_LEFT;
					}
					if (m_pos.x + m_size.x <= posold.x - playersize.x)		//�u���b�N�̉E�[
					{
						Playerpos.x = m_pos.x + m_size.x + playersize.x;

						// �u���b�N���E�Ɉړ������Ă���Ƃ�
						if (m_nBlockCondition == MOVE_RIGHT)
						{
							// �u���b�N���ړ����Ă�Ƃ��̃v���C���[�̈ړ�����
							Playerpos.x += m_move.x;
						}

						//move.y = 0.2f;

						pPlayer->SetPos(Playerpos);
						
						pPlayer->SetJump(false);

						// �v���C���[���u���b�N�̉E���ɂ���Ƃ�
						return MOVE_RIGHT;
					}

					if (m_pos.y - m_size.y >= posold.y + playersize.y)						//�u���b�N�̏㕔
					{
						Playerpos.y = m_pos.y - m_size.y - playersize.y;
						move.y = 0;

						// �u���b�N�̏�Ԃ̑J��
						switch (m_nBlockCondition)
						{
							// �u���b�N����Ɉړ������Ă���Ƃ�
						case MOVE_UP:
							Playerpos.y -= (m_move.y * 2);
							break;

							// �u���b�N���E�Ɉړ������Ă���Ƃ�
						case MOVE_RIGHT:
							// �u���b�N���ړ����Ă�Ƃ��̃v���C���[�̈ړ�����
							Playerpos.x += m_move.x;
							break;

							// �u���b�N�����Ɉړ������Ă���Ƃ�
						case MOVE_LEFT:
							// �u���b�N���ړ����Ă�Ƃ��̃v���C���[�̈ړ�����
							Playerpos.x -= m_move.x;
							break;

						default:
							break;
						}

						pPlayer->SetPos(Playerpos);
						pPlayer->SetMove(move);
						pPlayer->SetJump(false);

						// �v���C���[���u���b�N�̏㑤�ɂ���Ƃ�
						return MOVE_UP;
					}

					if (m_pos.y + m_size.y <= posold.y - playersize.y)			//�u���b�N�̉���
					{
						Playerpos.y = m_pos.y + m_size.y + playersize.y;
						move.y = 0;
						pPlayer->SetPos(Playerpos);
						pPlayer->SetMove(move);

						// �v���C���[���u���b�N�̉����ɂ���Ƃ�
						return MOVE_DOWN;
					}
				}
			}
			// �������I�u�W�F�N�g���v���C���[����Ȃ�
			else
			{

			}
		}
	}
	// �v���C���[���u���b�N�ɂ��Ȃ��Ƃ�
	return MOVE_NONE;
}