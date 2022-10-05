//=============================================================================
//
// 弾の破裂の処理 [rupture.h]
// Author : 佐藤瞭平
//
//=============================================================================
#ifndef _RUPTURE_H_
#define _RUPTURE_H_

#include"Scene.h"

#define MAX_BULLET (8)

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CBullet;
//*****************************************************************************
// 弾の破裂のクラス
//*****************************************************************************
class CRupture : public CScene
{
public:																		// 誰でもアクセス可能
	typedef enum
	{
		RUPTURE_TYPE_SCOND = 0,
		RUPTURE_TYPE_FOURTH,
		RUPTURE_TYPE_SIXTH,
		RUPTURE_TYPE_EIGHTH,
		RUPTURE_TYPE_LIMIT			//種類の最大数
	} RUPTURE_TYPE;

	CRupture(int Priority = PRIORITY_NOMAL);																// コンストラクタ
	~CRupture();																// デストラクタ
																			// メンバ関数
	static CRupture *Create(D3DXVECTOR3 pos, D3DXVECTOR2 Size, int nNum);	// 弾の破裂の生成	
	HRESULT Init(D3DXVECTOR3 pos);											// 弾の破裂の初期化関数
	void Uninit(void);														// 弾の破裂の終了関数
	void Update(void);														// 弾の破裂の更新関数
	void Draw(void);														// 弾の破裂の描画関数	
	void SetRupture(int Type);												// 弾の破裂の設定関数

private:																	// 自分だけがアクセス可能
	typedef enum
	{
		BULLET_NUM_ZERO = 0,
		BULLET_NUM_FIRST,
		BULLET_NUM_SECOND,
		BULLET_NUM_THIRD,
		BULLET_NUM_FOURTH,
		BULLET_NUM_FIFTH,
		BULLET_NUM_SIXTH,
		BULLET_NUM_SEVEBNTH,
		BULLET_NUM_EIGHTH,
		BULLET_NUM_LIMIT			//種類の最大数
	} BULLET_NUM;


	static CBullet* m_pBullet[8];
	D3DXVECTOR3 m_Pos;
	D3DXVECTOR2 m_Size;
};
#endif