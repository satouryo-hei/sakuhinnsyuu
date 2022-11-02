//=============================================================================
//
// ブロックの処理 [score.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include "moveblock.h"
#include"player.h"
#include"enemy.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
CMoveBlock::MOVE CMoveBlock::m_MoveBlock = CMoveBlock::MOVE_NONE;	// ブロックの移動状態

//=============================================================================
// ブロックのコンストラクタ
//=============================================================================
CMoveBlock::CMoveBlock(int nPriority) : CScene2D(PRIORITY_MOVEBLOCK)
{
	m_pos = D3DXVECTOR3(0, 0, 0);
	m_move = D3DXVECTOR3(0, 0, 0);
	m_size = D3DXVECTOR2(0, 0);	
	m_bMove = true;
}

//=============================================================================
// ブロックのデストラクタ
//=============================================================================
CMoveBlock::~CMoveBlock()
{

}

//=============================================================================
// ブロックの生成処理
//=============================================================================
CMoveBlock *CMoveBlock::Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size, D3DXVECTOR3 move,
	int nCondition, float fMin, float fMax, int nTex)
{
	CMoveBlock *pMoveBlock = NULL;
	pMoveBlock = new CMoveBlock;

	if (pMoveBlock != NULL)
	{
		pMoveBlock->Init(pos, Size);
		pMoveBlock->m_nBlockCondition = nCondition;
		pMoveBlock->m_fMin = fMin;
		pMoveBlock->m_fMax = fMax;
		pMoveBlock->m_move = move;
		pMoveBlock->Bindtexture(0);
	}
	return pMoveBlock;
}

//=============================================================================
// ブロックの初期化処理
//=============================================================================
HRESULT CMoveBlock::Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	m_pos = pos;
	m_size = Size;
	CScene2D::Init(pos, Size);
	return S_OK;
}

//=============================================================================
// ブロックの終了処理
//=============================================================================
void CMoveBlock::Uninit(void)
{
	//CScene2D::Uninit();
	Release();
}

//=============================================================================
// ブロックの更新処理
//=============================================================================
void CMoveBlock::Update(void)
{
	SetBlock();
	MoveColision();

	CScene2D::Update();
}

//=============================================================================
// ブロックの描画処理
//=============================================================================
void CMoveBlock::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// ブロックの設定処理
//=============================================================================
void CMoveBlock::SetBlock(void)
{
	// ブロックの状態の遷移
	switch (m_nBlockCondition)
	{
		// ブロックが上に移動をしているとき
	case MOVE_UP:
		if (m_pos.y > m_fMin)
		{
			m_pos.y -= m_move.y;
		}
		else
		{
			// ブロックが下に移動をするようにする
			m_nBlockCondition = MOVE_DOWN;
		}
		break;

		// ブロックが下に移動をしているとき
	case MOVE_DOWN:
		if (m_pos.y < m_fMax)
		{
			m_pos.y += m_move.y;
		}
		else
		{
			// ブロックが上に移動をするようにする
			m_nBlockCondition = MOVE_UP;
		}
		break;

		// ブロックが左に移動をしているとき
	case MOVE_LEFT:
		if (m_pos.x > m_fMin)
		{
			m_pos.x -= m_move.x;
		}
		else
		{
			// ブロックが右に移動をするようにする
			m_nBlockCondition = MOVE_RIGHT;
		}
		break;

		// ブロックが右に移動をしているとき
	case MOVE_RIGHT:
		if (m_pos.x < m_fMax)
		{
			m_pos.x += m_move.x;
		}
		else
		{
			// ブロックが左に移動をするようにする
			m_nBlockCondition = MOVE_LEFT;
		}
		break;

	default:
		break;
	}

	m_MoveBlock = (MOVE)m_nBlockCondition;
	CScene2D::SetPosition(m_pos);
}

