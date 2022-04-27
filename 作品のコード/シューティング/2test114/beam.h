//=============================================================================
//
// 光線の処理 [beam.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _BEAM_H_
#define _BEAM_H_

#include"bullet.h"

//*****************************************************************************
// 光線のクラス
//*****************************************************************************
class CBeam : public CBullet
{
public:																			// 誰でもアクセス可能
	CBeam(int nPriority = PRIORITY_BULLET);																	// コンストラクタ
	~CBeam();																	// デストラクタ
																				// メンバ関数
	static CBeam *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size);	// 弾の生成
	static HRESULT Load(void);													// テクスチャの読み込み
	static void Unload(void);													// テクスチャの破棄
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size);			// ビームの初期化関数
	void Uninit(void);															// ビームの終了関数
	void Update(void);															// ビームの更新関数
	void Draw(void);															// ビームの描画関数

private:																		// 自分だけがアクセス可能	
	static LPDIRECT3DTEXTURE9 m_pTexture;										// 共有するテスクチャのポインタ
	D3DXVECTOR3 m_Pos;
	D3DXVECTOR3 m_Move;															// 弾の移動量
	D3DXVECTOR2 m_Size;
	int m_Timer;
};

#endif