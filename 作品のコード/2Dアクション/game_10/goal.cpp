//=============================================================================
//
// �S�[���̏��� [score.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include "goal.h"
#include"manager.h"
#include"input.h"
#include"player.h"
#include"fade.h"
#include"pushbutton.h"


//=============================================================================
// �ÓI�����o�ϐ��̐錾
//=============================================================================
CPushButton * CGoal::m_pPushButton = NULL;

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
CGoal *CGoal::Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	CGoal *pGoal = NULL;
	pGoal = new CGoal;

	if (pGoal != NULL)
	{
		pGoal->Init(pos, Size);
		pGoal->Bindtexture(0);
	}
	return pGoal;
}

//=============================================================================
// �S�[���̏���������
//=============================================================================
HRESULT CGoal::Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	m_Pos = pos;
	m_Size = Size;
	CScene2D::Init(pos, Size);
	return S_OK;
}

//=============================================================================
// �S�[���̏I������
//=============================================================================
void CGoal::Uninit(void)
{
	Release();
}

//=============================================================================
// �S�[���̍X�V����
//=============================================================================
void CGoal::Update(void)
{
	bool bUIUse = CPushButton::GetUse();
	D3DXVECTOR3 Playerpos = CPlayer::GetPos();
	D3DXVECTOR3 Playersize = CPlayer::GetSize();
	// �v���C���[�ƓG�̎Εӂ̋����𑪂�A����Βl(a-b)
	float fRange = fabs(sqrtf(powf((Playerpos.x - m_Pos.x), 2.0f) + powf((Playerpos.y - m_Pos.y), 2.0f)));		// fabs = ��Βl

	if (fRange != 0)
	{
		// �~�̖ʐςɃv���C���[�Ƃ̎Εӂ̋����������Ă�����
		if (m_Size.x >= fRange)
		{
			// S�������ꂽ��
			if (CManager::GetInputKeyboard()->GetTrigger(DIK_S) == true && !m_bPush)
			{
				CFade::SetFade(CManager::MODE_RESULT);
				m_bPush = true;
			}

			// �g���Ă��Ȃ���������g���Ă�����G���X�ɓ���
			if (!bUIUse)
			{
				// �����{�^����UI�̐���
				m_pPushButton = CPushButton::Create(D3DXVECTOR3(Playerpos.x, Playerpos.y - Playersize.y-30, Playerpos.z), D3DXVECTOR2(20, 20), 10);// pos= �v���C���[�̌��݂̈ʒu-�傫���̔��a-UI�̑傫��-10
				bUIUse = true;
				CPushButton::SetUse(bUIUse);
			}
			else
			{
				m_pPushButton->SetPosition(D3DXVECTOR3(Playerpos.x, Playerpos.y - Playersize.y - 30, Playerpos.z));
			}
		}
		else
		{
			// �g�����Ă��������
			if (bUIUse)
			{
				bUIUse = false;
				CPushButton::SetUse(bUIUse);
			}			
		}
	}
	CScene2D::Update();
}

//=============================================================================
// ���Ԃ̕`�揈��
//=============================================================================
void CGoal::Draw(void)
{
	CScene2D::Draw();
}