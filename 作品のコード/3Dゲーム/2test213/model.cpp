//=============================================================================
//
// 汎用型のモデル処理 [model.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include"model.h"
#include"Camera.h"
#include"input.h"
#include"manager.h"
#include"renderer.h"

//=============================================================================
// 汎用型のモデルのコンストラクタ
//=============================================================================
CModel::CModel()
{
	memset(&m_mtxWorld, NULL, sizeof(m_mtxWorld));//ワールドマトリックス
	memset(&m_pTexture[0], NULL, sizeof(m_pTexture));//ワールドマトリックス
	m_pMesh = NULL;
	m_pBuffMat = NULL;
	m_vtxMin = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
	m_vtxMax = D3DXVECTOR3(-900.0f, -900.0f, -900.0f);
	m_nNumMat = 0;
	m_Pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	m_Size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	memset(&m_Vtx, 0, sizeof(m_Vtx));
	m_pParent = NULL;
	m_bUse;
}

//=============================================================================
// 汎用型のモデルのデストラクタ
//=============================================================================
CModel::~CModel()
{

}

//=============================================================================
// 汎用型のモデルの生成
//=============================================================================
CModel *CModel::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *pModelFileName)
{
	// 汎用型のモデルポインター生成
	CModel* pModel = NULL;

	// 動的メモリの確保
	pModel = new CModel;

	// NULLチェック
	if (pModel != NULL)
	{
		pModel->Init(pos, rot, pModelFileName);
	}
	return pModel;
}

//=============================================================================
// 汎用型のモデルの初期化関数
//=============================================================================
HRESULT CModel::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *pModelFileName)
{
	m_Pos = pos;
	m_rot = rot;

	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//-------------------//
	//Xファイルの読み込み//
	//-------------------//
	D3DXLoadMeshFromX(pModelFileName,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_nNumMat,
		&m_pMesh);

	D3DXMATERIAL *pMat = NULL;//マテリアルへのポインタ

					   //マテリアル情報に対するポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCnt = 0; nCnt < (int)m_nNumMat; nCnt++)
	{
		if (pMat[nCnt].pTextureFilename != NULL)
		{
			//テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCnt].pTextureFilename,
				&m_pTexture[nCnt]);	
		}
		else
		{
			//テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCnt].pTextureFilename,
				nullptr);
		}
	}

	int nNumVtx;//頂点数

	DWORD sizeFVF;//頂点フォーマットのサイズ

	BYTE *pVtxBuff;//頂点バッファのポインタ

				   //頂点数を取得
	nNumVtx = m_pMesh->GetNumVertices();

	//頂点フォーマットのサイズを取得
	sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	//頂点バッファをアンロック
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCnt = 0; nCnt < nNumVtx; nCnt++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;//頂点座標の代入

		//xの最大値の比較
		if (m_vtxMax.x <= vtx.x)
		{
			m_vtxMax.x = vtx.x;
		}
		//yの最大値の比較
		if (m_vtxMax.y <= vtx.y)
		{
			m_vtxMax.y = vtx.y;
		}
		//zの最大値の比較
		if (m_vtxMax.z <= vtx.z)
		{
			m_vtxMax.z = vtx.z;
		}
		//ｘの最小値の比較
		if (m_vtxMin.x >= vtx.x)
		{
			m_vtxMin.x = vtx.x;
		}
		//yの最小値の比較
		if (m_vtxMin.y >= vtx.y)
		{
			m_vtxMin.y = vtx.y;
		}
		//zの最小値の比較
		if (m_vtxMin.z >= vtx.z)
		{
			m_vtxMin.z = vtx.z;
		}

		m_Size.x = m_vtxMax.x - m_vtxMin.x;
		m_Size.y = m_vtxMax.y - m_vtxMin.y;
		m_Size.z = m_vtxMax.z - m_vtxMin.z;

		pVtxBuff += sizeFVF;//頂点フォーマットのサイズ分ポインタを進める
	}
	//頂点バッファをアンロック
	m_pMesh->UnlockVertexBuffer();

	//立方体の上左奥
	m_Vtx[0] = D3DXVECTOR3(
	-m_vtxMin.x,
	m_vtxMin.y, 
	m_vtxMin.z );

	//立方体の上右奥
	m_Vtx[1] = D3DXVECTOR3(
		m_vtxMin.x,
		m_vtxMin.y,
		m_vtxMin.z);

	//立方体の上右前
	m_Vtx[2] = D3DXVECTOR3(
		-m_vtxMin.x,
		m_vtxMin.y,
		-m_vtxMin.z);

	//右前（上面）
	m_Vtx[3] = D3DXVECTOR3(
		m_vtxMin.x,
		m_vtxMin.y,
		-m_vtxMin.z);
	//左奥（下面）
	m_Vtx[4] = D3DXVECTOR3(
		-m_vtxMin.x,
		-m_vtxMax.y,
		m_vtxMin.z);
	//右奥（下面）
	m_Vtx[5] = D3DXVECTOR3(
		m_vtxMin.x,
		-m_vtxMax.y,
		m_vtxMin.z);
	//左前（下面）
	m_Vtx[6] = D3DXVECTOR3(
		-m_vtxMin.x,
		-m_vtxMax.y,
		-m_vtxMin.z);
	//右前（下面）
	m_Vtx[7] = D3DXVECTOR3(
		m_vtxMin.x,
		-m_vtxMax.y,
		-m_vtxMin.z);

	return S_OK;
}

//=============================================================================
// 汎用型のモデルの終了処理
//=============================================================================
void CModel::Uninit(void)
{
	ReleaseModel();

	for (int nTex = 0; nTex < MAX_MODEL_TEX; nTex++)
	{
		if (m_pTexture[nTex] != NULL)
		{
			m_pTexture[nTex]->Release();
			m_pTexture[nTex] = NULL;
		}
	}
}

//=============================================================================
// 汎用型のモデルの更新処理
//=============================================================================
void CModel::Update(void)
{
}

//=============================================================================
// 汎用型のモデルの描画処理
//=============================================================================
void CModel::Draw(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;//計算用マトリックス
	D3DMATERIAL9 matDef;//現在のマテリアル保存用
	D3DXMATERIAL *pMat;//マテリアルデータのポインタ
	D3DXMATRIX mtxParent;						//親のマトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_Pos.x, m_Pos.y, m_Pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//各パーツの親のマトリックスの設定
	if (m_pParent != NULL)
	{
		mtxParent = m_pParent->GetMtx();
	}
	else
	{//最新のマトリックスを取得
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}

	//算出したパーツのワールドマトリックスと親のワールドマトリックスを掛け合わせる
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//マテリアルデータ編のポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, m_pTexture[nCntMat]);

		//モデル（パーツ）の描画
		m_pMesh->DrawSubset(nCntMat);
	}

	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);

}

//=============================================================================
// 汎用型のモデルのテクスチャ以外の終了処理
//=============================================================================
void CModel::ReleaseModel(void)
{
	//メッシュの破棄
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}

	//マテリアルの破棄
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}
}