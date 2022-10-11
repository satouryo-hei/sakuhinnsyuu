//=============================================================================
//
// ���C������ [renderer.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include"renderer.h"
#include"scene.h"
#include"manager.h"
#include"ui.h"
#include"ui_manager.h"
#include"texture.h"
#include"input.h"
#include "imgui_window.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CRenderer::CRenderer()
{
	m_pD3D = NULL;
	m_pD3DDevice = NULL;
	m_pFont = NULL;
	m_pUiFont = NULL;
	m_bUIControl = false;
	m_FontCol = D3DXCOLOR(255,255,255,255);
	m_FontColType = 0;
	m_bColorTrigger = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CRenderer::~CRenderer()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CRenderer::Init(HWND hWnd, bool bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;								//�v���[���e�[�V�����p�����[�^	
	D3DDISPLAYMODE d3ddm;										//�f�B�X�v���C���[�h

	// Direct3D�I�u�W�F�N�g�̍쐬
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));								// ���[�N���[���N���A
	d3dpp.BackBufferCount = 1;										// �o�b�N�o�b�t�@�̐�
	d3dpp.BackBufferWidth = SCREEN_WIDTH;							// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;							// �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;							// �J���[���[�h�̎w��
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;						// �f���M���ɓ������ăt���b�v����
	d3dpp.EnableAutoDepthStencil = TRUE;							// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;						// �f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed = bWindow;										// �E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// ���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		// �C���^�[�o��

	// �f�o�C�X�̐���
	// �f�B�X�v���C�A�_�v�^��\�����߂̃f�o�C�X���쐬
	// �`��ƒ��_�������n�[�h�E�F�A�ōs�Ȃ�
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &m_pD3DDevice)))
	{
		// ��L�̐ݒ肪���s������
		// �`����n�[�h�E�F�A�ōs���A���_������CPU�ōs�Ȃ�
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &m_pD3DDevice)))
		{
			// ��L�̐ݒ肪���s������
			// �`��ƒ��_������CPU�ōs�Ȃ�
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF, hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp, &m_pD3DDevice)))
			{
				// �������s
				return E_FAIL;
			}
		}
	}

	// �����_�[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);			// �J�����O���s��Ȃ�
	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);					// Z�o�b�t�@���g�p
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);			// ���u�����h���s��
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);	// ���\�[�X�J���[�̎w��
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);// ���f�X�e�B�l�[�V�����J���[�̎w��																			

	// �T���v���[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);// �e�N�X�`���A�h���b�V���O���@(U�l)��ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);// �e�N�X�`���A�h���b�V���O���@(V�l)��ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR); // �e�N�X�`���k���t�B���^���[�h��ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR); // �e�N�X�`���g��t�B���^���[�h��ݒ�

	// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	// ���\���p�t�H���g�̐���
	D3DXCreateFont(m_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);

	// ���\���p�t�H���g�̐���
	D3DXCreateFont(m_pD3DDevice, 20, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pUiFont);

	return S_OK;

}	// �����������I��



//=============================================================================
// �I������
//=============================================================================
void CRenderer::Uninit(void)
{
	// UI�֌W�p�̃t�H���g�̔j��
	if (m_pUiFont != NULL)
	{
		m_pUiFont->Release();
		m_pUiFont = NULL;
	}

	// ���\���p�t�H���g�̔j��
	if (m_pFont != NULL)
	{
		m_pFont->Release();
		m_pFont = NULL;
	}

	// �f�o�C�X�̔j��
	if (m_pD3DDevice != NULL)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;
	}

	// Direct3D�I�u�W�F�N�g�̔j��
	if (m_pD3D != NULL)
	{
		m_pD3D->Release();
		m_pD3D = NULL;
	}
}	// �I�������I��


//=============================================================================
// �X�V����
//=============================================================================
void CRenderer::Update(void)
{
	// �t�H���g�̐F�؂�ւ�
	ColorFont();

	//�|���S���̍X�V����
	CScene::UpdateAll();


}	// �X�V�����I��


//=============================================================================
// �`�揈��
//=============================================================================
void CRenderer::Draw(void)
{
	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	m_pD3DDevice->Clear(0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(125, 125, 125, 0), 1.0f, 0);

	// Direct3D�ɂ��`��̊J�n
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		CScene *pScene = NULL;

		//�|���S���̕`�揈��
		pScene->DrawAll();

		CManager::GetImguiWindow()->Draw();

		// FPS�\��
		DrawFPS();

		// UI���̕\��
		DrawUiInfo();
		DrawUiControl();

		// Direct3D�ɂ��`��̏I��
		m_pD3DDevice->EndScene();
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);

}	// �`�揈���I��


