//=============================================================================
//
// メッシュフィールドの処理 [meshfield.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include"meshfield.h"
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"scene3D.h"
#include"texture.h"

//=============================================================================
// 静的メンバ変数の宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CMeshField::m_pTexTure = NULL;

//=============================================================================
// メッシュフィールドのコンストラクタ
//=============================================================================
CMeshField::CMeshField(PRIORITY Priority) : CScene(Priority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot =	D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
//　メッシュフィールドのデストラクタ
//=============================================================================
CMeshField::~CMeshField()
{

}


//=============================================================================
// メッシュフィールドの生成処理
//=============================================================================
CMeshField *CMeshField::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// メッシュフィールドのポインター生成
	CMeshField* pMeshField = NULL;

	// 動的メモリの確保
	pMeshField = new CMeshField;

	// NULLチェック
	if (pMeshField != NULL)
	{
		// 初期化処理の呼び出し
		pMeshField->Init(pos, size);
	}
	return pMeshField;
}

//=============================================================================
// メッシュフィールドのデフォルト初期化処理
//=============================================================================
HRESULT CMeshField::Init(D3DXVECTOR3 pos)
{
	m_pos = pos;
	return S_OK;
}
//=============================================================================
// メッシュフィールドの初期化処理
//=============================================================================								
HRESULT CMeshField::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice = NULL;

	//デバイスの取得
	pDevice = CManager::GetRenderer()->GetDevice();

	//頂点情報を入力(X,Y,Z)
	m_Size = size;

	Init(pos);

	BindTextuer(24);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 9,
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
	pVtx[0].pos = D3DXVECTOR3(- m_Size.x, + m_Size.y, + m_Size.z);
	pVtx[1].pos = D3DXVECTOR3(0.0f, + m_Size.y,+ m_Size.z);
	pVtx[2].pos = D3DXVECTOR3(+ m_Size.x, + m_Size.y, + m_Size.z);
							  
	pVtx[3].pos = D3DXVECTOR3( - m_Size.x, + m_Size.y, 0.0f);
	pVtx[4].pos = D3DXVECTOR3(0.0f,  + m_Size.y, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(+ m_Size.x, + m_Size.y, 0.0f);
							  
	pVtx[6].pos = D3DXVECTOR3( - m_Size.x, + m_Size.y, - m_Size.z);
	pVtx[7].pos = D3DXVECTOR3(0.0f,  + m_Size.y, - m_Size.z);
	pVtx[8].pos = D3DXVECTOR3( + m_Size.x, + m_Size.y, - m_Size.z);

	//法線ベクトル
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[4].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[5].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[6].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[7].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[8].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//頂点カラー
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[8].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(2.0f, 0.0f);
	pVtx[3].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[4].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[5].tex = D3DXVECTOR2(2.0f, 1.0f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 2.0f);
	pVtx[7].tex = D3DXVECTOR2(1.0f, 2.0f);
	pVtx[8].tex = D3DXVECTOR2(2.0f, 2.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

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

	return S_OK;

}

//=============================================================================
// メッシュフィールドの終了処理
//=============================================================================
void CMeshField::Uninit(void)
{
	//バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//インデックスバッファの破棄
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}

	Release();
}

//=============================================================================
// メッシュフィールドの更新処理
//=============================================================================
void CMeshField::Update(void)
{
}

//=============================================================================
// メッシュフィールドの描画処理
//=============================================================================								
void CMeshField::Draw(void)
{	
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice = NULL;

	D3DXMATRIX mtxRot, mtxTrans;//計算用のマトリックス

	//CManager*pManager = NULL;

	//デバイスを取得する
	pDevice = CManager::GetRenderer()->GetDevice();

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

	//インデックスバッファをデバイスのデータストリームに設定
	pDevice->SetIndices(m_pIdxBuff);

	pDevice->SetFVF(FVF_VERTEX_3D);//頂点フォーマットの設定

								   //テクスチャの設定
	pDevice->SetTexture(0, m_pTexTure);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 14);

	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 9, 0, 14);
}


//((x+1)*(z+1))*1,
//インデックス数を求める公式
//(全ての頂点数)+(かぶり頂点数)
//((x+1)*(z+1))+((x+3)*(z-1))

//=============================================================================
// メッシュフィールドのテクスチャの設定
//=============================================================================
void CMeshField::BindTextuer(int nTextuer)
{
	m_pTexTure = CManager::GetTexture()->GetTex(nTextuer);
}