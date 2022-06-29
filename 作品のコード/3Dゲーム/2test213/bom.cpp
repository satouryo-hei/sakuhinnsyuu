//=============================================================================
//
// アイテム処理 [model_single.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include"bom.h"
#include"manager.h"
#include"renderer.h"
#include"model.h"
#include"explosion.h"
#include"enemy02.h"

//=============================================================================
// アイテムのコンストラクタ
//=============================================================================
CBom::CBom(PRIORITY Priprity) :CModel_Single(Priprity)
{
	memset(&m_mtxWorld, NULL, sizeof(m_mtxWorld));
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 100;
	m_fRadius = 10;
	m_bUse = true;
}

//=============================================================================
// アイテムのデストラクタ
//=============================================================================
CBom::~CBom()
{

}

//=============================================================================
// アイテムの生成処理
//=============================================================================
CBom *CBom::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char*Filedata)
{
	// アイテムのポインター生成
	CBom * pBom = NULL;

	// 動的メモリの確保
	pBom = new CBom;

	//NULLチェック
	if (pBom != NULL)
	{
		pBom->Init(pos, rot, Filedata);
	}

	return pBom;
}

//=============================================================================
// アイテムの初期化処理
//=============================================================================
HRESULT CBom::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char*Filedata)
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
void CBom::Uninit(void)
{
	// 継承元の終了処理を呼び出す
	CModel_Single::Uninit();

	// 解放処理
	Release();
}

//=============================================================================
// アイテムの更新処理
//=============================================================================
void CBom::Update(void)
{
	SetPos(m_pos);

	if (!m_bUse)
	{
		//=============================================================================
		// ボムと敵の当たり判定
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
				if (nPriority == CScene::PRIORITY_ENEMY)
				{
					// 現在のオブジェクトの種類を敵のポインター生成したものに敵のポインターでキャストして代入
					CEnemy2 *pEnemy2 = (CEnemy2*)pScene;

					if (m_pos.x + (m_fRadius * powf(D3DX_PI, 2)) >= pEnemy2->GetPos().x &&
						m_pos.x - (m_fRadius * powf(D3DX_PI, 2)) <= pEnemy2->GetPos().x &&
						m_pos.z + (m_fRadius * powf(D3DX_PI, 2)) >= pEnemy2->GetPos().z &&
						m_pos.z - (m_fRadius * powf(D3DX_PI, 2)) <= pEnemy2->GetPos().z)
					{
						// 敵の終了処理の呼び出し
						pEnemy2->Uninit();						
					}
				}
			}
		}
		// 終了処理の呼び出し
		Uninit();
		// 爆発の生成処理の呼び出し
		CExplosion::Create(m_pos, D3DXVECTOR2(100.0f, 100.0f));
		return;
	}
	else
	{
		// 体力を減らす
		m_nLife--;

		// 体力0以下になったとき
		if (m_nLife <= 0)
		{// 体力0にする
			m_nLife = 0;

			// 使わなくする
			m_bUse = false;
		}
		// 継承先の更新処理を呼び出す
		CModel_Single::Update();
	}
}

//=============================================================================
// アイテムの描画処理
//=============================================================================
void CBom::Draw(void)
{
	// 継承先の描画処理を呼び出す
	CModel_Single::Draw();
}