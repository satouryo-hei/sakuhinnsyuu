//=============================================================================
//
// テクスチャ処理 [texture.cpp]
// Author : 羽鳥太一作
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "texture.h"
#include "Renderer.h"
#include "manager.h"

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CTexture::CTexture()
{

}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CTexture::~CTexture()
{

}

//=============================================================================
// テクスチャの生成
//=============================================================================
void CTexture::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = CManager::GetRenderer()->GetDevice();	//デバイスを取得する

	D3DXCreateTextureFromFile(pDevice,
		"",	// 無し
		&m_pTexture[None]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/text_texture.png",//仮テクスチャ
		&m_pTexture[Text]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/Flag.png",//仮テクスチャ
		&m_pTexture[GOAL]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/number000.png",//数字
		&m_pTexture[TIME]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/fade.png",//数字
		&m_pTexture[FADE]);
	//---------------------------------
	//武器の選択
	//---------------------------------
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/WEAPON/Hammer000.png",//数字
		&m_pTexture[HAMMERTEX]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/WEAPON/Naifu000.png",//数字
		&m_pTexture[NAIHUTEX]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/WEAPON/Frame_Black.png",//数字
		&m_pTexture[FREAM]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/WEAPON/Frame0.png",//数字
		&m_pTexture[WEAPONSELECT]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/WEAPON/LB.png",//数字
		&m_pTexture[LB]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/WEAPON/RB.png",//数字
		&m_pTexture[RB]);


	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/sky_loop001.png",//空
		&m_pTexture[SKY]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/floor001.png",//海1
		&m_pTexture[SEA000]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/floor.png",//海２
		&m_pTexture[SEA001]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/shadow000.jpg",//影
		&m_pTexture[SHADOW]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/shadow000.jpg",//エフェクト
		&m_pTexture[Effect]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/Tyoko.png",//床	
		&m_pTexture[FIELD]);
	//============================================================
	//タイトル
	//============================================================
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/Title000.png",//タイトル背景
		&m_pTexture[Title]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/Titlelogo.png",//タイトルロゴ
		&m_pTexture[Titlelogo]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/GameStart.png",//ゲームスタート
		&m_pTexture[GameStart]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/Operation.png",//チュートリアル
		&m_pTexture[Operation]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/Ranking000.png",//ランキング
		&m_pTexture[Ranking000]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/002.png",		  //カーソル
		&m_pTexture[Cursol]);

	//============================================================
	//ゲームオーバー
	//============================================================
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/gameover.png",//ゲームオーバー背景
		&m_pTexture[GameOver]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/Gameover000.png",//ゲームオーバーロゴ
		&m_pTexture[Gameover000]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/gameclear002.png",//ゲームクリア背景
		&m_pTexture[GameClear000]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/gameclear003.png",//ゲームオーバーロゴ
		&m_pTexture[GameClear001]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/Retry.png",//リトライ
		&m_pTexture[Retry]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/Texture001.png",//タイトルに戻る
		&m_pTexture[Texture001]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/ReturnGame.png",//タイトルに戻る
		&m_pTexture[GameBack]);
	//============================================================
	//ゲーム画面
	//============================================================
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/GAUGE/icon.png",//誘惑ゲージ
		&m_pTexture[Gage003]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/GAUGE/Gage.png",//誘惑ゲージ
		&m_pTexture[Gage001]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/GAUGE/Gage002.png",//ゲージ
		&m_pTexture[Gage002]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/Naifu000.png",//剣
		&m_pTexture[Naifu000]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/Hammer000.png",//ハンマー
		&m_pTexture[Hammer000]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/000.png",//ハンマー
		&m_pTexture[a000]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/Tutorial000.png",//チュートリアル画面
		&m_pTexture[Operation01]);



}

//=============================================================================
// 終了
//=============================================================================
void CTexture::Uniinit(void)
{
	for (int nCntTexture = 0; nCntTexture < Max; nCntTexture++)
	{
		//テクスチャの破棄
		if (m_pTexture[nCntTexture] != NULL)
		{
			m_pTexture[nCntTexture]->Release();
			m_pTexture[nCntTexture] = NULL;
		}
	}
}