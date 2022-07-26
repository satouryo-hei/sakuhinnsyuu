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
#include"game.h"
#include"fade.h"
#include"bullet.h"
#include"homing.h"
#include"block.h"
#include"choose_game.h"
#include"noneblock.h"
#include"pushblock.h"
#include"moveblock.h"
#include"bullet03.h"

//=============================================================================
// 静的メンバ関数の宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;
CBullet* CPlayer::m_pBullet = NULL;
CHoming* CPlayer::m_pHoming[MAX_BULLET] = {};
CBullet03* CPlayer::m_pBullet03 = NULL;
int CPlayer::m_nItem = 0;
D3DXVECTOR3 CPlayer::m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
D3DXVECTOR2 CPlayer::m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
D3DXVECTOR3 CPlayer::m_posold = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
D3DXVECTOR3 CPlayer::m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
bool CPlayer::m_bJump = false;
bool CPlayer::m_bUse = true;
//=============================================================================
// プレイヤーのコンストラクタ
//=============================================================================
CPlayer::CPlayer(int nPriority) : CScene2D(PRIORITY_PLAYER)
{
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
	m_nTimer = 0;
	m_nCoolTime = 50;
	m_Playertype = PLAYER_NOMAL;
	m_bDeath = false;
	m_bBullet = false;	
	m_bMovePush = true;
	m_nBulletType = 0;
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
		pPlayer->Init(pos, Size);
		pPlayer->m_move = move;
		pPlayer->Bindtexture(1);
	}
	return pPlayer;
}

//=============================================================================
// プレイヤーの初期化処理
//=============================================================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	int m_Life = 2;
	float m_fSpeed = 0;
	m_posold = pos;
	m_pos = pos;
	m_size = Size;
	CScene2D::Init(pos, Size);
	const bool bNewGame = CChoose_Game::GetNewGame();
	if (bNewGame)
	{
		m_nItem = 1;
	}
	else if (!bNewGame)
	{
		LoadStatus();
	}

	return S_OK;
}	// プレイヤーの初期化処理終了



	//=============================================================================
	// プレイヤーの終了処理
	//=============================================================================
void CPlayer::Uninit(void)
{
	SaveStatus();
	CScene2D::Uninit();
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
	
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_F1) == true)
	{
		m_nBulletType++;
		if (m_nBulletType >= SHOTTYPE_MAX)
		{
			m_nBulletType = SHOTTYPE_NOMAL;
		}
	}

	m_nTimer++;

	switch (m_Playertype)
	{
	case PLAYER_NOMAL:
		m_posold = m_pos;		
		
		//任意で押されたかどうか
		if (pInputKeyboard->GetPress(DIK_A) == true && m_pos.x - (m_size.x / 2) >= 0)//左を押した
		{				
				m_pos.x -= m_move.x;
				m_bMovePush = false;
		}
		else if (pInputKeyboard->GetPress(DIK_D) == true && m_pos.x + (m_size.x / 2) <= SCREEN_WIDTH)//右を押した
		{							
				m_pos.x += m_move.x;
				m_bMovePush = true;
			
		}
		if (pInputKeyboard->GetTrigger(DIK_W) == true && !m_bJump)//上に移動
		{				
			m_move.y = -20.0f;

			m_bJump = true;
		}		


		if (m_bBullet)
		{
			m_nCoolTime--;
			if (m_nCoolTime < 0)
			{
				m_bBullet = false;
				m_nCoolTime = 0;
			}
		}

		if (pInputKeyboard->GetPress(DIK_SPACE) == true && !m_bBullet)
		{		
			Shot(m_nBulletType,m_bMovePush);
			//pManager->GetSound()->Play(CSound::SOUND_LABEL_SHOT000);		
			m_bBullet = true;
		}

		// 重力
		m_move.y++;
		m_pos.y += m_move.y;	

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
			m_bJump = false;
		}
		else if (m_pos.y <= m_size.y)
		{
			m_pos.y = m_size.y;			
			m_bJump = true;
		}
		break;

	case PLAYER_DEATH:

		if (m_nTimer % 5 == 0)
		{
			m_pos = D3DXVECTOR3(10.0f + m_size.x, 320.0f, 0.0f);

			m_Playertype = PLAYER_RESTARE;
		}
		m_bDeath = true;
		break;

	case PLAYER_RESTARE:
		if (m_pos.x >= 150)
		{
			m_Playertype = PLAYER_NOMAL;
		}
		else
		{
			m_pos.x += 5;
		}
		break;

		m_nTimer = 0;

	default:
		break;
	}

	BlockColision();
	PushColision();
	MoveColision();
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


