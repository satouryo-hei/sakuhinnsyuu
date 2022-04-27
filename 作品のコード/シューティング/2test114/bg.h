//=============================================================================
//
// 背景の処理 [bg.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _BG_H_
#define _BG_H_

#include"scene.h"
class CScene2D; //前方宣言
class CManager;
//*****************************************************************************
// 背景のクラス
//*****************************************************************************
class CBg : public CScene
{
public:																				// 誰でもアクセス可能

	//背景の種類
	typedef enum
	{
		TEX_TYP_TITLE = 0,
		TEX_TYP_GAME,
		TEX_TYP_RESULT,
		TEX_TYP_MAX
	} TEX_TYP;

	CBg(int nPriority);																// コンストラクタ
	~CBg();																			// デストラクタ
																					// メンバ関数
	static CBg *Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size);							// 背景の生成
	static HRESULT Load(void);														// テクスチャの読み込み
	static void Unload(void);														// テクスチャの破棄
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);								// 背景の初期化関数
	void Uninit(void);																// 背景の終了関数
	void Update(void);																// 背景の更新関数
	void Draw(void);																// 背景の描画関数
	float GetBgSpped(void) { return m_fPosTexU[0]; }

private:																			// 自分だけがアクセス可能	
	static LPDIRECT3DTEXTURE9 m_pTexture[TEX_TYP_MAX];								// 共有するテスクチャのポインタ
	CScene2D * m_apScene2D[TEX_TYP_MAX];											// オブジェクトクラスのポインタ
	float m_fPosTexU[TEX_TYP_MAX];													// テクスチャのUの更新
	float m_fPosTexV[TEX_TYP_MAX];													// テクスチャのUの更新

};
#endif