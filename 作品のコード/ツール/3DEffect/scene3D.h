//=============================================================================
//
// ポリゴンの処理 [scene3D.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _SCENE3D_H_
#define _SCENE3D_H_

#include"scene.h"
#include"texture.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)		//頂点フォーマット3D

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		//頂点座標
	D3DXVECTOR3 nor;		//法線ベクトル
	D3DCOLOR col;			//頂点カラー
	D3DXVECTOR2 tex;		//テクスチャ座標
} VERTEX_3D;

//*****************************************************************************
// 3Dオブジェクトクラス
//*****************************************************************************
class CScene3D : public CScene
{
public:															// 誰でもアクセス可能

	CScene3D(PRIORITY Priority = PRIORITY_NOMAL);				// コンストラクタ
	~CScene3D();												// デストラクタ
																// メンバ関数
	void BindTextuer(CTexture::Tex type);						// テクスチャの設定
	static CScene3D *Creste(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// ポリゴンの生成
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);			// ポリゴンの初期化関数
	void Uninit(void);											// ポリゴンの終了関数
	void Update(void);											// ポリゴンの更新関数
	void Draw(void);											// ポリゴンの描画関数
	D3DXVECTOR3 GetPosition(void) { return m_pos; }				// posの取得処理
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }			// posを返す処理

private:														// 自分だけがアクセス可能

	LPDIRECT3DTEXTURE9 m_pTexTure;								// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVlxBuff;							// 頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;							// インデックスへのポインタ
	D3DXMATRIX m_mtxWorld;										// ワールドマトリックス
	D3DXVECTOR3 m_pos;											// ポリゴンの位置
	D3DXVECTOR3 m_Size;											// ポリゴンの大きさ
	D3DXVECTOR3 m_rot;											// ポリゴンの向き
};
#endif