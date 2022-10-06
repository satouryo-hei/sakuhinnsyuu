//=============================================================================
//
// オブジェクト2Dの処理 [scene2D.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include"scene2D.h"
#include"renderer.h"
#include"manager.h"
#include"texture.h"

//=============================================================================
// オブジェクト2Dのコンストラクタ
//=============================================================================
CScene2D::CScene2D()
{
	m_pTexTure = NULL;
	m_pVlxBuff = NULL;			
	m_pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
	m_Size = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
}


//=============================================================================
// オブジェクト2Dのデストラクタ
//=============================================================================
CScene2D::~CScene2D()
{

}

//=============================================================================
// オブジェクト2Dのテクスチャの設定処理
//=============================================================================
void CScene2D::BindTextuer(int nTex)
{
	m_pTexTure = CManager::GetTexture()->GetTex(nTex);
}

//=============================================================================
// オブジェクト2Dのデフォルト初期化処理
//=============================================================================
HRESULT CScene2D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 Size)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice = NULL;

	CManager*pManager = NULL;
	
	//デバイスの取得
	pDevice = pManager->GetRenderer()->GetDevice();

	m_pos = pos;	
	m_Size = Size;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVlxBuff,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVlxBuff->Lock(0, 0, (void **)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_Size.x, m_pos.y - m_Size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_Size.x, m_pos.y - m_Size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_Size.x, m_pos.y + m_Size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_Size.x, m_pos.y + m_Size.y, 0.0f);

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
	m_pVlxBuff->Unlock();

	return S_OK;
}	// ポリゴンの初期化処理終了


//=============================================================================
// オブジェクト2Dの動く系の初期化処理
//=============================================================================
HRESULT CScene2D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 Size)
{
	CScene2D::Init(pos,Size);
	m_Move = move;
	return S_OK;
}

//=============================================================================
// オブジェクト2Dの終了処理
//=============================================================================
void CScene2D::Uninit(void)
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
// オブジェクト2Dの更新処理
//=============================================================================
void CScene2D::Update(void)
{		
	//頂点情報へのポインタ
	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVlxBuff->Lock(0, 0, (void **)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_Size.x, m_pos.y - m_Size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_Size.x, m_pos.y - m_Size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_Size.x, m_pos.y + m_Size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_Size.x, m_pos.y + m_Size.y, 0.0f);

	//頂点バッファをアンロックする
	m_pVlxBuff->Unlock();

}// ポリゴンの更新処理終了

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CScene2D::Draw(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice = NULL;
	
	// デバイスの取得
	pDevice = CManager::GetRenderer()->GetDevice();

	pDevice->SetStreamSource(0, m_pVlxBuff, 0, sizeof(VERTEX_2D));//
																  // 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexTure);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0, 2);
}	// ポリゴンの描画処理終了

//=============================================================================
// テクスチャの色の設定処理
//=============================================================================
void CScene2D::SetColor(D3DXCOLOR col)
{
	//頂点情報へのポインタ
	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVlxBuff->Lock(0, 0, (void **)&pVtx, 0);

	//頂点カラー
	pVtx[0].col = D3DXCOLOR(col);
	pVtx[1].col = D3DXCOLOR(col);
	pVtx[2].col = D3DXCOLOR(col);
	pVtx[3].col = D3DXCOLOR(col);

	//頂点バッファをアンロックする
	m_pVlxBuff->Unlock();
}

//=============================================================================
// アニメーションのテクスチャ設定処理
//=============================================================================
void CScene2D::SetTexAnime(int nPatternAnim, float fSizeAnimU, float fSizeMinV, float fSizeMaxV)
{
	//頂点情報へのポインタ
	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVlxBuff->Lock(0, 0, (void **)&pVtx, 0);

	//テクスチャ座標 
	pVtx[0].tex = D3DXVECTOR2(nPatternAnim*fSizeAnimU, fSizeMinV);
	pVtx[1].tex = D3DXVECTOR2(nPatternAnim*fSizeAnimU + fSizeAnimU, fSizeMinV);
	pVtx[2].tex = D3DXVECTOR2(nPatternAnim*fSizeAnimU, fSizeMaxV);
	pVtx[3].tex = D3DXVECTOR2(nPatternAnim*fSizeAnimU + fSizeAnimU, fSizeMaxV);

	//頂点バッファをアンロックする
	m_pVlxBuff->Unlock();
}

//=============================================================================
// テクスチャ設定処理
//=============================================================================
void CScene2D::SetTex(float fSizeMin, float fSizeMax)
{
	//頂点情報へのポインタ
	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVlxBuff->Lock(0, 0, (void **)&pVtx, 0);

	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(fSizeMin, fSizeMin);
	pVtx[1].tex = D3DXVECTOR2(fSizeMax, fSizeMin);
	pVtx[2].tex = D3DXVECTOR2(fSizeMin, fSizeMax);
	pVtx[3].tex = D3DXVECTOR2(fSizeMax, fSizeMax);

	//頂点バッファをアンロックする
	m_pVlxBuff->Unlock();
}