//=============================================================================
//
// 弾の破裂の処理 [player.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include"rupture.h"
#include"renderer.h"
#include"manager.h"
#include"bullet _circle.h"

//=============================================================================
// 静的メンバ関数の宣言
//=============================================================================
CBullet* CRupture::m_pBullet[MAX_BULLET] = {};

//=============================================================================
// 弾の破裂のコンストラクタ
//=============================================================================
CRupture::CRupture(int nPriority) : CScene(PRIORITY_PLAYER)
{

}


//=============================================================================
// 弾の破裂のデストラクタ
//=============================================================================
CRupture::~CRupture()
{

}

//=============================================================================
// 弾の破裂の生成処理
//=============================================================================
CRupture *CRupture::Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size, int nNum)
{
	CRupture* pRupture;

	pRupture = new CRupture;

	if (pRupture != NULL)
	{
		pRupture->Init(pos);		
		pRupture->m_Size = Size;
		pRupture->SetRupture(nNum);
	}
	return pRupture;
}

//=============================================================================
// 弾の破裂の初期化処理
//=============================================================================
HRESULT CRupture::Init(D3DXVECTOR3 pos)
{	
	m_Pos = pos;

	return S_OK;
}	// プレイヤーの初期化処理終了



	//=============================================================================
	// 弾の破裂の終了処理
	//=============================================================================
void CRupture::Uninit(void)
{
	// 解放
	Release();

}// プレイヤーの終了処理終了


 //=============================================================================
 // 弾の破裂の更新処理
 //=============================================================================
void CRupture::Update(void)
{


}// プレイヤーの更新処理終了

 //=============================================================================
 // 弾の破裂の描画処理
 //=============================================================================
void CRupture::Draw(void)
{

}	// プレイヤーの描画処理終了

	//=============================================================================
	// 弾の破裂の設定処理
	//=============================================================================
void CRupture::SetRupture(int type)
{
	switch (type)
	{
	case RUPTURE_TYPE_SCOND:
		for (int nCntBullet = 0; nCntBullet < 2; nCntBullet++)
		{
			CBulletCircle::Create(m_Pos, D3DXVECTOR3(10.0f, 10.0f, 0.0f), D3DXVECTOR2(10.0f, 10.0f), 60 * (D3DX_PI / 60) * nCntBullet, true);
		}
		break;
	case RUPTURE_TYPE_FOURTH:		
		for (int nCntBullet = 0; nCntBullet < 4; nCntBullet++)
		{
			CBulletCircle::Create(m_Pos, D3DXVECTOR3(10.0f, 10.0f, 0.0f), D3DXVECTOR2(10.0f, 10.0f), 90 * (D3DX_PI / 180) * nCntBullet, true);
		}
		break;
	case RUPTURE_TYPE_SIXTH:
		for (int nCntBullet = 0; nCntBullet < 6; nCntBullet++)
		{
			CBulletCircle::Create(m_Pos, D3DXVECTOR3(10.0f, 10.0f, 0.0f), D3DXVECTOR2(10.0f, 10.0f), 10 * (D3DX_PI / 30) * nCntBullet, true);
		}
		break;
	case RUPTURE_TYPE_EIGHTH:
		for (int nCntBullet = 0; nCntBullet < 8; nCntBullet++)
		{
			CBulletCircle::Create(m_Pos, D3DXVECTOR3(10.0f, 10.0f, 0.0f), D3DXVECTOR2(10.0f, 10.0f), 15 * (D3DX_PI / 60) * nCntBullet, true);
		}
		break;
	default:
		break;
	}
}