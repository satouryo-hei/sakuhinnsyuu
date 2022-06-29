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
	m_bUse = true;
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
		// アイテムの初期化処理の呼び出し
		pItem->Init(pos, rot, Filedata);
	}

	return pItem;
}

//=============================================================================
// アイテムの初期化処理
//=============================================================================
HRESULT CItem::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char*Filedata)
{
	// 継承元の初期化処理を呼び出す
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
	// 継承元の終了処理を呼び出す
	CModel_Single::ReleaseSingle();

	// 解放処理
	Release();
}

//=============================================================================
// アイテムの更新処理
//=============================================================================
void CItem::Update(void)
{
	// Y軸をぶっ刺して回す
	m_rot.y += 0.05f;

	// 現在の向きがπよりも大きかった場合
	if (m_rot.y >= D3DX_PI)
	{
		// 現在の向きに-πを代入して今状態を保存してπ以上にしないようにする
		m_rot.y = -D3DX_PI;
	}
	// 現在の向きが-πよりも大きかった場合
	else if(m_rot.y <= -D3DX_PI)
	{	
		// 現在の向きにπを代入して今状態を保存して-π以上にしないようにする
		m_rot.y = D3DX_PI;
	}
	// 現在の向きの更新
	SetRot(m_rot);

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
			// オブジェクトの種類がプレイヤーだったら
			if (nPriority == CScene::PRIORITY_PLAYER)
			{
				// 現在のオブジェクトの種類を敵のポインター生成したものに敵のポインターでキャストして代入
				CPlayer *pPlayer = (CPlayer*)pScene;

				// プレイヤーが持っているアイテム数を取得
				int nItem = pPlayer->GetItem();

				// 現在の位置がプレイヤーの現在の位置より大きいor小さかったら
				if (m_pos.x >= pPlayer->GetPos().x &&
					m_pos.x <= pPlayer->GetPos().x &&
					m_pos.y >= pPlayer->GetPos().y &&
					m_pos.y <= pPlayer->GetPos().y &&
					m_pos.z >= pPlayer->GetPos().z)
				{				
					// 使えなくする
					m_bUse = false;
					// 終了処理の呼び出し
					Uninit();
					// プレイヤーが持っているアイテム数を加算
					pPlayer->SetItem(nItem + 1);
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