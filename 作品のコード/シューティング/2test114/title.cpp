//=============================================================================
//
// タイトルの処理 [title.cpp]
// Author : 佐藤瞭平
//
//=============================================================================
#include "title.h"
#include "scene2D.h"
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"fade.h"
#include"title_logo.h"
#include"sound.h"
#include"press_next.h"

// 静的メンバ変数の宣言
LPDIRECT3DTEXTURE9 CTitle::m_pTexture = NULL;
CTitle_Logo* CTitle::m_pTitle_Logo = NULL;
CPress_Next * CTitle::m_Press_Next = NULL;
//=============================================================================
// タイトルのコンストラクタ
//=============================================================================
CTitle::CTitle(int nPriority)
{
	m_apScene2D = NULL;
	m_bNextMode = false; 
}

//=============================================================================
// タイトルのデストラクタ
//=============================================================================
CTitle::~CTitle()
{

}

//=============================================================================
// テクスチャの読み込む
//=============================================================================
HRESULT CTitle::Load(void)
{
	CManager *pManager = NULL;

	LPDIRECT3DDEVICE9 pDevice = pManager->GetRenderer()->GetDevice();

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/woods002.jpg",
		&m_pTexture);

	return S_OK;
}

//=============================================================================
// テクスチャの破棄
//=============================================================================
void CTitle::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// タイトルの初期化処理
//=============================================================================
HRESULT CTitle::Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	m_apScene2D = new CScene2D(PRIORITY_BG);

	if (m_apScene2D != NULL)
	{
		m_apScene2D->Init(pos, Size);
		m_apScene2D->BindTextuer(m_pTexture);
	}

	// テクスチャの読み込み
	CTitle_Logo::Load();
	CPress_Next::Load();

	// タイトルロゴの生成
	m_pTitle_Logo = CTitle_Logo::Create(D3DXVECTOR3(640.0f, 100.0f, 0.0f), D3DXVECTOR2(640.0f, 320.0f));

	// ENTERを押したら次にの生成
	m_Press_Next = CPress_Next::Create(D3DXVECTOR3(640.0f, 740.0f, 0.0f), D3DXVECTOR3(0.0f,5.0f, 0.0f), D3DXVECTOR2(300.0f, 100.0f), 540.0f);

	CManager *pManager = NULL;
	pManager->GetSound()->Play(CSound::SOUND_LABEL_SUMMER_FOG);

	return S_OK;
}

//=============================================================================
// タイトルの終了処理
//=============================================================================
void CTitle::Uninit(void)
{
	// テクスチャの破棄
	CTitle_Logo::Unload();
	CPress_Next::Unload();

	// シーンの破棄
	CScene::Relese();
}

//=============================================================================
// タイトルの更新処理
//=============================================================================
void CTitle::Update(void)
{
	CInputKeyboard *pInputKeyboard = NULL;
	pInputKeyboard = CManager::GetInputKeyboard();


	//任意で押されたかどうか
	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true && !m_bNextMode)//ENTERを押した
	{
		// チュートリアルに遷移
		CFade::SetFade(CManager::MODE_TUTORIAL);
		m_bNextMode = true;
	}
}

//=============================================================================
// タイトルの描画処理
//=============================================================================
void CTitle::Draw(void)
{

}