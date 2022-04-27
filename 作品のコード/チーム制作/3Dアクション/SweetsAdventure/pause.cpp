//---------------------------------------------------
//�w�i�̏���
//---------------------------------------------------
#include "pause.h"
#include "manager.h"
#include "Renderer.h"
#include "scene2D.h"
#include "polygon.h"
#include "texture.h"
#include "keyboard.h"
#include "fade.h"
#include "sound.h"
#include "XInput.h"

//--------------------------
//�R���X�g���N�g
//----------------------------
CPause::CPause(OBJTYPE nPriority) :CScene(nPriority)
{

}

//--------------------------
//�f�X�g���N�g
//----------------------------
CPause::~CPause()
{

}

//--------------------------
//������
//----------------------------
HRESULT CPause::Init(void)
{
	m_fAlpha = 0.0f;
	m_bNextMode = false;
	memset(m_pPolygon, 0, sizeof(m_pPolygon));
	m_pCursor = NULL;
	if (m_pPolygon != NULL)
	{
		m_pPolygon[0] = CPolygon::Create(D3DXVECTOR3(SCREEN_WIDTH/2.0f, 505.0f + (PAUSE_INERVAL * 0), 0.0f), D3DXVECTOR3(140.0f, 30.0f, 0.0f), CTexture::GameBack);
		m_pPolygon[1] = CPolygon::Create(D3DXVECTOR3(SCREEN_WIDTH/2.0f, 505.0f + (PAUSE_INERVAL * 1), 0.0f), D3DXVECTOR3(140.0f, 30.0f, 0.0f), CTexture::Retry);
		m_pPolygon[2] = CPolygon::Create(D3DXVECTOR3(SCREEN_WIDTH/2.0f, 505.0f + (PAUSE_INERVAL * 2), 0.0f), D3DXVECTOR3(140.0f, 30.0f, 0.0f), CTexture::Texture001);
	}
	//�J�[�\��
	m_pCursor = CPolygon::Create(D3DXVECTOR3(m_pos.x, m_pos.y + (PAUSE_INERVAL * 0), 0.0f), D3DXVECTOR3(40.0f, 40.0f, 0.0f), CTexture::Cursol);
	m_pBg = CPolygon::Create(D3DXVECTOR3(640.0f, 360.0f, 0.0f), D3DXVECTOR3(640.0f, 360.0f, 0.0f), CTexture::FADE);
	m_pBg->SetCol(D3DXCOLOR(1.0, 1.0, 1.0, 0.3));
	m_pTutorialUI = CPolygon::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 240.0f, 0.0f), D3DXVECTOR3(350.0f, 200.0f, 0.0f), CTexture::Operation01);

	return S_OK;
}

//--------------------------
//�I��
//----------------------------
void CPause::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_PAUSE; nCnt++)
	{
		if (m_pPolygon[nCnt] != NULL)
		{
			m_pPolygon[nCnt]->Uninit();
			delete m_pPolygon[nCnt];
		}

	}
	if (m_pCursor != NULL)
	{
		m_pCursor->Uninit();
		delete m_pCursor;
	}
	if (m_pTutorialUI != NULL)
	{
		m_pTutorialUI->Uninit();
		delete m_pTutorialUI;
	}

	if (m_pBg != NULL)
	{
		m_pBg->Uninit();
		delete m_pBg;
	}

	CManager::SetPause(false,false);

	Release();
}

//--------------------------
//�X�V
//--------------------------
void CPause::Update(void)
{
	//�Q�[���p�b�h�̎擾
	CXInput *pXInput = CManager::GetXInput();

	if (CManager::GetInputKeyboard()->GetTrigger(DIK_W) == true ||
		pXInput->GetButtonTrigger(XINPUT_GAMEPAD_DPAD_UP) == true)
	{
		//CManager::GetSound()->PlaySound(CManager::GetSound()->SOUND_LABEL_SE_CURSOL);
		//CManager::GetSound()->ControllVoice(CManager::GetSound()->SOUND_LABEL_SE_CURSOL, 2.0f);
		CManager::GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_SELECT);

		m_nPAUSEType--;
		if (m_nPAUSEType < 0)
		{
			m_nPAUSEType = MAX_PAUSE - 1;
		}
	}
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_S) == true ||
		pXInput->GetButtonTrigger(XINPUT_GAMEPAD_DPAD_DOWN) == true)
	{
		//CManager::GetSound()->PlaySound(CManager::GetSound()->SOUND_LABEL_SE_CURSOL);
		//CManager::GetSound()->ControllVoice(CManager::GetSound()->SOUND_LABEL_SE_CURSOL, 2.0f);
		CManager::GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_SELECT);

		m_nPAUSEType++;
		if (m_nPAUSEType >= MAX_PAUSE)
		{
			m_nPAUSEType = 0;
		}
	}
	switch (m_nPAUSEType)
	{
	case 0:
		m_pCursor->SetPos(D3DXVECTOR3(m_pPolygon[0]->GetPos().x - m_pPolygon[0]->GetScale().x - 20.0f, m_pPolygon[0]->GetPos().y,0.0f));
		break;

	case 1:
		m_pCursor->SetPos(D3DXVECTOR3(m_pPolygon[1]->GetPos().x - m_pPolygon[1]->GetScale().x - 20.0f, m_pPolygon[1]->GetPos().y, 0.0f));
		break;

	case 2:
		m_pCursor->SetPos(D3DXVECTOR3(m_pPolygon[2]->GetPos().x - m_pPolygon[2]->GetScale().x - 20.0f, m_pPolygon[2]->GetPos().y, 0.0f));
		break;

	}
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN) == true ||
		pXInput->GetButtonTrigger(XINPUT_GAMEPAD_A) == true&& m_bNextMode==false)
	{
		CManager::GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_ENTER);


		switch (m_nPAUSEType)
		{
		case 0://�Q�[���ɖ߂�
			CManager::SetPause(false,false);
			break;
		case 1://���g���C
			//�Q�[�����[�h�֍s��
			CFade::SetFade(CManager::MODE_GAME);
			break;
		case 2://�^�C�g�����
			//�^�C�g����ʂɍs��
			CFade::SetFade(CManager::MODE_TITLE);
			break;
		}
		m_bNextMode = true;
	}
	if (CManager::GetPause() == false)
	{
		m_bUninit = true;
	}
	if (m_bUninit == true)
	{
		Uninit();
	}

}

//--------------------------
//�`��
//----------------------------
void CPause::Draw(void)
{
	if (m_pBg != NULL)
	{
		m_pBg->Draw();
	}

	if (m_pTutorialUI != NULL)
	{
		m_pTutorialUI->Draw();
	}

	for (int nCnt = 0; nCnt < MAX_PAUSE; nCnt++)
	{
		if (m_pPolygon[nCnt] != NULL)
		{
			m_pPolygon[nCnt]->Draw();
		}
	}
	if (m_pCursor != NULL)
	{
		m_pCursor->Draw();
	}


}
//---------------------------------------------------------------
//�C���X�^���X��������
//---------------------------------------------------------------
CPause *CPause::Create(D3DXVECTOR3 pos)
{
	//�C���X�^���X����
	CPause *pPause = new CPause(OBJTYPE_PAUSE);
	if (pPause != NULL)
	{
		pPause->m_pos = pos;
		pPause->Init();
	}

	return pPause;
}
