//=============================================================================
//
// 影の処理 [shadow.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _SHADOW_H_//endifとセット（必ず一番上
#define _SHADOW_H_

#include"scene3D.h"
//*****************************************************************************
// 影のクラス
//*****************************************************************************
class CShadow : public CScene3D
{
public:																			// 誰でもアクセス可能
	CShadow(PRIORITY Priority = PRIORITY_SECOND);								// コンストラクタ
	~CShadow();																	// デストラクタ

	// メンバ関数
	static CShadow *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 Rot);	// 影の生成
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);							// 影の初期化関数
	void Uninit(void);															// 影の終了関数
	void Update(void);															// 影の更新関数
	void Draw(void);															// 影の描画関数
	void SetShodow(D3DXVECTOR3 pos, D3DXVECTOR3 size);							// 影の関数
	void SetPositionShadow(const D3DXVECTOR3 pos) { m_pos = pos; }				// 影の位置の設定関数
	D3DXVECTOR3 GetPositionShadow(void) { return m_pos; }						// 影の位置の取得関数

private:																		// 自分だけがアクセス可能
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;											// 頂点バッファへのポインタ
	D3DXMATRIX m_mtxWorld;														// ワールドマトリックス
	D3DXVECTOR3 m_pos;															// ポリゴン位置
	D3DXVECTOR3 m_size;															// ポリゴン位置
	D3DXVECTOR3 m_rot;															// ポリゴンの向き
	bool m_bUse;																// 使用しているか
};
#endif // _POLYGON_H_//ifndefとセット（必ず一番下