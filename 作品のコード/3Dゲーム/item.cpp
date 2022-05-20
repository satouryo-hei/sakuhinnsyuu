//=============================================================================
//
// アイテム処理 [model_single.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include"item.h"
#include"manager.h"
#include"renderer.h"
#include"model.h"
#include"player.h"

//=============================================================================
// アイテムのコンストラクタ
//=============================================================================
CItem::CItem(PRIORITY Priprity) :CModel_Single(Priprity)
{
	memset(&m_mtxWorld, NULL, sizeof(m_mtxWorld));
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// アイテムのデストラクタ
//=============================================================================
CItem::~CItem()
{

}

//=============================================================================
// アイテムの生成処理
//=============================================================================
CItem *CItem::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char*Filedata)
{
	// アイテムのポインター生成
	CItem * pItem = NULL;

	// 動的メモリの確保
	pItem = new CItem;

	//NULLチェック
	if (pItem != NULL)
	{
		pItem->Init(pos, rot, Filedata);
	}

	return pItem;
}

//=============================================================================
// アイテムの初期化処理
//=============================================================================
HRESULT CItem::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char*Filedata)
{
	// 継承先の初期化処理を呼び出す
	CModel_Single::Init(pos, rot, Filedata);
	m_pos = pos;
	m_rot = rot;
	SetPos(m_pos);
	SetRot(m_rot);
	return S_OK;
}

//=============================================================================
// アイテムの終了処理
//=============================================================================
void CItem::Uninit(void)
{
	// 継承先の終了処理を呼び出す
	CModel_Single::Uninit();
	Release();
}

//=============================================================================
// アイテムの更新処理
//=============================================================================
void CItem::Update(void)
{
	m_rot.y += 0.05f;
	if (m_rot.y >= D3DX_PI)
	{
		m_rot.y = -D3DX_PI;
	}
	else if(m_rot.y <= -D3DX_PI)
	{		
		m_rot.y = D3DX_PI;
	}
	SetRot(m_rot);

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
				int nAttack = pPlayer->GetAttack();

				if (m_pos.x+10 >= pPlayer->GetPos().x &&
					m_pos.x - 10 <= pPlayer->GetPos().x &&
					m_pos.y >= pPlayer->GetPos().y &&
					m_pos.y <= pPlayer->GetPos().y &&
					m_pos.z >= pPlayer->GetPos().z
					)
				{
					pPlayer->SetAttack(nAttack+10);
					Uninit();
					return;
				}
			}
		}
	}
	// 継承先の更新処理を呼び出す
	CModel_Single::Update();
}

//=============================================================================
// アイテムの描画処理
//=============================================================================
void CItem::Draw(void)
{
	// 継承先の描画処理を呼び出す
	CModel_Single::Draw();
}