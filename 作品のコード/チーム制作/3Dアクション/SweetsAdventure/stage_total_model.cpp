////----------------------------------
////ポリゴンの処理
////作成者　林海斗
////-----------------------------------
//#include "stage_total_model.h"
//#include "input.h"
//#include "Renderer.h"
//#include "manager.h"
//
////=============================================================================
//// コンストラクタ
////=============================================================================
//CStage_Total_Model::CStage_Total_Model()
//{
//	m_pMesh = NULL;					//メッシュ（頂点情報）へのポインタ
//	memset(m_vtx, NULL, sizeof(m_vtx));
//	m_nNumVtx = 0;						//頂点の数
//	m_vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//	m_vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//モデルの最小値、最大値
//	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//モデルの位置（オフセット）
//	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//向き
//	m_bDraw = false;
//}
//
////=============================================================================
//// デストラクタ
////=============================================================================
//CStage_Total_Model::~CStage_Total_Model()
//{
//}
////=============================================================================
//// ポリゴンの初期化処理
////=============================================================================
//void CStage_Total_Model::LoadX(const char *sModelFailName)
//{
//	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();//デバイスのポインタ
//
//																	 //Xファイルの読み込み
//	D3DXLoadMeshFromX(m_sFailName,
//		D3DXMESH_SYSTEMMEM,
//		pDevice,
//		NULL,
//		&m_pBuffMat,
//		NULL,
//		&m_nNumMat,
//		&m_pMesh);
//
//	//マテリアル情報に対するポインタを取得
//	m_pMat = (D3DXMATERIAL *)m_pBuffMat->GetBufferPointer();
//	//マテリアル情報を保存
//	m_pSaveMat = m_pMat;
//	for (int nCnt = 0; nCnt < (int)m_nNumMat; nCnt++)
//	{
//		if (m_pMat[nCnt].pTextureFilename != NULL)
//		{
//			//テクスチャの読み込み
//			D3DXCreateTextureFromFile
//			(pDevice,
//				m_pMat[nCnt].pTextureFilename,
//				&m_pTexture[nCnt]);
//		}
//	}
//	//頂点数を取得
//	m_nNumVtx = m_pMesh->GetNumVertices();
//	//頂点フォーマットのサイズを取得
//	m_sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());
//	//頂点バッファをアンロック
//	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&m_pVtxBuff);
//	//モデルの大きさを測る
//	for (int nCnt = 0; nCnt < m_nNumVtx; nCnt++)
//	{
//		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)m_pVtxBuff;//頂点座標の代入
//													//xの最大値の比較
//		if (m_vtxMax.x >= vtx.x)
//		{
//			m_vtxMax.x = vtx.x;
//		}
//		//ｘの最小値の比較
//		else if (m_vtxMin.x <= vtx.x)
//		{
//			m_vtxMin.x = vtx.x;
//		}
//		//yの最大値の比較
//		if (m_vtxMax.y >= vtx.y)
//		{
//			m_vtxMax.y = vtx.y;
//		}
//		//yの最小値の比較
//		else if (m_vtxMin.y <= vtx.y)
//		{
//			m_vtxMin.y = vtx.y;
//		}
//		//zの最大値の比較
//		if (m_vtxMax.z >= vtx.z)
//		{
//			m_vtxMax.z = vtx.z;
//		}
//		//zの最小値の比較
//		else if (m_vtxMin.z <= vtx.z)
//		{
//			m_vtxMin.z = vtx.z;
//		}
//		m_pVtxBuff += m_sizeFVF;//頂点フォーマットのサイズ分ポインタを進める
//	}
//	//頂点バッファをアンロック
//	m_pMesh->UnlockVertexBuffer();
//	//8つの頂点情報の保存
//	//左奥（上面）
//	m_vtx[0].vtx = D3DXVECTOR3(
//		-m_vtxMin.x,
//		m_vtxMin.y,
//		m_vtxMin.z);
//	//右奥（上面）
//	m_vtx[1].vtx = D3DXVECTOR3(
//		m_vtxMin.x,
//		m_vtxMin.y,
//		m_vtxMin.z);
//	//左前（上面）
//	m_vtx[2].vtx = D3DXVECTOR3(
//		-m_vtxMin.x,
//		m_vtxMin.y,
//		-m_vtxMin.z);
//	//右前（上面）
//	m_vtx[3].vtx = D3DXVECTOR3(
//		m_vtxMin.x,
//		m_vtxMin.y,
//		-m_vtxMin.z);
//	//左奥（下面）
//	m_vtx[4].vtx = D3DXVECTOR3(
//		-m_vtxMin.x,
//		-m_vtxMax.y,
//		m_vtxMin.z);
//	//右奥（下面）
//	m_vtx[5].vtx = D3DXVECTOR3(
//		m_vtxMin.x,
//		-m_vtxMax.y,
//		m_vtxMin.z);
//	//左前（下面）
//	m_vtx[6].vtx = D3DXVECTOR3(
//		-m_vtxMin.x,
//		-m_vtxMax.y,
//		-m_vtxMin.z);
//	//右前（下面）
//	m_vtx[7].vtx = D3DXVECTOR3(
//		m_vtxMin.x,
//		-m_vtxMax.y,
//		-m_vtxMin.z);
//
//}
//
////=============================================================================
//// ポリゴンの初期化処理
////=============================================================================
//void CStage_Total_Model::Init(void)
//{
//	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();//デバイスのポインタ
//
//																	 //Xファイルの読み込み
//	D3DXLoadMeshFromX(m_sFailName,
//		D3DXMESH_SYSTEMMEM,
//		pDevice,
//		NULL,
//		&m_pBuffMat,
//		NULL,
//		&m_nNumMat,
//		&m_pMesh);
//
//	//マテリアル情報に対するポインタを取得
//	m_pMat = (D3DXMATERIAL *)m_pBuffMat->GetBufferPointer();
//	//マテリアル情報を保存
//	m_pSaveMat = m_pMat;
//	for (int nCnt = 0; nCnt < (int)m_nNumMat; nCnt++)
//	{
//		if (m_pMat[nCnt].pTextureFilename != NULL)
//		{
//			//テクスチャの読み込み
//			D3DXCreateTextureFromFile
//			(pDevice,
//				m_pMat[nCnt].pTextureFilename,
//				&m_pTexture[nCnt]);
//		}
//	}
//	//頂点数を取得
//	m_nNumVtx = m_pMesh->GetNumVertices();
//	//頂点フォーマットのサイズを取得
//	m_sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());
//	//頂点バッファをアンロック
//	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&m_pVtxBuff);
//	//モデルの大きさを測る
//	for (int nCnt = 0; nCnt < m_nNumVtx; nCnt++)
//	{
//		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)m_pVtxBuff;//頂点座標の代入
//													//xの最大値の比較
//		if (m_vtxMax.x >= vtx.x)
//		{
//			m_vtxMax.x = vtx.x;
//		}
//		//ｘの最小値の比較
//		else if (m_vtxMin.x <= vtx.x)
//		{
//			m_vtxMin.x = vtx.x;
//		}
//		//yの最大値の比較
//		if (m_vtxMax.y >= vtx.y)
//		{
//			m_vtxMax.y = vtx.y;
//		}
//		//yの最小値の比較
//		else if (m_vtxMin.y <= vtx.y)
//		{
//			m_vtxMin.y = vtx.y;
//		}
//		//zの最大値の比較
//		if (m_vtxMax.z >= vtx.z)
//		{
//			m_vtxMax.z = vtx.z;
//		}
//		//zの最小値の比較
//		else if (m_vtxMin.z <= vtx.z)
//		{
//			m_vtxMin.z = vtx.z;
//		}
//		m_pVtxBuff += m_sizeFVF;//頂点フォーマットのサイズ分ポインタを進める
//	}
//	//頂点バッファをアンロック
//	m_pMesh->UnlockVertexBuffer();
//	//8つの頂点情報の保存
//	//左奥（上面）
//	m_vtx[0].vtx = D3DXVECTOR3(
//		-m_vtxMin.x,
//		m_vtxMin.y,
//		m_vtxMin.z);
//	//右奥（上面）
//	m_vtx[1].vtx = D3DXVECTOR3(
//		m_vtxMin.x,
//		m_vtxMin.y,
//		m_vtxMin.z);
//	//左前（上面）
//	m_vtx[2].vtx = D3DXVECTOR3(
//		-m_vtxMin.x,
//		m_vtxMin.y,
//		-m_vtxMin.z);
//	//右前（上面）
//	m_vtx[3].vtx = D3DXVECTOR3(
//		m_vtxMin.x,
//		m_vtxMin.y,
//		-m_vtxMin.z);
//	//左奥（下面）
//	m_vtx[4].vtx = D3DXVECTOR3(
//		-m_vtxMin.x,
//		-m_vtxMax.y,
//		m_vtxMin.z);
//	//右奥（下面）
//	m_vtx[5].vtx = D3DXVECTOR3(
//		m_vtxMin.x,
//		-m_vtxMax.y,
//		m_vtxMin.z);
//	//左前（下面）
//	m_vtx[6].vtx = D3DXVECTOR3(
//		-m_vtxMin.x,
//		-m_vtxMax.y,
//		-m_vtxMin.z);
//	//右前（下面）
//	m_vtx[7].vtx = D3DXVECTOR3(
//		m_vtxMin.x,
//		-m_vtxMax.y,
//		-m_vtxMin.z);
//
//
//}
//
////=============================================================================
//// ポリゴンの終了処理
////=============================================================================
//void CStage_Total_Model::Uninit(void)
//{
//	//メッシュの破棄
//	if (m_pMesh != NULL)
//	{
//		m_pMesh->Release();
//		m_pMesh = NULL;
//	}
//	//マテリアルの破棄
//	if (m_pBuffMat != NULL)
//	{
//		m_pBuffMat->Release();
//		m_pBuffMat = NULL;
//	}
//
//	for (int nTex = 0; nTex < MAX_STAGE_TOTAL_MODEL_TEX; nTex++)
//	{
//		if (m_pTexture[nTex] != NULL)
//		{
//			m_pTexture[nTex]->Release();
//			m_pTexture[nTex] = NULL;
//		}
//	}
//}
//
////=============================================================================
//// ポリゴンの更新処理
////=============================================================================
//void CStage_Total_Model::Update(void)
//{
//
//}
//
////=============================================================================
//// ポリゴンの描画処理
////=============================================================================
//void CStage_Total_Model::Draw(void)
//{
//	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();//デバイスのポインタ
//
//																	 //現在のマテリアルを取得
//	D3DXMATRIX mtxRotModel, mtxTransModel, mtxScale;//計算用マトリックス
//	D3DXMATRIX mtxParent;//親のマトリックス
//	D3DMATERIAL9 Matdef;
//	//各パーツのワールドマトリックスの初期化
//	D3DXMatrixIdentity(&m_mtxWorld);
//	//サイズ変更
//	D3DXMatrixScaling(&mtxScale, m_scale.x, m_scale.y, m_scale.z);
//	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);
//
//	D3DXMatrixRotationYawPitchRoll(&mtxRotModel, m_rot.y, m_rot.x, m_rot.z);
//	////向きを反映
//	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRotModel);
//	//位置を反映
//	D3DXMatrixTranslation(&mtxTransModel, m_pos.x, m_pos.y, m_pos.z);
//	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTransModel);
//	pDevice->GetMaterial(&Matdef);
//
//	//書くパーツの親のマトリックスを設定
//	if (m_pParent != NULL)
//	{
//		mtxParent = m_pParent->GetMatrix();
//	}
//	else
//	{
//		//最新のマトリックスを取得
//		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
//	}
//
//	//算出した各パーツのワールドマトリックスと親のマトリックスを掛け合わせる
//	D3DXMatrixMultiply(&m_mtxWorld,
//		&m_mtxWorld,
//		&mtxParent);
//	//各パーツのワールドマトリックスの設定
//	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
//
//	if (m_bDraw == false)
//	{
//		//マテリアルデータ編のポインタを取得
//		m_pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();
//
//		for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
//		{
//			//マテリアルの設定
//			pDevice->SetMaterial(&m_pMat[nCntMat].MatD3D);
//			//テクスチャの設定
//			pDevice->SetTexture(0, m_pTexture[nCntMat]);
//			//モデル（パーツ）の描画
//			m_pMesh->DrawSubset(nCntMat);
//		}
//		//保存していたマテリアルを戻す
//		pDevice->SetMaterial(&Matdef);
//
//	}
//
//}
////=============================================================================
//// ポリゴンの描画処理
////=============================================================================
//void CStage_Total_Model::SetDiffuse(float DiffuseA)
//{
//	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();//デバイスのポインタ
//																	 //マテリアルデータ編のポインタを取得
//	m_pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();
//
//	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
//	{
//		m_pMat[nCntMat].MatD3D.Diffuse.a = DiffuseA;
//		//マテリアルの設定
//		pDevice->SetMaterial(&m_pMat[nCntMat].MatD3D);
//	}
//
//}
////---------------------------------------------------------------
////インスタンス生成処理
////---------------------------------------------------------------
//CStage_Total_Model *CStage_Total_Model::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *sModelFailName, D3DXVECTOR3 scale)
//{
//	//インスタンス生成
//	CStage_Total_Model *pModel = new CStage_Total_Model;
//	if (pModel != NULL)
//	{
//		strcpy(pModel->m_sFailName, sModelFailName);
//		pModel->Init();
//	}
//	pModel->m_pos = pos;
//	pModel->m_rot = rot;
//	pModel->m_scale = scale;
//	return pModel;
//}
