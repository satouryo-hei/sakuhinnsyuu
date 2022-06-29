//=============================================================================
//
// 数字の処理 [number.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include "number.h"
#include"manager.h"
#include"renderer.h"
#include"scene2D.h"
#include"texture.h"

//=============================================================================
// 静的メンバ変数の宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CNumber::m_pTexture = NULL;

//=============================================================================
// 数字のコンストラクタ
//=============================================================================
CNumber::CNumber()
{
	m_pVtxBuff = NULL;
}

//=============================================================================
// 数字のデストラクタ
//=============================================================================
CNumber::~CNumber()
{

}

//=============================================================================
// 数字の生成処理
//=============================================================================
CNumber *CNumber::Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size, int nNum)
{
	// 数字のポインター生成
	CNumber *pNumber = NULL;

	// 動的メモリの確保
	pNumber = new CNumber;

	// NULLチェック
	if (pNumber != NULL)
	{
		// 数字の初期化処理を呼び出し
		pNumber->Init(pos, Size);
		// 数字のテクスチャの設定処理を呼び出し
		pNumber->BindTextuer(nNum);
	}
	return pNumber;
}

//=============================================================================
// テクスチャの設定
//=============================================================================
void CNumber::BindTextuer(int nTextuer)
{
	m_pTexture = CManager::GetTexture()->GetTex(nTextuer);
}

//=============================================================================
// 数字の初期化処理
//=============================================================================
HRESULT CNumber::Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice = NULL;

	//デバイスの取得
	pDevice = CManager::GetRenderer()->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void **)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(pos.x - Size.x, pos.y - Size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + Size.x, pos.y - Size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - Size.x, pos.y + Size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + Size.x, pos.y + Size.y, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

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
}

//=============================================================================
// 数字の終了処理
//=============================================================================
void CNumber::Uninit(void)
{
	////テクスチャの破棄
	//if (m_pTexture != NULL)
	//{
	//	m_pTexture->Release();
	//	m_pTexture = NULL;
	//}

	//バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//=============================================================================
// 数字の更新処理
//=============================================================================
void CNumber::Update(void)
{

}


//=============================================================================
// 数字の描画処理
//=============================================================================
void CNumber::Draw(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice = NULL;

	// デバイスの取得
	pDevice = CManager::GetRenderer()->GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0, 2);
}

//=============================================================================
// 数字の配置処理
//=============================================================================
void CNumber::SetNumber(int nNumber)
{
	// テクスチャのU座標の設定変数
	static const float fTexU = 0.1f;

	//頂点情報へのポインタ
	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void **)&pVtx, 0);

	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(fTexU*nNumber, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(fTexU*nNumber + fTexU, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(fTexU*nNumber, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(fTexU*nNumber + fTexU, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================================
// 数字の色の設定処理
//=============================================================================
void CNumber::SetColor(D3DXCOLOR col)
{
	//頂点情報へのポインタ
	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void **)&pVtx, 0);

	//頂点カラー
	pVtx[0].col = D3DXCOLOR(col);
	pVtx[1].col = D3DXCOLOR(col);
	pVtx[2].col = D3DXCOLOR(col);
	pVtx[3].col = D3DXCOLOR(col);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}