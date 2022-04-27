//=============================================================================
//
// ���C������ [renderer.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include"renderer.h"
#include"scene.h"
#include"manager.h"
#include"camera.h"
#include"effect_manager.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CRenderer::CRenderer()
{
	m_pD3D = NULL;
	m_pD3DDevice = NULL;
	m_pFont = NULL;
	m_pEffectInfoFont = NULL;
	m_nNumFont = 0;
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

	// �f�o�b�O���\���p�t�H���g�̐���
	D3DXCreateFont(m_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);

	// �G�t�F�N�g�̏��\���p�t�H���g�̐���
	D3DXCreateFont(m_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pEffectInfoFont);
	return S_OK;

}	// �����������I��



	//=============================================================================
	// �I������
	//=============================================================================
void CRenderer::Uninit(void)
{

	// �f�o�b�O���\���p�t�H���g�̔j��
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
	CScene *pScene = NULL;

	//�|���S���̍X�V����
	pScene->UpdateAll();

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
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// Direct3D�ɂ��`��̊J�n
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		CScene *pScene = NULL;

		//�|���S���̕`�揈��
		pScene->DrawAll();

		// FPS�\��
		DrawFPS();

		// �G�t�F�N�g�̏��\��
		Effectinfo();
		
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
	CManager *pManager = NULL;
	//FPS���擾
	int nCountFPS = GetFPS();

	D3DXVECTOR3 PosV = pManager->GetCamera()->GetPosV();
	D3DXVECTOR3 PosR= pManager->GetCamera()->GetPosR();
	D3DXVECTOR3 rot = pManager->GetCamera()->GetRot();


	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char str[256];

	int nNum = wsprintf(&str[0], "FPS:%d\n", nCountFPS);
	nNum += sprintf(&str[nNum], "�J�����̎��_:%.1f,%.1f,%.1f\n", PosV.x, PosV.y, PosV.z);
	nNum += sprintf(&str[nNum], "�J�����̒����_:%.1f,%.1f,%.1f\n", PosR.x, PosR.y, PosR.z);
	nNum += sprintf(&str[nNum], "�J�����̉�]��:%.2f,%.2f,%.2f\n", rot.x, rot.y, rot.z);

	m_nNumFont = nNum;

	// �e�L�X�g�`��
	m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

}

