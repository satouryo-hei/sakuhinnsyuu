//=============================================================================
//
// ポリゴンの処理 [scene2D.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include"scene2D.h"
#include"renderer.h"
#include"manager.h"


//=============================================================================
// ポリゴンのコンストラクタ
//=============================================================================
CScene2D::CScene2D(int nPriority) : CScene(nPriority)
{
	m_pTexTure = NULL;
	m_pVlxBuff = NULL;			
	m_pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
	m_Size = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	m_fRoll = 0;
	m_fHypot = 0;
	m_fAngle = 0;
	m_bAdd = true;
}


//=============================================================================
//　ポリゴンのデストラクタ
//=============================================================================
CScene2D::~CScene2D()
{

}


//=============================================================================
// ポリゴンのデフォルト初期化処理
//=============================================================================
HRESULT CScene2D::Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice = NULL;

	CManager*pManager = NULL;
	
	//デバイスの取得
	pDevice = pManager->GetRenderer()->GetDevice();

	m_pos = pos;	
	m_Size = Size;

	m_fAngle = atan2f(1.0f, 1.0f);											//角度を求めるために１回しか使わない（ラジアン//m_fAngleに角度を代入m_fAngleは角度
	m_fHypot = sqrtf(powf(m_Size.x, 2.0f) + powf(m_Size.y, 2.0f));					//斜辺を求める

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
// ポリゴンの動く系の初期化処理
//=============================================================================
HRESULT CScene2D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size)
{
	CScene2D::Init(pos,Size);
	m_Move = move;
	return S_OK;
}

//=============================================================================
// ポリゴンの終了処理
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
	Relese();

}// ポリゴンの終了処理終了


//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CScene2D::Update(void)
{		
	//頂点情報へのポインタ
	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVlxBuff->Lock(0, 0, (void **)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_Size.x*cosf(m_fAngle - m_fRoll), m_pos.y - m_Size.y*sinf(m_fAngle - m_fRoll), 0.0f);//ｘ＝半径＊cosf(角度)※角度=g_fAngle
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_Size.x*cosf(m_fAngle + m_fRoll), m_pos.y - m_Size.y*sinf(m_fAngle + m_fRoll), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_Size.x*cosf(m_fAngle + m_fRoll), m_pos.y + m_Size.y*sinf(m_fAngle + m_fRoll), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_Size.x*cosf(m_fAngle - m_fRoll), m_pos.y + m_Size.y*sinf(m_fAngle - m_fRoll), 0.0f);

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

	CManager*pManager = NULL;
	
	pDevice = pManager->GetRenderer()->GetDevice();

	pDevice->SetStreamSource(0, m_pVlxBuff, 0, sizeof(VERTEX_2D));//
																  // 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	//pDevice->SetTexture(0, m_pTexTure[m_Typ]);
	pDevice->SetTexture(0, m_pTexTure);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0, 2);
}	// ポリゴンの描画処理終了

//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CScene2D::SetUpdatePos(void)
{
	//頂点情報へのポインタ
	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVlxBuff->Lock(0, 0, (void **)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_fHypot*cosf(m_fAngle - m_fRoll), m_pos.y - m_fHypot*sinf(m_fAngle - m_fRoll), 0.0f);//ｘ＝半径-斜辺＊cosf(角度)※角度=g_fAngle
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_fHypot*cosf(m_fAngle + m_fRoll), m_pos.y - m_fHypot*sinf(m_fAngle + m_fRoll), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_fHypot*cosf(m_fAngle + m_fRoll), m_pos.y + m_fHypot*sinf(m_fAngle + m_fRoll), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_fHypot*cosf(m_fAngle - m_fRoll), m_pos.y + m_fHypot*sinf(m_fAngle - m_fRoll), 0.0f);

	//頂点バッファをアンロックする
	m_pVlxBuff->Unlock();
}

