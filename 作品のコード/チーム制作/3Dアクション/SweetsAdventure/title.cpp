//--------------------------------------
//�}�l�[�W���[�̏���
//--------------------------------------
#include "title.h"
#include "bg.h"
#include "texture.h"
#include "manager.h"
#include "keyboard.h"
#include "fade.h"
#include "Polygon.h"
#include "XInput.h"
#include "sound.h"

//--------------------------------------------
//�R���X�g���N�^
//--------------------------------------------
CTitle::CTitle()
{
	memset(m_Polygon, 0, sizeof(m_Polygon));
	m_bOpra = false;
}
//--------------------------------------------
//�f�X�g���N�^
//--------------------------------------------
CTitle::~CTitle()
{

}

//--------------------------------------------
//������
//--------------------------------------------
HRESULT CTitle::Init(void)
{
	m_bNextMode = false;
	CBg::Create(CTexture::Title, CScene::OBJTYPE_BG, false);	//�w�i
	m_Polygon[0]=CPolygon::Create(D3DXVECTOR3(SCREEN_WIDTH/2.0f, SCREEN_HEIGHT / 2 - 280.0f, 0.0f), D3DXVECTOR3(430.0f, 80.0f, 0.0f), CTexture::Titlelogo);	//�^�C�g�����S
	m_Polygon[1]=CPolygon::Create(D3DXVECTOR3(900.0f, SCREEN_HEIGHT / 2 + 50.0f, 0.0f), D3DXVECTOR3(300.0f, 80.0f, 0.0f), CTexture::GameStart);	//�Q�[���X�^�[�g
	m_Polygon[2]=CPolygon::Create(D3DXVECTOR3(900.0f, SCREEN_HEIGHT / 2 + 250, 0.0f), D3DXVECTOR3(300.0f, 40.0f, 0.0f), CTexture::Operation);	//�`���[�g���A��
	m_Cursol= CPolygon::Create(D3DXVECTOR3(900.0f, SCREEN_HEIGHT / 2 + 250, 0.0f), D3DXVECTOR3(40.0f, 40.0f, 0.0f), CTexture::Cursol);	//�J�[�\��
	return S_OK;
}
//--------------------------------------------
//�I��
//--------------------------------------------
void CTitle::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_TITLE_POLYGON; nCnt++)
	{
		if (m_Polygon[nCnt] != NULL)
		{
			m_Polygon[nCnt]->Uninit();
			m_Polygon[nCnt] = NULL;
		}
	}

	CManager::GetSound()->StopSound(CSound::SOUND_LABEL_BGM_TITLE);
}
//--------------------------------------------
//�X�V
//--------------------------------------------
void CTitle::Update(void)
{
	CXInput *pGamePad = CManager::GetXInput();

	if (m_bNextMode == false)
	{
		if (pGamePad->GetButtonTrigger(XINPUT_GAMEPAD_DPAD_UP) == true)
		{
			m_nSelectType--;
			if (m_nSelectType < 0)
			{
				m_nSelectType = OPERATION;
			}

			CManager::GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_SELECT);
		}

		else if (pGamePad->GetButtonTrigger(XINPUT_GAMEPAD_DPAD_DOWN) == true)
		{
			m_nSelectType++;
			if (m_nSelectType >= MAX)
			{
				m_nSelectType = GAME_START;
			}

			CManager::GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_SELECT);

		}

	}

	switch (m_nSelectType)
	{
	case GAME_START:
		m_Cursol->SetPos(D3DXVECTOR3(m_Polygon[1]->GetPos().x - m_Polygon[1]->GetScale().x - 20.0f, m_Polygon[1]->GetPos().y, 0.0f));
		break;
	case OPERATION:
		m_Cursol->SetPos(D3DXVECTOR3(m_Polygon[2]->GetPos().x - m_Polygon[2]->GetScale().x - 20.0f, m_Polygon[2]->GetPos().y, 0.0f));
		break;
	}

	//A�{�^����������
	if (pGamePad->GetButtonTrigger(XINPUT_GAMEPAD_A) == true && m_bNextMode == false)
	{
		CManager::GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_ENTER);

		if (m_bOpra == false)
		{
			switch (m_nSelectType)
			{
			case GAME_START:
				//�Q�[�����[�h�֍s��
				CFade::SetFade(CManager::MODE_GAME);
				////���ȏ�ʂ�Ȃ��悤�ɂ���
				m_bNextMode = true;

				break;
			case OPERATION:
				m_bOpra = true;
				m_Polygon[3] = CPolygon::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CTexture::FADE);	//�`���[�g���A��
				m_Polygon[4] = CPolygon::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 3.0f, SCREEN_HEIGHT / 3.0f, 0.0f), CTexture::Operation01);	//�`���[�g���A��
				m_Polygon[3]->SetCol(D3DXCOLOR(1.0, 1.0, 1.0, 0.5));
				break;
			}
		}
		//�`���[�g���A����ʐ������o����
		else if (m_bOpra == true)
		{
			//A��B�{�^����������
			if (pGamePad->GetButtonTrigger(XINPUT_GAMEPAD_A) == true)
			{
				if (m_Polygon[3] != NULL)
				{
					m_Polygon[3]->Uninit();
					m_Polygon[3] = NULL;
					m_bOpra = false;
				}
				if (m_Polygon[4] != NULL)
				{
					m_Polygon[4]->Uninit();
					m_Polygon[4] = NULL;
				}


			}
		}
	}
}
//--------------------------------------------
//�`��
//--------------------------------------------
void CTitle::Draw(void)
{

}

