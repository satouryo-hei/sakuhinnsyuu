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
#include"shotgun.h"
#include"enemy02.h"
#include"facialui.h"
/* ジャンプ中の移動がおかしい
なんか気持ち悪い　現実ぽくない
*/

//=============================================================================
// 静的メンバ関数の宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;
CBullet* CPlayer::m_pBullet = NULL;
CHoming* CPlayer::m_pHoming[MAX_BULLET] = {};
CShotgun* CPlayer::m_pShotgun = NULL;
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
CPlayer::CPlayer(int nPriority) : CScene2D(PRIORITY_PLAYER), m_fSizeU(0.25f)
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
	m_fSizeMaxV = 0.5f;
	m_fSizeMinV = 0.0f;
	m_nAttack = 2;
	m_fQuickening = 0.0f;
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
	CPlayer* pPlayer = NULL;

	pPlayer = new CPlayer;

	if (pPlayer != NULL)
	{
		pPlayer->Init(pos, Size);
		pPlayer->m_move = move;
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
	// オブジェクト2Dの初期化処理の呼び出し
	CScene2D::Init(pos, Size);

	// 新しくゲームを始めるかどうかの取得
	const bool bNewGame = CChoose_Game::GetNewGame();

	// ゲームに遷移したかどうかの取得
	const bool bGame = CChoose_Game::GetGame();

	// 新しく始めるか
	if (bNewGame)
	{// 新しく始めた場合

		// アイテム数を初期化
		m_nItem = 0;
#ifdef _DEBUG
		// デバック用にアイテム数を大きくする
		m_nItem = 100;
#endif // _DEBUG

	}
	else if (!bNewGame)
	{// 新しく始めてない場合

		// 保持しているアイテムを読み取って取得
		LoadItem();
	}

	// ゲームに遷移するか
	if (!bGame)
	{// ゲームに遷移しなかったら

		// アイテムを保持させる状態で初期化
		m_nItem = 1;
	}

	// アニメーション処理の呼び出し
	CScene2D::SetTexAnime(m_nPatternAnim, m_fSizeU, m_fSizeMinV, m_fSizeMaxV);	

	return S_OK;
}	// プレイヤーの初期化処理終了



	//=============================================================================
	// プレイヤーの終了処理
	//=============================================================================
void CPlayer::Uninit(void)
{
	// アイテム数を記録
	SaveItem();
//	CScene2D::Uninit();
	// 解放処理の呼び出し
	Release();

}// プレイヤーの終了処理終了


 //=============================================================================
 // プレイヤーの更新処理
 //=============================================================================
