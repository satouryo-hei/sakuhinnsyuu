//=============================================================================
//
// �u���b�N�̏��� [score.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include "noneblock.h"
#include"bullet.h"
#include"explosion.h"

//=============================================================================
// �u���b�N�̃R���X�g���N�^
//=============================================================================
CNoneBlock::CNoneBlock(int nPriority) : CScene2D(PRIORITY_BLOCK)
{
	m_pos = D3DXVECTOR3(0, 0, 0);
	m_size = D3DXVECTOR2(0, 0);
	m_bBreak = false;
	m_bUse = true;
}

//=============================================================================
// �u���b�N�̃f�X�g���N�^
//=============================================================================
CNoneBlock::~CNoneBlock()
{

}

//=============================================================================
// �u���b�N�̐�������
//=============================================================================
CNoneBlock *CNoneBlock::Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size,bool bBreak ,int nTex)
{
	// ���ʂ̃u���b�N�̃|�C���^�[����
	CNoneBlock *pNoneBlock = NULL;

	// ���I�������̊m��
	pNoneBlock = new CNoneBlock;

	// NULL����Ȃ�������
	if (pNoneBlock != NULL)
	{
		pNoneBlock->Init(pos, Size);
		pNoneBlock->m_bBreak = bBreak;
		pNoneBlock->Bindtexture(nTex);
	}
	return pNoneBlock;
}

//=============================================================================
// �u���b�N�̏���������
//=============================================================================
HRESULT CNoneBlock::Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	m_pos = pos;
	m_size = Size;

	// �I�u�W�F�N�g2D�̏����������̌Ăяo��
	CScene2D::Init(pos, Size);
	return S_OK;
}

//=============================================================================
// �u���b�N�̏I������
//=============================================================================
void CNoneBlock::Uninit(void)
{
	// �������
	Release();
}

//=============================================================================
// �u���b�N�̍X�V����
//=============================================================================
void CNoneBlock::Update(void)
{
	// �g�p���ĂȂ��Ȃ�
	if (!m_bUse)
	{
		Uninit();
		return;
	}

	// �e�Ƃ̓����蔻��
	Colision();

	// �I�u�W�F�N�g2D�̍X�V�����̌Ăяo��
	CScene2D::Update();
}

//=============================================================================
// �u���b�N�̕`�揈��
//=============================================================================
void CNoneBlock::Draw(void)
{
	// �I�u�W�F�N�g2D�̕`�揈���̌Ăяo��
	CScene2D::Draw();
}

//=============================================================================
// �u���b�N�ƒe�̓����蔻��
//=============================================================================
void CNoneBlock::Colision()
{
	// �e�̃I�u�W�F�N�g���擾
	CScene * pScene = CScene::GetScene(CScene::PRIORITY_BULLET);

	// �I�u�W�F�N�g��NULL����Ȃ������
	while (pScene != NULL)
	{
		// �擾�����I�u�W�F�N�g��e�ɑ�� 
		CBullet *pBullet = (CBullet*)pScene;

		// �e�̌��݂̈ʒu���擾
		D3DXVECTOR3 Bulletpos = pBullet->GetPosition();

		// �e�̑傫�����擾
		D3DXVECTOR2 BulletSize = pBullet->GetSize();		

		// �������Ă��邩�ǂ���
		if (m_pos.x + m_size.x >= Bulletpos.x &&	// �u���b�N�̍��[ <= �e�̉E�[
			m_pos.x - m_size.x <= Bulletpos.x &&	// �u���b�N�̉E�[ >= �e�̍��[
			m_pos.y + m_size.y >= Bulletpos.y &&	// �u���b�N�̏�[ <= �e�̉���
			m_pos.y - m_size.y <= Bulletpos.y)		// �u���b�N�̉��[ >= �e�̏㕔
		{
			// ����������u���b�N�ł��邩�ǂ���
			if (m_bBreak)
			{// ����u���b�N�ł����
				//�����̐���
				CExplosion::Create(m_pos, m_size, 9);

				// �g��Ȃ�����
				m_bUse = false;
			}
			else // ����ȊO
			{
				// �O��̒e�̈ʒu���擾
				D3DXVECTOR3 BulletOldpos = pBullet->GetPosOld();

				//�����̐���
				CExplosion::Create(BulletOldpos, BulletSize, 9);
			}
			// �e�̏I�������̌Ăяo��
			pBullet->Uninit();
		}

		// �u���b�N�I�u�W�F�N�g�̎��̃I�u�W�F�N�g���擾
		CScene * pSceneNext = CScene::GetNext(pScene);

		// �擾�����I�u�W�F�N�g����
		pScene = pSceneNext;
	}
}