//=============================================================================
//
// �J�������� [camera.cpp]
// Author : �����ĕ�
//
//=============================================================================
#include"Camera.h"
#include"input.h"
#include"manager.h"
#include"renderer.h"

//=============================================================================
// ���C�g�̃R���X�g���N�^
//=============================================================================
CCamera::CCamera()
{
	memset(&m_mtxProjection, NULL, sizeof(m_mtxProjection));
	memset(&m_mtxView, NULL, sizeof(m_mtxView));
	memset(&m_viewport, NULL, sizeof(m_viewport));
	m_posV = D3DXVECTOR3(0.0f, 200.0f, -100.0f);
	m_posVDest = D3DXVECTOR3(0.0f, 100.0f, -100.0f);
	m_posR = D3DXVECTOR3(0.0f,
		200.0f, //0�ɂȂ�ɂ�^�������ɂȂ�
		0.0f);
	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Range = m_posV.z*(-1);
}


//=============================================================================
// ���C�g�̃f�X�g���N�^
//=============================================================================
CCamera::~CCamera()
{

}

//=============================================================================
// �J�����̏�����
//=============================================================================
HRESULT CCamera::Init(void)
{
#if 0
	//_�����̈ʒu
	m_posV = D3DXVECTOR3(0.0f, 40.0f, -10.0f);
	m_posR = D3DXVECTOR3(0.0f,
		-30.0f, //0�ɂȂ�ɂ�܂������ɂȂ�
		10.0f);
#endif
	//m_posV = D3DXVECTOR3(0.0f, 100.0f, -100.0f);
	//m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//����3.14�`--3.14�܂�

	//m_posVDest = D3DXVECTOR3(0.0f, 100.0f, -100.0f);

	//m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

#if 0
	viewport.X = 100;
	viewport.Y = 100;
	viewport.Width = 100;
	viewport.Height = 100;
	viewport.MinZ = 0.0f;
	viewport.MaxZ = 1.0f;
#endif

	return S_OK;
}

//=============================================================================
// �J�����̏I������
//=============================================================================
void CCamera::Uninit(void)
{
}

//=============================================================================
// �J�����̍X�V����
//=============================================================================
void CCamera::Update(void)
{
	CInputKeyboard *pInputKeyboard = NULL;
	pInputKeyboard = CManager::GetInputKeyboard();

	//m_Range = m_posV.z;

#if 0
	//�����_�̏㉺
	if (pInputKeyboard->GetPress(DIK_T))//����������
	{
		m_posR.y += 2.0f;
	}
	if (pInputKeyboard->GetPress(DIK_G))
	{
		m_posR.y -= 2.0f;
	}
	//�����_�̏㉺�̏I���

	//���_�̏㉺
	if (pInputKeyboard->GetPress(DIK_I))
	{
		m_posV.y += 2.0f;
	}
	if (pInputKeyboard->GetPress(DIK_K))
	{
		m_posV.y -= 2.0f;
	}
	//���_�̏㉺�̏I���

#endif

#if 1
	//�J�����̈ړ�
	if (pInputKeyboard->GetPress(DIK_Q))
	{
		m_posV.x = m_posV.x - cosf(m_rot.y) * 2.0f;
		m_posV.z = m_posV.z + sinf(m_rot.y) * 2.0f;
		m_posR.z = m_posR.z + sinf(m_rot.y) * 2.0f;
		m_posR.x = m_posR.x - cosf(m_rot.y) * 2.0f;
	}
	if (pInputKeyboard->GetPress(DIK_E))
	{
		m_posV.x = m_posV.x + cosf(m_rot.y) * 2.0f;
		m_posV.z = m_posV.z - sinf(m_rot.y) * 2.0f;
		m_posR.z = m_posR.z - sinf(m_rot.y) * 2.0f;
		m_posR.x = m_posR.x + cosf(m_rot.y) * 2.0f;
	}
	if (pInputKeyboard->GetPress(DIK_Z))
	{
		m_posV.x = m_posV.x + sinf(m_rot.y) * 2.0f;
		m_posV.z = m_posV.z + cosf(m_rot.y) * 2.0f;
		m_posR.x = m_posR.x + sinf(m_rot.y) * 2.0f;
		m_posR.z = m_posR.z + cosf(m_rot.y) * 2.0f;
	}
	if (pInputKeyboard->GetPress(DIK_C))
	{
		m_posV.x = m_posV.x - sinf(m_rot.y) * 2.0f;
		m_posV.z = m_posV.z - cosf(m_rot.y) * 2.0f;
		m_posR.x = m_posR.x - sinf(m_rot.y) * 2.0f;
		m_posR.z = m_posR.z - cosf(m_rot.y) * 2.0f;
	}
	//�J�����̈ړ��̏I���

	////�J�����̒����_
	//if (pInputKeyboard->GetPress(DIK_R))
	//{
	//	m_rot.y += 0.01f;
	//	m_posR.x = m_posV.x + sinf(m_rot.y) * m_Range;//���݂̒����_(x)�����݂̎��_(x)+sinf(�J�����̌���(y))*�����_�܂ł̋���
	//	m_posR.z = m_posV.z + cosf(m_rot.y) * m_Range;
	//}
	//if (pInputKeyboard->GetPress(DIK_F))
	//{
	//	m_rot.y -= 0.01f;
	//	m_posR.x = m_posV.x + sinf(m_rot.y) * m_Range;
	//	m_posR.z = m_posV.z + cosf(m_rot.y) * m_Range;
	//}
	if (pInputKeyboard->GetPress(DIK_T))
	{
		m_posR.y += 2.0f;
	}
	if (pInputKeyboard->GetPress(DIK_G))
	{
		m_posR.y -= 2.0f;
	}
	//�����_�̏I���

	//�J�����̎��_
	if (pInputKeyboard->GetPress(DIK_F))
	{
		m_rot.y += 0.01f;
		m_posV.x = m_posR.x - sinf(m_rot.y) * m_Range;
		m_posV.z = m_posR.z - cosf(m_rot.y) * m_Range;
	}
	if (pInputKeyboard->GetPress(DIK_R))
	{
		m_rot.y -= 0.01f;
		m_posV.x = m_posR.x - sinf(m_rot.y) * m_Range;
		m_posV.z = m_posR.z - cosf(m_rot.y) * m_Range;
	}
	if (pInputKeyboard->GetPress(DIK_Y))
	{
		m_posV.y += 2.0f;
		//g_Camera.rot.x -= 0.01f;

		//g_Camera.posV.x= g_Camera.posR.x- sinf(g_Camera.rot.x) * 100.0f;

		//g_Camera.posV.y = g_Camera.posR.y + cosf(g_Camera.rot.x)*100.0;
	}
	if (pInputKeyboard->GetPress(DIK_H) == true)
	{
		m_posV.y -= 2.0f;
	}
	//�J�����̎��_�̏I���

#endif
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y = -D3DX_PI;
	}

	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y = D3DX_PI;
	}

}

//=============================================================================
// �J�����̐ݒ菈��
//=============================================================================
void CCamera::SetCamera(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();
#if 0
	//�r���[�{�[�g
	pDevice->SetViewport(&m_viewport);
#endif

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

#if 1
	//�v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),	//��p(�c����������)
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,		//��O
		1000.0f);	//��
#endif

#if 0
					//�v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&g_Camera.mtxProjection,
		D3DXToRadian(45.0f),	//��p(�c����������)
		(float)g_Camera.viewport.Width / (float)g_Camera.viewport.Height,
		10.0f,		//��O
		1000.0f);	//��
#endif

					//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}