//=============================================================================
//
// メッシュの空の処理 [meshsky.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _MESHSKY_H_//endifとセット（必ず一番上
#define _MESHSKY_H_

#include"scene.h"

//*****************************************************************************
// メッシュの空クラス
//*****************************************************************************
class CMeshSky : public CScene
{
public:																									// 誰でもアクセス可能

	CMeshSky(PRIORITY Priority = PRIORITY_NOMAL);														// コンストラクタ
	~CMeshSky();																						// デストラクタ
																										// メンバ関数
	static CMeshSky *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, int meshX, int meshY);	// メッシュの空の生成	
	HRESULT Init(D3DXVECTOR3 pos);																		// メッシュの空のデフォルト初期化関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, int meshX, int meshY);								// メッシュの空の初期化関数
	void Uninit(void);																					// メッシュの空の終了関数
	void Update(void);																					// メッシュの空の更新関数
	void Draw(void);																					// メッシュの空の描画関数
	void BindTextuer(int nTextuer);

private:																								// 自分だけがアクセス可能

	static LPDIRECT3DTEXTURE9 m_pTexTure;																		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;																	// 頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;																	// インデックスへのポインタ
	D3DXMATRIX m_mtxWorld;																				// ワールドマトリックス
	D3DXVECTOR3 m_pos;																					// メッシュの空の位置
	D3DXVECTOR3 m_Size;																					// メッシュの空の大きさ
	D3DXVECTOR3 m_rot;																					// メッシュの空の向き
	int m_nMeshX;																						// メッシュのX
	int m_nMeshY;																						// メッシュのY
};																										
#endif