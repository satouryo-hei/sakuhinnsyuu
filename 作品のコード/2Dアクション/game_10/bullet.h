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
public:																			// 誰でもアクセス可能
	CBullet(int nPriority = PRIORITY_SECOND);									// コンストラクタ
	~CBullet();																	// デストラクタ
	// メンバ関数
	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move,D3DXVECTOR2 Size, int nLife, bool bEffect);	// 弾の生成
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);							// 弾の初期化関数
	void Uninit(void);															// 弾の終了関数
	void Update(void);															// 弾の更新関数
	void Draw(void);															// 弾の描画関数
	bool GetUse(void) { return m_bUse; }
	void SetUse(bool bUse) { m_bUse = bUse; }
	void EnemyColision();
	D3DXVECTOR3 GetPosOld() { return m_PosOld; }
	int GetAttack() { return m_nAttack; }

private:																		// 自分だけがアクセス可能		
	bool m_bUse;															// 使っているかどうか
	bool m_bEffect;																// エフェクトを使うかどうか
	D3DXVECTOR3 m_Pos;															// 弾の現在地
	D3DXVECTOR3 m_PosOld;															// 弾の現在地
	D3DXVECTOR3 m_Move;															// 弾の移動量
	D3DXVECTOR2 m_Size;															// 弾の大きさ	
	int m_nLife;																// 弾の体力
	int m_nAttack;																// 弾の攻撃力

};
#endif
