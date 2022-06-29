//=============================================================================
//
// アイテム処理 [item.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _BOM_H_
#define _BOM_H_

#include "model_single.h"
#include"texture.h"

//*****************************************************************************
// アイテムクラス
//*****************************************************************************
class CBom : public CModel_Single
{
public:
	CBom(PRIORITY nPriority = PRIORITY_ITEM);					// コンストラクタ
	~CBom();														// デストラクタ
	static CBom *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char*Filedata);	// ポリゴンの生成		
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char * Filedata);			// 初期化関数
	void Uninit();																	// 終了関数
	void Update();																	// 更新関数
	void Draw();																	// 描画関数

private:
	LPDIRECT3DTEXTURE9	m_pTexture = NULL;					// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;				// 頂点バッファへのポインタ
	D3DXMATRIX m_mtxWorld;									// ワールドマトリックス	
	D3DXMATRIX m_mtxView;									// ビューマトリックス
	D3DXVECTOR3 m_pos;										// 位置
	D3DXVECTOR3 m_rot;										// 向き
	D3DXVECTOR3 m_size;										// 大きさ
	int m_nLife;											// 体力
	float m_fRadius;
	bool m_bUse;
};
#endif // !_BILLBOARD_H_