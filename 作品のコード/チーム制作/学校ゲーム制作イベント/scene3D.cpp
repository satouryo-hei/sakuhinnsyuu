//=============================================================================
//
// 3Dオブジェクトの処理 [scene3D.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include"scene3D.h"
#include"renderer.h"
#include"manager.h"
#include"texture.h"

//=============================================================================
// 3Dオブジェクトのコンストラクタ
//=============================================================================
CScene3D::CScene3D(PRIORITY Priority) : CScene(Priority)
{
	m_pTexTure = NULL;
	m_pVtxBuff = NULL;
	memset(&m_mtxWorld, NULL, sizeof(m_mtxWorld));
	m_pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
	m_Size = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
}


//=============================================================================
//　3Dオブジェクトのデストラクタ
//=============================================================================
CScene3D::~CScene3D()
{

}

#if 0
//=============================================================================
// 3Dオブジェクトの生成処理
//=============================================================================
CScene3D *CScene3D::Creste(D3DXVECTOR3 pos, D3DXVECTOR3 size, , D3DXVECTOR3 rot)
{
	CScene3D* pScene3D;

	pScene3D = new CScene3D;

	if (pScene3D != NULL)
	{
		pScene3D->Init(pos, size,rot);
		pScene3D->BindTextuer(0);
	}
	return pScene3D;
}
#endif // 0

//=============================================================================
// 3Dオブジェクトのテクスチャの設定
//=============================================================================
void CScene3D::BindTextuer(int nTex)
{
	m_pTexTure = CManager::GetTexture()->GetTex(nTex);
}

//=============================================================================
// 3Dオブジェクトのデフォルト初期化処理
//=============================================================================
HRESULT CScene3D::Init(D3DXVECTOR3 pos)
{
	m_pos = pos;
	return S_OK;
}

//=============================================================================
// 3Dオブジェクトの初期化処理
//=============================================================================
HRESULT CScene3D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 Size, D3DXVECTOR3 Rot)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice = NULL;

	//デバイスの取得
	pDevice = CManager::GetRenderer()->GetDevice();

	Init(pos);
	m_Size = Size;
	m_rot = Rot;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//頂点情報へのポインタ
	VERTEX_3D*pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void **)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3( - m_Size.x, + m_Size.y, + m_Size.z);
	pVtx[1].pos = D3DXVECTOR3( + m_Size.x, + m_Size.y, + m_Size.z);
	pVtx[2].pos = D3DXVECTOR3( - m_Size.x, 0.0f, - m_Size.z);
	pVtx[3].pos = D3DXVECTOR3( + m_Size.x, 0.0f, - m_Size.z);

	//法線ベクトル
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//頂点カラー
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}	// ポリゴンの初期化処理終了



//=============================================================================
// 3Dオブジェクトの終了処理
//=============================================================================
void CScene3D::Uninit(void)
{
	//バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//オブジェクトの破棄
	Release();

}// ポリゴンの終了処理終了


 //=============================================================================
 // 3Dオブジェクトの更新処理
 //=============================================================================
void CScene3D::Update(void)
{

}// ポリゴンの更新処理終了


 //=============================================================================
 // 3Dオブジェクトの描画処理
 //=============================================================================
void CScene3D::Draw(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice = NULL;

	//デバイスを取得する
	pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;//計算用のマトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexTure);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0, 2);
}	// ポリゴンの描画処理終了

//=============================================================================
// 3Dオブジェクトの法線ベクトルを設定関数
//=============================================================================
void CScene3D::SetNorVector(D3DXVECTOR3 nor)
{
	//頂点情報へのポインタ
	VERTEX_3D*pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void **)&pVtx, 0);

	//法線ベクトル
	pVtx[0].nor = nor;
	pVtx[1].nor = nor;
	pVtx[2].nor = nor;
	pVtx[3].nor = nor;

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}


//=============================================================================
// アニメーションのテクスチャ配置処理
//=============================================================================
void CScene3D::SetTexAnime(int nPatternAnim, float fSizeAnimU, float fSizeMinV, float fSizeMaxV)
{
	//頂点情報へのポインタ
	VERTEX_3D*pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void **)&pVtx, 0);

	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(nPatternAnim * fSizeAnimU, fSizeMinV);
	pVtx[1].tex = D3DXVECTOR2(nPatternAnim * fSizeAnimU + fSizeAnimU, fSizeMinV);
	pVtx[2].tex = D3DXVECTOR2(nPatternAnim * fSizeAnimU, fSizeMaxV);
	pVtx[3].tex = D3DXVECTOR2(nPatternAnim * fSizeAnimU + fSizeAnimU, fSizeMaxV);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}