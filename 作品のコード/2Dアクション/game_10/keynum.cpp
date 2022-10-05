//=============================================================================
//
// 鍵のUIの処理 [keyui.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include"keynum.h"
#include"renderer.h"
#include"manager.h"
#include"polygon.h"
#include"number.h"
#include"player.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CKeynum::CKeynum(PRIORITY Priority) :CScene2D(PRIORITY_UI)
{
	memset(&m_apNumber[0], NULL, sizeof(m_apNumber));
	m_Pos = D3DXVECTOR3(100.0f, 50.0f, 0);	
}


//=============================================================================
// デストラクタ
//=============================================================================
CKeynum::~CKeynum()
{

}

//=============================================================================
// 鍵のUIの生成処理
//=============================================================================
CKeynum *CKeynum::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	// 2Dエフェクトのポインター生成
	CKeynum* pKeyui = NULL;

	// 動的メモリの確保
	pKeyui = new CKeynum;

	// NULLチェック
	if (pKeyui != NULL)
	{		
		// 鍵のUIの初期化処理
		pKeyui->Init(pos,size);
	}
	return pKeyui;
}

//=============================================================================
// 鍵のUIの初期化処理
//=============================================================================
HRESULT CKeynum::Init(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	m_Pos = pos;

	for (int nCnt = 0; nCnt < MAX_KEYNUMBER; nCnt++)
	{
		m_Pos.x += (size.x * 2);
		m_apNumber[nCnt] = CNumber::Create(m_Pos, size, 5);
	}

	return S_OK;
}	//  ロゴの初期化処理の終了



	//=============================================================================
	// 鍵のUIの終了処理
	//=============================================================================
void CKeynum::Uninit(void)
{
	// シーンの解放処理
	CScene::Release();

}// ロゴの終了処理の終了


 //=============================================================================
 // 鍵のUIの更新処理
 //=============================================================================
void CKeynum::Update(void)
{
	int nItem = CPlayer::GetItem();
	SetNumKey(nItem);
}// 鍵のUIの更新処理終了



 //=============================================================================
 // 鍵のUIの描画処理
 //=============================================================================
void CKeynum::Draw(void)
{
	for (int nCntNum = 0; nCntNum < MAX_KEYNUMBER; nCntNum++)
	{
		m_apNumber[nCntNum]->Draw();
	}
}	// 鍵のUIの描画処理終了


	//=============================================================================
	// 鍵のUIの設定処理
	//=============================================================================
void CKeynum::SetNumKey(const int nNumKey)
{
	static const int nData = 10;

	int nNum = MAX_KEYNUMBER;
	int iNum = MAX_KEYNUMBER - 1;

	// NUMSCORE分回す
	for (int nCnt = 0; nCnt < MAX_KEYNUMBER; nCnt++, nNum--, iNum--)
	{
		m_apNumber[nCnt]->SetNumber(nNumKey % Exponentiation(nData, nNum) / Exponentiation(nData, iNum));
	}
}