//=============================================================================
//
// ポリゴンの処理 [scene2D.h]
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
// ポリゴンクラス
//*****************************************************************************
class CScene2D : public CScene
{
public:																						// 誰でもアクセス可能
	CScene2D(int nPriority = 3);															// コンストラクタ
	~CScene2D();																			// デストラクタ
	// メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);										// デフォルトポリゴンの初期化関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move,D3DXVECTOR2 Size);						// 動く系のポリゴンの初期化関数(オーバーロード)
	void Uninit(void);																		// ポリゴンの終了関数
	void Update(void);																		// ポリゴンの更新関数
	void Draw(void);																		// ポリゴンの描画関数	
	virtual D3DXVECTOR3 GetPosition(void) { return m_pos; }									// posの取得処理
	virtual void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }								// posを返す処理
	virtual D3DXVECTOR2 GetSize(void) { return m_Size; }									// posの取得処理
	virtual void SetSize(D3DXVECTOR2 size) { m_Size = size; }								// posを返す処理
	void BindTextuer(LPDIRECT3DTEXTURE9 pTexTure) { m_pTexTure = pTexTure;}					// テクスチャのポインタを返す処理
	void SetUpdatePos(void);																// 拡大縮小と回転の更新処理
	void SetUpdateMovePos(D3DXVECTOR3 pos,D3DXVECTOR3 move, D3DXVECTOR2 Size);				// 動くポリゴンの更新処理
	void SetUpdateRoll(void);																// ポリゴンの回転処理
	void SetUpdateScale(int nMAXSize, int nMINSize);										// ポリゴンのサイズ変更処理
	void SetTexAnime(int nPatternAnim,float fSizeAnim);										// アニメーションのテクスチャ配置処理
	void SetTexAnime(int nPatternAnim, float fSizeAnimU, float fSizeMinV,float fSizeMaxV);	// アニメーションのテクスチャ配置処理
	void SetTex(float fPosTexU ,float fPosTexV);											// 動くテクスチャの配置処理
	void SetColor(D3DXCOLOR col);															// テクスチャの色(1.0f)の設定処理
	void SetColor(int nRad, int nGreen, int nBlue, int nAlpha);								// テクスチャの色(255)の設定処理

private:																	// 自分だけがアクセス可能																			   
	LPDIRECT3DTEXTURE9 m_pTexTure;											// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVlxBuff;										// 頂点バッファへのポインタ
	D3DXVECTOR3 m_pos;														// ポリゴンの位置
	D3DXVECTOR3 m_Move;														// ポリゴンの移動量
	D3DXVECTOR2 m_Size;														// ポリゴンのサイズ
	int m_Typ;																// 種類
	float m_fRoll;															// 円周
	float m_fHypot;															// 斜辺((√半径の2乗＋半径の2乗)の値)
	float m_fAngle;															// 回る方向
	bool m_bAdd;															// 加算か減算か

};
#endif