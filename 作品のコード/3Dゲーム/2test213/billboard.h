//=============================================================================
//
// ビルボード処理 [billboard.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "scene.h"
#include"texture.h"

//*****************************************************************************
// ビルボードクラス
//*****************************************************************************
class CBillboard : public CScene
{
public:
	CBillboard(PRIORITY nPriority = PRIORITY_BILLBOARD);									// コンストラクタ
	~CBillboard();																			// デストラクタ
	static CBillboard *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size);							// ポリゴンの生成	
	HRESULT Init(D3DXVECTOR3 pos);															// デフォルト初期化関数
	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 size);								// 初期化関数
	virtual void Uninit();																	// 終了関数
	virtual void Update();																	// 更新関数
	virtual void Draw();																	// 描画関数
	void BindTextuer(int type);																// テクスチャの設定
	void SetPosSize(D3DXVECTOR3 pos, D3DXVECTOR2 size);										// 頂点情報設定
	void SetColor(D3DXCOLOR col);															// 色(1.0f)の設定処理
	void SetColor(int nRad, int nGreen, int nBlue, int nAlpha);								// 色(255)の設定処理
	void SetTexAnime(int nPatternAnim, float fSizeAnimU, float fSizeMinV, float fSizeMaxV);	// テクスチャのアニメーション設定処理
	D3DXVECTOR3 GetPos() { return m_pos; }
	D3DXVECTOR2 GetSize(){ return m_size; }
protected:																				// 自分と派生系のみアクセス可能

private:
	LPDIRECT3DTEXTURE9	m_pTexture = NULL;					// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;				// 頂点バッファへのポインタ
	D3DXMATRIX m_mtxWorld;									// ワールドマトリックス	
	D3DXVECTOR3 m_pos;										// 位置
	D3DXVECTOR2 m_size;										// 大きさ
	D3DXCOLOR m_col;										// 色
	int m_nRad;												// 赤
	int m_nGreen;											// 緑
	int m_nBlue;											// 青
	int m_nAlpha;											// 透明度

};
#endif // !_BILLBOARD_H_