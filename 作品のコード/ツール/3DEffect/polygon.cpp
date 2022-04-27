//=============================================================================
//
// �|���S���̏��� [polygon.h]
// Author : �����ĕ�
//
//=============================================================================
#include"polygon.h"
#include"manager.h"
#include"renderer.h"
#include"input.h"

//=============================================================================
// �ÓI�����o�ϐ��̐錾
//=============================================================================
LPDIRECT3DTEXTURE9 CPolygon::m_pTexture[POLYGON_TYPE_MAX] = {};

//=============================================================================
// �|���S���̃R���X�g���N�^
//=============================================================================
CPolygon::CPolygon()
{
	m_Size = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Porigon_Type = POLYGON_TYPE_MAX;
	m_pPorigon = NULL;
	m_nNumPorigon = 0;
}


//=============================================================================
// �|���S���̃f�X�g���N�^
//=============================================================================
CPolygon::~CPolygon()
{

}

//=============================================================================
// �|���S���̐�������
//=============================================================================
CPolygon *CPolygon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 Size)
{
	CPolygon* pPolygon;

	pPolygon = new CPolygon;

	if (pPolygon != NULL)
	{
		pPolygon->Init(pos, Size);
	}
	return pPolygon;
}

//=============================================================================
// �e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CPolygon::Load(void)
{
	CManager *pManager = NULL;

	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/PlayerAnim002.png",
		&m_pTexture[0]);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���̔j��
//=============================================================================
void CPolygon::Unload(void)
{
	for (int nCnt = 0; nCnt < POLYGON_TYPE_MAX; nCnt++)
	{
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}

//=============================================================================
// �|���S���̏���������
//=============================================================================
HRESULT CPolygon::Init(D3DXVECTOR3 pos, D3DXVECTOR3 Size)
{
	CScene2D::Init(pos,Size);

	return S_OK;
}	// �|���S���̏����������I��



	//=============================================================================
	// �|���S���̏I������
	//=============================================================================
void CPolygon::Uninit(void)
{
	CScene2D::Uninit();

}// �|���S���̏I�������I��


 //=============================================================================
 // �|���S���̍X�V����
 //=============================================================================
void CPolygon::Update(void)
{
	//CInputKeyboard *pInputKeyboard;

	//pInputKeyboard = CManager::GetInputKeyboard();


	//if (pInputKeyboard->GetTrigger(DIK_LEFT) == true)//����������
	//{
	//	m_nNumPorigon--;
	//	if (m_nNumPorigon < 0)
	//	{
	//		m_nNumPorigon = POLYGON_TYPE_MAX - 1;
	//	}

	//	m_Porigon_Type = (POLYGON_TYPE)m_nNumPorigon;
	//}
	//else if (pInputKeyboard->GetTrigger(DIK_RIGHT) == true)//����������
	//{
	//	m_nNumPorigon++;
	//	if (m_nNumPorigon >= POLYGON_TYPE_MAX)
	//	{
	//		m_nNumPorigon = 0;
	//	}

	//	m_Porigon_Type = (POLYGON_TYPE)m_nNumPorigon;
	//}

	//if (pInputKeyboard->GetPress(DIK_RETURN) == true)
	//{
	//	switch (m_Porigon_Type)
	//	{
	//	case POLYGON_TYPE_FIRST:
	//		if (m_pPorigon == NULL)
	//		{
	//			m_pPorigon->Create(D3DXVECTOR3(100.0f, 320.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f));
	//		}
	//		break;

	//	case POLYGON_TYPE_SECOND:
	//		if (m_pPorigon == NULL)
	//		{
	//			m_pPorigon->Create(D3DXVECTOR3(500.0f, 320.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f));;
	//		}
	//		break;

	//	case POLYGON_TYPE_THIRD:
	//		if (m_pPorigon == NULL)
	//		{
	//			m_pPorigon->Create(D3DXVECTOR3(1000.0f, 320.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f));
	//		}
	//		break;

	//	default:
	//		break;
	//	}
	//}
	//if (pInputKeyboard->GetPress(DIK_SPACE) == true)
	//{
	//	if (m_pPorigon != NULL)
	//	{
	//		m_pPorigon->Uninit();
	//		m_pPorigon = NULL;
	//		return;
	//	}
	//}

	CScene2D::Update();

}// �|���S���̍X�V�����I��



 //=============================================================================
 // �|���S���̕`�揈��
 //=============================================================================
void CPolygon::Draw(void)
{
	CScene2D::Draw();

}	// �|���S���̕`�揈���I��