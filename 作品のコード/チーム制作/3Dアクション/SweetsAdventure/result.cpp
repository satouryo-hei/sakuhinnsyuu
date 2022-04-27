//--------------------------------------
//���U���g��ʂ̏���
//--------------------------------------
#include "result.h"
#include "bg.h"
#include "texture.h"
#include "manager.h"
#include "keyboard.h"
#include "fade.h"
#include "Polygon.h"
#include "XInput.h"
#include "sound.h"

CBg *CResult::m_pBg = NULL;
//--------------------------------------------
//�R���X�g���N�^
//--------------------------------------------
CResult::CResult()
{
	m_bNextMode = false;
	m_Cursol = NULL;
}
//--------------------------------------------
//�f�X�g���N�^
//--------------------------------------------
CResult::~CResult()
{
}
//--------------------------------------------
//������
//--------------------------------------------
HRESULT CResult::Init(void)
{
	m_bNextMode = false;
	if (CManager::GetClear() == true)
	{
		m_pBg = CBg::Create(CTexture::GameClear000, CScene::OBJTYPE_BG, false);	//�w�i
		pPolygon[0] = CPolygon::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 50.0f, 0.0f), D3DXVECTOR3(500.0f, 300.0f, 0.0f), CTexture::GameClear001);	//�Q�[���I�[�o�[
	}
	else
	{
		m_pBg = CBg::Create(CTexture::GameOver, CScene::OBJTYPE_BG, false);	//�w�i
		pPolygon[0] = CPolygon::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 280.0f, 0.0f), D3DXVECTOR3(800.0f, 450.0f, 0.0f), CTexture::Gameover000);	//�Q�[���I�[�o�[

	}
	pPolygon[1] = CPolygon::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 80.0f, 0.0f), D3DXVECTOR3(200, 40.0f, 0.0f), CTexture::Retry);	//���g���C
	pPolygon[2] = CPolygon::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200.0f, 0.0f), D3DXVECTOR3(200, 40.0f, 0.0f), CTexture::Texture001);	//�^�C�g���ɖ߂�
	m_Cursol = CPolygon::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), CTexture::Cursol);	//�^�C�g���ɖ߂�
																																							//m_pBg->SetCol(D3DXCOLOR(0.0, 0.0, 1.0, 1.0));

	return S_OK;
}
//--------------------------------------------
//�I��
//--------------------------------------------

void CResult::Uninit(void)
{
	if (m_pBg != NULL)
	{
		m_pBg->Uninit();
		m_pBg = NULL;
	}
	for (int nCnt = 0; nCnt < MAX_RESULT; nCnt++)
	{
		if (pPolygon[nCnt] != NULL)
		{
			pPolygon[nCnt]->Uninit();
			pPolygon[nCnt] = NULL;
		}
	}
	if (m_Cursol != NULL)
	{
		m_Cursol->Uninit();
		m_Cursol = NULL;
	}
}
//--------------------------------------------
//�X�V
//--------------------------------------------
void CResult::Update(void)
{

	CXInput *pGamePad = CManager::GetXInput();
	if (m_bNextMode == false)
	{
		if (pGamePad->GetButtonTrigger(XINPUT_GAMEPAD_DPAD_UP) == true)
		{
			m_nSelectType--;
			if (m_nSelectType < 0)
			{
				m_nSelectType = TITLE;
			}

			CManager::GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_SELECT);
		}
		else if (pGamePad->GetButtonTrigger(XINPUT_GAMEPAD_DPAD_DOWN) == true)
		{
			m_nSelectType++;
			if (m_nSelectType >= MAX)
			{
				m_nSelectType = GAME_RETRY;
			}

			CManager::GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_SELECT);
		}

	}

	switch (m_nSelectType)
	{
	case GAME_RETRY:
		m_Cursol->SetPos(D3DXVECTOR3(pPolygon[1]->GetPos().x - pPolygon[1]->GetScale().x - 20.0f, pPolygon[1]->GetPos().y, 0.0f));
		break;
	case TITLE:
		m_Cursol->SetPos(D3DXVECTOR3(pPolygon[2]->GetPos().x - pPolygon[2]->GetScale().x - 20.0f, pPolygon[2]->GetPos().y, 0.0f));
		break;
	}

	//A�{�^����������
	if (pGamePad->GetButtonTrigger(XINPUT_GAMEPAD_A) == true && m_bNextMode == false)
	{
		CManager::GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_ENTER);

		switch (m_nSelectType)
		{
		case GAME_RETRY:
			//�Q�[�����[�h�֍s��
			CFade::SetFade(CManager::MODE_GAME);
			////���ȏ�ʂ�Ȃ��悤�ɂ���
			m_bNextMode = true;

			break;
		case TITLE:
			//�Q�[�����[�h�֍s��
			CFade::SetFade(CManager::MODE_TITLE);
			////���ȏ�ʂ�Ȃ��悤�ɂ���
			m_bNextMode = true;
			break;
		}

	}
}
//--------------------------------------------
//�`��
//--------------------------------------------

void CResult::Draw(void)
{

}

