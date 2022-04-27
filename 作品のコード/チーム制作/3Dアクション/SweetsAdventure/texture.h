//=============================================================================
//
// テクスチャ処理 [texture.h]
// Author : 羽鳥太一
//
//=============================================================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CTexture
{
public:
	CTexture();	// デフォルトコンストラクタ
	~CTexture();// デフォルトデストラクタ
	typedef enum
	{
		None = -1,		// テクスチャ無し
		Text,			// 仮テクスチャ
		TIME,			// タイムナンバー
		FADE,			
		HAMMERTEX,		//HAMMERの画像
		NAIHUTEX,		//ナイフの画像
		FREAM,			//枠
		WEAPONSELECT,	//武器を選択するカーソル
		LB,
		RB,
		GOAL,
		SEA000,			//海
		SEA001,			//海
		SHADOW,			//影
		FIELD,			//床
		SKY,			//空
		Title,			//タイトル背景
		GameOver,		//ゲームオーバー背景
		Titlelogo,		//タイトルロゴ
		GameStart,		//ゲームスタート
		Gameover000,	//ゲームオーバーロゴ
		GameClear000,	//ゲームクリアロゴ
		GameClear001,	//ゲームクリアロゴ
		Cursol,			//カーソル
		Retry,			//リトライ
		Texture001,		//タイトルに戻る
		GameBack,		//ゲームに戻る
		a000,			//ナイフ
		Gage003,		//誘惑ゲージアイコン
		Gage001,		//誘惑ゲージ
		Gage002,		//ゲージ
		Hammer000,		//ハンマー
		Naifu000,		//ナイフ
		Operation,		//チュートリアル
		Operation01,
		Ranking000,		//ランキング
		Effect,			//エフェクト
		Max,			// テクスチャの最大数
	} Type;

	void Init(void);	// テクスチャの生成
	LPDIRECT3DTEXTURE9 GetTexture(Type Type) { return m_pTexture[Type]; }	// テクスチャの割り当て(テクスチャの種類) { return 選んだテクスチャを返す }
	void Uniinit(void);	// 終了

private:
	LPDIRECT3DTEXTURE9	m_pTexture[Max];	//テクスチャ
};

#endif