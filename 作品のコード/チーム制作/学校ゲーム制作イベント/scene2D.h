//=============================================================================
//
// 2Dポリゴンの処理 [scene2D.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

#include"scene.h"

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
// オブジェクトクラス
//*****************************************************************************
class CScene2D : public CScene
{
public:																						// 誰でもアクセス可能

	CScene2D(PRIORITY Priority = PRIORITY_NOMAL);											// コンストラクタ
	~CScene2D();																			// デストラクタ
	// メンバ関数
	static CScene2D *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, int nTex);					// ポリゴンの生成
	void Bindtexture(int nTextuer);															// テクスチャの設定
	HRESULT Init(D3DXVECTOR3 pos);															// ポリゴンの初期化関数
	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 size);								// ポリゴンの初期化関数
	virtual void Uninit(void);																// ポリゴンの終了関数
	virtual void Update(void);																// ポリゴンの更新関数
	virtual void Draw(void);																// ポリゴンの描画関数		
	void SetColor(D3DXCOLOR col);															// テクスチャの色(1.0f)の設定処理
	void SetRgba(int nRed, int nGreen, int nBlue, int nAlpha);								// テクスチャの色(255)の設定処理
	void SetVtxBuffColor(D3DXCOLOR col, int nVtxBuff);										// それぞれの頂点の色(1.0f)の設定処理
	void SetAngle(D3DXVECTOR2 Angle, D3DXVECTOR2 size);										// テクスチャの色(255)の設定処理
	void SetUpdateRollingSize(void);														// 2Dオブジェクトの回転拡大縮小処理
	void SetUpdateSize(int MaxSize, int MinSize);											// 2Dオブジェクトの拡大縮小設定処理
	void SetUpdateRoll(float fSpeed,  bool bAdd);											// 2Dオブジェクトの回転設定処理
	void SetRolling(float fSpeed, float fMin,float fMax);									// 2Dオブジェクトの回転設定処理
	void SetPosSize(D3DXVECTOR3 pos, D3DXVECTOR2 Size);										// 2Dオブジェクトの位置と大きさの設定処理
	void SetVtxBuffPosSize(D3DXVECTOR3 pos, D3DXVECTOR2 Size,int nNum);						// 2Dオブジェクトの位置と大きさの頂点ごとの設定処理
	void SetTexAnime(int nPatternAnim, float fSizeAnimU, float fSizeMinV, float fSizeMaxV);	// 2Dオブジェクトのアニメーション処理
	virtual D3DXVECTOR3 GetPosition(void) { return m_pos; }									// posの取得処理
	virtual void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }								// 現在の位置を返す処理	
	virtual D3DXVECTOR2 GetSize(void) { return m_Size; }									// posの取得処理
	virtual void SetSize(D3DXVECTOR2 size) { m_Size = size; }								// 大きさを返す処理

private:																		// 自分だけがアクセス可能

	LPDIRECT3DTEXTURE9 m_pTexTure;												// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;											// 頂点バッファへのポインタ
	D3DXVECTOR3 m_pos;															// ポリゴンの位置
	D3DXVECTOR3 m_Move;															// ポリゴンの移動量
	D3DXVECTOR2 m_Size;															// ポリゴンの大きさ
	static const int m_nNumVertex;												// ポリゴンの頂点数
	int m_Tex_Typ;																// テクスチャの種類
	float m_fRoll;																// 円周
	float m_fHypot;																// (√半径の2乗＋半径の2乗)の値
	float m_fAngle;																// 回る方向
	bool m_bSizeAdd;															// 加算か減算か
	bool m_bRollAdd;															// 加算か減算か
};
#endif