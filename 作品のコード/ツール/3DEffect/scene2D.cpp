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
CScene2D::CScene2D(PRIORITY Priority) : CScene(Priority)
{
	//m_pTexTure[2] = {};
	m_pTexTure = NULL;
	m_pVlxBuff = NULL;
	m_pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);	
	m_Size = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
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
// テクスチャの初期化処理
//=============================================================================
void CScene2D::BindTextuer(CTexture::Tex type)
{
	m_pTexTure = CManager::GetTexture()->GetTex(type);
}

//=============================================================================
// ポリゴンの初期化処理
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

	m_fAngle = atan2f(1.0f, 1.0f);											//45°を求めるために１回しか使わない（ラジアン//g_fAngleに角度を代入g_fAngleは角度
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
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - 100.0f, m_pos.y - 100.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + 100.0f, m_pos.y - 100.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - 100.0f, m_pos.y + 100.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + 100.0f, m_pos.y + 100.0f, 0.0f);

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
	Release();

}// ポリゴンの終了処理終了


 //=============================================================================
 // ポリゴンの更新処理
 //=============================================================================
void CScene2D::Update(void)
{
	CScene2D::SetUpdatePosSize(m_pos, m_Size);

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
	pDevice->SetTexture(0, m_pTexTure);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0, 2);
}	// ポリゴンの描画処理終了

//=============================================================================
// 動くポリゴンの更新処理
//=============================================================================
void CScene2D::SetUpdatePosSize(D3DXVECTOR3 pos, D3DXVECTOR3 Size)
{
	//頂点情報へのポインタ
	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVlxBuff->Lock(0, 0, (void **)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(pos.x - Size.x, pos.y - Size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + Size.x, pos.y - Size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - Size.x, pos.y + Size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + Size.x, pos.y + Size.y, 0.0f);

	//頂点バッファをアンロックする
	m_pVlxBuff->Unlock();
}


//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CScene2D::SetUpdateRollingSize(void)
{
	//頂点情報へのポインタ
	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVlxBuff->Lock(0, 0, (void **)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_fHypot*cosf(m_fAngle - m_fRoll), m_pos.y - m_fHypot*sinf(m_fAngle - m_fRoll), 0.0f);//ｘ＝半径＊cosf(角度)角度=g_fAngle
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_fHypot*cosf(m_fAngle + m_fRoll), m_pos.y - m_fHypot*sinf(m_fAngle + m_fRoll), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_fHypot*cosf(m_fAngle + m_fRoll), m_pos.y + m_fHypot*sinf(m_fAngle + m_fRoll), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_fHypot*cosf(m_fAngle - m_fRoll), m_pos.y + m_fHypot*sinf(m_fAngle - m_fRoll), 0.0f);

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
void CScene2D::SetUpdateSize(void)
{
	if (m_bAdd == true)
	{
		m_fHypot++;
	}
	else
	{
		m_fHypot--;
	}

	if (m_fHypot > 100)
	{
		m_bAdd = false;

	}
	if (m_fHypot < 70)
	{
		m_bAdd = true;
	}
}