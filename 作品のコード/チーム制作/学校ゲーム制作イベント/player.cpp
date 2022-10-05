//=============================================================================
//
// プレイヤーの処理 [player.cpp]
// Author : 佐藤瞭平
// Author : 青木睦浩
//
//=============================================================================
#include"player.h"
#include"renderer.h"
#include"manager.h"
#include"input.h"
#include"game.h"
#include"fade.h"
#include"bullet.h"

//=============================================================================
// 静的メンバ関数の宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;
CBullet* CPlayer::m_pBullet = NULL;
D3DXVECTOR3 CPlayer::m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
D3DXVECTOR2 CPlayer::m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
D3DXVECTOR3 CPlayer::m_posold = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
D3DXVECTOR3 CPlayer::m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
bool CPlayer::m_bUse = true;
//=============================================================================
// プレイヤーのコンストラクタ
//=============================================================================
CPlayer::CPlayer(int nPriority) : CScene2D(PRIORITY_PLAYER)
{
	m_nTimer = 0;
	m_nCoolTime = 50;		
	m_bBullet = false;	
	m_nCoolTime = 0;
}


//=============================================================================
// プレイヤーのデストラクタ
//=============================================================================
CPlayer::~CPlayer()
{

}

//=============================================================================
// プレイヤーの生成処理
//=============================================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	CPlayer* pPlayer;

	pPlayer = new CPlayer;

	if (pPlayer != NULL)
	{
		pPlayer->Init(pos, Size);		
		pPlayer->Bindtexture(16);
	}
	return pPlayer;
}

//=============================================================================
// プレイヤーの初期化処理
//=============================================================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{	
	m_posold = pos;
	m_pos = pos;
	m_size = Size;
	m_bUse = true;
	CScene2D::Init(pos, Size);	

	return S_OK;
}	// プレイヤーの初期化処理終了



//=============================================================================
// プレイヤーの終了処理
//=============================================================================
void CPlayer::Uninit(void)
{
	// 解放
	Release();

}// プレイヤーの終了処理終了


 //=============================================================================
 // プレイヤーの更新処理
 //=============================================================================
void CPlayer::Update(void)
{	
	if (!m_bUse)
	{
		Uninit();
		return;
	}
	CInputKeyboard *pInputKeyboard = NULL;

	pInputKeyboard = CManager::GetInputKeyboard();

	m_nTimer++;
	m_nCoolTime++;

	if (m_nCoolTime >= 100)
	{
		if (pInputKeyboard->GetTrigger(DIK_SPACE))
		{
			m_pBullet = CBullet::Create(m_pos, D3DXVECTOR3(0.0f, -30.0f, 0.0f), D3DXVECTOR2(20.0f, 20.0f), true);
			m_nCoolTime = 0;
		}
	}

	if (m_pos.x + m_size.x >= SCREEN_WIDTH)
	{
		m_pos.x = SCREEN_WIDTH - m_size.x;
	}
	else if (m_pos.x <= m_size.x)
	{
		m_pos.x = m_size.x;
	}

	if (m_pos.y + m_size.y >= SCREEN_HEIGHT)
	{
		m_pos.y = SCREEN_HEIGHT - m_size.y;		
	}
	else if (m_pos.y <= m_size.y)
	{
		m_pos.y = m_size.y;		
	}

	SetPosition(m_pos);
	SetSize(m_size);
	CScene2D::Update();


}// プレイヤーの更新処理終了

//=============================================================================
// プレイヤーの描画処理
//=============================================================================
void CPlayer::Draw(void)
{
	CScene2D::Draw();

}	// プレイヤーの描画処理終了