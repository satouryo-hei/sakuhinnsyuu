//=============================================================================
//
// 弾の処理 [bullet.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include"scene2D.h"

//*****************************************************************************
// 弾のクラス
//*****************************************************************************
class CBullet : public CScene2D
{
public:																									// 誰でもアクセス可能
	CBullet(int nPriority = PRIORITY_BULLET);															// コンストラクタ
	~CBullet();																							// デストラクタ
	// メンバ関数
	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move,D3DXVECTOR2 Size,CScene::OBJTYPE ObjType);	// 弾の生成
	static HRESULT Load(void);																			// テクスチャの読み込み
	static void Unload(void);																			// テクスチャの破棄
	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size);									// 弾の初期化関数
	virtual void Uninit(void);																					// 弾の終了関数
	void Update(void);																					// 弾の更新関数
	virtual void Draw(void);																					// 弾の描画関数


private:																								// 自分だけがアクセス可能	
	static LPDIRECT3DTEXTURE9 m_pTexture;																// 共有するテスクチャのポインタ
	D3DXVECTOR3 m_Move;																					// 弾の移動量
	D3DXVECTOR2 m_Size;																					// 弾の大きさ
	const float m_fSpeedMax;																			// すばやさの最大値
	int m_nLife;																						// 弾の寿命
	int m_nPriority;
	static CScene::OBJTYPE m_ObjType;
};
#endif
