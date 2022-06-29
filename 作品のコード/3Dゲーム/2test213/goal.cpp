//=============================================================================
//
// ゴール処理 [goal.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include"goal.h"
#include"manager.h"
#include"renderer.h"
#include"model.h"
#include"player.h"
#include"fade.h"
#include"choose_game.h"

//=============================================================================
// ゴールのコンストラクタ
//=============================================================================
CGoal::CGoal(PRIORITY Priprity) :CModel_Single(Priprity)
{
	memset(&m_mtxWorld, NULL, sizeof(m_mtxWorld));
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fRadius = 8.0f;
}

//=============================================================================
// アイテムのデストラクタ
//=============================================================================
CGoal::~CGoal()
{

}

//=============================================================================
// アイテムの生成処理
//=============================================================================
CGoal *CGoal::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char*pFiledata)
{
	// アイテムのポインター生成
	CGoal * pGoal = NULL;

	// 動的メモリの確保
	pGoal = new CGoal;

	//NULLチェック
	if (pGoal != NULL)
	{
		// ゴールの初期化処理の呼び出し
		pGoal->Init(pos, rot, pFiledata);
	}

	return pGoal;
}

//=============================================================================
// アイテムの初期化処理
//=============================================================================
HRESULT CGoal::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char*pFiledata)
{
	// 継承元の初期化処理を呼び出す
	CModel_Single::Init(pos, rot, pFiledata);
	m_pos = pos;
	m_rot = rot;
	SetPos(m_pos);
	SetRot(m_rot);
	return S_OK;
}

//=============================================================================
// アイテムの終了処理
//=============================================================================
void CGoal::Uninit(void)
{
	// 継承元の終了処理を呼び出す
	CModel_Single::Uninit();

	// 解放処理
	Release();
}

//=============================================================================
// アイテムの更新処理
//=============================================================================
void CGoal::Update(void)
{
	//=============================================================================
	// 自機の弾と敵の当たり判定
	//=============================================================================
	for (int nPriority = 0; nPriority < PRIORITY_MAX; nPriority++)
	{
		// オブジェクトのポインター生成
		CScene * pScene = NULL;		

		// オブジェクトの取得処理
		pScene = CScene::GetScene(nPriority);

		// NULLチェック
		if (pScene != NULL)
		{
			// オブジェクトの種類が敵だったら			
			if (nPriority == CScene::PRIORITY_PLAYER)
			{
				// 現在のオブジェクトの種類を敵のポインター生成したものに敵のポインターでキャストして代入				
				CPlayer *pPlayer = (CPlayer*)pScene;			

				// プレイヤーの現在の位置を取得
				D3DXVECTOR3 Playerpos = pPlayer->GetPos();

				// プレイヤーと敵の斜辺の距離を測るA＝√（三平方より(c2乗 = a2乗+b2乗)）
				float fRange = sqrtf(powf((Playerpos.x - m_pos.x), 2.0f) + powf((Playerpos.z - m_pos.z), 2.0f));

				// 現在の位置+円の面積がプレイヤーと敵の斜辺の距離が円の面積以上(右の場合)or以下（左の場合）に入っていたら
				if (m_pos.x + (m_fRadius * powf(D3DX_PI, 2)) >= fRange&&
					m_pos.x - (m_fRadius * powf(D3DX_PI, 2)) <= fRange&&
					m_pos.z + (m_fRadius * powf(D3DX_PI, 2)) >= fRange&&
					m_pos.z - (m_fRadius * powf(D3DX_PI, 2)) <= fRange)
				{					
					// ゲームをしてるかどうか
					if (CChoose_Game::GetGame())
					{
						// 遷移先をリザルトにする
						CFade::SetFade(CManager::MODE_RESULT);
					}
					else
					{// してなかった場合
						// 遷移先を選択モードにする
						CFade::SetFade(CManager::MODE_SELECT);
					}
				}
			}
		}
	}
	// 継承元の更新処理を呼び出す
	CModel_Single::Update();
}

//=============================================================================
// アイテムの描画処理
//=============================================================================
void CGoal::Draw(void)
{
	// 継承元の描画処理を呼び出す
	CModel_Single::Draw();
}