#include "main.h"
#include "barrier_block.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "layer_structure.h"
#include "model_spawner.h"

CBarrier_Block::CBarrier_Block(OBJTYPE nPriority) : CScene(nPriority)
{

}

CBarrier_Block::~CBarrier_Block()
{

}

CBarrier_Block *CBarrier_Block::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CBarrier_Block *pPlayer = NULL;
	pPlayer = new CBarrier_Block;
	pPlayer->m_pos = pos;
	pPlayer->m_rot = rot;
	pPlayer->Init();
	return pPlayer;
}

HRESULT CBarrier_Block::Init()
{
	m_nLife = MAX_BLOCKLIFE;

	if (m_pModel == NULL)
	{
		m_pModel = CModel_Spawner::Create(m_pos, m_rot, "data/MODEL/Breaking_Wall.x");
	}

	return S_OK;
}

void CBarrier_Block::Uninit()
{
	if (m_pModel != NULL)
	{
		m_pModel->Uninit();
		m_pModel = NULL;
	}

	Release();

}

void CBarrier_Block::Update()
{
	//敵の行動パターン実装予定
	if (m_bUninit == true)
	{
		Uninit();
	}
}

void CBarrier_Block::Draw()
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
	if (m_pModel != NULL)
	{
		m_pModel->Draw();
	}
}

