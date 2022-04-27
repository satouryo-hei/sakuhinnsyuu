//=============================================================================
//
// プレイヤーの処理 [player.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _PRESS_NEXT_H_
#define _PRESS_NEXT_H_

#include"scene2D.h"

//*****************************************************************************
// 複数のポリゴンクラス
//*****************************************************************************
class CPress_Next : public CScene2D
{
public:																								// 誰でもアクセス可能
	CPress_Next(int nPriority = PRIORITY_UI);														// コンストラクタ
	~CPress_Next();																					// デストラクタ
	// メンバ関数
	static CPress_Next *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size, float fHeight);	// ポリゴンの生成
	static HRESULT Load(void);																		// テクスチャの読み込む
	static void Unload(void);																		// テクスチャの破棄
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move,D3DXVECTOR2 Size);								// ポリゴンの初期化関数
	void Uninit(void);																				// ポリゴンの終了関数
	void Update(void);																				// ポリゴンの更新関数
	void Draw(void);																				// ポリゴンの描画関数

private:																							// 自分だけがアクセス可能
	static LPDIRECT3DTEXTURE9 m_pTexture;															// 共有するテスクチャのポインタ
	D3DXVECTOR3 m_pos;																				// 位置
	D3DXVECTOR3 m_move;																				// 移動量
	D3DXVECTOR2 m_size;																				// 大きさ
	float m_fHeight;																				// 大きさ
};
#endif