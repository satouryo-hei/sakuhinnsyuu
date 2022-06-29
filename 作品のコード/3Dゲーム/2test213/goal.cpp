//=============================================================================
//
// �S�[������ [goal.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include"goal.h"
#include"manager.h"
#include"renderer.h"
#include"model.h"
#include"player.h"
#include"fade.h"
#include"choose_game.h"

//=============================================================================
// �S�[���̃R���X�g���N�^
//=============================================================================
CGoal::CGoal(PRIORITY Priprity) :CModel_Single(Priprity)
{
	memset(&m_mtxWorld, NULL, sizeof(m_mtxWorld));
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fRadius = 8.0f;
}

//=============================================================================
// �A�C�e���̃f�X�g���N�^
//=============================================================================
CGoal::~CGoal()
{

}

//=============================================================================
// �A�C�e���̐�������
//=============================================================================
CGoal *CGoal::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char*pFiledata)
{
	// �A�C�e���̃|�C���^�[����
	CGoal * pGoal = NULL;

	// ���I�������̊m��
	pGoal = new CGoal;

	//NULL�`�F�b�N
	if (pGoal != NULL)
	{
		// �S�[���̏����������̌Ăяo��
		pGoal->Init(pos, rot, pFiledata);
	}

	return pGoal;
}

//=============================================================================
// �A�C�e���̏���������
//=============================================================================
HRESULT CGoal::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char*pFiledata)
{
	// �p�����̏������������Ăяo��
	CModel_Single::Init(pos, rot, pFiledata);
	m_pos = pos;
	m_rot = rot;
	SetPos(m_pos);
	SetRot(m_rot);
	return S_OK;
}

//=============================================================================
// �A�C�e���̏I������
//=============================================================================
void CGoal::Uninit(void)
{
	// �p�����̏I���������Ăяo��
	CModel_Single::Uninit();

	// �������
	Release();
}

//=============================================================================
// �A�C�e���̍X�V����
//=============================================================================
void CGoal::Update(void)
{
	//=============================================================================
	// ���@�̒e�ƓG�̓����蔻��
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
			if (nPriority == CScene::PRIORITY_PLAYER)
			{
				// ���݂̃I�u�W�F�N�g�̎�ނ�G�̃|�C���^�[�����������̂ɓG�̃|�C���^�[�ŃL���X�g���đ��				
				CPlayer *pPlayer = (CPlayer*)pScene;			

				// �v���C���[�̌��݂̈ʒu���擾
				D3DXVECTOR3 Playerpos = pPlayer->GetPos();

				// �v���C���[�ƓG�̎Εӂ̋����𑪂�A����i�O�������(c2�� = a2��+b2��)�j
				float fRange = sqrtf(powf((Playerpos.x - m_pos.x), 2.0f) + powf((Playerpos.z - m_pos.z), 2.0f));

				// ���݂̈ʒu+�~�̖ʐς��v���C���[�ƓG�̎Εӂ̋������~�̖ʐψȏ�(�E�̏ꍇ)or�ȉ��i���̏ꍇ�j�ɓ����Ă�����
				if (m_pos.x + (m_fRadius * powf(D3DX_PI, 2)) >= fRange&&
					m_pos.x - (m_fRadius * powf(D3DX_PI, 2)) <= fRange&&
					m_pos.z + (m_fRadius * powf(D3DX_PI, 2)) >= fRange&&
					m_pos.z - (m_fRadius * powf(D3DX_PI, 2)) <= fRange)
				{					
					// �Q�[�������Ă邩�ǂ���
					if (CChoose_Game::GetGame())
					{
						// �J�ڐ�����U���g�ɂ���
						CFade::SetFade(CManager::MODE_RESULT);
					}
					else
					{// ���ĂȂ������ꍇ
						// �J�ڐ��I�����[�h�ɂ���
						CFade::SetFade(CManager::MODE_SELECT);
					}
				}
			}
		}
	}
	// �p�����̍X�V�������Ăяo��
	CModel_Single::Update();
}

//=============================================================================
// �A�C�e���̕`�揈��
//=============================================================================
void CGoal::Draw(void)
{
	// �p�����̕`�揈�����Ăяo��
	CModel_Single::Draw();
}