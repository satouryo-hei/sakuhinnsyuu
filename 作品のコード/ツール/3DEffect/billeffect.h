//=============================================================================
//
// エフェクト用のビルボード処理 [billeffect.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _BILLEFFECT_H_
#define _BILLEFFECT_H_

#include "scene.h"
#include"texture.h"

//*****************************************************************************
// エフェクト用のビルボードクラス
//*****************************************************************************
class CBilleffect : public CScene
{
public:
	CBilleffect(PRIORITY nPriority = PRIORITY_NOMAL);					// コンストラクタ
	~CBilleffect();														// デストラクタ
	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);			// 初期化関数
	virtual void Uninit();												// 終了関数
	virtual void Update();												// 更新関数
	virtual void Draw();												// 描画関数
	void BindTextuer(CTexture::Tex type);								// テクスチャの設定
	void Setposition(D3DXVECTOR3 pos, D3DXVECTOR3 Size);				// 頂点情報設定
	void SetColor(D3DXCOLOR col);										// 色(1.0f)の設定処理
	void SetColor(int nRad, int nGreen, int nBlue, int nAlpha);			// 色(255)の設定処理

private:
	LPDIRECT3DTEXTURE9	m_pTexture = NULL;					// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;				// 頂点バッファへのポインタ
	D3DXMATRIX m_mtxWorld;									// ワールドマトリックス	
	D3DXMATRIX m_mtxView;									// ビューマトリックス
	D3DXVECTOR3 m_pos;										// 位置
	D3DXVECTOR3 m_size;										// 大きさ
	D3DXCOLOR m_col;										// 色
	int m_nRad;												// 赤
	int m_nGreen;											// 緑
	int m_nBlue;											// 青
	int m_nAlpha;											// 透明度

};
#endif // !_BILLBOARD_H_