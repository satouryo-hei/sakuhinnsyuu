//=============================================================================
//
// オブジェクト2Dの処理 [scene2D.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

#include"scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define FVF_VERTEX_2D (D3DFVF_XYZRHW |D3DFVF_DIFFUSE | D3DFVF_TEX1)

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;	//頂点座標
	float rhw;			//1.0fで固定
	D3DCOLOR col;		//頂点カラー
	D3DXVECTOR2 tex;	//テクスチャ座標
} VERTEX_2D;

//*****************************************************************************
// オブジェクト2Dクラス
//*****************************************************************************
class CScene2D : public CScene
{
public:																									// 誰でもアクセス可能
	CScene2D();																							// コンストラクタ
	~CScene2D();																						// デストラクタ
	// メンバ関数
	void BindTextuer(int nTex); 																		// テクスチャの設定処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 Size);													// デフォルトポリゴンの初期化関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 Size);									// 動く系のポリゴンの初期化関数(オーバーロード)
	void Uninit(void);																					// オブジェクト2Dの終了関数
	void Update(void);																					// オブジェクト2Dの更新関数
	void Draw(void);																					// オブジェクト2Dの描画関数	
	virtual D3DXVECTOR3 GetPosition(void) { return m_pos; }												// posの取得処理
	virtual void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }											// posを返す処理
	virtual D3DXVECTOR3 GetSize(void) { return m_Size; }												// Sizeの取得処理
	virtual void SetSize(D3DXVECTOR3 size) { m_Size = size; }											// Sizeを返す処理
	void SetColor(D3DXCOLOR col);																		// 色を返す関数
	void CScene2D::SetTexAnime(int nPatternAnim, float fSizeAnimU, float fSizeMinV, float fSizeMaxV);	// テクスチャのアニメーション関数
	void SetTex(float fSizeMin, float fSizeMax);														// テクスチャの設定関数

private:																								// 自分だけがアクセス可能
	// メンバ変数
	LPDIRECT3DTEXTURE9 m_pTexTure;																		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVlxBuff;																	// 頂点バッファへのポインタ
	D3DXVECTOR3 m_pos;																					// オブジェクト2Dの位置
	D3DXVECTOR3 m_Move;																					// オブジェクト2Dの移動量
	D3DXVECTOR3 m_Size;																					// オブジェクト2Dのサイズ
};
#endif