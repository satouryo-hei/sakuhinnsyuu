//=============================================================================
//
// 2Dオブジェクトの処理 [scene2D.h]
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
// 2Dオブジェクトクラス
//*****************************************************************************
class CScene2D : public CScene
{
public:																			// 誰でもアクセス可能

	CScene2D(PRIORITY Priority = PRIORITY_NOMAL);											// コンストラクタ
	~CScene2D();																			// デストラクタ
	// メンバ関数
	static CScene2D *Creste(D3DXVECTOR3 pos, D3DXVECTOR2 size, int nTex);					// ポリゴンの生成
	void BindTextuer(int nTextuer);															// テクスチャの設定
	HRESULT Init(D3DXVECTOR3 pos);															// 2Dオブジェクトの初期化関数
	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 size);								// ポリゴンの初期化関数
	virtual void Uninit(void);																// 2Dオブジェクトの終了関数
	virtual void Update(void);																// 2Dオブジェクトの更新関数
	virtual void Draw(void);																// 2Dオブジェクトの描画関数
	void SetColor(D3DXCOLOR col);															// テクスチャの色(1.0f)の設定処理
	void SetVtxBuffColor(D3DXCOLOR col,int nVtxBuff);										// それぞれの頂点の色(1.0f)の設定処理
	void SetColor(int nRad, int nGreen, int nBlue, int nAlpha);								// テクスチャの色(255)の設定処理
	void SetAngle(D3DXVECTOR2 Angle, D3DXVECTOR2 size);										// テクスチャの色(255)の設定処理
	void SetUpdateRollingSize(void);														// 2Dオブジェクトの回転拡大縮小処理
	void SetUpdateSize(int MaxSize, int MinSize);											// 2Dオブジェクトの拡大縮小設定処理
	void SetUpdateRoll(float fSpeed,bool bAdd);												// 2Dオブジェクトの回転設定処理
	void SetUpdatePosSize(D3DXVECTOR3 pos, D3DXVECTOR2 Size);								// 2Dオブジェクトの位置と大きさ処理
	void SetTexAnime(int nPatternAnim, float fSizeAnimU, float fSizeMinV, float fSizeMaxV);	// 2Dオブジェクトのアニメーション処理
	D3DXVECTOR3 GetPosition(void) { return m_pos; }											// posの取得処理
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }										// posを返す処理
	D3DXVECTOR2 GetSize(void) { return m_Size; }											// Sizeの取得処理
	void SetSize(D3DXVECTOR2 Size) { m_Size = Size; }										// Sizeを返す処理

private:																					// 自分だけがアクセス可能
	LPDIRECT3DTEXTURE9 m_pTexTure;															// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;														// 頂点バッファへのポインタ
	D3DXVECTOR3 m_pos;																		// 2Dオブジェクトの位置
	D3DXVECTOR3 m_Move;																		// 2Dオブジェクトの移動量
	D3DXVECTOR2 m_Size;																		// 2Dオブジェクトの大きさ
	static const int m_nNumVertex;															// 2Dオブジェクトの頂点数
	int m_Tex_Typ;																			// テクスチャの種類
	float m_fRoll;																			// 円周
	float m_fHypot;																			// (√半径の2乗＋半径の2乗)の値
	float m_fAngle;																			// 回る方向
	bool m_bAdd;																			// 加算か減算か
};
#endif