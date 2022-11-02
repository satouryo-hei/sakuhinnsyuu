//=============================================================================
//
// �u���b�N�̏��� [score.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include "pushblock.h"
#include"noneblock.h"

//=============================================================================
// �u���b�N�̃R���X�g���N�^
//=============================================================================
CPushBlock::CPushBlock(int nPriority) : CScene2D(PRIORITY_PUSHBLOCK)
{
	m_pos = D3DXVECTOR3(0, 0, 0);
	m_move = D3DXVECTOR3(0, 0, 0);
	m_size = D3DXVECTOR2(0, 0);
}

//=============================================================================
// �u���b�N�̃f�X�g���N�^
//=============================================================================
CPushBlock::~CPushBlock()
{

}

//=============================================================================
// �u���b�N�̐�������
//=============================================================================
CPushBlock *CPushBlock::Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size, D3DXVECTOR3 move, int nTex)
{
	CPushBlock *pPushBlock = NULL;
	pPushBlock = new CPushBlock;

	if (pPushBlock != NULL)
	{
		pPushBlock->Init(pos, Size);
		pPushBlock->m_move = move;
		pPushBlock->Bindtexture(0);
	}
	return pPushBlock;
}

//=============================================================================
// �u���b�N�̏���������
//=============================================================================
HRESULT CPushBlock::Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	m_pos = pos;
	m_size = Size;
	CScene2D::Init(pos, Size);
	return S_OK;
}

//=============================================================================
// �u���b�N�̏I������
//=============================================================================
void CPushBlock::Uninit(void)
{
	//CScene2D::Uninit();
	Release();
}

//=============================================================================
// �u���b�N�̍X�V����
//=============================================================================
void CPushBlock::Update(void)
{
	m_posOld = m_pos;
	m_move.y ++;
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
	}
	else if (m_pos.y <= m_size.y)
	{
		m_pos.y = m_size.y;
	}

	NoneColision();

	CScene2D::SetPosition(m_pos);

	CScene2D::Update();
}

//=============================================================================
// �u���b�N�̕`�揈��
//=============================================================================
void CPushBlock::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// �u���b�N�̕`�揈��
//=============================================================================
void CPushBlock::NoneColision(void)
{
	// �u���b�N�I�u�W�F�N�g���擾
	CScene * pScene = CScene::GetScene(CScene::PRIORITY_BLOCK);

	// �I�u�W�F�N�g��NULL����Ȃ������
	while (pScene != NULL)
	{
		// �擾�����I�u�W�F�N�g�𕁒ʂ̃u���b�N�ɑ��
		CNoneBlock *pNoneBlock = (CNoneBlock*)pScene;

		// �m�[�}���u���b�N�̌��݂̈ʒu���擾
		D3DXVECTOR3 Nonepos = pNoneBlock->GetPosition();

		// �m�[�}���u���b�N�̑傫�����擾
		D3DXVECTOR2 Nonesize = pNoneBlock->GetSize();

		if (m_pos.x - m_size.x < Nonepos.x + Nonesize.x &&				// �����u���b�N�̍��[ < �u���b�N�̉E�[
			m_pos.x + m_size.x > Nonepos.x - Nonesize.x &&				// �����u���b�N�̉E�[ > �u���b�N�̍��[
			m_pos.y - m_size.y < Nonepos.y + Nonesize.y &&				// �����u���b�N�̏�[ < �u���b�N�̉���
			m_pos.y + m_size.y > Nonepos.y - Nonesize.y)				// �����u���b�N�̉��[ > �u���b�N�̏㕔
		{																   
			if (m_posOld.y + m_size.y <= Nonepos.y - Nonesize.y)		// �O�̈ʒu�̉����u���b�N�̉��� <= �u���b�N�̏㕔
			{															   
				m_pos.y = Nonepos.y - m_size.y - Nonesize.y;			   
				m_move.y = 0;											   
			}															   
			else if (m_posOld.x - m_size.x <= Nonepos.x + Nonesize.x)	// �O�̈ʒu�̉����u���b�N�̉E�� <= �u���b�N�̉E�[			
			{															   
				m_pos.x = Nonepos.x + m_size.x + Nonesize.x;			   
			}															   
			else if (m_posOld.x + m_size.x >= Nonepos.x - Nonesize.x)	// �O�̈ʒu�̉����u���b�N�̉E�� >=�u���b�N�̍��[			
			{
				m_pos.x = Nonepos.x - m_size.x - Nonesize.x;
			}
		}
		// �u���b�N�I�u�W�F�N�g�̎��̃I�u�W�F�N�g���擾
		CScene * pSceneNext = CScene::GetNext(pScene);

		// �擾�����I�u�W�F�N�g����
		pScene = pSceneNext;
	}
}