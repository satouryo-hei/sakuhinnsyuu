//=============================================================================
//
// �ǂ̊Ǘ��̏��� [wall_manager.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include "wall_manager.h"
#include "wall.h"
#include"manager.h"
#include"renderer.h"

//=============================================================================
// �ÓI�����o�ϐ��̐錾
//=============================================================================
CWall* CWall_Manager::m_pWall[MAX_WALL] = {};

//=============================================================================
// �ǂ̊Ǘ��̃R���X�g���N�^
//=============================================================================
CWall_Manager::CWall_Manager(int nPriority) : CScene(PRIORITY_SECOND)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// �ǂ̊Ǘ��̃f�X�g���N�^
//=============================================================================
CWall_Manager::~CWall_Manager()
{

}

//=============================================================================
// �ǂ̊Ǘ��̐�������
//=============================================================================
CWall_Manager *CWall_Manager::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot)
{
	// CWall_Manager�N���X�̃|�C���^�[�̐���(NULL���)
	CWall_Manager* pWall_Manager = NULL;
	// ���I�������̊m��
	pWall_Manager = new CWall_Manager;
	// NULL�`�F�b�N
	if (pWall_Manager != NULL)
	{
		// �ǂ̐ݒ菈���̌Ăяo��
		pWall_Manager->SetWall(pos,size,rot);
		pWall_Manager->Init(pos);
	}
	return pWall_Manager;
}

//=============================================================================
// �ǂ̊Ǘ��̏���������
//=============================================================================
HRESULT CWall_Manager::Init(D3DXVECTOR3 pos)
{

	m_pWall[0] = CWall::Create(D3DXVECTOR3(0.0f, 0.0f, 100.0f),	 m_size, D3DXVECTOR3(0.0f, 0, 0.0f));
	m_pWall[1] = CWall::Create(D3DXVECTOR3(100.0f, 0.0f, 0.0f),	 m_size, D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f));
	m_pWall[2] = CWall::Create(D3DXVECTOR3(0.0f, 0.0f, -100.0f), m_size, D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	m_pWall[3] = CWall::Create(D3DXVECTOR3(-100.0f, 0.0f, 0.0f), m_size, D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f));
	
	return S_OK;
}

//=============================================================================
// �ǂ̊Ǘ��̏I������
//=============================================================================
void CWall_Manager::Uninit(void)
{
	// �Ǖ���
	for (int nCnt = 0; nCnt < MAX_WALL; nCnt++)
	{
		if (m_pWall[nCnt] != NULL)
		{
			m_pWall[nCnt]->Uninit();
			m_pWall[nCnt] = NULL;
		}		
	}

	CScene::Release();

}

//=============================================================================
// �ǂ̊Ǘ��̍X�V����
//=============================================================================
void CWall_Manager::Update(void)
{

}

//=============================================================================
// �ǂ̊Ǘ��̕`�揈��
//=============================================================================
void CWall_Manager::Draw(void)
{

}

//=============================================================================
// �ǂ̊Ǘ��̐ݒ菈��
//=============================================================================
void CWall_Manager::SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot)
{
	m_pos = pos;
	m_size = size;
	m_rot = rot;
}