//=============================================================================
// プレイヤーの弾の処理
//=============================================================================
void CPlayer::Shot(int nType, bool bMovetype)
{
	int nHang = 0;	

	if (bMovetype)
	{
		nHang = 1;
	}
	else
	{
		nHang = -1;
	}
	
	switch (nType)
	{
	case SHOTTYPE_NOMAL:
		m_pBullet = CBullet::Create(m_pos, D3DXVECTOR3(nHang*30.0f, 0.0f, 0.0f), D3DXVECTOR2(20.0f, 20.0f), 30, true);
		m_nCoolTime = 40;
		break;

	case SHOTTYPE_HOMING:
		for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
		{
			m_pHoming[nCnt] = CHoming::Create(m_pos, D3DXVECTOR3(30.0f, 0.0f, 0.0f), D3DXVECTOR2(20.0f, 20.0f), D3DXVECTOR2(rand() % (int)1280.0f, 10.0f), m_nItem);
		}
		m_nCoolTime = 100;
		break;

	case SHOTTYPE_SHOYGUN:
		m_pBullet03 = CBullet03::Create(m_pos, D3DXVECTOR3(nHang*30.0f, nHang*20.0f, 0), D3DXVECTOR2(20.0f, 20.0f), 0);
		m_nCoolTime = 40;
		break;
	default:
		break;
	}
}

//=============================================================================
// プレイヤーのステータスの書き込み処理
//=============================================================================
void CPlayer::SaveStatus(void)
{
	// 開け～ファイル！
	FILE *pFile = fopen(STATUS_TEXT, "w");

	// ファイルがあったら
	if (pFile != NULL)
	{
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "# プレイヤーのステータス設定ファイル[Setui.txt]\n");
		fprintf(pFile, "# Author : 佐藤瞭平\n");
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "SCRIPT\t\t# この行は絶対消さないこと！\n");		
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "# プレイヤーのステータス情報\n");
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "SETSTATUS\n");
		fprintf(pFile, "\tATTACK = %d\n", m_nItem);
		fprintf(pFile, "END_SETSTATUS\n\n");
		
		fprintf(pFile, "END_SCRIPT\t\t# この行は絶対消さないこと！\n");
	}
	else
	{
		printf("ファイルが読み込まれませんでした。");
	}
	// 閉じれ～ファイル！
	fclose(pFile);
}

//=============================================================================
// プレイヤーのステータスの読み込み処理
//=============================================================================
void CPlayer::LoadStatus(void)
{
	// 開け～ファイル！
	FILE *pFile = fopen(STATUS_TEXT, "r");
	//--------------------------
	// 読み込む用の変数
	//--------------------------
	char aFile[3][128] = {};
	char aName[128] = {};

	// ファイルがあったら
	if (pFile != NULL)
	{
		// 無限ループ
		while (1)
		{
			fscanf(pFile, "%s", &aFile[0][0]);										// 1列を読み込み(2行目以降は上書きされる)

			while (strcmp(&aFile[0][0], "SETSTATUS") == 0)							// SETSTATUSが見つかったら
			{
				fscanf(pFile, "%s", &aFile[1]);										// 1列を読み込み(2行目以降は上書きされる)
				if (strcmp(&aFile[1][0], "ATTACK") == 0)							// ATTACKが見つかったら
				{
					fscanf(pFile, "%s%d", &aName[0], &m_nItem);	// 現在の位置を読み込む
				}
				else if (strcmp(&aFile[1][0], "END_SETSTATUS") == 0)					// END_SETUIが見つかったら
				{
					break;															// 無限ループを抜ける
				}
			}
			if (strcmp(&aFile[0][0], "END_SCRIPT") == 0)							// END_SCRIPTが見つかったら
			{
				break;																// 無限ループを抜ける
			}
		}
	}
	else
	{
		printf("ファイルが読み込まれませんでした。");
	}

	// 閉じれ～ファイル！
	fclose(pFile);
}

