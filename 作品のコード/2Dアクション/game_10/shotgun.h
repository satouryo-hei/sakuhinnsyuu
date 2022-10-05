//=============================================================================
//
// 弾の処理 [bullet.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _SHOTGUN_H_
#define _SHOTGUN_H_

#include"scene2D.h"

#define CIRCLE_HALF (float((rand() % 314) / 100.0f)/3- float((rand() % 314) / 100.0f))/3 //円の3分の1のマクロ

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CBullet;
//*****************************************************************************
// 弾のクラス
//*****************************************************************************
class CShotgun : public CScene2D
{
public:																			// 誰でもアクセス可能
	CShotgun(int nPriority = PRIORITY_SECOND);									// コンストラクタ
	~CShotgun();																	// デストラクタ
																				// メンバ関数
	static CShotgun *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 Size, int nAttack);	// 弾の生成
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);							// 弾の初期化関数
	void Uninit(void);															// 弾の終了関数
	void Update(void);															// 弾の更新関数
	void Draw(void);															// 弾の描画関数
	static bool GetUse(void) { return m_bUse; }
	static void SetUse(bool bUse) { m_bUse = bUse; }

private:																		// 自分だけがアクセス可能		
	static bool m_bUse;															// 使っているかどうか
	static CBullet * m_pBullet[3];													// 弾のポインター	
	D3DXVECTOR3 m_Pos;															// 弾の現在地
	D3DXVECTOR3 m_Move;															// 弾の移動量
	D3DXVECTOR2 m_Size;															// 弾の大きさ	
	int m_nLife;																// 弾の体力
	int m_nAttack;																// 弾の攻撃力
};
#endif