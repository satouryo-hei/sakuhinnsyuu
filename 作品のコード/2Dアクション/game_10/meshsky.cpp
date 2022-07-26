//=============================================================================
//
// メッシュの空の処理 [meshsky.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include"meshsky.h"
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"scene3D.h"
#include"texture.h"

//=============================================================================
// 静的メンバ変数の宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CMeshSky::m_pTexTure = NULL;

//=============================================================================
// メッシュの空のコンストラクタ
//=============================================================================
CMeshSky::CMeshSky(PRIORITY Priority) : CScene(Priority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nMeshX =0;
	m_nMeshY =0;
}

//=============================================================================
//　メッシュの空のデストラクタ
//=============================================================================
CMeshSky::~CMeshSky()
{

}


//=============================================================================
// メッシュの空の生成処理
//=============================================================================
CMeshSky *CMeshSky::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, int meshX, int meshY)
{
	// メッシュの空のポインター生成
	CMeshSky* pMeshSky = NULL;

	// 動的メモリの確保
	pMeshSky = new CMeshSky;

	//　NULLチェック
	if (pMeshSky != NULL)
	{
		pMeshSky->Init(pos, size, meshX, meshY);
		pMeshSky->m_rot = rot;
	}
	return pMeshSky;
}

//=============================================================================
// メッシュの空のデフォルト初期化処理
//=============================================================================
HRESULT CMeshSky::Init(D3DXVECTOR3 pos)
{
	m_pos = pos;
	return S_OK;
}
//=============================================================================
// ポリゴンの初期化処理
//=============================================================================								
HRESULT CMeshSky::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, int meshX, int meshY)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice = NULL;

	//デバイスの取得
	pDevice = CManager::GetRenderer()->GetDevice();

	//頂点情報を入力(X,Y,Z)
	m_Size = size;

	Init(pos);

	BindTextuer(2);

	m_nMeshX = meshX;
	m_nMeshY = meshY;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * ((meshX + 1) * (meshY + 1)) * 1,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//頂点情報へのポインタ
	VERTEX_3D*pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void **)&pVtx, 0);

	int nNum = 0;
	for (int nCntY = 0; nCntY < meshY + 1; nCntY++)
	{
		for (int nCntX = 0; nCntX < meshX + 1; nCntX++, nNum++)
		{
			pVtx[nNum].pos = D3DXVECTOR3(
				cos((D3DX_PI * 2 / meshX) * nCntX) * (sin(((D3DX_PI * 2 / meshX) * nCntY) + ((D3DX_PI * 2 / meshX) * meshY)) * (size.x / 2.0f)),
				sin((D3DX_PI * 2 / meshX) * nCntY) * (size.x / 2.0f),
				(sin((D3DX_PI * 2 / meshX) * nCntX) * (sin(((D3DX_PI * 2 / meshX) * nCntY) + ((D3DX_PI * 2 / meshX) * meshY)) * (size.x / 2.0f))));


			pVtx[nNum].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
			pVtx[nNum].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			pVtx[nNum].tex = D3DXVECTOR2(0.0f + (1.0f / meshX * nCntX), 0.0f + (1.0f / meshY * nCntY));
		}
	}

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * ((meshY - 1) * (meshX + 3) + (meshX + 1) * (meshY + 1)),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);


	WORD*pIdx; //インデックス情報へのポインタ

			   //インデックスバッファをロックし番号データへのポインタを取得
	m_pIdxBuff->Lock(0, 0, (void **)&pIdx, 0);

	/*インデックス数を求める公式
	(全ての頂点数)+(かぶり頂点数)
	((x+1)*(z+1))+((x+3)*(z-1)) */
	for (int nCntZ = 0; nCntZ < meshY; nCntZ++)
	{
		for (int nCntX = 0; nCntX < meshX + 1; nCntX++)
		{
			//番号データの設定
			pIdx[(nCntX * 2) + 0 + (meshX + 2) * 2 * nCntZ] = (meshX + 1) + nCntX + (meshX + 1) * nCntZ;
			pIdx[(nCntX * 2) + 1 + (meshX + 2) * 2 * nCntZ] = 0 + nCntX + (meshX + 1) * nCntZ;
		}
	}
	for (int nCntY = 0; nCntY < meshY - 1; nCntY++)
	{
		pIdx[((meshX + 1) * 2 + 0) * (nCntY + 1) + (2 * nCntY)] = meshX + (meshX + 1) * nCntY;
		pIdx[((meshX + 1) * 2 + 1) * (nCntY + 1) + (1 * nCntY)] = meshX * 2 + 2 + (meshX + 1) * nCntY;
	}

	//インデックスバッファをアンロックする
	m_pIdxBuff->Unlock();

	return S_OK;

}

//=============================================================================
// メッシュの空の終了処理
//=============================================================================
void CMeshSky::Uninit(void)
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
// メッシュの空の更新処理
//=============================================================================
void CMeshSky::Update(void)
{
	m_rot.y += 0.0005f;
	if (m_rot.y >= D3DX_PI)
	{
		m_rot.y = -D3DX_PI;
	}
}

//=============================================================================
// メッシュの空の描画処理
//=============================================================================								
void CMeshSky::Draw(void)
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
	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, (m_nMeshY - 1) * (m_nMeshX + 3) + (m_nMeshX + 1) * (m_nMeshY + 1));

	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
		0,
		0,
		((m_nMeshX + 1) * (m_nMeshY + 1)),					//頂点の数
		0,													//開始する頂点のインデックス
		2 * m_nMeshX * m_nMeshY + (m_nMeshY * 4) - 4);		//描画するプリミティブ数
}

//=============================================================================
// メッシュの空のテクスチャの設定
//=============================================================================
void CMeshSky::BindTextuer(int nTextuer)
{
	m_pTexTure = CManager::GetTexture()->GetTex(nTextuer);
}