//=============================================================================
//
// カメラ処理 [camera.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include"Camera.h"
#include"input.h"
#include"manager.h"
#include"renderer.h"

//=============================================================================
// ライトのコンストラクタ
//=============================================================================
CCamera::CCamera()
{
	memset(&m_mtxProjection, NULL, sizeof(m_mtxProjection));
	memset(&m_mtxView, NULL, sizeof(m_mtxView));
	memset(&m_viewport, NULL, sizeof(m_viewport));
	m_posV = D3DXVECTOR3(0.0f, 200.0f, -100.0f);
	m_posVDest = D3DXVECTOR3(0.0f, 100.0f, -100.0f);
	m_posR = D3DXVECTOR3(0.0f,
		200.0f, //0になるにつれ真っすぐになる
		0.0f);
	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Range = m_posV.z*(-1);
}


//=============================================================================
// ライトのデストラクタ
//=============================================================================
CCamera::~CCamera()
{

}

//=============================================================================
// カメラの初期化
//=============================================================================
HRESULT CCamera::Init(void)
{
#if 0
	//_初期の位置
	m_posV = D3DXVECTOR3(0.0f, 40.0f, -10.0f);
	m_posR = D3DXVECTOR3(0.0f,
		-30.0f, //0になるにつれまっすくになる
		10.0f);
#endif
	//m_posV = D3DXVECTOR3(0.0f, 100.0f, -100.0f);
	//m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//多分3.14～--3.14まで

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
// カメラの終了処理
//=============================================================================
void CCamera::Uninit(void)
{
}

//=============================================================================
// カメラの更新処理
//=============================================================================
void CCamera::Update(void)
{
	CInputKeyboard *pInputKeyboard = NULL;
	pInputKeyboard = CManager::GetInputKeyboard();

	//m_Range = m_posV.z;

#if 0
	//注視点の上下
	if (pInputKeyboard->GetPress(DIK_T))//左を押した
	{
		m_posR.y += 2.0f;
	}
	if (pInputKeyboard->GetPress(DIK_G))
	{
		m_posR.y -= 2.0f;
	}
	//注視点の上下の終わり

	//視点の上下
	if (pInputKeyboard->GetPress(DIK_I))
	{
		m_posV.y += 2.0f;
	}
	if (pInputKeyboard->GetPress(DIK_K))
	{
		m_posV.y -= 2.0f;
	}
	//視点の上下の終わり

#endif

#if 1
	//カメラの移動
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
	//カメラの移動の終わり

	////カメラの注視点
	//if (pInputKeyboard->GetPress(DIK_R))
	//{
	//	m_rot.y += 0.01f;
	//	m_posR.x = m_posV.x + sinf(m_rot.y) * m_Range;//現在の注視点(x)＝現在の視点(x)+sinf(カメラの向き(y))*注視点までの距離
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
	//注視点の終わり

	//カメラの視点
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
	//カメラの視点の終わり

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
// カメラの設定処理
//=============================================================================
void CCamera::SetCamera(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice = NULL;

	pDevice = CManager::GetRenderer()->GetDevice();
#if 0
	//ビューボート
	pDevice->SetViewport(&m_viewport);
#endif

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

#if 1
	//プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),	//画角(縦長か横長か)
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,		//手前
		1000.0f);	//奥
#endif

#if 0
					//プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH(&g_Camera.mtxProjection,
		D3DXToRadian(45.0f),	//画角(縦長か横長か)
		(float)g_Camera.viewport.Width / (float)g_Camera.viewport.Height,
		10.0f,		//手前
		1000.0f);	//奥
#endif

					//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}