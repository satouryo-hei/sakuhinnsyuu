//=============================================================================
//
// 壁の処理 [wall.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _WALL_H_//endifとセット（必ず一番上
#define _WALL_H_

#include"scene3D.h"
//*****************************************************************************
// 壁のクラス
//*****************************************************************************
class CWall : public CScene3D
{
public:																			// 誰でもアクセス可能
	CWall(PRIORITY Priority = PRIORITY_NOMAL);									// コンストラクタ
	~CWall();																	// デストラクタ
																				// メンバ関数
	static CWall *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 Rot);	// 壁の生成
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);							// 壁の初期化関数
	void Uninit(void);															// 壁の終了関数
	void Update(void);															// 壁の更新関数
	void Draw(void);															// 壁の描画関数
	void SetPositionWall(const D3DXVECTOR3 pos) { m_pos = pos; }				// 壁の位置の設定関数
	D3DXVECTOR3 GetPositionShadow(void) { return m_pos; }						// 壁の位置の取得関数

private:																		// 自分だけがアクセス可能
	D3DXVECTOR3 m_pos;															// ポリゴン位置
	D3DXVECTOR3 m_size;															// ポリゴン位置
	D3DXVECTOR3 m_rot;															// ポリゴンの向き
};
#endif // _POLYGON_H_//ifndefとセット（必ず一番下