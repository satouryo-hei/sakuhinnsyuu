//=============================================================================
//
// �J�b�g�C���̏��� [cutin.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include"cutin.h"
#include"renderer.h"
#include"scene2D.h"

// �ÓI�����o�ϐ��̐錾
LPDIRECT3DTEXTURE9 CCutin::m_pTexture[CUTTYP_MAX] = {};
CCutin::CUTTYP CCutin::m_Cuttyp = CUTTYP_BG;
CCutin::CUTIN CCutin::m_Cutin = CUTIN_NONE;
D3DXVECTOR3 CCutin::m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

//=============================================================================
// �J�b�g�C���̃R���X�g���N�^
//=============================================================================
CCutin::CCutin(int nPriority)
{
	memset(&m_apScene2D[0], 0, sizeof(m_apScene2D));
}

//=============================================================================
// �J�b�g�C���̃f�X�g���N�^
//=============================================================================
CCutin::~CCutin()
{

}

//=============================================================================
// �J�b�g�C���̐�������
//=============================================================================
CCutin *CCutin::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size, CUTTYP CutTyp)
{
	CCutin* pCutin;

	pCutin = new CCutin(PRIORITY_BG);

	if (pCutin != NULL)
	{
		pCutin->Init(pos,Size);
	}
	m_move = move;
	return pCutin;
}

//=============================================================================
// �J�b�g�C���̓ǂݍ���
//=============================================================================
HRESULT CCutin::Load(void)
{
	CManager *pManager = NULL;

	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/effect000.jpg",
		&m_pTexture[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/effect000.jpg",
		&m_pTexture[1]);

	return S_OK;
}

//=============================================================================
// �J�b�g�C���̔j��
//=============================================================================
void CCutin::Unload(void)
{
	for (int nCntCutin = 0; nCntCutin < CUTTYP_MAX; nCntCutin++)
	{
		if (m_pTexture[nCntCutin] != NULL)
		{
			m_pTexture[nCntCutin]->Release();
			m_pTexture[nCntCutin] = NULL;
		}
	}
}

//=============================================================================
// �J�b�g�C���̏���������
//=============================================================================
HRESULT CCutin::Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	for (int nCntCutin = 0; nCntCutin < CUTTYP_MAX; nCntCutin++)
	{
		m_apScene2D[nCntCutin] = new CScene2D(PRIORITY_UI);

		if (m_apScene2D[nCntCutin] != NULL)
		{
			m_apScene2D[nCntCutin]->Init(pos, Size);
			m_apScene2D[nCntCutin]->BindTextuer(m_pTexture[nCntCutin]);
		}
	}
	return S_OK;
}


//=============================================================================
// �J�b�g�C���̏I������
//=============================================================================
void CCutin::Uninit(void)
{
	for (int nCntnCntCutin = 0; nCntnCntCutin < CUTTYP_MAX; nCntnCntCutin++)
	{
		if (m_apScene2D[nCntnCntCutin] != NULL)
		{
			m_apScene2D[nCntnCntCutin]->Uninit();
			m_apScene2D[nCntnCntCutin] = NULL;
		}
	}
	Relese();
}


//=============================================================================
// �J�b�g�C���̍X�V����
//=============================================================================
void CCutin::Update(void)
{
	switch (m_Cutin)
	{
	case CUTTYP_BG:
		break;
	case CUTTYP_ANIME:
		break;
	default:
		break;
	}
}

//=============================================================================
// �J�b�g�C���̕`�揈��
//=============================================================================
void CCutin::Draw(void)
{

}