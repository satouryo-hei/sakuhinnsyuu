//=============================================================================
//
// 汎用型のモデル処理 [model.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _MODEL_H_//endifとセット（必ず一番上
#define _MODEL_H_

#include"main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_MODEL_TEX (128)//モデルのテクスチャの最大数

//*****************************************************************************
// 汎用型のモデルクラス
//*****************************************************************************
class CModel 
{
public:																						// 誰でもアクセス可能
	CModel();																				// コンストラクタ
	~CModel();																				// デストラクタ
																							// メンバ関数
	static CModel *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *pModelFileName);	// モデルの生成
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot,const char *pModelFileName);				// モデルの初期化関数
	void Uninit(void);																		// モデルの終了関数
	void Update(void);																		// モデルの更新関数
	void Draw(void);																		// モデルの描画関数

	void SetUse(bool bUse) { m_bUse = bUse; }												// 使っているかどうか
	D3DXMATRIX GetMtx(void) { return m_mtxWorld; }											// ワールドマトリックスの取得処理
	void SetMtx(const D3DXMATRIX &mtxworld) {m_mtxWorld = mtxworld; }						// ワールドマトリックスの設定処理
	void SetParent(CModel *pParent) { m_pParent = pParent; }								// 親のモデルを代入
	void SetPos(D3DXVECTOR3 pos) { m_Pos = pos; }
	D3DXVECTOR3 GetPos() { return m_Pos; }
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	D3DXVECTOR3 GetRot() { return m_rot; }
	void SetSize(D3DXVECTOR3 Size) { m_Size = Size; }
	D3DXVECTOR3 GetSize() { return m_Size; }
	void ReleaseModel(void);

private:																					// 自分だけがアクセス可能
	LPDIRECT3DTEXTURE9 m_pTexture[MAX_MODEL_TEX];											// テクスチャのポインターの生成
	D3DXMATRIX m_mtxWorld;																	// ワールドマトリックス
	LPD3DXMESH m_pMesh;																		// メッシュ（頂点情報）へのポインタ
	LPD3DXBUFFER m_pBuffMat;																// マテリアル（材質情報）へのポインタ
	D3DXVECTOR3 m_vtxMin, m_vtxMax;															// モデルの最小値、最大値
	DWORD m_nNumMat;																		// マテリアルの数
	D3DXVECTOR3 m_Pos;																		// 現在の位置
	D3DXVECTOR3 m_Size;																		// 現在の大きさ
	D3DXVECTOR3 m_rot;																		// 現在の向き
	D3DXVECTOR3 m_rotOld;																	// 前回の向き
	D3DXVECTOR3 m_Vtx[10];																	// 各モデルの頂点情報の格納変数
	CModel *m_pParent;																		// 親のモデル
	bool m_bUse;																			// 使っているかどうか
};

#endif // _POLYGON_H_//ifndefとセット（必ず一番下