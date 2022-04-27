//=============================================================================
//
// ポリゴンの処理 [scene.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

#include"scene.h"
#include"texture.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define FVF_VERTEX_2D (D3DFVF_XYZRHW |D3DFVF_DIFFUSE | D3DFVF_TEX1)		//頂点フォーマット2D

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;					//頂点座標
	float rhw;							//1.0fで固定
	D3DCOLOR col;						//頂点カラー
	D3DXVECTOR2 tex;					//テクスチャ座標
} VERTEX_2D;

//*****************************************************************************
// 2Dオブジェクトクラス
//*****************************************************************************
class CScene2D : public CScene
{
public:															// 誰でもアクセス可能

	CScene2D(PRIORITY Priority = PRIORITY_NOMAL);				// コンストラクタ
	~CScene2D();												// デストラクタ
	// メンバ関数
	void BindTextuer(CTexture::Tex type);						// テクスチャの設定
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);			// ポリゴンの初期化関数
	void Uninit(void);											// ポリゴンの終了関数
	void Update(void);											// ポリゴンの更新関数
	void Draw(void);											// ポリゴンの描画関数
	void SetColor(D3DXCOLOR col);								// テクスチャの色(1.0f)の設定処理
	void SetColor(int nRad, int nGreen, int nBlue, int nAlpha);	// テクスチャの色(255)の設定処理
	void SetUpdateRollingSize(void);
	void SetUpdateSize(void);
	void SetUpdateRoll(void);
	void SetUpdatePosSize(D3DXVECTOR3 pos, D3DXVECTOR3 Size);
	D3DXVECTOR3 GetPosition(void) { return m_pos; }				// posの取得処理
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }			// posを返す処理

private:														// 自分だけがアクセス可能
																   
	LPDIRECT3DTEXTURE9 m_pTexTure;								// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVlxBuff;							// 頂点バッファへのポインタ
	D3DXVECTOR3 m_pos;											// ポリゴンの位置
	D3DXVECTOR3 m_Size;											// ポリゴンの大きさ
	int m_Tex_Typ;												// テクスチャの種類
	float m_fRoll;												// 円周
	float m_fHypot;												// (√半径の2乗＋半径の2乗)の値
	float m_fAngle;												// 回る方向
	bool m_bAdd;												// 加算か減算か
};
#endif