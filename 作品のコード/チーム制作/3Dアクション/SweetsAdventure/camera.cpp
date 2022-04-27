//----------------------------------
//ポリゴンの処理
//-----------------------------------
#include "camera.h"
#include "input.h"
#include "Renderer.h"
#include "manager.h"
#include "keyboard.h"
#include "player.h"
#include "mouse.h"
#include "XInput.h"
//=============================================================================
// コンストラクタ
//=============================================================================
CCamera::CCamera()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CCamera::~CCamera()
{

}
//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
HRESULT CCamera::Init(void)
{
	m_fLong = 300.0f;
	m_posV = D3DXVECTOR3(0.0f, 200.0f, - m_fLong);
	m_posR = D3DXVECTOR3(0.0f, 40.0f,0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	return S_OK;
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CCamera::Uninit(void)
{
}

//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CCamera::Update(void)
{
	CMouse *pMouse = CManager::GetMouse();
	CXInput *pGamePad = CManager::GetXInput();

	CInputKeyBoard *pKey = CManager::GetInputKeyboard();
	//	//注視点の回転
	//if (pKey->GetPress(DIK_E) == true)
	//{
	//	m_rot.y += 0.01f;
	//	if (m_rot.y > D3DX_PI)
	//	{
	//		m_rot.y -= D3DX_PI;
	//	}

	//	m_posR.x = m_posV.x + sinf(m_rot.y)* m_fLong;
	//	m_posR.z = m_posV.z + cosf(m_rot.y)* m_fLong;
	//}
	//if (pKey->GetPress(DIK_Q) == true)
	//{
	//	m_rot.y += -0.01f;
	//	if (m_rot.y < -D3DX_PI)
	//	{
	//		m_rot.y = D3DX_PI;
	//	}

	//	m_posR.x = m_posV.x + sinf(m_rot.y)* m_fLong;
	//	m_posR.z = m_posV.z + cosf(m_rot.y)* m_fLong;
	//}
	//if (pKey->GetPress(DIK_R) == true)
	//{

	//	m_posR.y += 2.0f;

	//}
	//if (pKey->GetPress(DIK_F) == true)
	//{
	//	m_posR.y += -2.0f;
	//}

	//視点の回転
	if (pGamePad->GetGamePad()->m_state.Gamepad.sThumbRX >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
	{
		m_rot.y += 0.04f;
		if (m_rot.y > D3DX_PI)
		{
			m_rot.y = -D3DX_PI;
		}
		m_posV.x = m_posR.x - sinf(m_rot.y)* m_fLong;
		m_posV.z = m_posR.z - cosf(m_rot.y)* m_fLong;
	}
	
	if (pGamePad->GetGamePad()->m_state.Gamepad.sThumbRX <= -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
	{
		m_rot.y += -0.04f;
		if (m_rot.y < -D3DX_PI)
		{
			m_rot.y = D3DX_PI;
		}


		m_posV.x = m_posR.x - sinf(m_rot.y)* m_fLong;
		m_posV.z = m_posR.z - cosf(m_rot.y)* m_fLong;
	}
	if (pGamePad->GetGamePad()->m_state.Gamepad.sThumbRY >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
	{
		m_posV.y += -3.0f;

	}
	if (pGamePad->GetGamePad()->m_state.Gamepad.sThumbRY <= -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
	{
		m_posV.y += 3.0f;

	}
	//左クリック
	if (pMouse->GetTrigger(CMouse::MOUSE_LEFT) == true)
	{
		//クリックした位置のマウス座標を取得
		GetCursorPos(&m_Cursol);

	}
	if (pMouse->GetPress(CMouse::MOUSE_LEFT) == true)
	{

		SetCursorPos(m_Cursol.x, m_Cursol.y);

		m_rot.y += pMouse->GetMousePos().lX*0.01f;
		if (m_rot.y > D3DX_PI)
		{
			m_rot.y = -D3DX_PI;
		}
		m_posV.y += pMouse->GetMousePos().lY*-0.1f;
		m_posV.x = m_posR.x - sinf(m_rot.y)* m_fLong;
		m_posV.z = m_posR.z - cosf(m_rot.y)* m_fLong;
	}
	if (pMouse->GetTrigger(CMouse::MOUSE_RIGHT) == true)
	{
		//クリックした位置のマウス座標を取得
		GetCursorPos(&m_Cursol);

	}

	else if (pMouse->GetPress(CMouse::MOUSE_RIGHT) == true)
	{

		SetCursorPos(m_Cursol.x, m_Cursol.y);

		m_rot.y += pMouse->GetMousePos().lX*0.001f;
		if (m_rot.y > D3DX_PI)
		{
			m_rot.y = -D3DX_PI;
		}
		m_posR.y += pMouse->GetMousePos().lY*-0.1f;
		m_posR.x = m_posV.x + sinf(m_rot.y)* m_fLong;
		m_posR.z = m_posV.z + cosf(m_rot.y)* m_fLong;
	}
	if (pMouse->GetTrigger(CMouse::MOUSE_WHEEL) == true)
	{
		//クリックした位置のマウス座標を取得
		GetCursorPos(&m_Cursol);
	}
	else if (pMouse->GetPress(CMouse::MOUSE_WHEEL) == true)
	{
		SetCursorPos(m_Cursol.x, m_Cursol.y);
		m_rot.x += pMouse->GetMousePos().lX*0.1f;

		m_posR.y += pMouse->GetMousePos().lY*-0.1f;
		m_posV.y += pMouse->GetMousePos().lY*-0.1f;
		m_posR.x += cosf(m_rot.y)*(m_fLong*pMouse->GetMousePos().lX*0.001f);
		m_posR.z -= sinf(m_rot.y)*(m_fLong*pMouse->GetMousePos().lX*0.001f);
		m_posV.x += cosf(m_rot.y)*(m_fLong*pMouse->GetMousePos().lX*0.001f);
		m_posV.z -= sinf(m_rot.y)*(m_fLong*pMouse->GetMousePos().lX*0.001f);

	}

	////近寄る
	//if (pKey->GetPress(DIK_O) == true)
	//{
	//	m_fLong += 2.0f;
	//	m_posV.x = m_posR.x - sinf(m_rot.y)* m_fLong;
	//	m_posV.z = m_posR.z - cosf(m_rot.y)* m_fLong;
	//	if (m_fLong < 0.0f)
	//	{
	//		m_fLong = m_fLong;
	//	}

	//}
	////離れる
	//if (pKey->GetPress(DIK_L) == true)
	//{
	//	m_fLong += -2.0f;
	//	m_posV.x = m_posR.x - sinf(m_rot.y)* m_fLong;
	//	m_posV.z = m_posR.z - cosf(m_rot.y)* m_fLong;
	//	if (m_fLong < 4.0f)
	//	{
	//		m_fLong = 4.0f;
	//	}


	//}

}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CCamera::Draw(void)
{

}
//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CCamera::SetPlayerCamera(CPlayer *pPlayer)
{
	m_posR = D3DXVECTOR3(pPlayer->GetPos().x, m_posR.y, pPlayer->GetPos().z);
	m_posV.x = pPlayer->GetPos().x- sinf(m_rot.y)*m_fLong;
	m_posV.z = pPlayer->GetPos().z - cosf(m_rot.y)*m_fLong;

}
//設定
void CCamera::SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスのポインタ
	pDevice = CManager::GetRenderer()->GetDevice();

	//ビューポートの設定
	//pDevice->SetViewport(&m_viewport);
	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);
	//プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(70.0f),//カメラの画角
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,//画面比率!!!ビューポートを使うときビューポートの幅高さを使う
		10.0f,//手前の描画制限
		10000.0f);//奥の描画制限
				  //プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);
	//ビューマトリックスを作成
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU);
	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}
