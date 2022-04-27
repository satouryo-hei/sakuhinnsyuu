#include "main.h"
#include "barrier_wood.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "layer_structure.h"
#include "model_spawner.h"

CBarrier_wood::CBarrier_wood(OBJTYPE nPriority) : CScene(nPriority)
{

}

CBarrier_wood::~CBarrier_wood()
{

}

CBarrier_wood *CBarrier_wood::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CBarrier_wood *pPlayer = NULL;
	pPlayer = new CBarrier_wood;
	pPlayer->m_pos = pos;
	pPlayer->m_rot = rot;
	pPlayer->Init();
	return pPlayer;
}

HRESULT CBarrier_wood::Init()
{
	if (m_pWood == NULL)
	{
		m_pWood = CModel_Spawner::Create(m_pos, m_rot, "data/MODEL/wood.x");
	}
	m_nLife = MAX_WOOD_LIFE;
	return S_OK;
}

void CBarrier_wood::Uninit()
{

	if (m_pWood != NULL)
	{
		m_pWood->Uninit();
		m_pWood = NULL;
	}
	Release();

}

void CBarrier_wood::Update()
{
	//敵の行動パターン実装予定
	if (m_bUninit == true)
	{
		Uninit();
	}
}

void CBarrier_wood::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();//デバイスのポインタ
	D3DXMATRIX mtxRotModel, mtxTransModel;//計算用マトリックス
										  //各パーツのワールドマトリックスの初期化gtryg
	D3DXMatrixIdentity(&m_mtxWorld);
	D3DXMatrixRotationYawPitchRoll(&mtxRotModel, m_rot.y, m_rot.x, m_rot.z);
	//向きを反映
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRotModel);
	//位置を反映
	D3DXMatrixTranslation(&mtxTransModel, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTransModel);

	//各パーツのワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	////モデル生成
	//for (int nCntParts = 0; nCntParts < MAX_BARRIER_WOOD_PARTS; nCntParts++)
	//{
	//	m_pModel[nCntParts]->Draw();
	//}
	if (m_pWood != NULL)
	{
		m_pWood->Draw();
	}
}