void CPlayer::Update(void)
{
	// アニメーションのカウントを進める
	m_nCounterAnim++;

	// 使っているかどうか
	if (!m_bUse)
	{// 使っていないなら

		// やられた表情に切り替え
		CGame::GetFace()->SetFace(CFacialui::FACE_CRYING);
		// 終了処理の呼び出し
		Uninit();
		return;
	}

	CInputKeyboard *pInputKeyboard = NULL;

	pInputKeyboard = CManager::GetInputKeyboard();		
	
	// 弾の切り替え処理
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_F1))
	{
		// 弾の種類を加算で変える
		m_nBulletType++;

		// 弾の種類が最大値まで言ったら
		if (m_nBulletType >= SHOTTYPE_MAX)
		{
			// 弾の種類をNOMALに戻す
			m_nBulletType = SHOTTYPE_NOMAL;
		}
	}

	// 状態遷移
	switch (m_Playertype)
	{
	// 通常
	case PLAYER_NOMAL:
		m_posold = m_pos;		
		
		//任意で押されたかどうか
		if (pInputKeyboard->GetPress(DIK_A) /*&& !m_bJump*/)//左を押した
		{				
				m_fSizeMaxV = 1.0f;
				m_fSizeMinV = m_fSizeMaxV/2;
				m_pos.x -= m_move.x;
				m_fQuickening -= (m_move.x / 10);
				if (m_fQuickening <= -1.0f)
				{
					m_fQuickening = -1.0f;
				}
				// 移動する向き
				m_bMovePush = false;
				// アニメーションテクスチャの設定
				CScene2D::SetTexAnime(m_nPatternAnim, m_fSizeU, m_fSizeMinV, m_fSizeMaxV);
				SetAnimesion(m_nPatternAnim, m_fSizeU, m_fSizeMinV, m_fSizeMaxV);
		}
		else if (pInputKeyboard->GetPress(DIK_D) /*&& !m_bJump*/)//右を押した
		{							
				m_fSizeMaxV = 0.5f;
				m_fSizeMinV = 0.0f;
				m_pos.x += m_move.x;
				m_fQuickening += (m_move.x / 10);
				if (m_fQuickening >= 1.0f)
				{
					m_fQuickening = 1.0f;
				}
				// 移動する向き
				m_bMovePush = true;
				// アニメーションテクスチャの設定
				CScene2D::SetTexAnime(m_nPatternAnim, m_fSizeU, m_fSizeMinV, m_fSizeMaxV);
				SetAnimesion(m_nPatternAnim, m_fSizeU, m_fSizeMinV, m_fSizeMaxV);
		}

		if (pInputKeyboard->GetTrigger(DIK_W) && !m_bJump)//上に移動
		{				
			m_move.y = -20.0f;
			m_bJump = true;
		}		
		
		//// ジャンプ中の移動処理
		//if (m_bJump)
		//{
		//	//任意で押されたかどうか
		//	if (pInputKeyboard->GetPress(DIK_A))//左を押した
		//	{
		//		m_fSizeMaxV = 1.0f;
		//		m_fSizeMinV = m_fSizeMaxV / 2;
		//		m_pos.x -= sinf(D3DX_PI*0.25f)*(m_move.x*0.9f);				
		//		m_bMovePush = false;
		//		CScene2D::SetTexAnime(m_nPatternAnim, m_fSizeU, m_fSizeMinV, m_fSizeMaxV);
		//		SetAnimesion(m_nPatternAnim, m_fSizeU, m_fSizeMinV, m_fSizeMaxV);
		//	}
		//	else if (pInputKeyboard->GetPress(DIK_D))//右を押した
		//	{
		//		m_fSizeMaxV = 0.5f;
		//		m_fSizeMinV = 0.0f;
		//		m_pos.x += (m_move.x / 10);				
		//		m_bMovePush = true;
		//		CScene2D::SetTexAnime(m_nPatternAnim, m_fSizeU, m_fSizeMinV, m_fSizeMaxV);
		//		SetAnimesion(m_nPatternAnim, m_fSizeU, m_fSizeMinV, m_fSizeMaxV);
		//	}
		//}

		// 弾がうたれていたら
		if (m_bBullet)
		{
			m_nCoolTime--;
			// クール時間を0以下になったら
			if (m_nCoolTime < 0)
			{
				// 弾を打っていない判定にする
				m_bBullet = false;
				// クール時間を0にする
				m_nCoolTime = 0;
				CGame::GetFace()->SetFace(CFacialui::FACE_NOMAL);
			}
		}
		// 弾を打つ処理
		if (pInputKeyboard->GetPress(DIK_SPACE)&& !m_bBullet)	// スペースが押されていてかつ弾を打っていない時
		{	
			// 打つ弾はどれですか
			Shot(m_nBulletType,m_bMovePush);
			//pManager->GetSound()->Play(CSound::SOUND_LABEL_SHOT000);		
			// 表情の設定
			CGame::GetFace()->SetFace(CFacialui::FACE_SURPRISE);
			// 弾が打たれたよ
			m_bBullet = true;
		}

		// 重力
		m_move.y++;
		m_pos.y += m_move.y;	

		/*
		 画面端との当たり判定
		*/
		// 横
		if (m_pos.x + m_size.x >= SCREEN_WIDTH)
		{
			m_pos.x = SCREEN_WIDTH - m_size.x;			
		}
		else if (m_pos.x <= m_size.x)
		{
			m_pos.x = m_size.x;						
		}

		// 縦
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

	// 死んじゃった時
	case PLAYER_DEATH:
		// プレイヤー自信のタイマーが5で割り切れる時
		if (m_nTimer % 5 == 0)
		{
			// 現在の位置を代入してあげる
			m_pos = D3DXVECTOR3(10.0f + m_size.x, 320.0f, 0.0f);

			// 現在の状態をリスタートにする
			m_Playertype = PLAYER_RESTARE;
		}
		// プレイヤー内の時間を進める
		m_nTimer++;
		// 倒れちゃった…
		m_bDeath = true;
		break;

	// もう一度遊べる時
	case PLAYER_RESTARE:

		// 現在の位置がx=150以上?
		if (m_pos.x >= 150)
		{// 現在の位置がx=150以上だったら
			// 通常に戻す
			m_Playertype = PLAYER_NOMAL;
		}
		else
		{// それ以外
			// 現在の位置に加算する
			m_pos.x += 5;
		}
		break;

		m_nTimer = 0;

	default:
		break;
	}

	// 敵との当たり判定
	EnemyColision();
	// ブロックとの当たり判定
	BlockColision();
	// 押せるブロックとの当たり判定
	PushColision();
	// 移動するブロックとの当たり判定
	MoveColision();

	// 現在の位置の設定処理
	SetPosition(m_pos);

	// 現在の大きさの設定処理
	SetSize(m_size);
	CScene2D::Update();


}// プレイヤーの更新処理終了