//=============================================================================
// 動かないブロックの当たり判定
//=============================================================================
void CPlayer::BlockColision(void)
{
	/*オブジェクト分けをして当たり判定をわけるか
	ブロックcppでタイプ分けをして当たり判定を分けるか*/

	// ブロックオブジェクトを取得
	CScene * pScene = CScene::GetScene(CScene::PRIORITY_BLOCK);

	// pSceneがNULLじゃない場合ループさせる
	while (pScene != NULL)
	{
		// 取得したオブジェクトを普通のブロックに代入
		CNoneBlock *pBlock = (CNoneBlock*)pScene;

		D3DXVECTOR3 Blockpos = pBlock->GetPosition();
		D3DXVECTOR2 Blocksize = pBlock->GetSize();

		if (m_pos.x - m_size.x < Blockpos.x + Blocksize.x &&				// プレイヤーの左端<ブロックの右端
			m_pos.x + m_size.x > Blockpos.x - Blocksize.x &&				// プレイヤーの右端>ブロックの左端
			m_pos.y - m_size.y < Blockpos.y + Blocksize.y &&				// プレイヤーの上端<ブロックの下端
			m_pos.y + m_size.y > Blockpos.y - Blocksize.y)					// プレイヤーの下端>ブロックの上端
		{																	   
			if (m_posold.y + m_size.y <= Blockpos.y - Blocksize.y)			// 前回のプレイヤーの下端<=ブロックの上端
			{																   
				m_pos.y = Blockpos.y - m_size.y - Blocksize.y;				   
				m_bJump = false;											   
				m_move.y = 0.0f;											   
			}																   
			else if (m_posold.y - m_size.y >= Blockpos.y + Blocksize.y)		// 前回のプレイヤーの上端>=ブロックの下端
			{																   
				m_pos.y = Blockpos.y + Blocksize.y + m_size.y;				   
				m_move.y = 0.0f;											   
			}																   
			else if (m_posold.x - m_size.x >= Blockpos.x + Blocksize.x)		// 前回のプレイヤーの左端>=ブロックの右端			
			{																   
				m_pos.x = Blockpos.x + m_size.x + Blocksize.x;				   
				m_bJump = false;											   
			}																   
			else if (m_posold.x + m_size.x <= Blockpos.x - Blocksize.x)		// 前回のプレイヤーの右端<=ブロックの左端
			{
				m_pos.x = Blockpos.x - m_size.x - Blocksize.x;
				m_bJump = false;
			}
		}
		// 現在のオブジェクトの次を取得
		CScene * pSceneNext = CScene::GetNext(pScene);
		pScene = pSceneNext;
	}
}

