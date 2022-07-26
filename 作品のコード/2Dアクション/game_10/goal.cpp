//=============================================================================
//
// ゴールの処理 [score.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include "goal.h"
#include"manager.h"
#include"input.h"
#include"player.h"
#include"fade.h"
#include"pushbutton.h"


//=============================================================================
// 静的メンバ変数の宣言
//=============================================================================
CPushButton * CGoal::m_pPushButton = NULL;

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
CGoal *CGoal::Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	CGoal *pGoal = NULL;
	pGoal = new CGoal;

	if (pGoal != NULL)
	{
		pGoal->Init(pos, Size);
		pGoal->Bindtexture(0);
	}
	return pGoal;
}

//=============================================================================
// ゴールの初期化処理
//=============================================================================
HRESULT CGoal::Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	m_Pos = pos;
	m_Size = Size;
	CScene2D::Init(pos, Size);
	return S_OK;
}

//=============================================================================
// ゴールの終了処理
//=============================================================================
void CGoal::Uninit(void)
{
	Release();
}

//=============================================================================
// ゴールの更新処理
//=============================================================================
void CGoal::Update(void)
{
	bool bUIUse = CPushButton::GetUse();
	D3DXVECTOR3 Playerpos = CPlayer::GetPos();
	D3DXVECTOR3 Playersize = CPlayer::GetSize();
	// プレイヤーと敵の斜辺の距離を測るA＝絶対値(a-b)
	float fRange = fabs(sqrtf(powf((Playerpos.x - m_Pos.x), 2.0f) + powf((Playerpos.y - m_Pos.y), 2.0f)));		// fabs = 絶対値

	if (fRange != 0)
	{
		// 円の面積にプレイヤーとの斜辺の距離が入っていたら
		if (m_Size.x >= fRange)
		{
			// Sが押されたら
			if (CManager::GetInputKeyboard()->GetTrigger(DIK_S) == true && !m_bPush)
			{
				CFade::SetFade(CManager::MODE_RESULT);
				m_bPush = true;
			}

			// 使われていなかったら作る使われていたらエルスに入る
			if (!bUIUse)
			{
				// 押すボタンのUIの生成
				m_pPushButton = CPushButton::Create(D3DXVECTOR3(Playerpos.x, Playerpos.y - Playersize.y-30, Playerpos.z), D3DXVECTOR2(20, 20), 10);// pos= プレイヤーの現在の位置-大きさの半径-UIの大きさ-10
				bUIUse = true;
				CPushButton::SetUse(bUIUse);
			}
			else
			{
				m_pPushButton->SetPosition(D3DXVECTOR3(Playerpos.x, Playerpos.y - Playersize.y - 30, Playerpos.z));
			}
		}
		else
		{
			// 使かわれていたら消す
			if (bUIUse)
			{
				bUIUse = false;
				CPushButton::SetUse(bUIUse);
			}			
		}
	}
	CScene2D::Update();
}

//=============================================================================
// 時間の描画処理
//=============================================================================
void CGoal::Draw(void)
{
	CScene2D::Draw();
}