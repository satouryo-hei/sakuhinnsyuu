//=============================================================================
//
// �Q�[���̏��� [game.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include "game.h"
#include"input.h"
#include"manager.h"
#include"result.h"
#include"fade.h"
#include"scene3D.h"
#include"model.h"
#include"model_single.h"
#include"player.h"
#include"meshfield.h"
#include"meshsky.h"
#include"shadow.h"
#include"billboard.h"
#include"wall_manager.h"
#include"wall.h"
#include"timer.h"
#include"item.h"
#include"enemy.h"
#include"enemy02.h"

//=============================================================================
// �ÓI�����o�ϐ��̐錾
//=============================================================================
//CPlayer			* CGame::m_pPlayer[PORIGON_MAX] = {};
CScene3D		* CGame::m_pScene3D			= NULL;
CModel			* CGame::m_pModel			= NULL;
CModel_Single	* CGame::m_pModel_Single	= NULL;
CPlayer			* CGame::m_pPlayer			= NULL;
CMeshField		* CGame::m_pMeshField		= NULL;
CMeshSky		* CGame::m_pMeshSky			= NULL;
CShadow			* CGame::m_pShadow			= NULL;
CBillboard		* CGame::m_pBillboard		= NULL;
CWall_Manager	* CGame::m_pWall_Manager	= NULL;
CWall			* CGame::m_pWall			= NULL;
CTimer			* CGame::m_pTimer			= NULL;
CItem			* CGame::m_pItem[3]			= {};
CEnemy			* CGame::m_pEnemy			= NULL;
CEnemy2			* CGame::m_pEnemy2			= NULL;

//=============================================================================
// ���[�J���}�N����`
//=============================================================================
const char* CGame::m_pModelAttack = "data/MODEL/ITEM/AttackUp.x";
const char* CGame::m_pModelData = "data/MODEL/PLAYER/Eye.x" ;

//=============================================================================
// �Q�[���̃R���X�g���N�^
//=============================================================================
CGame::CGame() : CScene(PRIORITY_NOMAL)
{
	m_bUse = false;
}

//=============================================================================
// �Q�[���̃f�X�g���N�^
//=============================================================================
CGame::~CGame()
{

}

//=============================================================================
// �Q�[���̏���������
//=============================================================================
HRESULT CGame::Init(D3DXVECTOR3 pos)
{
	// 1�̃��f���𐶐�
	m_pModel_Single = CModel_Single::Create(D3DXVECTOR3(10.0f, 0.0f, 50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_pModelData);
	// 3D�̃v���C���[�𐶐�
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(50.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	// ���b�V���t�B�[���h(�n��)�̐���
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(100.0f, 0.0f, 100.0f));
	// ���b�V���X�J�C(��)�̐���
	m_pMeshSky = CMeshSky::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1000.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 32, 8);
	// �r���{�[�h�̐���
	m_pBillboard = CBillboard::Create(D3DXVECTOR3(0.0f, 25.0f, 0.0f), D3DXVECTOR2(50.0f, 25.0f));
	// �l�p�`�ݒ�̕ǂ𐶐�
	m_pWall_Manager = CWall_Manager::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(100.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI/2, 0.0f));
	// ���Ԃ̐���
	m_pTimer = CTimer::Create(D3DXVECTOR3(420.0f, 50.0f, 0.0f), D3DXVECTOR2(20.0f, 30.0f));
	// �A�C�e���̐���
	m_pItem[0] = CItem::Create(D3DXVECTOR3(-30.0f, 0.0f, 40.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_pModelAttack);
	// �A�C�e���̐���
	m_pItem[1] = CItem::Create(D3DXVECTOR3(30.0f, 0.0f, 40.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_pModelAttack);
	// �A�C�e���̐���
	m_pItem[2] = CItem::Create(D3DXVECTOR3(-30.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_pModelAttack);
	// �G�̐���
	//m_pEnemy = CEnemy::Create(D3DXVECTOR3(-30.0f, 0.0f, 0.0f), PLAYER_TEXT);
	// �G�̐���
	m_pEnemy2 = CEnemy2::Create(D3DXVECTOR3(-60.0f, 0.0f, 0.0f), PLAYER_TEXT);
	return S_OK;
}

//=============================================================================
// �Q�[���̏I������
//=============================================================================
void CGame::Uninit(void)
{
	if (m_pTimer != NULL)
	{
		m_pTimer->Uninit();
		m_pTimer = NULL;
	}

	//if (m_pItem != NULL)
	//{
	//	m_pItem->Uninit();
	//	m_pItem = NULL;
	//}

	if (m_pMeshField != NULL)
	{
		m_pMeshField->Uninit();
		m_pMeshField = NULL;
	}

	if (m_pPlayer != NULL)
	{
		m_pPlayer->Uninit();
		m_pPlayer = NULL;
	}

	//if (m_pEnemy2 != NULL)
	//{
	//	m_pEnemy2->Uninit();
	//	m_pEnemy2 = NULL;
	//}
	//if (m_pEnemy != NULL)
	//{
	//	m_pEnemy->Uninit();
	//	m_pEnemy = NULL;
	//}

	if (m_pModel_Single != NULL)
	{
		m_pModel_Single->Uninit();
		m_pModel_Single = NULL;
	}

	if (m_pWall_Manager != NULL)
	{
		m_pWall_Manager->Uninit();
		m_pWall_Manager = NULL;
	}

	//if (m_pBillboard != NULL)
	//{
	//	m_pBillboard->Uninit();
	//	m_pBillboard = NULL;
	//}

	if (m_pMeshSky != NULL)
	{
		m_pMeshSky->Uninit();
		m_pMeshSky = NULL;
	}

	CScene::Release();
}

//=============================================================================
// �Q�[���̍X�V����
//=============================================================================
void CGame::Update(void)
{
	CInputKeyboard *pInputKeyboard = NULL;
	pInputKeyboard = CManager::GetInputKeyboard();

	//�C�ӂŉ����ꂽ���ǂ���
	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)//ENTER��������
	{
		CFade::SetFade(CManager::MODE_RESULT);
	}
}

//=============================================================================
// �Q�[���̕`�揈��
//=============================================================================
void CGame::Draw(void)
{

}