//=============================================================================
// プレイヤーの描画処理
//=============================================================================
void CPlayer::Draw(void)
{
	// オブジェクト2Dの描画処理の呼び出し
	CScene2D::Draw();

}	// プレイヤーの描画処理終了


//=============================================================================
// プレイヤーの弾の処理
//=============================================================================
void CPlayer::Shot(int nType, bool bMovetype)
{
	int nHang = 0;	

	// ブロックオブジェクトを取得
	CScene * pScene = CScene::GetScene(CScene::PRIORITY_ENEMY);

	// どっちを向いているか
	if (bMovetype)
	{
		nHang = 1;
	}
	else
	{
		nHang = -1;
	}
	
	// 打つ弾の種類は？
	switch (nType)
	{
	case SHOTTYPE_NOMAL:
		m_pBullet = CBullet::Create(m_pos, D3DXVECTOR3(nHang*30.0f, 0.0f, 0.0f), D3DXVECTOR2(20.0f, 20.0f), 30, true);
		m_nCoolTime = 40;
		break;

	case SHOTTYPE_HOMING:
		if (pScene != NULL)
		{
			CEnemy02 * pEnemy02 = (CEnemy02*)pScene;
			for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
			{
				m_pHoming[nCnt] = CHoming::Create(m_pos, D3DXVECTOR3(30.0f, 0.0f, 0.0f), D3DXVECTOR2(20.0f, 20.0f), D3DXVECTOR2(pEnemy02->GetPos().x, pEnemy02->GetPos().y), m_nAttack);
			}
		}
		else
		{
			for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
			{
				m_pHoming[nCnt] = CHoming::Create(m_pos, D3DXVECTOR3(30.0f, 0.0f, 0.0f), D3DXVECTOR2(20.0f, 20.0f), D3DXVECTOR2(rand() % 1280, 10), m_nAttack);
			}
		}
		
		m_nCoolTime = 100;
		break;

	case SHOTTYPE_SHOTGUN:
		m_pShotgun = CShotgun::Create(m_pos, D3DXVECTOR3(nHang*30.0f, nHang*20.0f, 0), D3DXVECTOR2(20.0f, 20.0f), 0);
		m_nCoolTime = 40;
		break;
	default:
		break;
	}
}

