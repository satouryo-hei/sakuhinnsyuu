//=============================================================================
//
// ゴールの処理 [score.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include "goal.h"
#include"input.h"
#include"player.h"
#include"fade.h"
#include"pushbutton.h"
#include"facialui.h"
#include"game.h"
#include"choose_game.h"

//=============================================================================
// 静的メンバ変数の宣言
//=============================================================================
CPushButton * CGoal::m_pPushButton = NULL;
bool CGoal::m_bGameClear = false;

//=============================================================================
// ゴールのコンストラクタ
//=============================================================================
CGoal::CGoal(int nPriority) : CScene2D(PRIORITY_GOAL)
{	
	m_bPush = false;	
}

//=============================================================================
// ゴールのデストラクタ
//=============================================================================
CGoal::~CGoal()
{

}

//=============================================================================
// ゴールの生成処理
//=============================================================================
CGoal *CGoal::Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size, CManager::MODE NextMode)
{
	CGoal *pGoal = NULL;
	pGoal = new CGoal;

	if (pGoal != NULL)
	{
		pGoal->Init(pos, Size);
		pGoal->m_NextMode = NextMode;
		pGoal->Bindtexture(12);
	}
	return pGoal;
}

//=============================================================================
// ゴールの初期化処理
//=============================================================================
HRESULT CGoal::Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	// 繰り返しゲームをした場合のために初期化
	m_bGameClear = false;
	m_Pos = pos;
	m_Size = Size;
	CScene2D::Init(pos, Size);
	// アニメーションのテクスチャ設定
	CScene2D::SetTexAnime(m_nPatternAnim, 0.125f, 0, 1);
	return S_OK;
}

//=============================================================================
// ゴールの終了処理
//=============================================================================
void CGoal::Uninit(void)
{
	CScene2D::Uninit();

	Release();
}

//=============================================================================
// ゴールの更新処理
//=============================================================================
void CGoal::Update(void)
{
	// アイテム数を取得
	int nItem = CPlayer::GetItem();

	// 押されるボタンが使われているか取得
	bool bUIUse = CPushButton::GetUse();

	// プレイヤーの現在の位置を取得
	D3DXVECTOR3 Playerpos = CPlayer::GetPos();

	// プレイヤーの大きさを取得
	D3DXVECTOR3 Playersize = CPlayer::GetSize();

	// プレイヤーと敵の斜辺の距離を測るA＝絶対値(a-b)
	float fRange = fabs(sqrtf(powf((Playerpos.x - m_Pos.x), 2.0f) + powf((Playerpos.y - m_Pos.y), 2.0f)));		// fabs = 絶対値

	// アイテム数をが1以上だったら
	if (nItem >= 1)
	{
		// プレイヤーと敵の距離が0じゃなかったら
		if (fRange != 0)
		{
			// 円の面積にプレイヤーとの斜辺の距離が入っていたら
			if (m_Size.x - Playersize.x > fRange)
			{
				// Sが押されたら
				if (CManager::GetInputKeyboard()->GetTrigger(DIK_S) == true && !m_bPush)
				{
					// 押されたよ
					m_bPush = true;
				}
				// 押されていたら
				if (m_bPush)
				{
					// アニメーションのカウントを進める
					m_nCounterAnim++;

					// アニメーションのカウントがアニメーションの速さで割って余ったのが0だった時(割り切れた時)
					if (m_nCounterAnim % 10 == 0)
					{
						// アニメーションのパターン数を進める
						m_nPatternAnim++;

						// アニメーションのテクスチャ設定
						CScene2D::SetTexAnime(m_nPatternAnim, 0.125f, 0, 1);

						// アニメーションのパターン数がパターンの最大数を超えたら
						if (m_nPatternAnim >= 8)
						{
							// ゲームをクリアしたことにする
							m_bGameClear = true;
							if (CChoose_Game::GetGame())
							{
								// 喜び表情に切り替え
								CGame::GetFace()->SetFace(CFacialui::FACE_JOY);
							}
							// 次のモードに遷移
							CFade::SetFade(m_NextMode);

							// アニメーションのパターン数の初期化
							m_nPatternAnim = 0;

							// アイテム数を減少
							nItem--;
							// アイテム数が0以下になったら
							if (nItem <= 0)
							{// アイテム数を0にする
								nItem = 0;
							}
							// アイテム数を設定
							CPlayer::SetItem(nItem);
						}
					}
				}

				// 使われていなかったら作る使われていたらエルスに入る
				if (!bUIUse)
				{
					// 押すボタンのUIの生成
					m_pPushButton = CPushButton::Create(D3DXVECTOR3(Playerpos.x, Playerpos.y - Playersize.y - 30, Playerpos.z), D3DXVECTOR2(20, 20), 10);// pos= プレイヤーの現在の位置-大きさの半径-UIの大きさ-10
					bUIUse = true;
					CPushButton::SetUse(bUIUse);
				}
				else
				{
					// 押すボタンのUIの現在の位置の設定
					m_pPushButton->SetPosition(D3DXVECTOR3(Playerpos.x, Playerpos.y - Playersize.y - 30, Playerpos.z));
				}
			}
			else
			{
				// 使かわれているか
				if (bUIUse)
				{// 使かわれていたら消す
					bUIUse = false;
					CPushButton::SetUse(bUIUse);
				}
			}
		}
	}
	// オブジェクト2Dの更新処理
	CScene2D::Update();
}

//=============================================================================
// 時間の描画処理
//=============================================================================
void CGoal::Draw(void)
{
	CScene2D::Draw();
}