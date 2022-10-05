//=============================================================================
//
// 弾の処理 [bullet_circle.h]
// Author : 小笠原彪我
//
//=============================================================================
#ifndef _BULLET_CIRCLE_H_
#define _BULLET_CIRCLE_H_

#include"scene2D.h"

//*****************************************************************************
// 弾のクラス
//*****************************************************************************
class CBulletCircle : public CScene2D
{
public:																			// 誰でもアクセス可能
	CBulletCircle(int nPriority = PRIORITY_SECOND);									// コンストラクタ
	~CBulletCircle();																	// デストラクタ
	// メンバ関数
	static CBulletCircle *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move,D3DXVECTOR2 Size, float fAngle, bool bEffect);	// 弾の生成
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 Size);							// 弾の初期化関数
	void Uninit(void);															// 弾の終了関数
	void Update(void);															// 弾の更新関数
	void Draw(void);															// 弾の描画関数
	bool GetUse(void) { return m_bUse; }
	void SetUse(bool bUse) { m_bUse = bUse; }
	//void EnemyColision();
	D3DXVECTOR3 GetPosOld() { return m_PosOld; }	

private:																		// 自分だけがアクセス可能	
	bool EnemyCollision(void);

	bool m_bUse;															// 使っているかどうか
	bool m_bEffect;																// エフェクトを使うかどうか
	D3DXVECTOR3 m_Pos;															// 弾の現在地
	D3DXVECTOR3 m_PosOld;															// 弾の現在地
	D3DXVECTOR3 m_Move;															// 弾の移動量
	D3DXVECTOR2 m_Size;															// 弾の大きさ		
	const D3DXVECTOR2 m_AddSize;
	const D3DXCOLOR m_AddColor;	
	float m_fAngle;																// 弾の発射角度
};
#endif
