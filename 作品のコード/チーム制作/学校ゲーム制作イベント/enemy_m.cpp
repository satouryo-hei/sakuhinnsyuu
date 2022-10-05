//=============================================================================
//
// �G�l�~�[M�̏��� [enemy_m.cpp]
// Author : �ؖr�_
//
//============================================================================
#include "enemy_m.h"
#include"bullet.h"
#include"game.h"
#include "rupture.h"
#include "score.h"
//=============================================================================
// �G�l�~�[M�̃R���X�g���N�^
//=============================================================================
CEnemyM::CEnemyM() : CEnemy(TYPE_M)
{
	// �C�ӂ̒l�ŃN���A
	m_nLife = 0;
	m_nSpeed = 0;
}

//=============================================================================
// �G�l�~�[M�̃f�X�g���N�^
//=============================================================================
CEnemyM::~CEnemyM()
{
}

//=============================================================================
// �G�l�~�[M�̏���������
//=============================================================================
HRESULT CEnemyM::Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	srand(time(NULL));
	int nSpawn = (int)(rand() % 10 + 1);

	switch (nSpawn)
	{
	case 1:
		CEnemy::Init(D3DXVECTOR3(-80.0f, 100, 0.0f), D3DXVECTOR2(25.0f, 25.0f));
		m_nSpeed = 1;
		break;

	case 2:
		CEnemy::Init(D3DXVECTOR3(-80.0f, 200, 0.0f), D3DXVECTOR2(25.0f, 25.0f));
		m_nSpeed = 1;
		break;

	case 3:
		CEnemy::Init(D3DXVECTOR3(-80.0f, 300, 0.0f), D3DXVECTOR2(25.0f, 25.0f));
		m_nSpeed = 1;
		break;

	case 4:
		CEnemy::Init(D3DXVECTOR3(-80.0f, 400, 0.0f), D3DXVECTOR2(25.0f, 25.0f));
		m_nSpeed = 1;
		break;

	case 5:
		CEnemy::Init(D3DXVECTOR3(-80.0f, 500, 0.0f), D3DXVECTOR2(25.0f, 25.0f));
		m_nSpeed = 1;
		break;

	case 6:
		CEnemy::Init(D3DXVECTOR3(1360.0f, 100, 0.0f), D3DXVECTOR2(25.0f, 25.0f));
		m_nSpeed = -1;
		break;

	case 7:
		CEnemy::Init(D3DXVECTOR3(1360.0f, 200, 0.0f), D3DXVECTOR2(25.0f, 25.0f));
		m_nSpeed = -1;
		break;

	case 8:
		CEnemy::Init(D3DXVECTOR3(1360.0f, 300, 0.0f), D3DXVECTOR2(25.0f, 25.0f));
		m_nSpeed = -1;
		break;

	case 9:
		CEnemy::Init(D3DXVECTOR3(1360.0f, 400, 0.0f), D3DXVECTOR2(25.0f, 25.0f));
		m_nSpeed = -1;
		break;

	case 10:
		CEnemy::Init(D3DXVECTOR3(1360.0f, 500, 0.0f), D3DXVECTOR2(25.0f, 25.0f));
		m_nSpeed = -1;
		break;

	default:
		break;
	}

	// ������
	m_nLife = 0;

	return S_OK;
}

//=============================================================================
// �G�l�~�[M�̏I������
//=============================================================================
void CEnemyM::Uninit(void)
{
	CEnemy::Uninit();
}

//=============================================================================
// �G�l�~�[M�̍X�V����
//=============================================================================
void CEnemyM::Update(void)
{
	m_pos.x += m_nSpeed;

	if (BulletCollision() == true)
	{
		CRupture::Create(m_pos, D3DXVECTOR2(10.0f, 10.0f), CRupture::RUPTURE_TYPE_FOURTH);
	}
	
	CEnemy::Update();
}

//=============================================================================
// �G�l�~�[M�̕`�揈��
//=============================================================================
void CEnemyM::Draw(void)
{
	CEnemy::Draw();
}

//=============================================================================
// �G�ƃu���b�N�̓����蔻�菈��
//=============================================================================
bool CEnemyM::BulletCollision()
{
	int nNum = 0;
	CScene * pScene = CScene::GetScene(CScene::PRIORITY_BULLET);
	CScore *pScore = CGame::GetScore();

	while (pScene != NULL)
	{
		// �擾�����I�u�W�F�N�g�𕁒ʂ̃u���b�N�ɑ��
		CBullet *pBullet = (CBullet*)pScene;

		D3DXVECTOR3 Bulletpos = pBullet->GetPosition();
		D3DXVECTOR2 Bulletsize = pBullet->GetSize();

		if (m_pos.x - m_size.x <= Bulletpos.x + Bulletsize.x &&				//�u���b�N�̉E�[
			m_pos.x + m_size.x >= Bulletpos.x - Bulletsize.x &&				//�u���b�N�̍��[
			m_pos.y - m_size.y <= Bulletpos.y + Bulletsize.y &&				//�u���b�N�̉���
			m_pos.y + m_size.y >= Bulletpos.y - Bulletsize.y)					//�u���b�N�̏㕔
		{

			pBullet->SetUse(true);
			pScore->AddScore(100);
			Uninit();
			return true;
		}

		// �u���b�N�I�u�W�F�N�g�̎��̃I�u�W�F�N�g���擾
		CScene * pSceneNext = CScene::GetNext(pScene);
		pScene = pSceneNext;
	}
	return false;
}