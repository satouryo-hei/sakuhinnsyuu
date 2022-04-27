//----------------------------------
//ポリゴンの処理
//-----------------------------------
#include "billeffect.h"
#include "input.h"
#include "Renderer.h"
#include "manager.h"
#include "texture.h"
#include"Scene3D.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CBilleffect::CBilleffect(OBJTYPE nPriority) :CScene(nPriority)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CBilleffect::~CBilleffect()
{

}
void CBilleffect::BindTexture(CTexture::Type type)
{
	m_pTexture = CManager::GetTexture()->GetTexture(type);
}
//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
HRESULT CBilleffect::Init(CTexture::Type type)
{

	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();//デバイスのポインタ

																	 // 頂点情報を設定
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);


	//テクスチャ画像の設定
	m_pTexture = CManager::GetTexture()->GetTexture(type);

	VERTEX_3D *pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//バッファの生成
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y + m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, 0.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0, 0.0);
	pVtx[1].tex = D3DXVECTOR2(1.0, 0.0);
	pVtx[2].tex = D3DXVECTOR2(0.0, 1.0);
	pVtx[3].tex = D3DXVECTOR2(1.0, 1.0);

	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	m_pVtxBuff->Unlock();

	return S_OK;
}
HRESULT CBilleffect::Init(void)
{

	return S_OK;
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CBilleffect::Uninit(void)
{
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	Release();
}

//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CBilleffect::Update(void)
{
	Setposition(m_pos, m_size);
}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CBilleffect::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();//デバイスのポインタ
	D3DXMATRIX mtxRot, mtxTrans;//計算用マトリックス

	//ライト無効
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//アルファテスト関係
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//Zテスト関係
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	//加算合成関係
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//ビューマトリックスの取得
	pDevice->GetTransform(D3DTS_VIEW,&m_mtxView);

	//ポリゴンをカメラに対して正面に向ける
	//逆行列を求める
	m_mtxWorld._11 = m_mtxView._11;
	m_mtxWorld._12 = m_mtxView._21;
	m_mtxWorld._13 = m_mtxView._31;
	m_mtxWorld._21 = m_mtxView._12;
	m_mtxWorld._22 = m_mtxView._22;
	m_mtxWorld._23 = m_mtxView._32;
	m_mtxWorld._31 = m_mtxView._13;
	m_mtxWorld._32 = m_mtxView._23;
	m_mtxWorld._33 = m_mtxView._33;
	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをでバスのでーたすとりーむに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
	pDevice->SetFVF(FVF_VERTEX_3D);//頂点フォーマットの設定

	pDevice->SetTexture(0, m_pTexture);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
	
	//Zテスト関係
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//アルファテスト関係
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);

	//通常合成に戻す(加算合成)
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//ライトをもとに戻す
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}
//---------------------------------------------------------------
//インスタンス生成処理
//---------------------------------------------------------------
CBilleffect *CBilleffect::Create(D3DXVECTOR3 size)
{
	//インスタンス生成
	CBilleffect *pBilleffect = new CBilleffect();

	pBilleffect->m_size = size;

	if (pBilleffect != NULL)
	{
		pBilleffect->Init(CTexture::Effect);
	}
	return pBilleffect;
}

void CBilleffect::Setposition(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	VERTEX_3D *pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(-scale.x,scale.y, scale.z);
	pVtx[1].pos = D3DXVECTOR3(scale.x,scale.y, scale.z);
	pVtx[2].pos = D3DXVECTOR3(-scale.x,-scale.y, scale.z);
	pVtx[3].pos = D3DXVECTOR3(scale.x,-scale.y, scale.z);

	m_pVtxBuff->Unlock();

	m_pos = pos;

	m_size = scale;
}

void CBilleffect::SetColor(D3DXCOLOR col)
{
	VERTEX_3D *pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
	pVtx[1].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
	pVtx[2].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
	pVtx[3].col = D3DXCOLOR(col.r, col.g, col.b, col.a);

	m_pVtxBuff->Unlock();

}