//=============================================================================
//
// 時間の処理 [score.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include "item.h"
#include"player.h"

//=============================================================================
// 時間のコンストラクタ
//=============================================================================
CItem::CItem(int nPriority) : CScene2D(PRIORITY_ITEM)
{


}

//=============================================================================
// 時間のデストラクタ
//=============================================================================
CItem::~CItem()
{

}

//=============================================================================
// 時間の生成処理
//=============================================================================
CItem *CItem::Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	CItem *pAttack_up = NULL;
	pAttack_up = new CItem;

	if (pAttack_up != NULL)
	{
		pAttack_up->Init(pos, Size);
		pAttack_up->Bindtexture(17);
	}
	return pAttack_up;
}

//=============================================================================
// 時間の初期化処理
//=============================================================================
HRESULT CItem::Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	m_pos = pos;
	m_size = Size;
	CScene2D::Init(pos,Size);
	return S_OK;
}

//=============================================================================
// 時間の終了処理
//=============================================================================
void CItem::Uninit(void)
{
	Release();
}

//=============================================================================
// 時間の更新処理
//=============================================================================
void CItem::Update(void)
{
	int nItem = CPlayer::GetItem();

	//=============================================================================
	// 自機の弾と敵の当たり判定
	//=============================================================================
	for (int nPriority = 0; nPriority < PRIORITY_MAX; nPriority++)
	{
		CScene * pScene = NULL;

		pScene = CScene::GetScene(nPriority);

		if (pScene != NULL)
		{
			if (nPriority == CScene::PRIORITY_PLAYER)
			{
				CPlayer *pPlayer = (CPlayer*)pScene;

				if (m_pos.x + (m_size.x / 2) >= pPlayer->GetPos().x - pPlayer->GetSize().x &&
					m_pos.x - (m_size.x / 2) <= pPlayer->GetPos().x + pPlayer->GetSize().x &&
					m_pos.y + (m_size.y / 2) >= pPlayer->GetPos().y - pPlayer->GetSize().y &&
					m_pos.y - (m_size.y / 2) <= pPlayer->GetPos().y + pPlayer->GetSize().y)
				{
					Uninit();
					CPlayer::SetItem(nItem+1);
					return;
				}
			}
		}
	}

	CScene2D::Update();
}

//=============================================================================
// 時間の描画処理
//=============================================================================
void CItem::Draw(void)
{
	CScene2D::Draw();
}