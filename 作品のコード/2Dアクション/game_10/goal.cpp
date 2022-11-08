//=============================================================================
//
// �S�[���̏��� [score.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include "goal.h"
#include"input.h"
#include"player.h"
#include"fade.h"
#include"pushbutton.h"
#include"facialui.h"
#include"game.h"
#include"choose_game.h"

//=============================================================================
// �ÓI�����o�ϐ��̐錾
//=============================================================================
CPushButton * CGoal::m_pPushButton = NULL;
bool CGoal::m_bGameClear = false;

//=============================================================================
// �S�[���̃R���X�g���N�^
//=============================================================================
CGoal::CGoal(int nPriority) : CScene2D(PRIORITY_GOAL)
{	
	m_bPush = false;	
}

//=============================================================================
// �S�[���̃f�X�g���N�^
//=============================================================================
CGoal::~CGoal()
{

}

//=============================================================================
// �S�[���̐�������
//=============================================================================
CGoal *CGoal::Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size, CManager::MODE NextMode)
{
	CGoal *pGoal = NULL;
	pGoal = new CGoal;

	if (pGoal != NULL)
	{
		pGoal->Init(pos, Size);
		pGoal->m_NextMode = NextMode;
		pGoal->Bindtexture(12);
	}
	return pGoal;
}

//=============================================================================
// �S�[���̏���������
//=============================================================================
HRESULT CGoal::Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	// �J��Ԃ��Q�[���������ꍇ�̂��߂ɏ�����
	m_bGameClear = false;
	m_Pos = pos;
	m_Size = Size;
	CScene2D::Init(pos, Size);
	// �A�j���[�V�����̃e�N�X�`���ݒ�
	CScene2D::SetTexAnime(m_nPatternAnim, 0.125f, 0, 1);
	return S_OK;
}

//=============================================================================
// �S�[���̏I������
//=============================================================================
void CGoal::Uninit(void)
{
	CScene2D::Uninit();

	Release();
}

//=============================================================================
// �S�[���̍X�V����
//=============================================================================
void CGoal::Update(void)
{
	// �A�C�e�������擾
	int nItem = CPlayer::GetItem();

	// �������{�^�����g���Ă��邩�擾
	bool bUIUse = CPushButton::GetUse();

	// �v���C���[�̌��݂̈ʒu���擾
	D3DXVECTOR3 Playerpos = CPlayer::GetPos();

	// �v���C���[�̑傫�����擾
	D3DXVECTOR3 Playersize = CPlayer::GetSize();

	// �v���C���[�ƓG�̎Εӂ̋����𑪂�A����Βl(a-b)
	float fRange = fabs(sqrtf(powf((Playerpos.x - m_Pos.x), 2.0f) + powf((Playerpos.y - m_Pos.y), 2.0f)));		// fabs = ��Βl

	// �A�C�e��������1�ȏゾ������
	if (nItem >= 1)
	{
		// �v���C���[�ƓG�̋�����0����Ȃ�������
		if (fRange != 0)
		{
			// �~�̖ʐςɃv���C���[�Ƃ̎Εӂ̋����������Ă�����
			if (m_Size.x - Playersize.x > fRange)
			{
				// S�������ꂽ��
				if (CManager::GetInputKeyboard()->GetTrigger(DIK_S) == true && !m_bPush)
				{
					// �����ꂽ��
					m_bPush = true;
				}
				// ������Ă�����
				if (m_bPush)
				{
					// �A�j���[�V�����̃J�E���g��i�߂�
					m_nCounterAnim++;

					// �A�j���[�V�����̃J�E���g���A�j���[�V�����̑����Ŋ����ė]�����̂�0��������(����؂ꂽ��)
					if (m_nCounterAnim % 10 == 0)
					{
						// �A�j���[�V�����̃p�^�[������i�߂�
						m_nPatternAnim++;

						// �A�j���[�V�����̃e�N�X�`���ݒ�
						CScene2D::SetTexAnime(m_nPatternAnim, 0.125f, 0, 1);

						// �A�j���[�V�����̃p�^�[�������p�^�[���̍ő吔�𒴂�����
						if (m_nPatternAnim >= 8)
						{
							// �Q�[�����N���A�������Ƃɂ���
							m_bGameClear = true;
							if (CChoose_Game::GetGame())
							{
								// ��ѕ\��ɐ؂�ւ�
								CGame::GetFace()->SetFace(CFacialui::FACE_JOY);
							}
							// ���̃��[�h�ɑJ��
							CFade::SetFade(m_NextMode);

							// �A�j���[�V�����̃p�^�[�����̏�����
							m_nPatternAnim = 0;

							// �A�C�e����������
							nItem--;
							// �A�C�e������0�ȉ��ɂȂ�����
							if (nItem <= 0)
							{// �A�C�e������0�ɂ���
								nItem = 0;
							}
							// �A�C�e������ݒ�
							CPlayer::SetItem(nItem);
						}
					}
				}

				// �g���Ă��Ȃ���������g���Ă�����G���X�ɓ���
				if (!bUIUse)
				{
					// �����{�^����UI�̐���
					m_pPushButton = CPushButton::Create(D3DXVECTOR3(Playerpos.x, Playerpos.y - Playersize.y - 30, Playerpos.z), D3DXVECTOR2(20, 20), 10);// pos= �v���C���[�̌��݂̈ʒu-�傫���̔��a-UI�̑傫��-10
					bUIUse = true;
					CPushButton::SetUse(bUIUse);
				}
				else
				{
					// �����{�^����UI�̌��݂̈ʒu�̐ݒ�
					m_pPushButton->SetPosition(D3DXVECTOR3(Playerpos.x, Playerpos.y - Playersize.y - 30, Playerpos.z));
				}
			}
			else
			{
				// �g�����Ă��邩
				if (bUIUse)
				{// �g�����Ă��������
					bUIUse = false;
					CPushButton::SetUse(bUIUse);
				}
			}
		}
	}
	// �I�u�W�F�N�g2D�̍X�V����
	CScene2D::Update();
}

//=============================================================================
// ���Ԃ̕`�揈��
//=============================================================================
void CGoal::Draw(void)
{
	CScene2D::Draw();
}