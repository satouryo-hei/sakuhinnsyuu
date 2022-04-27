//=============================================================================
//
// プレイヤーの処理 [player.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include"player.h"
#include"renderer.h"
#include"manager.h"
#include"input.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = 0;

//=============================================================================
// コンストラクタ
//=============================================================================
CPlayer::CPlayer(PRIORITY Priority) :CScene2D(Priority), m_fSpeedMax(2.1f)
{
	int m_Life = 0;
	float m_fSpeed = 0;

	m_bUse = true;
}


//=============================================================================
//　デストラクタ
//=============================================================================
CPlayer::~CPlayer()
{

}

//=============================================================================
// ポリゴンの生成処理
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
// テクスチャの読み込み
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
// テクスチャの破棄
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
// ポリゴンの初期化処理
//=============================================================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 Size)
{
	int m_Life = 2;
	float m_fSpeed = 0;

	CScene2D::Init(pos, Size);

	return S_OK;
}	// ポリゴンの初期化処理終了



//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CPlayer::Uninit(void)
{	
	CScene2D::Uninit();

}// ポリゴンの終了処理終了


 //=============================================================================
 // ポリゴンの更新処理
 //=============================================================================
void CPlayer::Update(void)
{
	CInputKeyboard *pInputKeyboard;

	pInputKeyboard = CManager::GetInputKeyboard();

	D3DXVECTOR3 pos = GetPosition();

	//任意で押されたかどうか
	if (pInputKeyboard->GetPress(DIK_A) == true)//左を押した
	{
		if (pInputKeyboard->GetPress(DIK_W) == true)//上に移動
		{
			pos.x += sinf(D3DX_PI*-0.75f)*m_fSpeedMax;
			pos.y += cosf(D3DX_PI*-0.75f)*m_fSpeedMax;
		}

		else if (pInputKeyboard->GetPress(DIK_S) == true)//下に移動
		{
			pos.x += sinf(D3DX_PI*-0.25f)*m_fSpeedMax;
			pos.y += cosf(D3DX_PI*-0.25f)*m_fSpeedMax;
		}

		else
		{
			pos.x -= m_fSpeedMax;
		}
	}

	if (pInputKeyboard->GetPress(DIK_D) == true)//右を押した
	{
		if (pInputKeyboard->GetPress(DIK_W) == true)//上に移動
		{
			pos.x += sinf(D3DX_PI*0.75f)*m_fSpeedMax;
			pos.y += cosf(D3DX_PI*0.75f)*m_fSpeedMax;
		}

		else if (pInputKeyboard->GetPress(DIK_S) == true)//下に移動
		{
			pos.x += sinf(D3DX_PI*0.25f)*m_fSpeedMax;
			pos.y += cosf(D3DX_PI*0.25f)*m_fSpeedMax;
		}

		else
		{
			pos.x += m_fSpeedMax;
		}
	}

	if (pInputKeyboard->GetPress(DIK_W) == true)//上に移動
	{
		pos.y -= m_fSpeedMax;
	}

	if (pInputKeyboard->GetPress(DIK_S) == true)//下に移動
	{
		pos.y += m_fSpeedMax;
	}

	if (pInputKeyboard->GetTrigger(DIK_SPACE) == true)
	{
		//弾の生成
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
}// ポリゴンの更新処理終了



 //=============================================================================
 // ポリゴンの描画処理
 //=============================================================================
void CPlayer::Draw(void)
{
	CScene2D::Draw();

}	// ポリゴンの描画処理終了