//=============================================================================
// FPS�\��
//=============================================================================
void CRenderer::DrawFPS(void)
{
	//FPS���擾
	int nCountFPS = GetFPS();

	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char str[256];
	
	wsprintf(&str[0], "FPS:%d\n", nCountFPS);
	
	// �e�L�X�g�`��
	m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, m_FontCol);
}

//=============================================================================
// UI�̏��\��
//=============================================================================
void CRenderer::DrawUiInfo(void)
{
	CManager *pManager = NULL;
	char str[512] = {};
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	bool bUse = pManager->GetUi_manager()->GetUse();
	if (bUse)
	{
		int nMax = pManager->GetUi_manager()->GetMax();
		int nDiff = LIMITUI - nMax;
		int nWarning = 0;
		if (nDiff == 0)
		{
			nWarning += sprintf(&str[nWarning], "========================================\n");
			nWarning += sprintf(&str[nWarning], "      �����������₹�Ȃ���I�I����\n");
			nWarning += sprintf(&str[nWarning], "========================================\n");
		}
		else
		{
			nWarning = 0;
		}
	}
	else
	{
		int nNum = sprintf(&str[0], "\n========================================\n");
		nNum += sprintf(&str[nNum], "      �������������Ȃ���I�I����\n");
		nNum += sprintf(&str[nNum], "========================================\n");
		nNum += sprintf(&str[nNum], "�I���������ꍇ��ESC�L�[�������Ă�������\n");
	}
	// �e�L�X�g�`��
	m_pUiFont->DrawText(NULL, str, -1, &rect, DT_LEFT, m_FontCol);

}

//=============================================================================
// ������@�\��
//=============================================================================
void CRenderer::DrawUiControl(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char str[1024];
	
	int nNum = sprintf(&str[0], "========================================\n");
	nNum += sprintf(&str[nNum], "UI�̏������݃t�@�C��:%s\n", SETUITEXT);
	nNum += sprintf(&str[nNum], "========================================\n");
	nNum += sprintf(&str[nNum], "�t�H���g�̐F�̕ύX:[U][J]\n");

	// �e�L�X�g�`��
	m_pUiFont->DrawText(NULL, str, -1, &rect, DT_RIGHT, m_FontCol);
}

//=============================================================================
// �t�H���g�̐F�̐؂�ւ�����
//=============================================================================
void CRenderer::ColorFont(void)
{
	//-----------------------------------------------------------------------------
	// �F�̕ύX
	//-----------------------------------------------------------------------------
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_U) == true)
	{
		m_FontColType++;
		if (m_FontColType > FontCol_NONE)
		{
			m_FontColType = FontCol_WHITE;
		}
	}
	else if (CManager::GetInputKeyboard()->GetTrigger(DIK_J) == true)
	{
		m_FontColType--;
		if (m_FontColType < FontCol_WHITE)
		{
			m_FontColType = FontCol_NONE;
		}
	}

	//-----------------------------------------------------------------------------
	// �F�̐؂�ւ�
	//-----------------------------------------------------------------------------
	switch (m_FontColType)
	{
	case FontCol_WHITE:
		m_FontCol = D3DXCOLOR(255, 255, 255, 255);
		break;
	case FontCol_RED:
		m_FontCol = D3DXCOLOR(255, 0, 0, 255);
		break;

	case FontCol_GREEN:
		m_FontCol = D3DXCOLOR(0, 255, 0, 255);
		break;

	case FontCol_BLUE:
		m_FontCol = D3DXCOLOR(0, 0, 255, 255);
		break;

	case FontCol_YELLOW:
		m_FontCol = D3DXCOLOR(255, 255, 0, 255);
		break;

	case FontCol_PURPLE:
		m_FontCol = D3DXCOLOR(255, 0, 255, 255);
		break;

	case FontCol_LIGHT_BLUE:
		m_FontCol = D3DXCOLOR(0, 255, 255, 255);
		break;
		
	case FontCol_NONE:
		m_FontCol = D3DXCOLOR(0, 0, 0, 0);
		break;

	default:
		break;
	}
}