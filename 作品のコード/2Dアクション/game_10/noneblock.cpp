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
	CNoneBlock *pBlock = NULL;
	pBlock = new CNoneBlock;

	if (pBlock != NULL)
	{
		pBlock->Init(pos, Size);
		pBlock->m_bBreak = bBreak;
		pBlock->Bindtexture(nTex);
	}
	return pBlock;
}

//=============================================================================
// �u���b�N�̏���������
//=============================================================================
HRESULT CNoneBlock::Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	m_pos = pos;
	m_size = Size;
	CScene2D::Init(pos, Size);
	return S_OK;
}

//=============================================================================
// �u���b�N�̏I������
//=============================================================================
void CNoneBlock::Uninit(void)
{
	//CScene2D::Uninit();
	Release();
}

//=============================================================================
// �u���b�N�̍X�V����
//=============================================================================
void CNoneBlock::Update(void)
{
	if (!m_bUse)
	{
		Uninit();
		return;
	}

	Colision();

	CScene2D::Update();
}

//=============================================================================
// �u���b�N�̕`�揈��
//=============================================================================
void CNoneBlock::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// �u���b�N�ƒe�̓����蔻��
//=============================================================================
void CNoneBlock::Colision()
{
	CScene * pScene = CScene::GetScene(CScene::PRIORITY_BULLET);

	while (pScene != NULL)
	{
		CBullet *pBullet = (CBullet*)pScene;

		D3DXVECTOR3 Bulletpos = pBullet->GetPosition();
		D3DXVECTOR2 BulletSize = pBullet->GetSize();		

		if (m_pos.x + m_size.x >= Bulletpos.x &&
			m_pos.x - m_size.x <= Bulletpos.x &&
			m_pos.y + m_size.y >= Bulletpos.y &&
			m_pos.y - m_size.y <= Bulletpos.y)
		{
			if (m_bBreak)
			{
				//�����̐���
				CExplosion::Create(m_pos, m_size, 9);
				m_bUse = false;
			}
			else
			{
				D3DXVECTOR3 BulletOldpos = pBullet->GetPosOld();
				//�����̐���
				CExplosion::Create(BulletOldpos, BulletSize, 9);
			}
			pBullet->Uninit();
		}

		CScene * pSceneNext = CScene::GetNext(pScene);
		pScene = pSceneNext;
	}
}