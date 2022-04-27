//=============================================================================
//
// プレイヤーの処理 [player.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _PLATER_H_
#define _PLATER_H_

#include"scene2D.h"

//*****************************************************************************
// オブジェクトクラス
//*****************************************************************************
class CPlayer : public CScene2D
{
public:																// 誰でもアクセス可能
	CPlayer(PRIORITY Priority = PRIORITY_NOMAL);														// コンストラクタ
	~CPlayer();														// デストラクタ
	// メンバ関数
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 Size);		// ポリゴンの生成
	static HRESULT Load(void);										// テクスチャの読み込む
	static void Unload(void);										// テクスチャの破棄
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 Size);				// ポリゴンの初期化関数
	void Uninit(void);												// ポリゴンの終了関数
	void Update(void);												// ポリゴンの更新関数
	void Draw(void);												// ポリゴンの描画関数

	void SetUse(bool bUse) { m_bUse = bUse; }

private:															// 自分だけがアクセス可能
	int m_Life;														//体力
	float m_fSpeed;													//すばやさ
	float m_fUpSpeed;												//加速度
	const float m_fSpeedMax;										//すばやさの最大値																	
	static LPDIRECT3DTEXTURE9 m_pTexture;

	bool m_bUse;

};
#endif
