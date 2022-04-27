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
#include"bullet.h"
#include"sound.h"
#include"score.h"
#include"enemy.h"
#include"explosion.h"
#include"game.h"
#include"life.h"
#include"fade.h"
#include"ranking.h"

// 静的メンバ変数の宣言
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;

//=============================================================================
// プレイヤーのコンストラクタ
//=============================================================================
CPlayer::CPlayer(int nPriority) : CScene2D(nPriority), m_fSpeedMax(1.0f)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
	m_nTimer = 0;
	m_Playertype = PLAYER_NOMAL;
	m_bDeath = false;
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
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size)
{
	CPlayer* pPlayer;

	pPlayer = new CPlayer;

	if (pPlayer != NULL)
	{
		pPlayer->Init(pos, move, Size);
		pPlayer->BindTextuer(m_pTexture);
	}
	return pPlayer;
}

//=============================================================================
// テクスチャの読み込み
//=============================================================================
HRESULT CPlayer::Load(void)
{
	CManager *pManager = NULL;

	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/PlayerAnim002.png",
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
// プレイヤーの初期化処理
//=============================================================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size)
{
	int m_Life = 2;
	float m_fSpeed = 0;

	CScene2D::Init(pos, move, Size);

	m_move = move;

	return S_OK;
}	// プレイヤーの初期化処理終了



//=============================================================================
// プレイヤーの終了処理
//=============================================================================
void CPlayer::Uninit(void)
{	
	CScene2D::Uninit();

}// プレイヤーの終了処理終了


 //=============================================================================
 // プレイヤーの更新処理
 //=============================================================================
void CPlayer::Update(void)
{
	CInputKeyboard *pInputKeyboard = NULL;

	pInputKeyboard = CManager::GetInputKeyboard();

	CLife * pLife = NULL;

	pLife = CGame::GetLife();

	CManager *pManager = NULL;

	D3DXVECTOR3 pos = GetPosition();

	D3DXVECTOR2 size = GetSize();

	m_nCounterAnim++;

	float fSizeanim = 0.125f;

	if (m_nCounterAnim % 4 == 0)
	{
		m_nPatternAnim++;

		CScene2D::SetTexAnime(m_nPatternAnim, fSizeanim);

		if (m_nPatternAnim >= 8)
		{
			return;
		}
	}

	m_nTimer++;	

	switch (m_Playertype)
	{
	case PLAYER_NOMAL:
		//任意で押されたかどうか
		if (pInputKeyboard->GetPress(DIK_A) == true && pos.x - (size.x / 1.5) >= 0)//左を押した
		{
			if (pInputKeyboard->GetPress(DIK_W) == true && pos.y - (size.y / 1.5) >= 0)//上に移動
			{
				pos.y += cosf(D3DX_PI*0.75f)*(m_move.y*0.9f);
				pos.x -= sinf(D3DX_PI*0.75f)*(m_move.x*0.9f);
			}
			else if (pInputKeyboard->GetPress(DIK_S) == true && pos.y + (size.y / 1.5) <= SCREEN_HEIGHT)//下に移動
			{
				pos.x -= sinf(D3DX_PI*0.25f)*(m_move.x*0.9f);
				pos.y += cosf(D3DX_PI*0.25f)*(m_move.y*0.9f);
			}
			else
			{
				pos.x -= m_move.x;
			}
		}
		else if (pInputKeyboard->GetPress(DIK_D) == true && pos.x + (size.x / 1.5) <= SCREEN_WIDTH)//右を押した
		{
			if (pInputKeyboard->GetPress(DIK_W) == true && pos.y - (size.y / 1.5) >= 0)//上に移動
			{
				pos.x += sinf(D3DX_PI*0.75f)*(m_move.x*0.9f);
				pos.y += cosf(D3DX_PI*0.75f)*(m_move.y*0.9f);
			}
			else if (pInputKeyboard->GetPress(DIK_S) == true && pos.y + (size.y / 1.5) <= SCREEN_HEIGHT)//下に移動
			{
				pos.x += sinf(D3DX_PI*0.25f)*(m_move.x*0.9f);
				pos.y += cosf(D3DX_PI*0.25f)*(m_move.y*0.9f);
			}
			else
			{
				pos.x += m_move.y;
			}
		}
		else if (pInputKeyboard->GetPress(DIK_W) == true && pos.y - (size.y / 1.5) >= 0)//上に移動
		{
			pos.y -= m_move.y;
		}
		else if (pInputKeyboard->GetPress(DIK_S) == true && pos.y + (size.y / 1.5) <= SCREEN_HEIGHT)//下に移動
		{
			pos.y += m_move.y;
		}


		if (pInputKeyboard->GetPress(DIK_SPACE) == true)
		{
			if (m_nTimer % 20 == 0)
			{
				//弾の生成
				CBullet::Create(pos, D3DXVECTOR3(6.0f, 0.0f, 0.0f), D3DXVECTOR2(20.0f, 20.0f), CScene::OBJTYPE_PLAYERBULLET);
				m_nTimer = 0;
				pManager->GetSound()->Play(CSound::SOUND_LABEL_SHOT000);

			}
		}		

		if (!m_bDeath)
		{
			//=============================================================================
			// 自機と敵の当たり判定
			//=============================================================================
			for (int nPriority = 0; nPriority < PRIORITY_MAX; nPriority++)
			{
				for (int nCntScene = 0; nCntScene < MAX_DATA; nCntScene++)
				{
					CScene * pScene = NULL;

					pScene = CScene::GetScene(nPriority, nCntScene);

					if (pScene != NULL)
					{
						CScene::OBJTYPE objType;
						objType = pScene->GetOnjType();

						if (objType == CScene::OBJTYPE_ENEMY)
						{
							CEnemy *pEnemy = (CEnemy*)pScene;

							if (pos.x + (size.x / 2) >= pEnemy->GetPosition().x - pEnemy->GetSize().x &&
								pos.x - (size.x / 2) <= pEnemy->GetPosition().x + pEnemy->GetSize().x &&
								pos.y + (size.y / 2) >= pEnemy->GetPosition().y - pEnemy->GetSize().y &&
								pos.y - (size.y / 2) <= pEnemy->GetPosition().y + pEnemy->GetSize().y)
							{
								//爆発の生成
								CExplosion::Create(pos, D3DXVECTOR2(100.0f, 100.0f));
								CExplosion::Create(pEnemy->GetPosition(), D3DXVECTOR2(100.0f, 100.0f));
								pLife->AddLife(1);
								if (pLife->GetLife() == 0)
								{
									CManager *pManager = NULL;
									pManager->GetSound()->Stop(CSound::SOUND_LABEL_SUMMER_EXPEDITION);

									CFade::SetFade(CManager::MODE_RESULT);
								}
								else
								{
									m_Playertype = PLAYER_DEATH;
								}
								pEnemy->Uninit();
								pManager->GetSound()->Play(CSound::SOUND_LABEL_bom000);
								return;
							}
						}

					}
				}
			}
		}
		else if (m_bDeath)
		{			
			if (m_nTimer % 20 == 0)
			{
				m_bDeath = false;
			}
		}
		break;

	case PLAYER_DEATH:

		if (m_nTimer % 5 == 0)
		{
			pos = D3DXVECTOR3(10.0f+size.x, 320.0f, 0.0f);

			m_Playertype = PLAYER_RESTARE;
		}
		m_bDeath = true;
		break;

	case PLAYER_RESTARE:
		if (pos.x >= 150)
		{
			m_Playertype = PLAYER_NOMAL;
		}
		else
		{
			pos.x += 5;
		}
		break;

		m_nTimer = 0;

		default:
			break;
	}

	SetPosition(pos);

	SetSize(size);

	CScene2D::Update();

}// プレイヤーのの更新処理終了



 //=============================================================================
 // プレイヤーの描画処理
 //=============================================================================
void CPlayer::Draw(void)
{
	CScene2D::Draw();

}	// プレイヤーの描画処理終了

