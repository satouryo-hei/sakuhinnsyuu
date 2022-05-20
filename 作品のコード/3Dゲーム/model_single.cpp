//=============================================================================
//
// 単体のモデル処理 [model_single.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include"model_single.h"
#include"manager.h"
#include"renderer.h"
#include"model.h"

//=============================================================================
// 単体のモデルのコンストラクタ
//=============================================================================
CModel_Single::CModel_Single(PRIORITY Priprity) :CScene(Priprity)
{
	m_pModel = NULL;
	memset(&m_mtxWorld, NULL, sizeof(m_mtxWorld));
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// 単体のモデルのデストラクタ
//=============================================================================
CModel_Single::~CModel_Single()
{

}

//=============================================================================
// 単体のモデルの生成処理
//=============================================================================
CModel_Single *CModel_Single::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char*pFiledata)
{
	// 単体のモデルのポインター生成
	CModel_Single * pSingle = NULL;

	// 動的メモリの確保
	pSingle = new CModel_Single;

	// NULLチェック
	if (pSingle != NULL)
	{
		pSingle->Init(pos, rot, pFiledata);
	}
	return pSingle;
}

//=============================================================================
// 単体のモデルのデフォルト初期化処理
//=============================================================================
HRESULT CModel_Single::Init(D3DXVECTOR3 pos)
{
	m_Pos = pos;
	return S_OK;
}

//=============================================================================
// 単体のモデルの初期化処理
//=============================================================================
HRESULT CModel_Single::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot , const char * pFiledata)
{	
	if (m_pModel == NULL)
	{
		//　モデルシングルの生成設定
		m_pModel = CModel::Create(pos, rot, pFiledata);

		// 親のモデルの設定
		m_pModel->SetParent(NULL);
	}

	Init(pos);
	m_rot = rot;
	return S_OK;
}

//=============================================================================
// 単体のモデルの終了処理
//=============================================================================
void CModel_Single::Uninit(void)
{
	if (m_pModel != NULL)
	{
		m_pModel->ReleaseModel();
		m_pModel = NULL;
	}

	Release();
}

//=============================================================================
// 単体のモデルの更新処理
//=============================================================================
void CModel_Single::Update(void)
{

}

//=============================================================================
// 単体のモデルの描画処理
//=============================================================================
void CModel_Single::Draw(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_Pos.x, m_Pos.y, m_Pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	if (m_pModel != NULL)
	{
		m_pModel->Draw();
	}
}

//=============================================================================
// 単体のモデルの向きの設定
//=============================================================================
void CModel_Single::SetRot(D3DXVECTOR3 rot)
{
	if (m_pModel != NULL)
	{
		m_pModel->SetRot(rot);
	}
}

//=============================================================================
// 単体のモデルの向きの設定
//=============================================================================
void CModel_Single::SetPos(D3DXVECTOR3 pos)
{
	if (m_pModel != NULL)
	{
		m_pModel->SetPos(pos);
	}
}