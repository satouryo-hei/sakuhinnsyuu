//=============================================================================
//
// ポリゴンの処理 [scene3D.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include"scene3D.h"
#include"renderer.h"
#include"manager.h"


//=============================================================================
// ポリゴンのコンストラクタ
//=============================================================================
CScene3D::CScene3D(PRIORITY Priority) : CScene(Priority)
{
	m_pTexTure = NULL;
	m_pVlxBuff = NULL;
	m_pIdxBuff = NULL;
	memset(&m_mtxWorld, NULL, sizeof(m_mtxWorld));
	m_pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
	m_Size = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
}


//=============================================================================
//　ポリゴンのデストラクタ
//=============================================================================
CScene3D::~CScene3D()
{

}

//=============================================================================
// テクスチャの初期化処理
//=============================================================================
void CScene3D::BindTextuer(CTexture::Tex type)
{
	m_pTexTure = CManager::GetTexture()->GetTex(type);
}

//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
CScene3D *CScene3D::Creste(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene3D* pScene3D;

	pScene3D = new CScene3D;

	if (pScene3D != NULL)
	{
		pScene3D->Init(pos, size);
	}
	return pScene3D;
}


//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
HRESULT CScene3D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 Size)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice = NULL;

	CManager*pManager = NULL;

	//デバイスの取得
	pDevice = pManager->GetRenderer()->GetDevice();

	m_pos = pos;
	m_Size = Size;

	BindTextuer(CTexture::Tex_Fild);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVlxBuff,
		NULL);

	//頂点情報へのポインタ
	VERTEX_3D*pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVlxBuff->Lock(0, 0, (void **)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_Size.x, m_pos.y + m_Size.y, m_pos.z + m_Size.z);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_Size.x, m_pos.y + m_Size.y, m_pos.z + m_Size.z);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_Size.x, m_pos.y + m_Size.y, m_pos.z - m_Size.z);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_Size.x, m_pos.y + m_Size.y, m_pos.z - m_Size.z);

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
	m_pVlxBuff->Unlock();
/*
	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * 14,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	WORD*pIdx; //インデックス情報へのポインタ

			   //インデックスバッファをロックし番号データへのポインタを取得
	m_pIdxBuff->Lock(0, 0, (void **)&pIdx, 0);

	//番号データの設定
	pIdx[0] = 3;
	pIdx[1] = 0;
	pIdx[2] = 4;
	pIdx[3] = 1;
	pIdx[4] = 5;
	pIdx[5] = 2;
	pIdx[6] = 2;
	pIdx[7] = 6;
	pIdx[8] = 6;
	pIdx[9] = 3;
	pIdx[10] = 7;
	pIdx[11] = 4;
	pIdx[12] = 8;
	pIdx[13] = 5;

	//インデックスバッファをアンロックする
	m_pIdxBuff->Unlock();
*/
	return S_OK;
}	// ポリゴンの初期化処理終了



	//=============================================================================
	// ポリゴンの終了処理
	//=============================================================================
void CScene3D::Uninit(void)
{
	//バッファの破棄
	if (m_pVlxBuff != NULL)
	{
		m_pVlxBuff->Release();
		m_pVlxBuff = NULL;
	}
	//オブジェクトの破棄
	Release();

}// ポリゴンの終了処理終了


 //=============================================================================
 // ポリゴンの更新処理
 //=============================================================================
void CScene3D::Update(void)
{

}// ポリゴンの更新処理終了


 //=============================================================================
 // ポリゴンの描画処理
 //=============================================================================
void CScene3D::Draw(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice = NULL;

	CManager*pManager = NULL;

	//デバイスを取得する
	pDevice = pManager->GetRenderer()->GetDevice();

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
	pDevice->SetStreamSource(0, m_pVlxBuff, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	//pDevice->SetTexture(0, m_pTexTure[m_Typ]);
	pDevice->SetTexture(0, m_pTexTure);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0, 2);
}	// ポリゴンの描画処理終了