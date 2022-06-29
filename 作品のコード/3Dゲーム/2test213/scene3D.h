//=============================================================================
//
// 3Dポリゴンの処理 [scene3D.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _SCENE3D_H_
#define _SCENE3D_H_

#include"scene.h"

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
public:																					// 誰でもアクセス可能

	CScene3D(PRIORITY Priority = PRIORITY_NOMAL);										// コンストラクタ
	~CScene3D();																		// デストラクタ
	// メンバ関数
	static CScene3D *Creste(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot);		// 3Dオブジェクトの生成
	void BindTextuer(int nTex);															// テクスチャの設定
	HRESULT Init(D3DXVECTOR3 pos);														// 3Dオブジェクトのデフォルト初期化関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot);					// 3Dオブジェクトの初期化関数
	void Uninit(void);																	// 3Dオブジェクトの終了関数
	void Update(void);																	// 3Dオブジェクトの更新関数
	void Draw(void);																	// 3Dオブジェクトの描画関数
	void SetNorVector(D3DXVECTOR3 nor);													// 法線ベクトルを設定関数
	D3DXVECTOR3 GetPosition(void) { return m_pos; }										// posの取得処理
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }									// posを返す処理

private:																				// 自分だけがアクセス可能

	LPDIRECT3DTEXTURE9 m_pTexTure;														// 共有するテスクチャのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;													// 頂点バッファへのポインタ
	D3DXMATRIX m_mtxWorld;																// ワールドマトリックス
	D3DXVECTOR3 m_pos;																	// 3Dオブジェクトの位置
	D3DXVECTOR3 m_Size;																	// 3Dオブジェクトの大きさ
	D3DXVECTOR3 m_rot;																	// 3Dオブジェクトの向き
};
#endif