//=============================================================================
//
// �A�C�e������ [model_single.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include"bom.h"
#include"manager.h"
#include"renderer.h"
#include"model.h"
#include"explosion.h"
#include"enemy02.h"

//=============================================================================
// �A�C�e���̃R���X�g���N�^
//=============================================================================
CBom::CBom(PRIORITY Priprity) :CModel_Single(Priprity)
{
	memset(&m_mtxWorld, NULL, sizeof(m_mtxWorld));
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 100;
	m_fRadius = 10;
	m_bUse = true;
}

//=============================================================================
// �A�C�e���̃f�X�g���N�^
//=============================================================================
CBom::~CBom()
{

}

//=============================================================================
// �A�C�e���̐�������
//=============================================================================
CBom *CBom::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char*Filedata)
{
	// �A�C�e���̃|�C���^�[����
	CBom * pBom = NULL;

	// ���I�������̊m��
	pBom = new CBom;

	//NULL�`�F�b�N
	if (pBom != NULL)
	{
		pBom->Init(pos, rot, Filedata);
	}

	return pBom;
}

//=============================================================================
// �A�C�e���̏���������
//=============================================================================
HRESULT CBom::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char*Filedata)
{
	// �p�����̏������������Ăяo��
	CModel_Single::Init(pos, rot, Filedata);
	m_pos = pos;
	m_rot = rot;
	SetPos(m_pos);
	SetRot(m_rot);
	return S_OK;
}

//=============================================================================
// �A�C�e���̏I������
//=============================================================================
void CBom::Uninit(void)
{
	// �p�����̏I���������Ăяo��
	CModel_Single::Uninit();

	// �������
	Release();
}

//=============================================================================
// �A�C�e���̍X�V����
//=============================================================================
void CBom::Update(void)
{
	SetPos(m_pos);

	if (!m_bUse)
	{
		//=============================================================================
		// �{���ƓG�̓����蔻��
		//=============================================================================
		for (int nPriority = 0; nPriority < PRIORITY_MAX; nPriority++)
		{
			// �I�u�W�F�N�g�̃|�C���^�[����
			CScene * pScene = NULL;

			// �I�u�W�F�N�g�̎擾����
			pScene = CScene::GetScene(nPriority);

			// NULL�`�F�b�N
			if (pScene != NULL)
			{
				// �I�u�W�F�N�g�̎�ނ��G��������
				if (nPriority == CScene::PRIORITY_ENEMY)
				{
					// ���݂̃I�u�W�F�N�g�̎�ނ�G�̃|�C���^�[�����������̂ɓG�̃|�C���^�[�ŃL���X�g���đ��
					CEnemy2 *pEnemy2 = (CEnemy2*)pScene;

					if (m_pos.x + (m_fRadius * powf(D3DX_PI, 2)) >= pEnemy2->GetPos().x &&
						m_pos.x - (m_fRadius * powf(D3DX_PI, 2)) <= pEnemy2->GetPos().x &&
						m_pos.z + (m_fRadius * powf(D3DX_PI, 2)) >= pEnemy2->GetPos().z &&
						m_pos.z - (m_fRadius * powf(D3DX_PI, 2)) <= pEnemy2->GetPos().z)
					{
						// �G�̏I�������̌Ăяo��
						pEnemy2->Uninit();						
					}
				}
			}
		}
		// �I�������̌Ăяo��
		Uninit();
		// �����̐��������̌Ăяo��
		CExplosion::Create(m_pos, D3DXVECTOR2(100.0f, 100.0f));
		return;
	}
	else
	{
		// �̗͂����炷
		m_nLife--;

		// �̗�0�ȉ��ɂȂ����Ƃ�
		if (m_nLife <= 0)
		{// �̗�0�ɂ���
			m_nLife = 0;

			// �g��Ȃ�����
			m_bUse = false;
		}
		// �p����̍X�V�������Ăяo��
		CModel_Single::Update();
	}
}

//=============================================================================
// �A�C�e���̕`�揈��
//=============================================================================
void CBom::Draw(void)
{
	// �p����̕`�揈�����Ăяo��
	CModel_Single::Draw();
}