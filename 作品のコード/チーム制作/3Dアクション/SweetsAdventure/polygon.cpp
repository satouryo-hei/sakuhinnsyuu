//=============================================================================
//
// Polygon処理
// Author : 齋藤幸宏 & 村元翼
//
//=============================================================================
#include "Polygon.h"
#include "manager.h"
#include "Renderer.h"
#include "scene2D.h"

//=============================================================================
//コンストラクタ
//=============================================================================
CPolygon::CPolygon(OBJTYPE nPriority) : CScene2D(nPriority)
{

}

//=============================================================================
//デストラクタ
//=============================================================================
CPolygon::~CPolygon()
{

}
//------------------------------------------------------------
//頂点座標の設定
//------------------------------------------------------------

void CPolygon::SetPos(D3DXVECTOR3 pos)
{

	CScene::SetPos(pos);

	VERTEX_2D *pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//バッファの生成
	pVtx[0].pos = D3DXVECTOR3(pos.x - m_Scale.x, pos.y - m_Scale.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + m_Scale.x, pos.y - m_Scale.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - m_Scale.x, pos.y + m_Scale.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + m_Scale.x, pos.y + m_Scale.y, 0.0f);

	m_pVtxBuff->Unlock();

}
//=============================================================================
//初期化
//=============================================================================
HRESULT CPolygon::Init(void)
{
	CScene2D::BindTexture(m_Tex);
	CScene2D::Init();
	CScene2D::SetPos(m_Pos, m_Scale);
	CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	return S_OK;
}

//=============================================================================
//終了
//=============================================================================
void CPolygon::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
//更新
//=============================================================================
void CPolygon::Update(void)
{
	CScene2D::Update();
}

//=============================================================================
//描画
//=============================================================================
void CPolygon::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();//デバイスのポインタ

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_NOTEQUAL);

	CScene2D::Draw();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
}

//=============================================================================
//クリエイト
//=============================================================================
CPolygon *CPolygon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, CTexture::Type texture)
{
	//インスタンス生成
	CPolygon *pPolygon = new CPolygon(OBJTYPE_POLYGON);

	pPolygon->m_Pos = pos;
	pPolygon->m_Scale = scale;
	pPolygon->m_Tex = texture;

	if (pPolygon != NULL)
	{
		pPolygon->Init();
	}

	return pPolygon;
}