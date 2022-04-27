//=============================================================================
//
// �e�̏��� [bullet.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include"bullet.h"
#include"renderer.h"
#include"manager.h"
#include"input.h"
#include"explosion.h"
#include"enemy.h"
#include"effect.h"
#include"score.h"
#include"game.h"

/*��肽������*/
/*�e�̉�]�@������̂��H
�`���[�W�V���b�g
�`���[�W�V���b�g�Œe�̊g��*/

// �ÓI�����o�ϐ��̐錾
LPDIRECT3DTEXTURE9 CBullet::m_pTexture = NULL;
CScene::OBJTYPE CBullet::m_ObjType = OBJTYPE_NOMAL;

//=============================================================================
// �e�̃R���X�g���N�^
//=============================================================================
CBullet::CBullet(int nPriority) : CScene2D(nPriority), m_fSpeedMax(2.1f)
{
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_nPriority = nPriority;

	m_nLife = 0;
}


//=============================================================================
// �e�̃f�X�g���N�^
//=============================================================================
CBullet::~CBullet()
{

}


//=============================================================================
// �e�̐�������
//=============================================================================
CBullet *CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move,D3DXVECTOR2 Size, CScene::OBJTYPE ObjType)
{
	CBullet* pBullet;

	pBullet = new CBullet;

	if (pBullet != NULL)
	{
		pBullet->Init(pos, move, Size);
		pBullet->BindTextuer(m_pTexture);
		pBullet->SetType(ObjType);
	}

	m_ObjType = ObjType;
	return pBullet;
}

//=============================================================================
// �e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CBullet::Load(void)
{
	CManager *pManager = NULL;

	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();


	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/Bullet000.png",
		&m_pTexture);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���̔j��
//=============================================================================
void CBullet::Unload(void)
{		
	if (m_pTexture != NULL)
	{		  
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// �e�̏���������
//=============================================================================
HRESULT CBullet::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move,D3DXVECTOR2 Size)
{
	CScene2D::Init(pos, move, Size);

	m_nLife = 10;
	m_Size = Size;
	m_Move = move;

	return S_OK;
}	// �|���S���̏����������I��



//=============================================================================
// �e�̏I������
//=============================================================================
void CBullet::Uninit(void)
{
	CScene2D::Uninit();

}// �|���S���̏I�������I��


//=============================================================================
// �e�̍X�V����
//=============================================================================
void CBullet::Update(void)
{
	CScore * pScore = NULL;

	pScore = CGame::GetScore();

	D3DXVECTOR3 pos = GetPosition();	

	CEffect::Create(pos, D3DXVECTOR2(20.0f,20.0f));

	pos.x += m_Move.x;

	CScene2D::Update();

	SetPosition(pos);

	// ��ʊO����
	if (pos.x >= SCREEN_WIDTH - (m_Size.x/2))
	{
		Uninit();
		return;
	}
	else if (pos.x <= (m_Size.x / 2))
	{
		Uninit();
		return;
	}
	if (pos.y >= SCREEN_HEIGHT - (m_Size.y/2))
	{
		Uninit();
		return;
	}
	else if (pos.y <= (m_Size.y / 2))
	{
		Uninit();
		return;
	}

	//=============================================================================
	// ���@�̒e�ƓG�̓����蔻��
	//=============================================================================
	for (int nPriority = 0; nPriority < PRIORITY_MAX; nPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_DATA; nCntScene++)
		{
			CScene * pScene = NULL;

			pScene = CScene::GetScene(nPriority, nCntScene);

			if (pScene != NULL)
			{
				CScene::OBJTYPE objType;
				objType = pScene->GetOnjType();

				if (objType == CScene::OBJTYPE_ENEMY &&m_ObjType == CScene::OBJTYPE_PLAYERBULLET)
				{
					CEnemy *pEnemy = (CEnemy*)pScene;

					if (pos.x + (m_Size.x / 2) >= pEnemy->GetPosition().x - pEnemy->GetSize().x &&
						pos.x - (m_Size.x / 2) <= pEnemy->GetPosition().x + pEnemy->GetSize().x &&
						pos.y + (m_Size.y / 2) >= pEnemy->GetPosition().y - pEnemy->GetSize().y &&
						pos.y - (m_Size.y / 2) <= pEnemy->GetPosition().y + pEnemy->GetSize().y)
					{
						//�����̐���
						CExplosion::Create(pos, D3DXVECTOR2(100.0f, 100.0f));
						pScore->AddScore(100);
						Uninit();
						pEnemy->Uninit();
						return;
					}
				}

			}
		}
	}

}// �|���S���̍X�V�����I��



//=============================================================================
// �e�̕`�揈��
//=============================================================================
void CBullet::Draw(void)
{
	CScene2D::Draw();

}	// �|���S���̕`�揈���I��

