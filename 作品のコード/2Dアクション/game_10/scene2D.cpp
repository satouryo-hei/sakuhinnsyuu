//=============================================================================
//
// 2Dオブジェクトの処理 [scene2D.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include"scene2D.h"
#include"renderer.h"
#include"manager.h"
#include"texture.h"

//=============================================================================
// 静的メンバ関数の宣言
//=============================================================================
const int CScene2D::m_nNumVertex = 4;

//=============================================================================
// 2Dオブジェクトのコンストラクタ
//=============================================================================
CScene2D::CScene2D(PRIORITY Priority) : CScene(Priority)
{
	m_pTexTure = NULL;
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
	m_Size = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	m_fRoll = 0;
	m_fHypot = 0;
	m_fAngle = 0;
	m_bSizeAdd = true;
}

//=============================================================================
// 2Dオブジェクトのデストラクタ
//=============================================================================
CScene2D::~CScene2D()
{

}

//=============================================================================
// 2Dオブジェクトの生成処理
//=============================================================================
CScene2D *CScene2D::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, int nTex)
{
	// ポリゴンのポインター生成
	CScene2D* pScene2D = NULL;

	// 動的メモリの確保
	pScene2D = new CScene2D;

	// NULLチェック
	if (pScene2D != NULL)
	{
		pScene2D->Init(pos, size);
		pScene2D->Bindtexture(nTex);
	}
	return pScene2D;
}

//=============================================================================
//　2Dオブジェクトのテクスチャの設定
//=============================================================================
void CScene2D::Bindtexture(int nTex)
{
	m_pTexTure = CManager::GetTexture()->GetTex(nTex);
}

//=============================================================================
// 2Dオブジェクトのデフォルト初期化処理
//=============================================================================
HRESULT CScene2D::Init(D3DXVECTOR3 pos)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice = NULL;

	//デバイスの取得
	pDevice = CManager::GetRenderer()->GetDevice();

	m_pos = pos;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * m_nNumVertex,
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
	m_pVtxBuff->Unlock();
	return S_OK;
}

//=============================================================================
// 2Dオブジェクトの初期化処理
//=============================================================================
HRESULT CScene2D::Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	m_Size = Size;
	// 2Dオブジェクトのデフォルト初期化処理の呼び出し
	Init(pos);

	//角度を求めるために１回しか使わない（ラジアン//m_fAngleに角度を代入m_fAngleは角度(45度)
	m_fAngle = atan2f(1, 1);														// -1.0f～1.0fの範囲がラジアン数値(-3.14～-3.14)になる
																					// ポリゴン内の斜辺を求める
	m_fHypot = sqrtf(powf(m_Size.x, 2.0f) + powf(m_Size.y, 2.0f));

	return S_OK;
}	// ポリゴンの初期化処理終了

	//=============================================================================
	// 2Dオブジェクトの終了処理
	//=============================================================================
void CScene2D::Uninit(void)
{
	//バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	//オブジェクトの破棄
	Release();

}// ポリゴンの終了処理終了S

 //=============================================================================
 // 2Dオブジェクトの更新処理
 //=============================================================================
void CScene2D::Update(void)
{
	CScene2D::SetPosSize(m_pos, m_Size);

}// ポリゴンの更新処理終了S

 //=============================================================================
 // 2Dオブジェクトの描画処理
 //=============================================================================
void CScene2D::Draw(void)
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
	pDevice->SetTexture(0, m_pTexTure);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0, 2);
}	// ポリゴンの描画処理終了

//=============================================================================
// 2Dオブジェクトの位置と大きさの設定処理
//=============================================================================
void CScene2D::SetPosSize(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	//頂点情報へのポインタ
	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void **)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(pos.x - Size.x, pos.y - Size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + Size.x, pos.y - Size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - Size.x, pos.y + Size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + Size.x, pos.y + Size.y, 0.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================================
// 2Dオブジェクトの位置と大きさの頂点ごとの設定処理
//=============================================================================
void CScene2D::SetVtxBuffPosSize(D3DXVECTOR3 pos, D3DXVECTOR2 Size, int nNum)
{
	//頂点情報へのポインタ
	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void **)&pVtx, 0);

	switch (nNum)
	{
	case 0:
		pVtx[nNum].pos = D3DXVECTOR3(pos.x - Size.x, pos.y - Size.y, 0.0f);
		break;

	case 1:
		pVtx[nNum].pos = D3DXVECTOR3(pos.x + Size.x, pos.y - Size.y, 0.0f);
		break;

	case 2:
		pVtx[nNum].pos = D3DXVECTOR3(pos.x - Size.x, pos.y + Size.y, 0.0f);
		break;

	case 3:
		pVtx[nNum].pos = D3DXVECTOR3(pos.x + Size.x, pos.y + Size.y, 0.0f);
		break;

	default:
		break;
	}
	//頂点座標の設定

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}


