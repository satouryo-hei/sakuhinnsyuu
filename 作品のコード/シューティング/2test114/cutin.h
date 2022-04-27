//=============================================================================
//
// カットインの処理 [cutin.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _CUTIN_H_//endifとセット（必ず一番上
#define _CUTIN_H_

#include "scene.h"
#include"manager.h"

class CScene2D;

//*****************************************************************************
// カットインのクラス
//*****************************************************************************
class CCutin : public CScene
{
public:
	//カットインの状態
	typedef enum
	{
		CUTIN_NONE = 0,																//何もしてない状態
		CUTIN_IN,																	//カットイン(入る)
		CUTIN_OUT,																	//カットアウト(出る)
		CUTIN_MAX
	} CUTIN;

	//カットインの状態
	typedef enum
	{
		CUTTYP_BG = 0,
		CUTTYP_ANIME,	
		CUTTYP_MAX
	} CUTTYP;

	CCutin(int nPriority = PRIORITY_FADE);											// コンストラクタ
	~CCutin();																		// デストラクタ

	// メンバ関数
	static CCutin *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size, CUTTYP CutTyp);	// 弾の生成
	static HRESULT Load(void);														// テクスチャの読み込む
	static void Unload(void);														// テクスチャの破棄
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);								// カットインの初期化関数
	void Uninit(void);																// カットインの終了関数　
	void Update(void);																// カットインの更新関数
	void Draw(void);																// カットインの描画関数

private:																			// 自分だけがアクセス可能
	static LPDIRECT3DTEXTURE9 m_pTexture[CUTTYP_MAX];										// 共有するテスクチャのポインタ
	CScene2D * m_apScene2D[CUTTYP_MAX];
	static CUTIN m_Cutin;															// カットインの状態
	static CUTTYP m_Cuttyp;
	static D3DXCOLOR m_col;															// カットインの色
	static D3DXVECTOR3 m_move;
	static bool m_bCutMood;															// カットインしてるかどうか

};
#endif // _FADE_H_//ifndefとセット（必ず一番下