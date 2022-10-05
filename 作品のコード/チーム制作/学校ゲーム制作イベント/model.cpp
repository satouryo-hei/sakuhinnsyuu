//=============================================================================
//
// モデルクラス [model.cpp]
// Author : 小笠原　彪我
//
//=============================================================================
//=============================================================================
//ヘッダファイルのインクルード
//=============================================================================
#include "model.h"
#include"renderer.h"
//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CModel::CModel()
{
	// メンバ変数のクリア
	memset(m_pTexture, NULL, sizeof(m_pTexture));	// テクスチャのポインタ
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向き
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 大きさ
	m_vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 各頂点の最小値
	m_vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 各頂点の最大値
	m_pMesh = NULL;									// メッシュ（頂点情報）へのポインタ
	m_pBuffMat = NULL;								// マテリアル（材質情報）へのポインタ
	m_pParent = NULL;								// 親モデルへのポインタ
	m_nNumMat = 0;									// マテリアル数
	m_nIdxParent = 0;								// 親モデルのインデックス
}
//=============================================================================
// デストラクタ
//=============================================================================
CModel::~CModel()
{
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CModel::Init(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// Xファイルの読み込み
	D3DXLoadMeshFromX(m_pModelFileName, D3DXMESH_SYSTEMMEM,
		pDevice, NULL, &m_pBuffMat, NULL, &m_nNumMat, &m_pMesh);

	// マテリアルデータへのポインタ
	D3DXMATERIAL	*pMat;
	int nCntTex = 0;

	// マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			//テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &m_pTexture[nCntTex]);
			nCntTex++;
		}
	}

	// 頂点情報の取得
	int nNumVtx;		// 頂点数
	DWORD sizeFVF;		// 頂点フォーマットのサイズ
	BYTE *pVtxBuff;		// 頂点バッファへのポインタ

	// 頂点数を取得
	nNumVtx = m_pMesh->GetNumVertices();

	// 頂点フォーマットのサイズを取得
	sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	// 頂点バッファをロック
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{	
		// 頂点座標の代入
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		// 全ての頂点を比較して最大値と最小値を抜き出す
		// 最大値
		if (vtx.x >= m_vtxMax.x)
		{
			m_vtxMax.x = vtx.x;
		}
		if (vtx.y >= m_vtxMax.y)
		{
			m_vtxMax.y = vtx.y;
		}
		if (vtx.z >= m_vtxMax.z)
		{
			m_vtxMax.z = vtx.z;
		}
		// 最小値
		if (vtx.x <= m_vtxMin.x)
		{
			m_vtxMin.x = vtx.x;
		}
		if (vtx.y <= m_vtxMin.y)
		{
			m_vtxMin.y = vtx.y;
		}
		if (vtx.z <= m_vtxMin.z)
		{
			m_vtxMin.z = vtx.z;
		}
		// 最大値と最小値を引いた値がモデルの大きさ
		m_size.x = m_vtxMax.x - m_vtxMin.x;
		m_size.y = m_vtxMax.y - m_vtxMin.y;
		m_size.z = m_vtxMax.z - m_vtxMin.z;

		// 頂点フォーマットのサイズ分ポインタを進める
		pVtxBuff += sizeFVF;
	}

	// 頂点バッファをアンロック
	m_pMesh->UnlockVertexBuffer();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CModel::Uninit(void)
{
	// メッシュの破棄
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}
	// マテリアルの破棄
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}
	// テクスチャの破棄
	for (int nCntTex = 0; nCntTex < MODEL_TEX; nCntTex++)
	{
		if (m_pTexture[nCntTex] != NULL)
		{
			m_pTexture[nCntTex]->Release();
			m_pTexture[nCntTex] = NULL;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CModel::Update(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void CModel::Draw(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX	mtxRot, mtxTrans;	// 計算用マトリックス
	D3DMATERIAL9		matDef;		// 現在のマテリアル保存用
	D3DXMATERIAL		*pMat;		// マテリアルデータへのポインタ
	int					nCntTex = 0;// テクスチャ数カウント

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// 各パーツの親のマトリックスの設定
	D3DXMATRIX	mtxParent;

	if (m_pParent != NULL)
	{	// 親のマトリックスを取得
		mtxParent = m_pParent->GetMtxWorld();
	}
	else
	{	// 一番最初のマトリックス(基本になるマトリックス)を掛け合わせる
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}

	// 算出した各パーツのワールドマトリックスと親のマトリックスを掛け合わせる
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	// 各パーツのワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// マテリアルを取得
	pDevice->GetMaterial(&matDef);

	// マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		// マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		if (pMat->pTextureFilename)
		{	// テクスチャの設定
			pDevice->SetTexture(0, m_pTexture[nCntTex]);
			nCntTex++;
		}
		else
		{	// テクスチャの設定
			pDevice->SetTexture(0, NULL);
		}
		// モデル（パーツ）の描画	
		m_pMesh->DrawSubset(nCntMat);
	}
	// 保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}
//=============================================================================
// 生成処理
//=============================================================================
CModel *CModel::Create(const char *pModelFileName)
{
	CModel *pModel = nullptr;
	if (pModel == nullptr)
	{
		pModel = new CModel;

		if (pModel != nullptr)
		{
			pModel->SetModelFile(pModelFileName);	// ファイルのパス設定
			pModel->Init();		// 初期化処理
		}
	}
	return pModel;
}