//=============================================================================
// 2Dオブジェクト回転拡縮の更新の設定処理
//=============================================================================
void CScene2D::SetUpdateRollingSize(void)
{
	//頂点情報へのポインタ
	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void **)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_fHypot*cosf(m_fAngle - m_fRoll), m_pos.y - m_fHypot*sinf(m_fAngle - m_fRoll), 0.0f);//ｘ＝半径＊cosf(角度)角度=g_fAngle
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_fHypot*cosf(m_fAngle + m_fRoll), m_pos.y - m_fHypot*sinf(m_fAngle + m_fRoll), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_fHypot*cosf(m_fAngle + m_fRoll), m_pos.y + m_fHypot*sinf(m_fAngle + m_fRoll), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_fHypot*cosf(m_fAngle - m_fRoll), m_pos.y + m_fHypot*sinf(m_fAngle - m_fRoll), 0.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}


//=============================================================================
// 2Dオブジェクトの1回転の更新処理
//=============================================================================
void CScene2D::SetUpdateRoll(float fSpeed, bool bAdd)
{
	if (bAdd)
	{
		m_fRoll += fSpeed;
	}
	else
	{
		m_fRoll -= fSpeed;
	}

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
// 2Dオブジェクトの回転の設定更新処理
//=============================================================================
void CScene2D::SetRolling(float fSpeed, float fMin, float fMax)
{
	if (m_bRollAdd)
	{
		m_fRoll += fSpeed;
	}
	else
	{
		m_fRoll -= fSpeed;
	}

	if (m_fRoll > fMax)
	{
		m_bRollAdd = false;
	}
	else if (m_fRoll < fMin)
	{
		m_bRollAdd = true;
	}
}

//=============================================================================
// 2Dオブジェクトの拡大縮小の更新処理
//=============================================================================
void CScene2D::SetUpdateSize(int MaxSize, int MinSize)
{
	if (m_bSizeAdd)
	{
		m_fHypot++;
	}
	else
	{
		m_fHypot--;
	}

	if (m_fHypot > MaxSize)
	{
		m_bSizeAdd = false;

	}
	else if (m_fHypot < MinSize)
	{
		m_bSizeAdd = true;
	}
}

//=============================================================================
// 2Dオブジェクトの色の設定処理
//=============================================================================
void CScene2D::SetColor(D3DXCOLOR col)
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

//=============================================================================
// 2Dオブジェクトの色の設定処理
//=============================================================================
void CScene2D::SetRgba(int nRed, int nGreen, int nBlue, int nAlpha)
{
	//頂点情報へのポインタ
	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void **)&pVtx, 0);

	//頂点カラー
	pVtx[0].col = D3DCOLOR_RGBA(nRed, nGreen, nBlue, nAlpha);
	pVtx[1].col = D3DCOLOR_RGBA(nRed, nGreen, nBlue, nAlpha);
	pVtx[2].col = D3DCOLOR_RGBA(nRed, nGreen, nBlue, nAlpha);
	pVtx[3].col = D3DCOLOR_RGBA(nRed, nGreen, nBlue, nAlpha);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================================
// 2Dオブジェクトの頂点の色の設定処理
//=============================================================================
void CScene2D::SetVtxBuffColor(D3DXCOLOR col, int nVtxBuff)
{
	//頂点情報へのポインタ
	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void **)&pVtx, 0);

	//頂点カラー
	pVtx[nVtxBuff].col = D3DXCOLOR(col);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================================
// ポリゴンの中心から斜め距離の設定処理
//=============================================================================
void CScene2D::SetAngle(D3DXVECTOR2 Angle, D3DXVECTOR2 size)
{
	//角度を求めるために１回しか使わない（ラジアン//m_fAngleに角度を代入m_fAngleは角度(45度)
	m_fAngle = atan2f(Angle.y, Angle.x);														// -1.0f～1.0fの範囲がラジアン数値(-3.14～-3.14)になる
																								// ポリゴン内の斜辺を求める
	m_fHypot = sqrtf(powf(size.x, 2.0f) + powf(size.y, 2.0f));
}

//=============================================================================
// アニメーションのテクスチャ配置処理
//=============================================================================
void CScene2D::SetTexAnime(int nPatternAnim, float fSizeAnimU, float fSizeMinV, float fSizeMaxV)
{
	//頂点情報へのポインタ
	VERTEX_2D*pVtx;

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