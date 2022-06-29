//=============================================================================
//
// 影の処理 [shadow.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include"shadow.h"
#include"renderer.h"
#include"manager.h"
#include"texture.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CShadow::CShadow(PRIORITY Priority) : CScene3D(PRIORITY_SECOND)
{
	m_pVtxBuff = NULL;
	m_mtxWorld;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bUse = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CShadow::~CShadow()
{

}

//=============================================================================
// 影の生成処理
//=============================================================================
CShadow *CShadow::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR3 Rot)
{
	// 影のポインター生成
	CShadow* pShadow = NULL;

	// 動的メモリの確保
	pShadow = new CShadow;

	// NULLチェック
	if (pShadow != NULL)
	{
		// 初期化処理
		pShadow->Init(pos, size);

		// 向きを設定
		pShadow->m_rot = Rot;

		// テクスチャの設定
		pShadow->BindTextuer(4);
	}

	return pShadow;
}

//=============================================================================
// 影の初期化処理
//=============================================================================
HRESULT CShadow::Init(D3DXVECTOR3 pos, D3DXVECTOR3 Size)
{
	// 影の位置と大きさの設定処理を呼び出す
	SetShodow(pos, Size);

	// 継承元の初期化処理を呼び出す
	CScene3D::Init(pos, Size, m_rot);

	return S_OK;
}	// ポリゴンの初期化処理終了



//=============================================================================
// 影の終了処理
//=============================================================================
void CShadow::Uninit(void)
{
	// 継承元の終了処理を呼び出す
	CScene3D::Uninit();

	// 解放処理
	Release();

}// ポリゴンの終了処理終了


 //=============================================================================
 // 影の更新処理
 //=============================================================================
void CShadow::Update(void)
{

}// ポリゴンの更新処理終了


 //=============================================================================
 // 影の描画処理
 //=============================================================================
void CShadow::Draw(void)
{
	//デバイスを取得する
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;//計算用のマトリックス

								//減算合成の設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// 継承元の描画処理を呼び出す
	CScene3D::Draw();

	//通常の合成に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}	// ポリゴンの描画処理終了

//=============================================================================
// 影の位置と大きさの設定処理
//=============================================================================
void CShadow::SetShodow(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	m_pos = pos;
	m_size = size;
}