//=============================================================================
//
// ビルボード処理 [billboard.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include "billboard.h"
#include "input.h"
#include "renderer.h"
#include "manager.h"
#include"scene3D.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CBillboard::CBillboard(PRIORITY nPriority) :CScene(nPriority)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CBillboard::~CBillboard()
{

}
//=============================================================================
//　ビルボードのテクスチャの設定
//=============================================================================
void CBillboard::BindTextuer(int type)
{
	m_pTexture = CManager::GetTexture()->GetTex(type);
}
//=============================================================================
//　ビルボードの生成
//=============================================================================
CBillboard *CBillboard::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	// ビルボードのポインター生成
	CBillboard* pBillboard = NULL;

	// 動的メモリの確保
	pBillboard = new CBillboard;

	// NULLチェック
	if (pBillboard != NULL)
	{
		// ビルボードの初期化処理の呼び出し
		pBillboard->Init(pos, size);
		pBillboard->BindTextuer(0);
	}
	return pBillboard;
}

//=============================================================================
// ビルボードのデフォルト初期化処理
//=============================================================================
HRESULT CBillboard::Init(D3DXVECTOR3 pos)
{
	m_pos = pos;
	return S_OK;
}

//=============================================================================
// ビルボードの初期化処理
//=============================================================================
HRESULT CBillboard::Init(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	// ビルボードのデフォルト初期化処理の呼び出し
	Init(pos);
	m_size = size;

	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();//デバイスのポインタ

	 // 頂点情報を設定
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//頂点情報へのポインタ
	VERTEX_3D *pVtx;
	
	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(- m_size.x, + m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+ m_size.x, + m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(- m_size.x, - m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+ m_size.x, - m_size.y, 0.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0, 0.0);
	pVtx[1].tex = D3DXVECTOR2(1.0, 0.0);
	pVtx[2].tex = D3DXVECTOR2(0.0, 1.0);
	pVtx[3].tex = D3DXVECTOR2(1.0, 1.0);

	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// ビルボードの終了処理
//=============================================================================
void CBillboard::Uninit(void)
{
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	////頂点バッファの破棄
	//if (m_pTexture != NULL)
	//{
	//	m_pTexture->Release();
	//	m_pTexture = NULL;
	//}

	// 解放処理
	Release();
}

//=============================================================================
// ビルボードの更新処理
//=============================================================================
void CBillboard::Update(void)
{
}

//=============================================================================
// ビルボードの描画処理
//=============================================================================
void CBillboard::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();//デバイスのポインタ
	D3DXMATRIX mtxRot,mtxTrans;//計算用マトリックス
	D3DXMATRIX mtxView;									// ビューマトリックス

								//ライト無効
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//アルファテスト関係
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//Zテスト関係
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//ビューマトリックスの取得
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//ポリゴンをカメラに対して正面に向ける
	D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxView); //逆行列を求める

	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);		// m_mtxWorld = m_mtxWorld * mtxTrans 行列を掛け合わせる
	
	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
	pDevice->SetFVF(FVF_VERTEX_3D);//頂点フォーマットの設定

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);

	////Zテスト関係
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//アルファテスト関係
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);

	//ライトをもとに戻す
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}

//=============================================================================
// ビルボードの位置設定処理
//=============================================================================
void  CBillboard::SetPosSize(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	m_pos = pos;

	VERTEX_3D *pVtx = NULL;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(- size.x, + size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+ size.x, + size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(- size.x, - size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+ size.x, - size.y, 0.0f);

	m_pVtxBuff->Unlock();
}

//=============================================================================
// ビルボードの（1.0f最大）色の設定処理
//=============================================================================
void CBillboard::SetColor(D3DXCOLOR col)
{
	VERTEX_3D *pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
	pVtx[1].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
	pVtx[2].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
	pVtx[3].col = D3DXCOLOR(col.r, col.g, col.b, col.a);

	m_pVtxBuff->Unlock();

}

//=============================================================================
// ビルボードの（255最大）色の設定処理
//=============================================================================
void CBillboard::SetColor(int nRad, int nGreen, int nBlue, int nAlpha)
{
	VERTEX_3D *pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].col = D3DCOLOR_RGBA(nRad, nGreen, nBlue, nAlpha);
	pVtx[1].col = D3DCOLOR_RGBA(nRad, nGreen, nBlue, nAlpha);
	pVtx[2].col = D3DCOLOR_RGBA(nRad, nGreen, nBlue, nAlpha);
	pVtx[3].col = D3DCOLOR_RGBA(nRad, nGreen, nBlue, nAlpha);

	m_pVtxBuff->Unlock();

}

//=============================================================================
// アニメーションのテクスチャ配置処理
//=============================================================================
void CBillboard::SetTexAnime(int nPatternAnim, float fSizeAnimU, float fSizeMinV, float fSizeMaxV)
{
	//頂点情報へのポインタ
	VERTEX_3D*pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void **)&pVtx, 0);

	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(nPatternAnim*fSizeAnimU, fSizeMinV);
	pVtx[1].tex = D3DXVECTOR2(nPatternAnim*fSizeAnimU + fSizeAnimU, fSizeMinV);
	pVtx[2].tex = D3DXVECTOR2(nPatternAnim*fSizeAnimU, fSizeMaxV);
	pVtx[3].tex = D3DXVECTOR2(nPatternAnim*fSizeAnimU + fSizeAnimU, fSizeMaxV);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}