//=============================================================================
// プレイヤーのステータスの書き込み処理
//=============================================================================
void CPlayer::SaveItem(void)
{
	// 開け～ファイル！
	FILE *pFile = fopen(ITEM_TEXT, "w");

	// ファイルがあったら
	if (pFile != NULL)
	{
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "# プレイヤーのアイテム数設定ファイル[Setui.txt]\n");
		fprintf(pFile, "# Author : 佐藤瞭平\n");
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "SCRIPT\t\t# この行は絶対消さないこと！\n");		
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "# プレイヤーのアイテム数情報\n");
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "SETITEM\n");
		fprintf(pFile, "\tITEM = %d\n", m_nItem);
		fprintf(pFile, "END_SETITEM\n\n");
		
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
void CPlayer::LoadItem(void)
{
	// 開け～ファイル！
	FILE *pFile = fopen(ITEM_TEXT, "r");
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

			while (strcmp(&aFile[0][0], "SETITEM") == 0)							// SETSTATUSが見つかったら
			{
				fscanf(pFile, "%s", &aFile[1]);										// 1列を読み込み(2行目以降は上書きされる)
				if (strcmp(&aFile[1][0], "ITEM") == 0)							// ATTACKが見つかったら
				{
					fscanf(pFile, "%s%d", &aName[0], &m_nItem);	// 現在の位置を読み込む
				}
				else if (strcmp(&aFile[1][0], "END_SETITEM") == 0)					// END_SETUIが見つかったら
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
				if (m_posold.x - m_size.x >= Blockpos.x + Blocksize.x)		// 前回のプレイヤーの左端>=ブロックの右端			
				{
					m_pos.x = Blockpos.x + m_size.x + Blocksize.x;
				}
				else if (m_posold.x + m_size.x <= Blockpos.x - Blocksize.x)		// 前回のプレイヤーの右端<=ブロックの左端
				{
					m_pos.x = Blockpos.x - m_size.x - Blocksize.x;
				}
				else
				{
					m_pos.y = Blockpos.y + Blocksize.y + m_size.y;
					m_move.y = 0.0f;
				}
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

//=============================================================================
// 敵との当たり判定
//=============================================================================
void CPlayer::EnemyColision(void)
{
	// 敵のオブジェクトを取得
	CScene * pScene = CScene::GetScene(CScene::PRIORITY_ENEMY);

	// pSceneがNULLじゃない場合ループさせる
	while (pScene != NULL)
	{
		CEnemy02 *pEnemy = (CEnemy02*)pScene;
		D3DXVECTOR3 Enemypos = pEnemy->GetPos();
		D3DXVECTOR3 Enemyposold = pEnemy->GetPosold();
		D3DXVECTOR3 Enemymove = pEnemy->GetMove();
		D3DXVECTOR2 Enemysize = pEnemy->GetSize();

		if (m_pos.x - m_size.x < Enemypos.x + Enemysize.x &&				// プレイヤーの左端<敵の右端
			m_pos.x + m_size.x > Enemypos.x - Enemysize.x &&				// プレイヤーの右端>敵の左端
			m_pos.y - m_size.y < Enemypos.y + Enemysize.y &&				// プレイヤーの上端<敵の下端
			m_pos.y + m_size.y > Enemypos.y - Enemysize.y)					// プレイヤーの下端>敵の上端
		{
			// 敵が死んだことにする
			pEnemy->SetAlive(false);
			// アイテム数を0にする
			m_nItem = 0;
			// プレイヤーも死んだことにする
			m_bUse = false;			
			// リザルトに遷移
			CFade::SetFade(CManager::MODE_RESULT);

		}		
		// 現在のオブジェクトの次を取得
		CScene * pSceneNext = CScene::GetNext(pScene);
		pScene = pSceneNext;
	}
}


//=============================================================================
// プレイヤーのアニメーション設定処理
//=============================================================================
void CPlayer::SetAnimesion(int nPatternAnim, float fSizeAnimU, float fSizeMinV, float fSizeMaxV)
{
	if (m_nCounterAnim % 10 == 0)
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