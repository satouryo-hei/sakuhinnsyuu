//=============================================================================
//
// フェードの処理 [fade.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include"fade.h"
#include"renderer.h"
#include"texture.h"
#include"bg.h"

//=============================================================================
// 静的メンバ変数の宣言
//=============================================================================
CFade::FADE CFade::m_Fade = CFade::FADE_NONE;
D3DXCOLOR CFade::m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
CManager::MODE CFade::m_ModeNext = CManager::MODE_INVALID;

//=============================================================================
// フェードのコンストラクタ
//=============================================================================
CFade::CFade(PRIORITY Priority) : CScene2D(PRIORITY_FADE)
{
}

//=============================================================================
// フェードのデストラクタ
//=============================================================================
CFade::~CFade()
{

}

//=============================================================================
// フェードの生成処理
//=============================================================================
CFade *CFade::Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size, CManager::MODE mode)
{
	// フェードのポインター生成
	CFade* pFade = NULL;

	// 動的メモリの確保
	pFade = new CFade;

	// NULLチェック
	if (pFade != NULL)
	{
		// フェードの初期化処理の呼び出し
		pFade->Init(pos, Size);

		// フェードの設定処理の呼び出し
		pFade->SetFade(mode);

		// フェードのテクスチャの設定
		pFade->BindTextuer(1);
	}
	return pFade;

}

//=============================================================================
// フェードの初期化処理
//=============================================================================
HRESULT CFade::Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	m_Fade = FADE_IN;
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

	// 継承元の初期化処理を呼び出す
	CScene2D::Init(pos,Size);
	return S_OK;
}


//=============================================================================
// フェードの終了処理
//=============================================================================
void CFade::Uninit(void)
{
	// 継承元の終了処理を呼び出す
	CScene2D::Uninit();
}


//=============================================================================
// フェードの更新処理
//=============================================================================
void CFade::Update(void)
{
	// フェードがされていなかったら
	if (m_Fade != FADE_NONE)
	{
		// フェードイン状態にされていたら
		if (m_Fade == FADE_IN)
		{
			m_col.a -= 0.03f;

			if (m_col.a <= 0.00f)
			{
				m_col.a = 0.00f;

				// フェードを終わらせる
				m_Fade = FADE_NONE;
			}
		}
		// フェードアウト状態にされていたら
		else if (m_Fade == FADE_OUT)
		{
			m_col.a += 0.05f;

			if (m_col.a >= 1.00f)
			{
				m_col.a = 1.00f;

				// フェードイン状態にする
				m_Fade = FADE_IN;

				//モードの設定処理
				CManager::SetMode(m_ModeNext);
			}
		}		
		// 色の設定処理
		CScene2D::SetColor(m_col);
	}
	// 継承元の更新処理を呼び出す
	CScene2D::Update();
}

//=============================================================================
// フェードの描画処理
//=============================================================================
void CFade::Draw(void)
{
	// 継承元の描画処理を呼び出す
	CScene2D::Draw();
}

//=============================================================================
// フェードの設定処理
//=============================================================================
void CFade::SetFade(CManager::MODE modeNext)
{
	// フェードアウト状態にする
	m_Fade = FADE_OUT;

	// 次のモード切替させる
	m_ModeNext = modeNext;

	// 色の初期化
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}