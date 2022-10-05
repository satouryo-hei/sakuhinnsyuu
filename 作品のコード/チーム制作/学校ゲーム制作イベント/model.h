//=============================================================================
//
// モデルクラス [model.h]
// Author : 小笠原　彪我
//
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "manager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_VTX 8
#define MODEL_TEX 5

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CXload;
//*****************************************************************************
//	モデルクラス
//*****************************************************************************
class CModel
{
public:
	CModel();	// デフォルトコンストラクタ
	~CModel();	// デストラクタ

	HRESULT Init(void);			// 初期化処理
	void Uninit(void);			// 終了処理
	void Update(void);			// 更新処理
	void Draw(void);			// 描画処理

	// 生成処理
	static CModel *Create(const char *pModelFileName);	

	// 取得処理
	D3DXMATRIX GetMtxWorld(void) { return m_mtxWorld; }		// ワールドマトリックス
	D3DXVECTOR3 GetPosition(void) { return m_pos; }			// パーツの位置
	D3DXVECTOR3 GetRotation(void) { return m_rot; }			// パーツの向き
	D3DXVECTOR3 GetSize(void) { return m_size; }			// パーツの大きさ

	// 設定処理
	void SetModelFile(const char *pModelFileName) { m_pModelFileName = pModelFileName; }	// モデルファイル名
	void SetParent(CModel *pModel) { m_pParent = pModel; }	// 親モデルを設定
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }		// パーツの位置
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }		// パーツの向き

private:
	LPDIRECT3DTEXTURE9	m_pTexture[MODEL_TEX];	// テクスチャのポインタ
	LPD3DXMESH			m_pMesh;				// メッシュ（頂点情報）へのポインタ
	LPD3DXBUFFER		m_pBuffMat;				// マテリアル（材質情報）へのポインタ
	DWORD				m_nNumMat;				// マトリックス数
	CModel				*m_pParent;				// 親モデルへのポインタ
	int					m_nIdxParent;			// 親モデルのインデックス
	D3DXMATRIX			m_mtxWorld;				// ワールドマトリックス
	D3DXVECTOR3			m_pos;					// 位置
	D3DXVECTOR3			m_rot;					// 向き
	D3DXVECTOR3			m_size;					// 大きさ
	D3DXVECTOR3			m_vtxMin, m_vtxMax;		// 頂点の最小値、最大値
	const char			*m_pModelFileName;		// モデルファイル名
};
#endif //!_MODEL_H_