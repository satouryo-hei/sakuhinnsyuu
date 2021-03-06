//=============================================================================
//
// 弾の処理 [bullet.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include"bullet03.h"
#include"renderer.h"
#include"manager.h"
#include"input.h"
#include"player.h"
#include"effect.h"
#include"bullet.h"

/*やりたいこと*/
/*弾の回転　←いるのか？
チャージショット
チャージショットで弾の拡大*/

//=============================================================================
// 静的メンバ関数の宣言
//=============================================================================
bool CBullet03::m_bUse = false;
CBullet * CBullet03::m_pBullet[3] = {};

//=============================================================================
// 弾のコンストラクタ
//=============================================================================
CBullet03::CBullet03(int nPriority) : CScene2D(PRIORITY_BULLET)
{
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Size = D3DXVECTOR2(0.0f, 0.0f);
	m_nLife = 0;
}


//=============================================================================
// 弾のデストラクタ
//=============================================================================
CBullet03::~CBullet03()
{

}


//=============================================================================
// 弾の生成処理
//=============================================================================
CBullet03 *CBullet03::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size, int nAttack)
{
	CBullet03* pBullet = NULL;

	pBullet = new CBullet03;

	if (pBullet != NULL)
	{
		pBullet->m_Size = Size;
		pBullet->m_Move = move;
		pBullet->Init(pos, Size);
		pBullet->m_bUse = false;
	}
	return pBullet;
}

//=============================================================================
// 弾の初期化処理
//=============================================================================
HRESULT CBullet03::Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	m_Pos = pos;

	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		float fAngle = D3DX_PI * (0.25f * (nCnt+1));
		m_pBullet[nCnt] = CBullet::Create(pos, D3DXVECTOR3(m_Move.x*sinf(fAngle) , m_Move.y* cosf(fAngle), 0.0f), m_Size, 30, true);
	}
	return S_OK;
}	// ポリゴンの初期化処理終了



	//=============================================================================
	// 弾の終了処理
	//=============================================================================
void CBullet03::Uninit(void)
{

	Release();

}// ポリゴンの終了処理終了


 //=============================================================================
 // 弾の更新処理
 //=============================================================================
void CBullet03::Update(void)
{

}// ポリゴンの更新処理終了



 //=============================================================================
 // 弾の描画処理
 //=============================================================================
void CBullet03::Draw(void)
{

}	// ポリゴンの描画処理終了