//=============================================================================
//
// 弾の処理 [bullet.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include"beam.h"
#include"manager.h"
#include"renderer.h"

// 静的メンバ変数の宣言
LPDIRECT3DTEXTURE9 CBeam::m_pTexture = NULL;

//=============================================================================
// 弾のコンストラクタ
//=============================================================================
CBeam::CBeam(int nPriority) : CBullet(nPriority)
{
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Size = D3DXVECTOR2(0.0f, 0.0f);
	m_Timer = 0;
}

//=============================================================================
// 弾のデストラクタ
//=============================================================================
CBeam::~CBeam()
{

}

//=============================================================================
// 弾の生成処理
//=============================================================================
CBeam *CBeam::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size)
{
	CBeam* pBeam;

	pBeam = new CBeam;

	if (pBeam != NULL)
	{
		pBeam->Init(pos, move, Size);
		pBeam->BindTextuer(m_pTexture);
		pBeam->SetType(CScene::OBJTYPE_PLAYERBULLET);
	}
	return pBeam;
}

//=============================================================================
// テクスチャの読み込み
//=============================================================================
HRESULT CBeam::Load(void)
{
	CManager *pManager = NULL;

	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();


	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/beam001.png",
		&m_pTexture);

	return S_OK;
}

//=============================================================================
// テクスチャの破棄
//=============================================================================
void CBeam::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// 弾の初期化処理
//=============================================================================
HRESULT CBeam::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size)
{
	CBullet::Init(pos, move, Size);
	m_Pos = pos;
	m_Move = move;
	m_Size = Size;
	m_Timer = 0;
	return S_OK;
}

//=============================================================================
// 弾の終了関数
//=============================================================================
void CBeam::Uninit(void)
{
	CBullet::Uninit();
}

//=============================================================================
// 弾の更新関数
//=============================================================================
void CBeam::Update(void)
{
	m_Pos.x += m_Move.x;

	D3DXVECTOR3 pos = m_Pos;

	CScene2D::Update();

	SetPosition(m_Pos);

	// 画面外処理
	if (m_Pos.x >= SCREEN_WIDTH - (m_Size.x / 2))
	{
		Uninit();
		return;
	}
	else if (m_Pos.x <= (m_Size.x / 2))
	{
		Uninit();
		return;
	}
	if (m_Pos.y >= SCREEN_HEIGHT - (m_Size.y / 2))
	{
		Uninit();
		return;
	}
	else if (m_Pos.y <= (m_Size.y / 2))
	{
		Uninit();
		return;
	}
}

//=============================================================================
// 弾の描画関数
//=============================================================================
void CBeam::Draw(void)
{
	CBullet::Draw();
}
