//=============================================================================
//
// 敵の処理 [player2.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include"enemy02.h"
#include"renderer.h"
#include"manager.h"
#include"input.h"
#include"model.h"
#include"shadow.h"
#include"title.h"
#include"bullet.h"
#include"game.h"
#include"player.h"
#include"score.h"
#include"choose_game.h"
#include"tutorial.h"
#include"explosion.h"

//=============================================================================
// 静的メンバ変数の宣言
//=============================================================================
CShadow* CEnemy2::m_pShadow = NULL;
CModel * CEnemy2::m_pModel[20] = {};
bool CEnemy2::m_bUse = true;

//=============================================================================
// コンストラクタ
//=============================================================================
CEnemy2::CEnemy2(PRIORITY Priority) :CEnemy(PRIORITY_ENEMY)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fRadius = 10.0f;
	m_fFlame = 5.0f;
	m_nNumKey = 0;	
}


//=============================================================================
// デストラクタ
//=============================================================================
CEnemy2::~CEnemy2()
{

}

//=============================================================================
// 敵の生成処理
//=============================================================================
CEnemy2 *CEnemy2::Create(D3DXVECTOR3 pos, const char *pFileName)
{
	// 敵のポインター生成
	CEnemy2* pEnemy2 = NULL;

	// 動的メモリの確保
	pEnemy2 = new CEnemy2;

	// NULLチェック
	if (pEnemy2 != NULL)
	{
		// 初期化処理の呼び出し
		pEnemy2->Init(pos, pFileName);		
	}
	return pEnemy2;
}

	//=============================================================================
	// 敵のロード関数をオーバーロードした初期化処理
	//=============================================================================
HRESULT CEnemy2::Init(D3DXVECTOR3 pos, const char *pFileName)
{
	// 敵の初期化処理を呼び出す
	CEnemy::Init(pos, pFileName);
	// 影の生成処理の　
	m_pShadow = CShadow::Create(D3DXVECTOR3(0,0,0), D3DXVECTOR3(20,0,20),D3DXVECTOR3(0,0,0));

	return S_OK;
}



//=============================================================================
// 敵の終了処理
//=============================================================================
void CEnemy2::Uninit(void)
{
	// 使えなくする
	m_bUse = false;

	// NULLチェック
	if (m_pShadow != NULL)
	{// 影の終了処理を呼び出す
		m_pShadow->Uninit();
		m_pShadow = NULL;
	}

	// 敵の終了処理を呼び出す
	CEnemy::Uninit();

	// 解放処理
	Release();

}// 敵の終了処理終了


 //=============================================================================
 // 敵の更新処理
 //=============================================================================
void CEnemy2::Update(void)
{
	D3DXVECTOR3 size = CEnemy::GetSize();

	CPlayer * pPlayer = NULL;
	int nAttack = 0;
	CScore * pScore = NULL;

	// ゲームをしたかどうか
	if (CChoose_Game::GetGame())
	{
		// プレイヤーをゲームから取得
		pPlayer = CGame::GetPlayer();

		// プレイヤーの攻撃力を取得
		nAttack = pPlayer->GetAttack();

		// ゲームから現在のスコア状況を取得
		pScore = CGame::GetScore();
	}
	else 	// ゲームをしてないとき
	{// プレイヤーを別で生成するのはチュートリアルだけなので
		// チュートリアルでのプレイヤーを取得
		pPlayer = CTutorial::GetPlayer();

		// プレイヤーの攻撃力を取得
		nAttack = pPlayer->GetAttack();
	}

	//=============================================================================
	// 自機の弾と敵の当たり判定
	//=============================================================================
	for (int nPriority = 0; nPriority < PRIORITY_MAX; nPriority++)
	{
		// オブジェクトのポインター生成
		CScene * pScene = NULL;

		// 現在のオブジェクトの取得
		pScene = CScene::GetScene(nPriority);

		// NULLチェック
		if (pScene != NULL)
		{
			// 現在のオブジェクトが弾だった場合
			if (nPriority == CScene::PRIORITY_BULLET)
			{				
				// 現在のオブジェクトの種類を弾のポインター生成したものに弾のポインターでキャストして代入
				CBullet *pBullet = (CBullet*)pScene;

				if (m_pos.x/* + (size.x / 2)*/ + 10 >= pBullet->GetPos().x - pBullet->GetSize().x&&
					m_pos.x/* - (size.x / 2)*/ - 10 <= pBullet->GetPos().x + pBullet->GetSize().x&&
					m_pos.y/* + (size.y / 2)*/ + 50 >= pBullet->GetPos().y - pBullet->GetSize().y&&
					m_pos.y/* + (size.y / 2)*/ + 50 <= pBullet->GetPos().y + pBullet->GetSize().y&&
					m_pos.z/* - (size.z / 2)*/ - 10 <= pBullet->GetPos().z
					)
				{
					// 弾を使わなくする
					pBullet->SetUse(false);

					// ゲームをしたかどうかを取得
					if (CChoose_Game::GetGame())
					{// していれば
						// スコアを加算する
						pScore->AddScore(100);
						// プレイヤーの攻撃力を加算させる
						pPlayer->SetAttack(nAttack + 10);

						CExplosion::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 50, m_pos.z), D3DXVECTOR2(50,50));
					}
					// 終了処理の呼び出し
					Uninit();
					return;
				}
			}
		}
	}
	
	// プレイヤーの現在の位置を取得
	D3DXVECTOR3 Playerpos = pPlayer->GetPos();

	// プレイヤーと敵の斜辺の距離を測るA＝√（三平方より(c2乗 = a2乗+b2乗)）
	m_fRange = sqrtf(powf((Playerpos.x - m_pos.x), 2.0f) + powf((Playerpos.z - m_pos.z), 2.0f));

	// 現在の位置+円の面積がプレイヤーと敵の斜辺の距離が円の面積以上(右の場合)or以下（左の場合）に入っていたら
	if (m_pos.x + (m_fRadius*powf(D3DX_PI, 2)) >= m_fRange &&
		m_pos.x - (m_fRadius*powf(D3DX_PI, 2)) <= m_fRange &&
		m_pos.z + (m_fRadius*powf(D3DX_PI, 2)) >= m_fRange &&
		m_pos.z - (m_fRadius*powf(D3DX_PI, 2)) <= m_fRange)
	{
		// プレイヤーと敵の斜辺の距離が入っているかの確認
		if (m_fRange != NULL)
		{// 入っていたら
			// 移動量 = ((プレイヤーの現在の位置 - 敵の現在の位置)/斜辺)/フレーム数
			m_Move.x = ((Playerpos.x - m_pos.x) / m_fRange) / m_fFlame;
			m_Move.z = ((Playerpos.z - m_pos.z) / m_fRange) / m_fFlame;
		}
	}
	// 範囲外の場合
	else
	{
		m_Move.x = 0;
		m_Move.z = 0;
	}

	// 現在の位置に移動量を加算させる
	m_pos += m_Move;

	// 現在の位置の更新
	SetPos(m_pos);

	// 影の現在の位置を更新
	m_pShadow->SetPosition(m_pos);

	// 継承元の更新処理を呼び出す
	CEnemy::Update();


}// ポリゴンの更新処理終了



 //=============================================================================
 // 敵の描画処理
 //=============================================================================
void CEnemy2::Draw(void)
{
	// 継承元の描画処理を呼び出す
	CEnemy::Draw();

}// 敵の描画処理終了