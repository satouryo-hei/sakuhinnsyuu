//=============================================================================
//
// 鍵のUIの処理 [keyui.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include"bulletui.h"
#include"renderer.h"
#include"manager.h"
#include"polygon.h"
#include"number.h"
#include"player.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
CPolygon *CBulletui::m_pPolygon = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CBulletui::CBulletui(PRIORITY Priority) :CScene(PRIORITY_UI)
{
	memset(&m_apNumber[0], NULL, sizeof(m_apNumber));
	m_Pos = D3DXVECTOR3(100.0f, 50.0f, 0);
	m_Size = D3DXVECTOR2(100.0f, 50.0f);
}


//=============================================================================
// デストラクタ
//=============================================================================
CBulletui::~CBulletui()
{

}

//=============================================================================
// 鍵のUIの生成処理
//=============================================================================
CBulletui *CBulletui::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	// 2Dエフェクトのポインター生成
	CBulletui* pBulletui = NULL;

	// 動的メモリの確保
	pBulletui = new CBulletui;

	// NULLチェック
	if (pBulletui != NULL)
	{
		pBulletui->m_Size = size;

		// 鍵のUIの初期化処理
		pBulletui->Init(pos);
	}
	return pBulletui;
}

//=============================================================================
// 鍵のUIの初期化処理
//=============================================================================
HRESULT CBulletui::Init(D3DXVECTOR3 pos)
{
	m_Pos = pos;
	m_pPolygon = CPolygon::Create(pos, m_Size, 17);

	D3DXVECTOR3 Pos = pos;
	Pos.x += m_Size.x*2;

	D3DXVECTOR2 Size = D3DXVECTOR2(20.0f, 30.0f);

	for (int nCnt = 0; nCnt < MAX_KEYNUMBER; nCnt++)
	{
		m_apNumber[nCnt] = CNumber::Create(Pos, Size, 5);
		Pos.x += (Size.x * 2);
	}

	return S_OK;
}	//  ロゴの初期化処理の終了



	//=============================================================================
	// 鍵のUIの終了処理
	//=============================================================================
void CBulletui::Uninit(void)
{
	// シーンの解放処理
	CScene::Release();

}// ロゴの終了処理の終了


 //=============================================================================
 // 鍵のUIの更新処理
 //=============================================================================
void CBulletui::Update(void)
{
	int nBullet = CPlayer::GetBulletNum();
	SetNumbullet(nBullet);
}// 鍵のUIの更新処理終了



 //=============================================================================
 // 鍵のUIの描画処理
 //=============================================================================
void CBulletui::Draw(void)
{
	for (int nCntNum = 0; nCntNum < MAX_KEYNUMBER; nCntNum++)
	{
		m_apNumber[nCntNum]->Draw();
	}
}	// 鍵のUIの描画処理終了


	//=============================================================================
	// 鍵のUIの設定処理
	//=============================================================================
void CBulletui::SetNumbullet(const int nNumbullet)
{
	static const int nData = 10;

	int nNum = MAX_KEYNUMBER;
	int iNum = MAX_KEYNUMBER - 1;

	// NUMSCORE分回す
	for (int nCnt = 0; nCnt < MAX_KEYNUMBER; nCnt++, nNum--, iNum--)
	{
		m_apNumber[nCnt]->SetNumber(nNumbullet % Exponentiation(nData, nNum) / Exponentiation(nData, iNum));
	}
}