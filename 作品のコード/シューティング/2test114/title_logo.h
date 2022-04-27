//=============================================================================
//
// タイトルロゴの処理 [title_logo.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _TITLE_LOGO_H_
#define _TITLE_LOGO_H_

#include"scene.h"
class CScene2D; //前方宣言
class CManager;
//*****************************************************************************
// タイトルロゴのクラス
//*****************************************************************************
class CTitle_Logo : public CScene
{
public:																				// 誰でもアクセス可能
	CTitle_Logo(int nPriority);																// コンストラクタ
	~CTitle_Logo();																			// デストラクタ
																					// メンバ関数
	static CTitle_Logo *Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size);							// タイトルロゴの生成
	static HRESULT Load(void);														// テクスチャの読み込み
	static void Unload(void);														// テクスチャの破棄
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);								// タイトルロゴの初期化関数
	void Uninit(void);																// タイトルロゴの終了関数
	void Update(void);																// タイトルロゴの更新関数
	void Draw(void);																// タイトルロゴの描画関数

private:																			// 自分だけがアクセス可能	
	static LPDIRECT3DTEXTURE9 m_pTexture;								// 共有するテスクチャのポインタ
	CScene2D * m_apScene2D;											// オブジェクトクラスのポインタ
	D3DXVECTOR3 m_pos;																// ポリゴンの位置
	D3DXVECTOR3 m_move;																// ポリゴンの移動量
	D3DXVECTOR2 m_Size;																// ポリゴンの大きさ
};
#endif