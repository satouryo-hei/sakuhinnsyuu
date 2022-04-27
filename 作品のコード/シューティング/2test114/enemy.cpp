//=============================================================================
//
// 敵の処理 [enemy.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include"enemy.h"
#include"renderer.h"
#include"manager.h"

// 静的メンバ変数の宣言
LPDIRECT3DTEXTURE9 CEnemy::m_pTexture = NULL;

//=============================================================================
// 敵のコンストラクタ
//=============================================================================
CEnemy::CEnemy(int nPriority) : CScene2D(nPriority)
{
	m_Move = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Size = D3DXVECTOR2(0.0f,0.0f);
}


//=============================================================================
// 敵のデストラクタ
//=============================================================================
CEnemy::~CEnemy()
{

}

//=============================================================================
// 敵の生成処理
//=============================================================================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size)
{
	CEnemy* pEnemy;

	pEnemy = new CEnemy;

	if (pEnemy != NULL)
	{
		pEnemy->Init(pos, move, Size);
		pEnemy->BindTextuer(m_pTexture);
		pEnemy->SetType(CScene::OBJTYPE_ENEMY);
	}
	return pEnemy;
}

//=============================================================================
// テクスチャの読み込み
//=============================================================================
HRESULT CEnemy::Load(void)
{
	CManager *pManager = NULL;

	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/komoko000.png",
		&m_pTexture);

	return S_OK;
}

//=============================================================================
// テクスチャの破棄
//=============================================================================
void CEnemy::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// 敵の初期化処理
//=============================================================================
HRESULT CEnemy::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size)
{
	int m_Life = 2;
	float m_fSpeed = 0;

	CScene2D::Init(pos, move, Size);

	m_Move = move;

	return S_OK;
}	// プレイヤーの初期化処理終了



//=============================================================================
// 敵の終了処理
//=============================================================================
void CEnemy::Uninit(void)
{
	CScene2D::Uninit();

}// プレイヤーの終了処理終了


//=============================================================================
// 敵の更新処理
//=============================================================================
void CEnemy::Update(void)
{	

	D3DXVECTOR3 pos = GetPosition();

	D3DXVECTOR2 size = GetSize();

	pos.x -= m_Move.x;

	CScene2D::Update();

	SetPosition(pos);
	SetSize(size);

	// 画面外の当たり判定
	if (pos.x + (size.x / 2) <= 0)
	{
		Uninit();
		return;
	}
	if (pos.x - (size.x / 2) >= SCREEN_WIDTH)
	{
		Uninit();
		return;
	}
	if (pos.y + (size.y / 2) <= 0)
	{
		Uninit();
		return;
	}
	if (pos.y - (size.y / 2) >= SCREEN_HEIGHT)
	{
		Uninit();
		return;
	}


}// プレイヤーのの更新処理終了



//=============================================================================
// 敵の描画処理
//=============================================================================
void CEnemy::Draw(void)
{
	CScene2D::Draw();

}	// プレイヤーの描画処理終了