//=============================================================================
// 移動ブロックの当たり判定処理
//=============================================================================
int CMoveBlock::MoveColision(void)
{
	//=============================================================================
	// 自機と移動ブロックの当たり判定
	//=============================================================================
	for (int nPriority = 0; nPriority < PRIORITY_MAX; nPriority++)
	{
		// オブジェクトのポインター生成
		CScene * pScene = NULL;

		// オブジェクトの取得
		pScene = CScene::GetScene(nPriority);

		// オブジェクトがNULLじゃない限り回す
		if (pScene != NULL)
		{
			// もしもオブジェクトがプレイヤーなら
			if (nPriority == CScene::PRIORITY_PLAYER)
			{
				// 取得したオブジェクトをプレイヤーに代入
				CPlayer *pPlayer = (CPlayer*)pScene;

				// プレイヤーの現在の位置を取得
				D3DXVECTOR3 Playerpos = pPlayer->GetPos();

				// プレイヤーの前回の位置を取得
				D3DXVECTOR3 posold = pPlayer->GetPosold();

				// プレイヤーの移動量を取得
				D3DXVECTOR3 move = pPlayer->GetMove();

				// プレイヤーの大きさを取得
				D3DXVECTOR2 playersize = pPlayer->GetSize();						

				// プレイヤーがブロックに当たっているかどうかorめり込んでいるか
				if (m_pos.x - m_size.x <= Playerpos.x + playersize.x &&				// ブロックの左端 <= プレイヤーの右端
					m_pos.x + m_size.x >= Playerpos.x - playersize.x &&				// ブロックの右端 >= プレイヤーの左端
					m_pos.y - m_size.y <= Playerpos.y + playersize.y &&				// ブロックの上端 <= プレイヤーの下部
					m_pos.y + m_size.y >= Playerpos.y - playersize.y)				// ブロックの下端 >= プレイヤーの上部
				{
					// あったていてかつプレイヤー前回の位置がブロックの左側にあったら
					if (m_pos.x - m_size.x >= posold.x + playersize.x)				// ブロックの左端 <= 前回のプレイヤーの右端
					{
						// めり込んでいた時のために現在の位置を戻す
						Playerpos.x = m_pos.x - m_size.x - playersize.x; // プレイヤーの現在の位置 =ブロックの左側の位置+大きさ-プレイヤーの大きさ

						// ブロックが左に移動をしているとき
						if (m_nBlockCondition == MOVE_LEFT)
						{// ブロックが移動してるときのプレイヤーの移動処理
							// プレイヤーの位置をブロックの移動量分移動させる
							Playerpos.x -= m_move.x;
						}						
						// プレイヤーの現在の位置を設定
						pPlayer->SetPos(Playerpos);
						
						// プレイヤーのジャンプ状況を設定
						pPlayer->SetJump(false);

						// プレイヤーがブロックの左側にいるとき
						return MOVE_LEFT;
					}
					// あったていてかつプレイヤー前回の位置がブロックの右側にあったら
					if (m_pos.x + m_size.x <= posold.x - playersize.x)		// ブロックの右端 <= 前回のプレイヤーの左端
					{
						// めり込んでいた時のために現在の位置を戻す
						Playerpos.x = m_pos.x + m_size.x + playersize.x;// プレイヤーの現在の位置 =ブロックの右側の位置+大きさ-プレイヤーの大きさ

						// ブロックが右に移動をしているとき
						if (m_nBlockCondition == MOVE_RIGHT)
						{// ブロックが移動してるときのプレイヤーの移動処理

							// プレイヤーの位置をブロックの移動量分移動させる
							Playerpos.x += m_move.x;
						}						
						// プレイヤーの現在の位置を設定
						pPlayer->SetPos(Playerpos);
						
						// プレイヤーのジャンプ状況を設定
						pPlayer->SetJump(false);

						// プレイヤーがブロックの右側にいるとき
						return MOVE_RIGHT;
					}

					// あったていてかつプレイヤー前回の位置がブロックの右側にあったら
					if (m_pos.y - m_size.y >= posold.y + playersize.y)						// ブロックの上部 <= 前回のプレイヤーの下端
					{
						// めり込んでいた時のために現在の位置を戻す
						Playerpos.y = m_pos.y - m_size.y - playersize.y;// プレイヤーの現在の位置 =ブロックの上側の位置+大きさ-プレイヤーの大きさ

						// 重力を0にする
						move.y = 0;

						// ブロックが移動してるときのプレイヤーの移動処理
						switch (m_nBlockCondition)
						{
							// ブロックが上に移動をしているとき
						case MOVE_UP:
							// プレイヤーの位置をブロックの移動量分移動させる
							Playerpos.y -= (m_move.y * 2);
							break;

							// ブロックが右に移動をしているとき
						case MOVE_RIGHT:
							// プレイヤーの位置をブロックの移動量分移動させる
							Playerpos.x += m_move.x;
							break;

							// ブロックが左に移動をしているとき
						case MOVE_LEFT:
							// プレイヤーの位置をブロックの移動量分移動させる
							Playerpos.x -= m_move.x;
							break;

						default:
							break;
						}

						// プレイヤーの現在の位置を設定
						pPlayer->SetPos(Playerpos);

						// プレイヤーの移動量を設定
						pPlayer->SetMove(move);

						// プレイヤーのジャンプ状況を設定
						pPlayer->SetJump(false);

						// プレイヤーがブロックの上側にいるとき
						return MOVE_UP;
					}

					if (m_pos.y + m_size.y <= posold.y - playersize.y)			//ブロックの下部 <= 前回のプレイヤーの上端
					{
						// めり込んでいた時のために現在の位置を戻す
						Playerpos.y = m_pos.y + m_size.y + playersize.y;	// プレイヤーの現在の位置 =ブロックの下側の位置+大きさ-プレイヤーの大きさ

						// 重力を0にする
						move.y = 0;

						// プレイヤーの現在の位置を設定
						pPlayer->SetPos(Playerpos);

						// プレイヤーの移動量を設定
						pPlayer->SetMove(move);

						// プレイヤーがブロックの下側にいるとき
						return MOVE_DOWN;
					}
				}
			}
			// もしもオブジェクトがプレイヤーじゃない
			else
			{

			}
		}
	}
	// プレイヤーがブロックにいないとき
	return MOVE_NONE;
}