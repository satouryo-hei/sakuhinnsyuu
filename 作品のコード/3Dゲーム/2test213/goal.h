//=============================================================================
//
// ゴール処理 [goal.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _GOAL_H_
#define _GOAL_H_

#include "model_single.h"
#include"texture.h"

//*****************************************************************************
// ゴールクラス
//*****************************************************************************
class CGoal : public CModel_Single
{
public:
	CGoal(PRIORITY nPriority = PRIORITY_ITEM);					// コンストラクタ
	~CGoal();														// デストラクタ
	static CGoal *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char*pFiledata);	// ポリゴンの生成		
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char * pFiledata);			// 初期化関数
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
	float m_fRadius;										// 半径

};
#endif // !_BILLBOARD_H_