//=============================================================================
// 動くポリゴンの更新処理
//=============================================================================
void CScene2D::SetUpdateMovePos(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size)
{
	//頂点情報へのポインタ
	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVlxBuff->Lock(0, 0, (void **)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(pos.x - Size.x+move.x, pos.y - Size.y+move.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + Size.x+move.x, pos.y - Size.y+move.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - Size.x+move.x, pos.y + Size.y+move.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + Size.x+move.x, pos.y + Size.y+move.y, 0.0f);

	//頂点バッファをアンロックする
	m_pVlxBuff->Unlock();
}


//=============================================================================
// ポリゴンの回転の更新処理
//=============================================================================
void CScene2D::SetUpdateRoll(void)
{
	m_fRoll += 0.01f;

	if (m_fRoll > D3DX_PI)
	{
		m_fRoll = -D3DX_PI;
	}
	else if (m_fRoll < -D3DX_PI)
	{
		m_fRoll = D3DX_PI;
	}
}

//=============================================================================
// ポリゴンの拡大縮小の更新処理
//=============================================================================
void CScene2D::SetUpdateScale(int nMAXSize, int nMINSize)
{
	if (m_bAdd == true)
	{
		m_fHypot++;
	}
	else
	{
		m_fHypot--;
	}

	if (m_fHypot > nMAXSize)
	{
		m_bAdd = false;

	}
	if (m_fHypot < nMINSize)
	{
		m_bAdd = true;
	}
}

//=============================================================================
// アニメーションのテクスチャ配置処理
//=============================================================================
void CScene2D::SetTexAnime(int nPatternAnim, float fSizeAnim)
{	
	//頂点情報へのポインタ
	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVlxBuff->Lock(0, 0, (void **)&pVtx, 0);

	//テクスチャ座標 (横8パターン)
	pVtx[0].tex = D3DXVECTOR2(nPatternAnim*fSizeAnim, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(nPatternAnim*fSizeAnim + fSizeAnim, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(nPatternAnim*fSizeAnim, 0.0f + 1.0f);
	pVtx[3].tex = D3DXVECTOR2(nPatternAnim*fSizeAnim + fSizeAnim, 0.0f + 1.0f);

	//頂点バッファをアンロックする
	m_pVlxBuff->Unlock();
}

//=============================================================================
// アニメーションのテクスチャ配置処理
//=============================================================================
void CScene2D::SetTexAnime(int nPatternAnim, float fSizeAnimU, float fSizeMinV, float fSizeMaxV)
{
	//頂点情報へのポインタ
	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVlxBuff->Lock(0, 0, (void **)&pVtx, 0);

	//テクスチャ座標 (横8パターン)
	pVtx[0].tex = D3DXVECTOR2(nPatternAnim*fSizeAnimU, fSizeMinV);
	pVtx[1].tex = D3DXVECTOR2(nPatternAnim*fSizeAnimU + fSizeAnimU, fSizeMinV);
	pVtx[2].tex = D3DXVECTOR2(nPatternAnim*fSizeAnimU, fSizeMaxV);
	pVtx[3].tex = D3DXVECTOR2(nPatternAnim*fSizeAnimU + fSizeAnimU, fSizeMaxV);

	//頂点バッファをアンロックする
	m_pVlxBuff->Unlock();
}

//=============================================================================
// 動くテクスチャの配置処理
//=============================================================================
void CScene2D::SetTex(float fPosTexU, float fPosTexV)
{
	//頂点情報へのポインタ
	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVlxBuff->Lock(0, 0, (void **)&pVtx, 0);

	//テクスチャ座標 (横8パターン)
	pVtx[0].tex = D3DXVECTOR2(fPosTexU, fPosTexV);
	pVtx[1].tex = D3DXVECTOR2(fPosTexU + 1.0f, fPosTexV);
	pVtx[2].tex = D3DXVECTOR2(fPosTexU, fPosTexV+1.0f);
	pVtx[3].tex = D3DXVECTOR2(fPosTexU + 1.0f, fPosTexV+1.0f);

	//頂点バッファをアンロックする
	m_pVlxBuff->Unlock();
}

//=============================================================================
// テクスチャの色の設定処理
//=============================================================================
void CScene2D::SetColor(int nRad, int nGreen, int nBlue, int nAlpha)
{
	//頂点情報へのポインタ
	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVlxBuff->Lock(0, 0, (void **)&pVtx, 0);

	//頂点カラー
	pVtx[0].col = D3DCOLOR_RGBA(nRad, nGreen, nBlue, nAlpha);
	pVtx[1].col = D3DCOLOR_RGBA(nRad, nGreen, nBlue, nAlpha);
	pVtx[2].col = D3DCOLOR_RGBA(nRad, nGreen, nBlue, nAlpha);
	pVtx[3].col = D3DCOLOR_RGBA(nRad, nGreen, nBlue, nAlpha);

	//頂点バッファをアンロックする
	m_pVlxBuff->Unlock();
}

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