//=============================================================================
// �G�t�F�N�g�̏��\������
//=============================================================================
void CRenderer::Effectinfo(void)
{

	CManager *pManager = NULL;

	D3DXVECTOR3 pos = pManager->GetEffectManager()->GetPos();
	D3DXVECTOR3 move = pManager->GetEffectManager()->GetMove();
	D3DXVECTOR3 addmove = pManager->GetEffectManager()->GetAddMove();
	D3DXVECTOR3 Size = pManager->GetEffectManager()->GetSize();
	D3DXVECTOR3 AddSize = pManager->GetEffectManager()->GetAddSize();
	D3DXCOLOR col = pManager->GetEffectManager()->GetCol();
	D3DXCOLOR AddCol = pManager->GetEffectManager()->GetAddCol();
	int nLife = pManager->GetEffectManager()->GetLife();			
	int nDensity = pManager->GetEffectManager()->GetDensity();
	int nRadius = pManager->GetEffectManager()->GetRadius();
	int nType = pManager->GetEffectManager()->GetEffectType();
	int nColor = pManager->GetEffectManager()->GetColorType();
	int nVerType = pManager->GetEffectManager()->GetVectorType();

	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char str[1024];

	int nNum = 0;
	nNum += sprintf(&str[nNum], "���݂̈ʒu�̒l[X,Y,Z]:%.2f,%.2f,%.2f\n", pos.x, pos.y, pos.z);
	nNum += sprintf(&str[nNum], "�ړ��ʂ̒l[X,Y,Z]:%.2f,%.2f,%.2f\n", move.x, move.y, move.z);
	nNum += sprintf(&str[nNum], "�ړ��ʂ̌��Z�l[X,Y,Z]:%.2f,%.2f,%.2f\n", addmove.x, addmove.y, addmove.z);
	nNum += sprintf(&str[nNum], "�傫���̒l[X,Y,Z]:%.2f,%.2f,%.2f\n", Size.x, Size.y, Size.z);
	nNum += sprintf(&str[nNum], "�傫���̌��Z�l[X,Y,Z]:%.2f,%.2f,%.2f\n", AddSize.x, AddSize.y, AddSize.z);
	nNum += sprintf(&str[nNum], "�F�̒l[R,G,B,A]:%.2f,%.2f,%.2f,%.2f\n", col.r, col.g, col.b, col.a);
	nNum += sprintf(&str[nNum], "�F�̌��Z�l[R,G,B,A]:%.2f,%.2f,%.2f,%.2f\n", AddCol.r, AddCol.g, AddCol.b, AddCol.a);
	nNum += sprintf(&str[nNum], "����:%d\n", nLife);
	nNum += sprintf(&str[nNum], "���x:%d\n", nDensity);

	switch (nType)
	{
	case CEffect_Manager::EffectType_STRAIGHT:
		nNum += sprintf(&str[nNum], "�G�t�F�N�g�̎��:�X�g���[�g\n");
		break;
	case CEffect_Manager::EffectType_CIRCLE:
		nNum += sprintf(&str[nNum], "���a:%d\n", nRadius);
		nNum += sprintf(&str[nNum], "�G�t�F�N�g�̎��:�~�`\n");
		break;
	case CEffect_Manager::EffectType_EXPLOSIN:
		nNum += sprintf(&str[nNum], "�G�t�F�N�g�̎��:����\n");
		break;
	case CEffect_Manager::EffectType_DOME:
		nNum += sprintf(&str[nNum], "���a:%d\n", nRadius);
		nNum += sprintf(&str[nNum], "�G�t�F�N�g�̎��:�h�[���^\n");
		break;
	case CEffect_Manager::EffectType_WATER_CREST:
		nNum += sprintf(&str[nNum], "���a:%d\n", nRadius);
		nNum += sprintf(&str[nNum], "�G�t�F�N�g�̎��:�g��\n");
		break;
	case CEffect_Manager::EffectType_SMOKE:
		nNum += sprintf(&str[nNum], "���a:%d\n", nRadius);
		nNum += sprintf(&str[nNum], "�G�t�F�N�g�̎��:��\n");
		break;
	case CEffect_Manager::EffectType_LANDING:
		nNum += sprintf(&str[nNum], "���a:%d\n", nRadius);
		nNum += sprintf(&str[nNum], "�G�t�F�N�g�̎��:���n\n");
		break;
	default:
		nNum += sprintf(&str[nNum], "�G�t�F�N�g�̎��:�Ȃ�\n");
		break;
	}

	switch (nColor)
	{
	case CEffect_Manager::ColorType_RED:
		nNum += sprintf(&str[nNum], "�F:��\n");
		break;
	case CEffect_Manager::ColorType_GREEN:
		nNum += sprintf(&str[nNum], "�F:��\n");
		break;
	case CEffect_Manager::ColorType_BLUE:
		nNum += sprintf(&str[nNum], "�F:��\n");
		break;
	case CEffect_Manager::ColorType_ARUFA:
		nNum += sprintf(&str[nNum], "�F:�����x\n");
		break;	
	default:	
		break;
	}

	switch (nVerType)
	{
	case CEffect_Manager::Vector_X:
		nNum += sprintf(&str[nNum], "���̃x�N�g��:X\n");
		break;
	case CEffect_Manager::Vector_Y:
		nNum += sprintf(&str[nNum], "���̃x�N�g��:Y\n");
		break;
	case CEffect_Manager::Vector_Z:
		nNum += sprintf(&str[nNum], "���̃x�N�g��:Z\n");
		break;
	default:
		break;
	}

	// �e�L�X�g�`��
	m_pEffectInfoFont->DrawText(NULL, str, -1, &rect, DT_RIGHT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}