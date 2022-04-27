//=============================================================================
//
// プレイヤーの処理 [player.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include"press_next.h"
#include"renderer.h"
#include"manager.h"
#include"input.h"

// 静的メンバ変数の宣言
LPDIRECT3DTEXTURE9 CPress_Next::m_pTexture = NULL;

//=============================================================================
// プレイヤーのコンストラクタ
//=============================================================================
CPress_Next::CPress_Next(int nPriority) : CScene2D(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR2(0.0f, 0.0f);
}


//=============================================================================
// プレイヤーのデストラクタ
//=============================================================================
CPress_Next::~CPress_Next()
{

}

//=============================================================================
// プレイヤーの生成処理
//=============================================================================
CPress_Next *CPress_Next::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size , float fHeight)
{
	CPress_Next* pPlayer;

	pPlayer = new CPress_Next;

	if (pPlayer != NULL)
	{
		pPlayer->Init(pos, move, Size);
		pPlayer->BindTextuer(m_pTexture);
		pPlayer->m_fHeight = fHeight;
	}
	return pPlayer;
}

//=============================================================================
// テクスチャの読み込み
//=============================================================================
HRESULT CPress_Next::Load(void)
{
	CManager *pManager = NULL;

	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/2DSTART.png",
		&m_pTexture);

	return S_OK;
}

//=============================================================================
// テクスチャの破棄
//=============================================================================
void CPress_Next::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// プレイヤーの初期化処理
//=============================================================================
HRESULT CPress_Next::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size)
{
	CScene2D::Init(pos, move, Size);

	m_pos = pos;
	m_move = move;
	m_size = Size;

	return S_OK;
}	// プレイヤーの初期化処理終了

//=============================================================================
// プレイヤーの終了処理
//=============================================================================
void CPress_Next::Uninit(void)
{
	CScene2D::Uninit();

}// プレイヤーの終了処理終了

 //=============================================================================
 // プレイヤーの更新処理
 //=============================================================================
void CPress_Next::Update(void)
{

	if (m_pos.y > m_fHeight)
	{
		m_pos -= m_move;		
		CScene2D::SetPosition(m_pos);
	}
	CScene2D::Update();

}// プレイヤーのの更新処理終了

 //=============================================================================
 // プレイヤーの描画処理
 //=============================================================================
void CPress_Next::Draw(void)
{
	CScene2D::Draw();

}	// プレイヤーの描画処理終了