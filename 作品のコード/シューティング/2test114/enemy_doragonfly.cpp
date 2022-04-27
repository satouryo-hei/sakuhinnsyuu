//=============================================================================
//
// 敵(トンボ)の処理 [enemy_doragonfly.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include"enemy_doragonfly.h"
#include"renderer.h"
#include"manager.h"
#include"player.h"
#include"game.h"

// 静的メンバ変数の宣言
LPDIRECT3DTEXTURE9 CEnemy_Doragonfly::m_pTexture = NULL;

//=============================================================================
// 敵(トンボ)のコンストラクタ
//=============================================================================
CEnemy_Doragonfly::CEnemy_Doragonfly(int nPriority) : CEnemy(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Size = D3DXVECTOR2(0.0f, 0.0f);
	m_Playerpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fRange = 0.0f;
	m_bUse = false;
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
	m_fSizeAnimU = 0.0f;
	m_fSizeMinV = 0.0f;
	m_fSizeMaxV = 0.5f;
	m_bAimPlayer = false;
}


//=============================================================================
// 敵(トンボ)のデストラクタ
//=============================================================================
CEnemy_Doragonfly::~CEnemy_Doragonfly()
{

}

//=============================================================================
// 敵(トンボ)の生成処理
//=============================================================================
CEnemy_Doragonfly *CEnemy_Doragonfly::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size)
{
	CEnemy_Doragonfly* pEnemy_Doragonfly;

	pEnemy_Doragonfly = new CEnemy_Doragonfly;

	if (pEnemy_Doragonfly != NULL)
	{
		pEnemy_Doragonfly->Init(pos, move, Size);
		pEnemy_Doragonfly->BindTextuer(m_pTexture);
		pEnemy_Doragonfly->SetType(CScene::OBJTYPE_ENEMY);
	}
	return pEnemy_Doragonfly;
}

//=============================================================================
// テクスチャの読み込み
//=============================================================================
HRESULT CEnemy_Doragonfly::Load(void)
{
	CManager *pManager = NULL;

	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/doragonflyAnime001.png",
		&m_pTexture);

	return S_OK;
}

//=============================================================================
// テクスチャの破棄
//=============================================================================
void CEnemy_Doragonfly::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// 敵(トンボ)の初期化処理
//=============================================================================
HRESULT CEnemy_Doragonfly::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size)
{
	CScene2D::Init(pos, move, Size);

	m_pos = pos;
	m_Move = move;
	m_Size = Size;

	return S_OK;
}	// プレイヤーの初期化処理終了



//=============================================================================
// 敵(トンボ)の終了処理
//=============================================================================
void CEnemy_Doragonfly::Uninit(void)
{
	CEnemy::Uninit();

}// プレイヤーの終了処理終了


//=============================================================================
// 敵(トンボ)の更新処理
//=============================================================================
void CEnemy_Doragonfly::Update(void)
{
	if (m_pos.x - (m_Size.x / 2) > 0 &&
		m_pos.x < SCREEN_WIDTH &&
		m_pos.y > 0 &&
		m_pos.y < SCREEN_WIDTH)
	{
		m_bUse = true;
	}
	else
	{
		m_bUse = false;
	}

	m_fSizeAnimU = 0.25f;

	m_Playerpos = CGame::GetPlayer()->GetPosition();

	// トンボの現在の位置が1100を超えたら
	if (m_pos.x > 1100)
	{
		m_fSizeMaxV = 1.0f;
		m_fSizeMinV = m_fSizeMaxV / 2;

		m_bAimPlayer = true;

		// プレイヤーとトンボの斜辺の距離を測るA＝√（三平方より(c2乗 = a2乗+b2乗)）
		m_fRange = sqrtf(powf((m_Playerpos.x - m_pos.x), 2.0f) + powf((m_Playerpos.y - m_pos.y), 2.0f));
		if (m_fRange != NULL)
		{
			m_Move.x = (m_Playerpos.x - m_pos.x) / m_fRange * 10;
			m_Move.y = (m_Playerpos.y - m_pos.y) / m_fRange * 10;
		}
		else
		{
			m_Move.y = 1;
		}
	}

	switch (m_bAimPlayer)
	{
	case TRUE:
		SetAnimesion(m_nPatternAnim, m_fSizeAnimU, m_fSizeMinV, m_fSizeMaxV);
		break;

	case FALSE:
		SetAnimesion(m_nPatternAnim, m_fSizeAnimU, m_fSizeMinV, m_fSizeMaxV);
		break;
	}

	m_pos += m_Move;

	if (m_bUse = false)
	{
		// 画面外の当たり判定
		if (m_pos.x + (m_Size.x / 2) <= 0)
		{
			Uninit();
			return;
		}

		if (m_pos.x - (m_Size.x / 2) >= SCREEN_WIDTH)
		{
			Uninit();
			return;
		}

		if (m_pos.y + (m_Size.y / 2) <= 0)
		{
			Uninit();
			return;
		}

		if (m_pos.y - (m_Size.y / 2) >= SCREEN_HEIGHT)
		{
			Uninit();
			return;
		}
	}
	SetPosition(m_pos);

	SetSize(m_Size);

	CScene2D::Update();


}// プレイヤーのの更新処理終了



 //=============================================================================
 // 敵(トンボ)の描画処理
 //=============================================================================
void CEnemy_Doragonfly::Draw(void)
{
	CEnemy::Draw();

}	// プレイヤーの描画処理終了


//=============================================================================
// 敵のアニメーション設定処理
//=============================================================================
void CEnemy_Doragonfly::SetAnimesion(int nPatternAnim, float fSizeAnimU, float fSizeMinV, float fSizeMaxV)
{
	m_nCounterAnim++;

	if (m_nCounterAnim % 4 == 0)
	{
		m_nPatternAnim++;

		CScene2D::SetTexAnime(nPatternAnim, fSizeAnimU, fSizeMinV, fSizeMaxV);

		if (m_nPatternAnim >= 4)
		{
			m_nPatternAnim = 0;
			return;
		}
	}
}