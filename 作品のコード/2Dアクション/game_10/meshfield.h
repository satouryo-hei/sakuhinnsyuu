//=============================================================================
//
// メッシュフィールドの処理 [meshfield.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _MESHFIELD_H_//endifとセット（必ず一番上
#define _MESHFIELD_H_

#include"scene.h"

//*****************************************************************************
// メッシュフィールドクラス
//*****************************************************************************
class CMeshField : public CScene
{
public:																// 誰でもアクセス可能

	CMeshField(PRIORITY Priority = PRIORITY_NOMAL);					// コンストラクタ
	~CMeshField();													// デストラクタ
	// メンバ関数
	static CMeshField *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// メッシュフィールドの生成	
	HRESULT Init(D3DXVECTOR3 pos);									// メッシュフィールドのデフォルト初期化関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);				// メッシュフィールドの初期化関数
	void Uninit(void);												// メッシュフィールドの終了関数
	void Update(void);												// メッシュフィールドの更新関数
	void Draw(void);												// メッシュフィールドの描画関数
	void BindTextuer(int nTextuer);

private:															// 自分だけがアクセス可能

	static LPDIRECT3DTEXTURE9 m_pTexTure;									// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;								// 頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;								// インデックスへのポインタ
	D3DXMATRIX m_mtxWorld;											// ワールドマトリックス
	D3DXVECTOR3 m_pos;												// メッシュフィールドの位置
	D3DXVECTOR3 m_Size;												// メッシュフィールドの大きさ
	D3DXVECTOR3 m_rot;												// メッシュフィールドの向き

};
#endif