//=============================================================================
// 押すブロックの当たり判定
//=============================================================================
void CPlayer::PushColision(void)
{
	// 押すブロックオブジェクトを取得
	CScene * pScene = CScene::GetScene(CScene::PRIORITY_PUSHBLOCK);	

	// pSceneがNULLじゃない場合ループさせる
	while (pScene != NULL)
	{		
		CPushBlock *pBlock = (CPushBlock*)pScene;
		D3DXVECTOR3 Blockpos = pBlock->GetPos();
		D3DXVECTOR3 Blockposold = pBlock->GetPosold();
		D3DXVECTOR3 Blockmove = pBlock->GetMove();
		D3DXVECTOR2 Blocksize = pBlock->Getsize();
		
		if (m_pos.x - m_size.x < Blockpos.x + Blocksize.x &&				// プレイヤーの左端<ブロックの右端
			m_pos.x + m_size.x > Blockpos.x - Blocksize.x &&				// プレイヤーの右端>ブロックの左端
			m_pos.y - m_size.y < Blockpos.y + Blocksize.y &&				// プレイヤーの上端<ブロックの下端
			m_pos.y + m_size.y > Blockpos.y - Blocksize.y)					// プレイヤーの下端>ブロックの上端
		{
			if (m_posold.y + m_size.y <= Blockpos.y - Blocksize.y)			// 前回のプレイヤーの下端<=ブロックの上端
			{
				m_pos.y = Blockpos.y - Blocksize.y - m_size.y;
				m_move.y = 0.0f;
				m_bJump = false;
			}
			else if (m_posold.y - m_size.y >= Blockpos.y + Blocksize.y)		// 前回のプレイヤーの上端>=ブロックの下端
			{
				m_pos.y = Blockpos.y + Blocksize.y + m_size.y;
			}
			if (m_posold.x + m_size.x <= Blockpos.x - Blocksize.x)			// 前回のプレイヤーの左端>=ブロックの右端
			{																
				m_pos.x = Blockpos.x - m_size.x - Blocksize.x;
				m_move.x = 2;
				Blockmove.x = m_move.x;
				Blockpos.x += Blockmove.x;
				pBlock->SetPos(Blockpos);									
				pBlock->SetMove(Blockmove);
			}
			if (m_posold.x - m_size.x >= Blockpos.x + Blocksize.x)			// 前回のプレイヤーの右端<=ブロックの左端
			{
				m_pos.x = Blockpos.x + m_size.x + Blocksize.x;
				m_move.x = 2;
				Blockmove.x = m_move.x;				
				Blockpos.x -= Blockmove.x;
				pBlock->SetPos(Blockpos);
				pBlock->SetMove(Blockmove);
			}
		}
		// もしもオブジェクトがプレイヤーじゃない
		else
		{
			m_move.x = 10;
		}
		// 現在のオブジェクトの次を取得
		CScene * pSceneNext = CScene::GetNext(pScene);
		pScene = pSceneNext;
	}
}

//=============================================================================
// 移動ブロックの当たり判定
//=============================================================================
void CPlayer::MoveColision(void)
{
	// 移動ブロックのオブジェクトを取得
	CScene * pScene = CScene::GetScene(CScene::PRIORITY_MOVEBLOCK);	

	// pSceneがNULLじゃない場合ループさせる
	while (pScene != NULL)
	{
		CMoveBlock *pBlock = (CMoveBlock*)pScene;
		D3DXVECTOR3 Blockpos = pBlock->GetPos();
		D3DXVECTOR3 Blockposold = pBlock->GetPosold();
		D3DXVECTOR3 Blockmove = pBlock->GetMove();
		D3DXVECTOR2 Blocksize = pBlock->Getsize();

		if (m_pos.x + m_size.x >= Blockpos.x - Blocksize.x &&			// プレイヤーの左端<=ブロックの右端左端左端
			m_pos.x - m_size.x <= Blockpos.x + Blocksize.x &&			// プレイヤーの右端>=ブロックの左端右端右端
			m_pos.y + m_size.y >= Blockpos.y - Blocksize.y &&			// プレイヤーの上端<=ブロックの下端下部下部
			m_pos.y - m_size.y <= Blockpos.y + Blocksize.y)				// プレイヤーの下端>=ブロックの上端
		{
			if (m_posold.x + m_size.x <= Blockpos.x - Blocksize.x)		// 前回のプレイヤーの右端<=ブロックの左端
			{
				m_pos.x = Blockpos.x - m_size.x - Blocksize.x;

				// ブロックが右に移動をしているとき
				if (pBlock->GetMoveBlock() == CMoveBlock::MOVE_RIGHT)
				{
					// ブロックが移動してるときのプレイヤーの移動処理
					m_pos.x -= Blockmove.x;
				}
			}
			if (m_posold.x - m_size.x >= Blockpos.x + Blocksize.x)		// 前回のプレイヤーの左端>=ブロックの右端
			{
				m_pos.x = Blockpos.x + m_size.x + Blocksize.x;

				// ブロックが右に移動をしているとき
				if (pBlock->GetMoveBlock() == CMoveBlock::MOVE_LEFT)
				{
					// ブロックが移動してるときのプレイヤーの移動処理
					m_pos.x += Blockmove.x;
				}
			}
		}
		// 現在のオブジェクトの次を取得
		CScene * pSceneNext = CScene::GetNext(pScene);
		pScene = pSceneNext;
	}
}