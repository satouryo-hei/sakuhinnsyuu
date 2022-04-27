//=============================================================================
//
// �v���C���[�̏��� [player.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include"player.h"
#include"renderer.h"
#include"manager.h"
#include"input.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = 0;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPlayer::CPlayer(PRIORITY Priority) :CScene2D(Priority), m_fSpeedMax(2.1f)
{
	int m_Life = 0;
	float m_fSpeed = 0;

	m_bUse = true;
}


//=============================================================================
//�@�f�X�g���N�^
//=============================================================================
CPlayer::~CPlayer()
{

}

//=============================================================================
// �|���S���̐�������
//=============================================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 Size)
{
	CPlayer* pPlayer;

	pPlayer = new CPlayer;

	if (pPlayer != NULL)
	{
		pPlayer->Init(pos, Size);
	}
	return pPlayer;
}

//=============================================================================
// �e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CPlayer::Load(void)
{
	CManager *pManager=NULL;

	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/boss.png",
		&m_pTexture);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���̔j��
//=============================================================================
void CPlayer::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// �|���S���̏���������
//=============================================================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 Size)
{
	int m_Life = 2;
	float m_fSpeed = 0;

	CScene2D::Init(pos, Size);

	return S_OK;
}	// �|���S���̏����������I��



//=============================================================================
// �|���S���̏I������
//=============================================================================
void CPlayer::Uninit(void)
{	
	CScene2D::Uninit();

}// �|���S���̏I�������I��


 //=============================================================================
 // �|���S���̍X�V����
 //=============================================================================
void CPlayer::Update(void)
{
	CInputKeyboard *pInputKeyboard;

	pInputKeyboard = CManager::GetInputKeyboard();

	D3DXVECTOR3 pos = GetPosition();

	//�C�ӂŉ����ꂽ���ǂ���
	if (pInputKeyboard->GetPress(DIK_A) == true)//����������
	{
		if (pInputKeyboard->GetPress(DIK_W) == true)//��Ɉړ�
		{
			pos.x += sinf(D3DX_PI*-0.75f)*m_fSpeedMax;
			pos.y += cosf(D3DX_PI*-0.75f)*m_fSpeedMax;
		}

		else if (pInputKeyboard->GetPress(DIK_S) == true)//���Ɉړ�
		{
			pos.x += sinf(D3DX_PI*-0.25f)*m_fSpeedMax;
			pos.y += cosf(D3DX_PI*-0.25f)*m_fSpeedMax;
		}

		else
		{
			pos.x -= m_fSpeedMax;
		}
	}

	if (pInputKeyboard->GetPress(DIK_D) == true)//�E��������
	{
		if (pInputKeyboard->GetPress(DIK_W) == true)//��Ɉړ�
		{
			pos.x += sinf(D3DX_PI*0.75f)*m_fSpeedMax;
			pos.y += cosf(D3DX_PI*0.75f)*m_fSpeedMax;
		}

		else if (pInputKeyboard->GetPress(DIK_S) == true)//���Ɉړ�
		{
			pos.x += sinf(D3DX_PI*0.25f)*m_fSpeedMax;
			pos.y += cosf(D3DX_PI*0.25f)*m_fSpeedMax;
		}

		else
		{
			pos.x += m_fSpeedMax;
		}
	}

	if (pInputKeyboard->GetPress(DIK_W) == true)//��Ɉړ�
	{
		pos.y -= m_fSpeedMax;
	}

	if (pInputKeyboard->GetPress(DIK_S) == true)//���Ɉړ�
	{
		pos.y += m_fSpeedMax;
	}

	if (pInputKeyboard->GetTrigger(DIK_SPACE) == true)
	{
		//�e�̐���
		//CBullet::Creste(pos, D3DXVECTOR3(6.0f, 0.0f, 0.0f),D3DXVECTOR2(10.0f, 10.0f));
	}

	float fSpeed;

	fSpeed = m_fSpeedMax;

	if (pInputKeyboard->GetRelease(DIK_A)==true)
	{
		fSpeed -= 0.1f;

		pos.x += fSpeed;
	}

	SetPosition(pos);

	CScene2D::Update();

	if (pos.x >= SCREEN_WIDTH - MAX_DATA)
	{
		pos.x = SCREEN_WIDTH - MAX_DATA;
	}
	else if (pos.x <= MAX_DATA)
	{
		pos.x = MAX_DATA;
	}
	if (pos.y >= SCREEN_HEIGHT - MAX_DATA)
	{
		pos.y = SCREEN_HEIGHT - MAX_DATA;
	}
	else if (pos.y <= MAX_DATA)
	{
		pos.y = MAX_DATA;
	}

	if (!m_bUse)
	{
		Uninit();
	}
}// �|���S���̍X�V�����I��



 //=============================================================================
 // �|���S���̕`�揈��
 //=============================================================================
void CPlayer::Draw(void)
{
	CScene2D::Draw();

}	// �|���S���̕`�揈���I��

