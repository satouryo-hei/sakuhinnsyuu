//----------------------------------------------
//�Q�[�W�̏���
//Author::���c
//--------------------------------------------
#include "main.h" 
#include "manager.h"
#include "renderer.h"
#include "gauge.h"
#include "fade.h"
#include "sound.h"

D3DXVECTOR3 CGauge::m_Scale = {};

CGauge::CGauge(OBJTYPE nPriority) : CScene2D(nPriority)
{

}

CGauge::~CGauge()
{

}

CGauge *CGauge::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	CGauge *pGauge = NULL;
	pGauge = new CGauge;
	pGauge->m_pos = pos;
	pGauge->m_Scale = scale;
	pGauge->Init(pos, scale);
	pGauge->BindTexture(CTexture::Gage002);
	return pGauge;
}

HRESULT CGauge::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	CScene2D::Init();
	m_bNextMode = false;
	m_bOneTimeOnlyPlay = false;
	m_fScaleSpeed = 0.1f;
	return S_OK;
}

HRESULT CGauge::Init(void)
{
	return 0;
}

void CGauge::Uninit()
{
	CScene2D::Uninit();
}

void CGauge::Update()
{

	CScene2D::Update();
	CScene2D::SetScalePos(m_pos, m_Scale);
	m_Scale.x += m_fScaleSpeed;//�Q�[�W�̏㏸

	//�Q�[�W���}�C�i�X�܂ł������Ȃ�
	if (m_Scale.x <= 0)
	{
		m_Scale.x = 0.0f;
	}

	if (m_Scale.x >= 300.0f && m_bOneTimeOnlyPlay == false)
	{
		m_bOneTimeOnlyPlay = true;
		CManager::GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_WARNING);
		//CManager::GetSound()->ControllVoice(CSound::SOUND_LABEL_SE_WARNING, 10.0f);
	}

	if (m_Scale.x >= 395.0f && m_bNextMode == false)
	{
		CManager::GetSound()->StopSound(CSound::SOUND_LABEL_SE_WARNING);
		m_Scale.x = 395.0f;
		CManager::SetClear(false);
		//�Q�[�����[�h�֍s��
		CFade::SetFade(CManager::MODE_RESULT);
		////���ȏ�ʂ�Ȃ��悤�ɂ���
		m_bNextMode = true;

	}
}

void CGauge::Draw()
{
	
	CScene2D::Draw();
	
}

//�Q�[�W�̌����p
void CGauge::SetGauge(float Set)
{
	if (m_Scale.x <= 395.0f)
	{
		m_Scale.x += Set;
	}
}