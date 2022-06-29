//---------------------------------------
// �ǂ̏���(���C��)
//Author:�����@�ĕ�
//---------------------------------------
#include"wall.h"
#include"renderer.h"
#include"manager.h"
#include"texture.h"
#include"player.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CWall::CWall(PRIORITY Priority) : CScene3D(PRIORITY_SECOND)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CWall::~CWall()
{

}

//=============================================================================
// �ǂ̐�������
//=============================================================================
CWall *CWall::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 Rot)
{
	// �ǂ̃|�C���^�[�̐���(NULL���)
	CWall* pWall = NULL;

	// ���I�������̊m��
	pWall = new CWall;

	// NULL�`�F�b�N
	if (pWall != NULL)
	{
		// �ǂ̌�����ݒ�
		pWall->m_rot = Rot;
		// �ǂ̏����������̌Ăяo��
		pWall->Init(pos, size);
		// �e�N�X�`���̐ݒ�
		pWall->BindTextuer(0);
	}
	return pWall;
}

//=============================================================================
//�ǂ̏���������
//=============================================================================
HRESULT CWall::Init(D3DXVECTOR3 pos, D3DXVECTOR3 Size)
{
	m_pos = pos;
	m_size = Size;

	// �p�����̏��������Ăяo��
	CScene3D::Init(pos, Size, m_rot);

	return S_OK;
}	// �|���S���̏����������I��



	//=============================================================================
	// �ǂ̏I������
	//=============================================================================
void CWall::Uninit(void)
{
	// �p�����̏I���������Ăяo��
	CScene3D::Uninit();

	// �������
	Release();

}// �|���S���̏I�������I��


 //=============================================================================
 // �ǂ̍X�V����
 //=============================================================================
void CWall::Update(void)
{

	////=============================================================================
	//// ���@�̒e�ƓG�̓����蔻��
	////=============================================================================
	//for (int nPriority = 0; nPriority < PRIORITY_MAX; nPriority++)
	//{
	//	CScene * pScene = NULL;

	//	pScene = CScene::GetScene(nPriority);

	//	if (pScene != NULL)
	//	{
	//		if (nPriority == CScene::PRIORITY_PLAYER)
	//		{
	//			CPlayer *pPlayer = (CPlayer*)pScene;

	//			if (m_pos.x - (m_size.x / 2) <= pPlayer->GetPos().x &&
	//				m_pos.x + (m_size.x / 2) >= pPlayer->GetPos().x &&
	//				m_pos.y - (m_size.y / 2) <= pPlayer->GetPos().y &&
	//				m_pos.y + (m_size.y / 2) >= pPlayer->GetPos().y &&
	//				m_pos.z - (m_size.z / 2) <= pPlayer->GetPos().z &&
	//				m_pos.z + (m_size.z / 2) >= pPlayer->GetPos().z)
	//			{
	//				if (m_pos.x - (m_size.x / 2) <= pPlayer->GetPos().x&&
	//					m_pos.x + (m_size.x / 2) >= pPlayer->GetPos().x&&
	//					m_pos.y - (m_size.y / 2) <= pPlayer->GetPos().y&&
	//					m_pos.y + (m_size.y / 2) >= pPlayer->GetPos().y&&
	//					m_pos.z - (m_size.z / 2) <= pPlayer->GetPos().z &&
	//					m_pos.z + (m_size.z / 2) >= pPlayer->GetPos().z)
	//				{
	//					return;
	//				}
	//			}
	//		}
	//	}	
	//}

	// �p�����̍X�V�������Ăяo��
	CScene3D::Update();

}// �|���S���̍X�V�����I��


 //=============================================================================
 // �ǂ̕`�揈��
 //=============================================================================
void CWall::Draw(void)
{
	// �p�����̕`�揈�����Ăяo��
	CScene3D::Draw();

}	// �|���S���̕`�揈���I��